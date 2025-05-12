from openai import OpenAI, OpenAIError
import os
import json
import csv
from typing import Tuple
from convert_ce import inject_counterexample_by_ast, parse_counterexample, extract_nondet_variables_with_type # type: ignore
from threading import Thread
from queue import Queue, Empty
import clang.cindex
clang.cindex.Config.set_library_file("/usr/lib/llvm-14/lib/libclang.so")      #"/usr/lib/llvm-10/lib/libclang.so"
import re
import subprocess
from datetime import datetime

def extract_c_code_block(text: str) -> str:
    """
    Extracts the first C code block (inside ```c ... ```) from a Markdown-style LLM response.
    If not found, returns the original text as fallback.
    """
    match = re.search(r"```c\s*(.*?)```", text, re.DOTALL)
    if match:
        return match.group(1).strip()
    return text.strip()

def call_openai_api(data, model="gpt-3.5-turbo"):
    """
    通过API key，发送请求给OPENAI接口，支持自定义模型和base_url
    非流式响应.为提供的对话消息创建新的回答
    @param data:
    @param model:
    @param base_url:
    @return:
    """
    if type(data) is str:
        messages = [{'role': 'user', 'content': data}]
    else:
        messages = data

    client = OpenAI(
        base_url="https://api.key77qiqi.cn/v1",   # /v1
        api_key=  "sk-PNo1AkLOdnkRX4uvxUmRknC7zKk9h7rfBQMBdNbYqpkrYWn4" # "sk-k4T6wX2wYKzosij54j4KahUl4ByPteb8Sng6EhwhWzBDZLBF" # new_dpseek  
        # api_key = "sk-vSbKzD7p3Cha2xKNB7649706009c4d2b9054604196Cc1e78" # openai
        # sk-PNo1AkLOdnkRX4uvxUmRknC7zKk9h7rfBQMBdNbYqpkrYWn4
        # sk-vSbKzD7p3Cha2xKNB7649706009c4d2b9054604196Cc1e78   
    )
    # print(f"model: {model}")
    completion = client.chat.completions.create(model=model, messages=messages)
    return completion.choices[0].message.content

def generate_svcomp_style_test(prompt_desc, function_header):
    system_prompt = (
        "Given a programming task description and a function signature, generate a C verification harness "
        "in the SV-COMP style. The harness should check whether the student's implementation produces the same result "
        "as a known correct reference implementation named `std`. "
        "You must use __VERIFIER_nondet_*() to generate nondeterministic inputs and assume_abort_if_not() to restrict valid input ranges. "
        "Use assert() to compare the outputs of the student function and `std` on the same inputs. "
        "Include extern declarations for all used __VERIFIER_nondet_* functions (e.g., __VERIFIER_nondet_int, __VERIFIER_nondet_double, etc.), "
        "as well as extern declarations for both the student function and the std function. "
        "Do not define either function. Only include the main() function and the fixed assume_abort_if_not definition. "
        "The definition of assume_abort_if_not must be exactly:\n"
        "void assume_abort_if_not(int cond) {\n"
        "    if (!cond)\n"
        "        abort();\n"
        "}"
    )






    user_prompt = f"""Programming Task Description: {prompt_desc}
Function Signature: {function_header}

Please output the verification harness in C:"""

    messages = [
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": user_prompt}
    ]

    response = call_openai_api(messages, model="deepseek-v3")
    return response




def evaluate_case(problem_desc, test_case_code,std_code):
    system_prompt = (
        "You are an expert in program verification. "
        "The user will provide a programming task description and a C verification harness. "
        "Your task is to determine whether the harness correctly checks whether a student implementation behaves "
        "identically to a standard reference implementation (named `std`) under all valid inputs, "
        "and whether it conforms to the SV-COMP verification standard. "
        "Specifically, ensure that it includes both function declarations (`std` and the original function), "
        "uses __VERIFIER_nondet_*() to generate inputs, assume_abort_if_not() to restrict input range, "
        "and assert() to compare the results of the two implementations. "
        "Please answer **Yes** or **No**, and explain your reasoning."
    )


    user_prompt = f"""The programming task is described as follows:
{problem_desc}

The following is the C verification harness:
{test_case_code}


Please analyze whether this verification harness is correct, complete, and consistent with the problem specification. Answer **Yes** or **No**, and explain your reasoning."""

    messages = [
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": user_prompt}
    ]

    response = call_openai_api(messages, model="deepseek-v3")
    return response

def gen_temp_svcomp(
    prompt_desc: str,
    function_header: str,
    std_code: str,
    output_folder: str,
    max_retries: int = 5
) -> str:
    """
    Generate a verified SV-COMP style verification template, and save it to `template.c` inside the given folder
    if the generated result passes evaluation. Retries generation if the evaluation fails.
    
    Returns the final verified template as a string if successful, or raises an error if all attempts fail.
    """
    last_feedback = ""
    for attempt in range(1, max_retries + 1):
        print(f"⏳ Attempt {attempt} to generate verification template...")

        # Add feedback to prompt if available
        if last_feedback:
            prompt_with_feedback = (
                prompt_desc + "\n\nNote: The previous attempt failed. "
                "Here is the analysis from the verification expert:\n" + last_feedback
            )
        else:
            prompt_with_feedback = prompt_desc

        # Generate and evaluate template
        raw_template = generate_svcomp_style_test(prompt_with_feedback, function_header)
        evaluation_result = evaluate_case(prompt_desc, raw_template,std_code)

        if "**Yes**" in evaluation_result:
            verified_code = extract_c_code_block(raw_template)

            # Save to file
            os.makedirs(output_folder, exist_ok=True)
            template_path = os.path.join(output_folder, "template.c")
            with open(template_path, 'w') as f:
                f.write(verified_code)

            print(f"✅ Template passed verification and saved to {template_path}")
            return verified_code
        else:
            print("❌ Template failed verification.")
            last_feedback = evaluation_result.strip()

    raise RuntimeError("Failed to generate a valid verification template after multiple attempts.")

import sys

def gen_temp(folder_path: str):
    """
    Entry point to read QA.txt and interface.txt from the given folder,
    and generate std.c and template.c in the same folder after evaluation.
    """
    qa_path = os.path.join(folder_path, "QA.txt")
    interface_path = os.path.join(folder_path, "interface.txt")
    std_path = os.path.join(folder_path, "std.c")
    try:
        with open(qa_path, 'r') as f:
            prompt_description = f.read().strip()
    except Exception as e:
        print(f"❌ Failed to read QA.txt: {e}")
        return

    try:
        with open(interface_path, 'r') as f:
            function_header = f.read().strip()
    except Exception as e:
        print(f"❌ Failed to read interface.txt: {e}")
        return
    try:
        with open(std_path, 'r') as f:
            std_code = f.read().strip()
    except Exception as e:
        print(f"❌ Failed to read interface.txt: {e}")
        return

    gen_temp_svcomp(prompt_description, function_header,std_code,folder_path)

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <root_folder>")
        sys.exit(1)

    root_folder = sys.argv[1]

    if not os.path.isdir(root_folder):
        print(f"Error: {root_folder} is not a valid directory.")
        sys.exit(1)

    for entry in os.listdir(root_folder):
        full_path = os.path.join(root_folder, entry)
        if os.path.isdir(full_path) and entry.startswith("task"):
            gen_temp(full_path)
if __name__ == "__main__":
    # if len(sys.argv) != 2:
    #     print("Usage: python script.py <task_folder>")
    # else:
    #     gen_temp(sys.argv[1])
    main()
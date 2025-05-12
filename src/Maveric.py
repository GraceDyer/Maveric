import os
from openai import OpenAI
import pandas as pd
import tempfile
import re
import subprocess
import concurrent.futures
import json

def extract_c_code_block(text: str) -> str:
    """
    Extracts the first C code block (inside ```c ... ```) from a Markdown-style LLM response.
    If not found, returns the original text as fallback.
    """
    match = re.search(r"```c\s*(.*?)```", text, re.DOTALL)
    if match:
        return match.group(1).strip()
    return text.strip()
def inject_counterexample(program: str, counterexample: dict) -> str:
    client = OpenAI(
        base_url="https://api.key77qiqi.cn/v1",
        api_key="sk-PNo1AkLOdnkRX4uvxUmRknC7zKk9h7rfBQMBdNbYqpkrYWn4"
    )

    system_prompt = (
        "You are a C programming assistant.\n"
        "You will receive a C program and a counterexample in JSON format.\n"
        "Your task is to only modify the `main` function by replacing all occurrences of `__VERIFIER_nondet_*()` "
        "with concrete values from the counterexample, without changing any other part of the code.\n"
        "If a counterexample contains an array (e.g., 'budgets': [0, 1, 2]), replace related `__VERIFIER_nondet_*()` "
        "calls in array assignments inside `main` accordingly.\n"
        "Preserve all other functions and structures as-is.\n"
        "Return only the modified C code without explanation."
    )

    user_prompt = f"""[C Program]
```c
{program}
[Counterexample]
{json.dumps(counterexample, ensure_ascii=False)}
```"""

    completion = client.chat.completions.create(
        model="deepseek-v3",
        messages=[
            {"role": "system", "content": system_prompt},
            {"role": "user", "content": user_prompt}
        ],
        temperature=0
    )

    tmp_code = completion.choices[0].message.content.strip()
    modified_code = extract_c_code_block(tmp_code)
    return modified_code


def inject_counterexample_and_check(template_code, std_code, student_code, counterexample) -> bool:
    with tempfile.TemporaryDirectory() as tmpdir:
        combined_code_path = os.path.join(tmpdir, "combined.c")
        
        # 替换 __VERIFIER_nondet_* 赋值语句
        
        
        new_code = inject_counterexample(template_code, counterexample)
        
        # print(new_code)
        combined_code = new_code + "\n\n" + std_code + "\n\n" + student_code
        with open(combined_code_path, "w", encoding="utf-8") as f:
            f.write(combined_code)

        result = subprocess.run(
            ["cbmc", combined_code_path, "--no-built-in-assertions"],
            stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,timeout=10
        )
        # print(result)
        return "VERIFICATION FAILED" in result.stdout

def extract_json_object(text):
    match = re.search(r'\{.*\}', text, re.DOTALL)
    if match:
        return match.group(0)
    return None
# === 调用LLM进行代码评估 ===
def evaluate_with_llm(qa_text, std_code, student_code, template_code) -> dict:
    client = OpenAI(
        base_url="https://api.key77qiqi.cn/v1",
        api_key="sk-PNo1AkLOdnkRX4uvxUmRknC7zKk9h7rfBQMBdNbYqpkrYWn4"
    )

    system_prompt = (
        "You are an expert in programming assignment verification. "
        "You will be given a programming problem description, a reference (correct) solution, a student-submitted solution, "
        "and a verification template used to evaluate correctness. "
        "Your task is to determine whether the student's solution correctly solves the problem **under the verification template**. "
        "If the student's code is correct, respond with JSON:\n"
        "{\"status\": \"**Successful**\"}\n"
        "If the student's code is incorrect, generate a counterexample input that would cause the student's code to fail when combined "
        "with the verification template, and respond with JSON:\n"
        "{\"status\": \"**Failed**\", \"counterexample\": {\"hours\": 20.0}}\n"
        "Do not include any explanation or comment. Your output must strictly follow the specified JSON format only."
    )

    base_prompt = f"""You are given the following programming problem, a reference solution, a student's solution, 
and a verification template used to check the solution's correctness.

[Problem Description]
{qa_text}

[Reference Solution]
{std_code}

[Student's Solution]
{student_code}

[Verification Template]
{template_code}
"""

    retry = 0
    prompt = base_prompt
    while retry < 5:
        completion = client.chat.completions.create(
            model="deepseek-v3",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": prompt}
            ],
            temperature=0
        )
        reply = completion.choices[0].message.content.strip()
        try:
            json_str = extract_json_object(reply)
            if json_str:
                result = json.loads(json_str)

                status = str(result.get("status", "")).strip("* ")

                if "Successful" in status:
                    return {
                        "status": "Successful",
                        "confirmed": False,
                        "counterexample": {},
                        "message": "LLM judged correct",
                        "raw": reply
                    }

                elif "Failed" in status:
                    counterexample = result.get("counterexample", {})
                    if inject_counterexample_and_check(template_code, std_code, student_code, counterexample):
                        return {
                            "status": "Failed",
                            "confirmed": True,
                            "counterexample": counterexample,
                            "message": "Counterexample confirmed",
                            "raw": reply
                        }
                    else:
                        # Retry with note
                        prompt = base_prompt + f"\n\nNote: The following counterexample did not cause failure: {counterexample}"
                        retry += 1
                        continue
                else:
                    return {
                        "status": "Error",
                        "confirmed": False,
                        "counterexample": {},
                        "message": "Unrecognized status field",
                        "raw": reply
                    }

        except json.JSONDecodeError:
            return {
                "status": "Error",
                "confirmed": False,
                "counterexample": {},
                "message": "Invalid JSON format",
                "raw": reply
            }

    # If all retries failed
    return {
        "status": "Timeout",
        "confirmed": False,
        "counterexample": {},
        "message": "No valid counterexample after 5 retries",
        "raw": ""
    }

def evaluate_with_cbmc(template_code, std_code, student_code):
    try:
        with tempfile.TemporaryDirectory() as tmpdir:
            final_code_path = os.path.join(tmpdir, "combined.c")
            with open(final_code_path, "w", encoding="utf-8") as f:
                f.write(template_code + "\n\n")
                f.write(std_code + "\n\n")
                f.write(student_code + "\n")

            result = subprocess.run(
                ["cbmc", final_code_path, "--unwind", "20", "--no-built-in-assertions"],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=60
            )

            if "VERIFICATION SUCCESSFUL" in result.stdout:
                return {
                    "status": "CBMC_Correct",
                    "trace": result.stdout
                }
            else:
                return {
                    "status": "CBMC_Incorrect",
                    "trace": result.stdout
                }

    except subprocess.TimeoutExpired:
        return {
            "status": "CBMC_Timeout",
            "trace": "CBMC execution timed out after 60 seconds."
        }

    except Exception as e:
        return {
            "status": f"CBMC_Error: {str(e)}",
            "trace": ""
        }

import threading
import time
import concurrent.futures
import time
import json
from concurrent.futures import CancelledError

def process_one_solution(task_id, qa_text, template_code, std_code, student_path, solution_index):
    with open(student_path, "r", encoding="utf-8") as f:
        student_code = f.read()

    TIMEOUT = 60
    start_time = time.time()

    result = {
        "Task ID": task_id,
        "Solution Index": solution_index,
        "LLM Status": "Not Started",
        "CBMC Result": "Not Started",
        "Counterexample": "",
        "Confirmed": "",
        "Correctness": True,
        "First Finished": ""
    }

    with concurrent.futures.ThreadPoolExecutor() as executor:
        future_llm = executor.submit(evaluate_with_llm, qa_text, std_code, student_code, template_code)
        future_cbmc = executor.submit(evaluate_with_cbmc, template_code, std_code, student_code)

        llm_result = None
        cbmc_result = None

        while time.time() - start_time < TIMEOUT:
            # === CBMC 返回 ===
            if future_cbmc.done():
                try:
                    cbmc_result = future_cbmc.result()
                    result["CBMC Result"] = cbmc_result.get("status", "Unknown")
                    result["First Finished"] = "CBMC"

                    if result["CBMC Result"] == "CBMC_Correct":
                        result["Correctness"] = True
                        future_llm.cancel()
                        result["LLM Status"] = "Cancelled"
                        return result

                    elif result["CBMC Result"] == "CBMC_Incorrect":
                        result["Correctness"] = False
                        future_llm.cancel()
                        result["LLM Status"] = "Cancelled"
                        return result
                except Exception as e:
                    result["CBMC Result"] = f"CBMC_Error: {str(e)}"

            # === LLM 返回 ===
            if future_llm.done():
                try:
                    llm_result = future_llm.result()
                    result["LLM Status"] = llm_result.get("status", "LLM_Error")

                    if llm_result.get("status") == "Failed":
                        result["Counterexample"] = json.dumps(llm_result.get("counterexample", {}), ensure_ascii=False)
                        result["Confirmed"] = llm_result.get("confirmed", False)

                        if llm_result.get("confirmed", False):
                            result["Correctness"] = False
                            result["First Finished"] = "LLM"
                            future_cbmc.cancel()
                            return result
                        else:
                            result["Correctness"] = True
                            result["First Finished"] = "LLM"

                    elif llm_result.get("status") == "Successful":
                        result["Correctness"] = True
                        result["First Finished"] = "LLM"
                        # 等待 CBMC 完成用于记录
                        try:
                            cbmc_result = future_cbmc.result(timeout=max(0, TIMEOUT - (time.time() - start_time)))
                            result["CBMC Result"] = cbmc_result.get("status", "Unknown")
                        except Exception as e:
                            result["CBMC Result"] = f"CBMC_LateError: {str(e)}"
                        return result

                    else:
                        result["LLM Status"] = f"LLM_Error: {llm_result.get('message', '')}"

                except CancelledError:
                    result["LLM Status"] = "Cancelled"
                except Exception as e:
                    result["LLM Status"] = f"LLM_Error: {str(e)}"

            time.sleep(0.1)

    # === 超时兜底 ===
    if not future_llm.done():
        result["LLM Status"] = "Timeout"
    if not future_cbmc.done():
        result["CBMC Result"] = "Timeout"

    result["First Finished"] = "Timeout"
    result["Correctness"] = True  # ✅ 默认宽松判断
    return result



import sys
import os
import csv

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <data_root_folder>")
        sys.exit(1)

    DATA_ROOT = sys.argv[1]
    OUTPUT_CSV = "evaluation_result.csv"

    header = [
        "Task ID",
        "Solution Index",
        "LLM Status",
        "CBMC Result",
        "Counterexample",
        "Confirmed",
        "Correctness",
        "First Finished"
    ]

    with open(OUTPUT_CSV, 'w', newline='', encoding='utf-8') as f:
        writer = csv.DictWriter(f, fieldnames=header)
        writer.writeheader()

        for task_id in sorted(os.listdir(DATA_ROOT)):
            task_path = os.path.join(DATA_ROOT, task_id)
            if not os.path.isdir(task_path) or not task_id.startswith("task"):
                continue

            print(f"\n📂 Processing task: {task_id}")

            try:
                with open(os.path.join(task_path, "QA.txt"), "r", encoding="utf-8") as f_qa:
                    qa_text = f_qa.read()
                with open(os.path.join(task_path, "std.c"), "r", encoding="utf-8") as f_std:
                    std_code = f_std.read()
                with open(os.path.join(task_path, "template.c"), "r", encoding="utf-8") as f_temp:
                    template_code = f_temp.read()

                student_dir = os.path.join(task_path, "student_code")
                for filename in sorted(os.listdir(student_dir)):
                    if not filename.endswith(".c"):
                        continue

                    print(f"   🧪 Evaluating: {filename}")
                    student_path = os.path.join(student_dir, filename)

                    result = process_one_solution(
                        task_id,
                        qa_text,
                        template_code,
                        std_code,
                        student_path,
                        filename
                    )

                    writer.writerow(result)
                    f.flush()  # 确保立即写入文件

                    print(f"     ✅ Result: {result['Correctness']} (LLM: {result['LLM Status']}, CBMC: {result['CBMC Result']}, First: {result['First Finished']})")

            except Exception as e:
                error_result = {
                    "Task ID": task_id,
                    "Solution Index": "ALL",
                    "LLM Status": "Error",
                    "CBMC Result": "Error",
                    "Counterexample": "",
                    "Confirmed": False,
                    "Correctness": False,
                    "First Finished": "Task Load Failed"
                }
                writer.writerow(error_result)
                f.flush()
                print(f"❌ Failed to process task {task_id}: {e}")

    print(f"\n📄 全部结果已保存至 {OUTPUT_CSV}")

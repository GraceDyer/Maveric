import os
from openai import OpenAI
import pandas as pd
import sys
import csv
# === 配置 ===
DATA_ROOT = sys.argv[1]
OUTPUT_EXCEL = "LLM_result.csv"

# === 调用LLM进行代码评估 ===
def evaluate_solution(llm_prompt: str) -> str:

    client = OpenAI(
            base_url="https://api.key77qiqi.cn/v1",   # /v1
            # api_key=  "sk-PNo1AkLOdnkRX4uvxUmRknC7zKk9h7rfBQMBdNbYqpkrYWn4" # "sk-k4T6wX2wYKzosij54j4KahUl4ByPteb8Sng6EhwhWzBDZLBF" # new_dpseek  
            api_key = "sk-vSbKzD7p3Cha2xKNB7649706009c4d2b9054604196Cc1e78" # gpt-4o
            # sk-PNo1AkLOdnkRX4uvxUmRknC7zKk9h7rfBQMBdNbYqpkrYWn4
            # sk-vSbKzD7p3Cha2xKNB7649706009c4d2b9054604196Cc1e78   
    )
    # print(f"model: {model}")
    completion = client.chat.completions.create(
        model="gpt-4o",  # 你也可以使用其他模型
        messages=[
            {"role": "system", "content": "You are an expert in evaluating the correctness of student code"},
            {"role": "user", "content": llm_prompt}
        ],
        temperature=0
    )
    
    return completion.choices[0].message.content

# === 主流程 ===
results = []

for task_id in os.listdir(DATA_ROOT):
    print("Processing task:", task_id)
    task_path = os.path.join(DATA_ROOT, task_id)
    if not os.path.isdir(task_path):
        continue

    # 读取题目描述和标准答案
    with open(os.path.join(task_path, "QA.txt"), "r", encoding="utf-8") as f:
        qa_text = f.read()
    with open(os.path.join(task_path, "std.c"), "r", encoding="utf-8") as f:
        std_code = f.read()

    # 遍历 student_code 下的所有 solution
    student_dir = os.path.join(task_path, "student_code")
    for filename in sorted(os.listdir(student_dir)):
        print("Processing solution:", filename)
        if not filename.endswith(".c"):
            continue
        student_path = os.path.join(student_dir, filename)
        with open(student_path, "r", encoding="utf-8") as f:
            student_code = f.read()

        # 构造 prompt
        # Construct English prompt
        prompt = f"""You are given a programming problem and a reference solution.
[Problem Description]
{qa_text}

[Reference Solution]
{std_code}

[Student Submission]
{student_code}

Please evaluate whether the student's solution correctly solves the problem.  
Respond with only one of the following two options:
**Correct** or **Incorrect**
"""


        judgment = evaluate_solution(prompt)
        result = {
            "Task ID": task_id,
            "Solution Index": filename,
            "Correctness": "Correct" if "**Correct**" in judgment else "Incorrect",
        }
        results.append(result)

# === 保存为 Excel ===
df = pd.DataFrame(results)
df.to_excel(OUTPUT_EXCEL, index=False)
print(f"结果已保存至 {OUTPUT_EXCEL}")

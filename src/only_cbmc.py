import csv
import os
import sys
import subprocess
def run_cbmc_on_students_with_csv(task_folder: str, csv_writer):
    std_file = os.path.join(task_folder, "std.c")
    template_file = os.path.join(task_folder, "template.c")
    student_folder = os.path.join(task_folder, "student_code")

    if not os.path.isfile(std_file):
        print(f"❌ Missing std.c in {task_folder}")
        return
    if not os.path.isfile(template_file):
        print(f"❌ Missing template.c in {task_folder}")
        return
    if not os.path.isdir(student_folder):
        print(f"❌ Missing student_code folder in {task_folder}")
        return

    for filename in sorted(os.listdir(student_folder)):
        if filename.endswith(".c"):
            student_file = os.path.join(student_folder, filename)
            cmd = [
                "cbmc",
                std_file,
                template_file,
                student_file,
                "--unwind", "20",
                "--no-built-in-assertions"
            ]
            print(f"▶ Running: {' '.join(cmd)}")
            try:
                result = subprocess.run(cmd, capture_output=True, text=True, timeout=10)
                # output_file = os.path.join(task_folder, f"{filename}_cbmc_output.txt")
                # with open(output_file, 'w') as out:
                #     out.write(result.stdout + "\n" + result.stderr)

                status = "VERIFICATION FAILED" if "VERIFICATION FAILED" in result.stdout else "VERIFICATION SUCCESSFUL"
                csv_writer.writerow({"file": student_file, "result": status})
                # print(f"✅ Output written to {output_file} | {status}")

            except subprocess.TimeoutExpired:
                print(f"⏱ Timeout on {filename}")
                csv_writer.writerow({"file": student_file, "result": "TIMEOUT"})

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <root_folder>")
        sys.exit(1)

    root = sys.argv[1]
    if not os.path.isdir(root):
        print(f"❌ Not a valid directory: {root}")
        sys.exit(1)

    csv_output = os.path.join(root, "cbmc_results.csv")

    # If file exists, clear it
    with open(csv_output, 'w', newline='') as csvfile:
        fieldnames = ["file", "result"]
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()

    # Then append per task
    with open(csv_output, 'a', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=["file", "result"])
        for entry in sorted(os.listdir(root)):
            sub_path = os.path.join(root, entry)
            if os.path.isdir(sub_path) and entry.startswith("task"):
                run_cbmc_on_students_with_csv(sub_path, writer)

    print(f"\n📄 Summary CSV written to {csv_output}")

if __name__ == "__main__":
    main()

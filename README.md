
# Maveric: Multi-Agent Verification for Student Code

**Maveric** is a multi-agent framework that integrates large language models (LLMs) with formal verification to assess the semantic correctness of student-submitted programs. It systematically detects errors often missed by traditional test-case-based methods by orchestrating four intelligent agents: template generator, consistency checker, code analyzer, and counterexample validator.

##  Project Structure

```
.
├── benchmarks/        # Evaluation data for 10 real-world programming tasks
│   ├── task1/
│   ├── task2/
│   └── ...            # Each task contains QA.txt, std.c, template.c, student_code/
├── src/               # Source code for different evaluation modes
│   ├── gen_template.py    # Generates SV-COMP-style verification templates
│   ├── Maveric.py         # Full pipeline: LLM + formal verification (recommended)
│   ├── only_cbmc.py       # Baseline: Formal verification only (CBMC)
│   └── only_LLM.py        # Baseline: LLM-only analysis
├── result.xlsx        # Summary of experimental results
└── README.md          # This documentation file
```

## Environment Requirements

   * Python 3.9+
   * `openai` package (for LLM APIs)
   * `clang`, `cbmc`, `pandas`, etc.
   * CBMC installed and accessible from CLI
   * Set your OpenAI-compatible API key in  `src/only_LLm.py`, `src/Maveric.py`, `src/gen_template.py`

## Manner of execution
1. **Generate Verification Templates**

   ```bash
   python src/gen_template.py ../benchmarks
   ```

2. **Run Maveric**
   ```bash
   python src/Maveric.py ../benchmarks
   ```

3. **Run Baselines**

   * CBMC-only:

     ```bash
     python src/only_cbmc.py ../benchmarks
     ```
   * LLM-only:

     ```bash
     python src/only_LLM.py ../benchmarks
     ```



##  Benchmark

Each task in `benchmarks/` contains:

* `QA.txt`: Problem description
* `std.c`: Reference implementation
* `template.c`: Auto-generated verification harness
* `student_code/`: Folder with 10 student solutions

##  Results

The file `result.xlsx` summarizes Maveric’s evaluation outcomes across 100 student submissions from 10 tasks. Metrics include true positives, false negatives, false positives, and timeouts.

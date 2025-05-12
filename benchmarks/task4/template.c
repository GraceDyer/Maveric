extern int __VERIFIER_nondet_int();
extern void abort(void);
extern int sum_fac(int n);
extern int std(int n);  // reference implementation

void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Generate non-deterministic input
    int n = __VERIFIER_nondet_int();
    
    // Restrict input to valid range (n >= 1 to avoid 0! case)
    // Also limit to reasonable values to prevent overflow
    assume_abort_if_not(n >= 1 && n <= 12);  // 13! overflows 32-bit int
    
    // Call both implementations
    int student_result = sum_fac(n);
    int reference_result = std(n);
    
    // Compare results
    assert(student_result == reference_result);
    
    return 0;
}
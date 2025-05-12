extern int f(int n);
extern int std(int n);
extern int __VERIFIER_nondet_int();
void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Use nondeterministic input
    int n = __VERIFIER_nondet_uint();
    
    // Restrict input to reasonable values to prevent overflow in implementations
    // Maximum input where digit multiplication won't cause overflow (for 32-bit unsigned)
    assume_abort_if_not(n <= 429496729 && n>0); // 9^9 is 387420489, so this is safe
    
    // Compute results from both implementations
    int student_result = f(n);
    int reference_result = std(n);
    
    // Verify they match
    assert(student_result == reference_result);
    
    return 0;
}
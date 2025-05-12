extern double __VERIFIER_nondet_double();
extern void abort(void);
extern double vipShouFei(double money);
extern double std(double money);  // reference implementation

void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Generate non-deterministic input
    double money = __VERIFIER_nondet_double();
    
    // Assume money is non-negative and not NaN/infinity
    assume_abort_if_not(money >= 0.0);
    assume_abort_if_not(money == money);  // checks for NaN
    
    // Call both implementations
    double student_result = vipShouFei(money);
    double std_result = std(money);
    
    
    // Assert equality
    assert(student_result == std_result);
    
    return 0;
}
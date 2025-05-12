extern double __VERIFIER_nondet_double();
extern void abort(void);
extern double getSalary(double);
extern double std(double);

void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Generate non-deterministic input
    double hours = __VERIFIER_nondet_double();
    
    // Restrict input to reasonable working hours (0-168 hours/week)
    // Also ensure it's not NaN and not infinite
    assume_abort_if_not(hours >= 0.0 && hours <= 168.0);
    assume_abort_if_not(hours == hours); // not NaN
    
    // Call both implementations
    double student_result = getSalary(hours);
    double std_result = std(hours);
    
    // Assert that results match
    assert(student_result == std_result);
    
    return 0;
}
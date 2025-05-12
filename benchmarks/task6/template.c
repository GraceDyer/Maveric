extern int solve(int x);
extern int std(int x);

extern int __VERIFIER_nondet_int();

void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Get non-deterministic input
    int x = __VERIFIER_nondet_int();
    
    // Call both implementations
    int student_result = solve(x);
    int reference_result = std(x);
    
    // Verify the results match
    assert(student_result == reference_result);
    
    return 0;
}
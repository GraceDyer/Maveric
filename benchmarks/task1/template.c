extern int solve(int budgets[12]);
extern int std(int budgets[12]);

extern int __VERIFIER_nondet_int();
void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Initialize budgets array
    int budgets[12];
    
    // Generate and validate 12 monthly budgets
    for (int i = 0; i < 12; i++) {
        budgets[i] = __VERIFIER_nondet_int();
        // Budget must be non-negative and less than 350
        assume_abort_if_not(budgets[i] >= 0 && budgets[i] < 350);
    }
    
    // Call both implementations
    int student_result = solve(budgets);
    int reference_result = std(budgets);
    
    // Verify results match
    assert(student_result == reference_result);
    
    return 0;
}
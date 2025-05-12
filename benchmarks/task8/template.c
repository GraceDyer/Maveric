extern int f(int n, int m, int a[]);
extern int std(int n, int m, int a[]);
extern int __VERIFIER_nondet_int();

void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Non-deterministic input generation
    int N = __VERIFIER_nondet_int();
    int M = __VERIFIER_nondet_int();
    
    // Input constraints
    assume_abort_if_not(N >= 1 && N <= 100);
    assume_abort_if_not(M >= 1 && M <= 100);
    
    // Allocate array for cat food prices
    int a[M];
    for (int i = 0; i < M; i++) {
        a[i] = __VERIFIER_nondet_int();
        assume_abort_if_not(a[i] >= 1 && a[i] <= 100);
    }
    
    // Call both implementations
    int student_result = f(N, M, a);
    int std_result = std(N, M, a);
    
    // Compare results
    assert(student_result == std_result);
    
    return 0;
}
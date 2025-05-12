#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);
extern int solve(int pos[], int n, int len);
extern int std(int pos[], int n, int len);

void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Read rod length and number of ants
    int len = __VERIFIER_nondet_int();
    int n = __VERIFIER_nondet_int();
    
    // Assume valid input ranges
    assume_abort_if_not(len > 0 && len <= 10000);
    assume_abort_if_not(n > 0 && n <= 10000);
    
    // Allocate and initialize ant positions
    int* pos = (int*)malloc(n * sizeof(int));
    if (!pos) abort();
    
    for (int i = 0; i < n; i++) {
        pos[i] = __VERIFIER_nondet_int();
        assume_abort_if_not(pos[i] >= 0 && pos[i] <= len);
    }
    
    // Call both implementations
    int student_result = solve(pos, n, len);
    int reference_result = std(pos, n, len);
    
    // Compare results
    assert(student_result == reference_result);
    
    free(pos);
    return 0;
}
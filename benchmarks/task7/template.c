extern int f(int n);
extern int std(int n);
extern int __VERIFIER_nondet_int();
void assume_abort_if_not(int cond) {
    if (!cond)
        abort();
}

int main() {
    // Generate nondeterministic input
    int n = __VERIFIER_nondet_int();

    // Constrain the input to the valid range
    assume_abort_if_not(n > 0 && n < 1000);

    // Compare the outputs of the student and reference implementations
    assert(f(n) == std(n));

    return 0;
}


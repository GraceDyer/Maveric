void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}

extern _Bool __VERIFIER_nondet_bool(void);
extern int __VERIFIER_nondet_int(void);
extern void sort(int data[], int len);
extern void std(int data[], int len);  // reference implementation

#define MAX_SIZE 100

int main() {
    // Determine array length
    int len = __VERIFIER_nondet_int();
    assume_abort_if_not(len >= 0 && len < MAX_SIZE);
    
    // Create and initialize arrays
    int data_student[MAX_SIZE];
    int data_std[MAX_SIZE];
    
    // Initialize arrays with same random values
    for(int i = 0; i < len; i++) {
        int val = __VERIFIER_nondet_int();
        data_student[i] = val;
        data_std[i] = val;
    }
    
    // Call both implementations
    sort(data_student, len);
    std(data_std, len);
    
    // Verify results match
    for(int i = 0; i < len; i++) {
        assert(data_student[i] == data_std[i]);
    }
    
    // Additional check for sorted order (optional but recommended)
    for(int i = 0; i < len-1; i++) {
        assert(data_student[i] <= data_student[i+1]);
    }
    
    return 0;
}
void mpz_alea(mpz_t a, mpz_t max);
void mpz_bin(mpz_t n, int *nb);
void sq_mul(mpz_t a, mpz_t exp, mpz_t n, int *nb, mpz_t resul);
int test_f(mpz_t n, mpz_t a, int *nb);
int test_fermat(int k, mpz_t n);
int decomp(mpz_t n, mpz_t t);
int miller_rabin(mpz_t n, int k);
void ex_time(clock_t begin, clock_t end);

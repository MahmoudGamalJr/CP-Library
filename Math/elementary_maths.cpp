//Elementary Maths

const int prime32 = (1 << 31) - 1;
const long long prime64 = (1ll << 61) - 1;

int ceil(int x, int y) {
    return (x + y - 1) / y;
}

//round to the nearest multiple of m
int rnd(int x, int m) {
    return (int) round((1.0 * x) / m) * m;
}

//number of bits in a number
int cntbits(int x) {
    return (int) floor(log2(x)) + 1;
}

//number of digits in a number
int cntdigits(int x) {
    return (int) floor(log10(x)) + 1;
}

//general mod formula for +ve & -ve numbers
int mod(int x, int k) {
    return (x % k + k) % k;
}


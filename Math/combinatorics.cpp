// returns a^k % m
long long powmodk(long long a, long long k, long long m) 
{
    if (k == 0) return 1;
    long long r = powmodk(a, k / 2, m);
    r = (r * r) % m;
    if (k % 2) r = (r * a) % m;
    return r;
}


//obtain n factorial mod p using wilson theorem
long long factmodprime(long long n, long long p) { //O(plogn)
    long long res = 1;
    while (n > 0) {
        for (ll i = 1; i <= n % p; i++)
            res = (res * i) % p;
        n /= p; //to obtain the power
    }
    if (n % 2 != 0) {
        res = p - res;
    }

    return res;
}

// how many times can we find a specific  prime in a factorial
int factprimepow(int x, int p){ //O(logp(x))
    int pow=0;
    for(int i=p; i<=x; i*=p){
        pow+= x/i; //for each level
    }
    return pow;
}

long long nckmodprime(long long n, long long k, long long p) {
    long long pow = factprimepow(n, p) - factprimepow(k, p) - factprimepow(n - k, p);
    if (pow) { //then nck is divisible by p
        return 0;
    }
    long long up = factmodprime(n, p);
    long long down = (factmodprime(k, p) * factmodprime(n - k, p)) % p;
    long long downinv = powmodk(down, p - 2, p);
    return (up * downinv) % p;
}

//recurence relation c(n,k)=c(n-1,k-1)+c(n-1,k)
long long nCk(int n, int k) {
    long long comb[n + 5][k + 5];
    memset(comb, 0, sizeof(comb));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; ++j) {
            comb[i][j] = j == 0 ? 1 : (i == 0 ? 0 : comb[i - 1][j - 1] + comb[i - 1][j]);
        }
    }
    return comb[n][k];
}

//Pascal's Rule: iterative | Bottom-up approach
long long nCk2(int N, int K) {
    ll comb[N + 5][N + 5];
    memset(comb, 0, sizeof(comb));
    comb[0][0] = 1;
    for (int i = 1; i < N; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]);        //may use mod
    }
    return comb[N][K];
}

//multiplicative formula
int nCK3(int N, int K){		// O(K)
    if (K > N)
        return 0;
    int res = 1;
    for (int i = 1; i <= K; ++i)
        res = (N - K + i) * res / i;
    return res;
}


//stirling numbers of the second kind divide int n groups with no size limitations
long long stirling2(long long n, long long k) {
    if (n == k || k == 1) return 1;
    return k * stirling2(n - 1, k) + stirling2(n - 1, k - 1);
}

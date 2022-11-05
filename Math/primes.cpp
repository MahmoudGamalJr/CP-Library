
//check whether a number is prime or not
bool isprime(long long x) { //O(sqrt(x))
    if (x == 2) return true;
    if (x < 2 || x % 2 == 0) return false;
    for (long long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

void sieve(long long r, vector<bool> &isprime) { //O(Nlog(log(N)))
    isprime.assign(r + 1, true);
    isprime[0] = isprime[1] = false;
    for (ll i = 2; i * i <= r; i++) {
        if (isprime[i]) {
            for (ll j = i * 2; j <= r; j += i) {
                isprime[j] = false;
            }
        }
    }
}

vi primes;
vector<bool> isprime;

void sieve(int N) { // O(N log log N) 
    isprime.assign(N + 1, true);
    isprime[0] = isprime[1] = false;
    for (ll i = 2; i <= N; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            if (i * i <= N) {
                for (ll j = i * i; j <= N; j += i) {
                    isprime[j] = false;
                }
            }
        }
    }
}


//Preprocessing: call sieve with sqrt(N), O(sqrt(N) log log sqrt(N))
//Query: best case O(1), worst case O(sqrt(N) / log sqrt(N))
bool primalitytest(ll N) { 
    if (N < isprime.size())
        return isprime[N];
    for (int p: primes) {
        if (1ll * p * p > N) break;
        if (N % p == 0)
            return false;
    }

    return true;
}

//obtain the divisors of a number (not necessarily prime)
void gendivs(ll x, vector<ll> &divs) { //O(sqrt(x))
    ll i;
    for (i = 1; i * i < x; i++) {
        if (x % i == 0) divs.push_back(i), divs.push_back(x / i);
    }

    if (i * i == x) divs.push_back(i);
}

//obtain the prime divisors of a number
//take care of overflow!
void genprimedivs(int x, vector<ii> &primes) { //O(sqrt(x))
    for (int i = 2; i * i <= x; i++) {
        int pow = 0;
        while (x % i == 0) pow++, x /= i;
        if (pow > 0) primes.push_back(ii(i, pow));

    }

    if (x > 1) primes.push_back(ii(x, 1));
}

//count the number of divisors using prime factorization
long long cntdivs(int x) { //O(sqrt(x))
    vector<ii> primes;
    genprimedivs(x, primes);
    ll cnt = 1;
    for (int i = 0; i < primes.size(); i++) {
        cnt *= primes[i].second + 1;
    }
    //or:
    vector<ll> divs;
    gendivs(x, divs);
    cnt = divs.size();

    return cnt;
}

// find the number of divisors for each number in the range from 1 to r
void rangefactorization(int r) {
    vi numfactors(r + 1, 0); //similar to sieve approach
    for (int i = 1; i <= r; i++) {  //i divides k
        for (int k = i; k <= r; k += i) {
            numfactors[k]++;
        }
    }
}

// how many times can we find a specific  prime in a factorial
int factprimepow(int x, int p){ //O(logp(x))
    int pow=0;
    for(int i=p; i<=x; i*=p){
        pow+= x/i; //for each level
    }
    return pow;
}

//count prime factors for each number in the range from 1 to r
void sieveprimefactors(long long r, vector<int> &pf) { //O(sqrt(r))
    pf.assign(r + 1, 0);
    for (long long i = 2; i * i <= r; i++) { //divisor
        if (pf[i] == 0) {
            for (long long j = i * 2; j <= r; j += i) {
                int pow = 0;
                long long k = j;
                while (k % i == 0) {
                    k /= i;
                    pow++;
                }
                pf[j] += pow;
            }
        }
    }
}


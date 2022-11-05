// ax==1 mod m iff a,m are coprimes
ll modinverse(ll a, ll m) {
    ll x, y;
    ll d = extendedeuclid(a, m, x, y);
    if (d != 1)return -1;
    return (x % m + m) % m;
}

// returns a^k % m
ll powmodk(ll a, ll k, ll m) {
    if (k == 0) return 1;
    ll r = powmodk(a, k / 2, m);
    r = (r * r) % m;
    if (k % 2) r = (r * a) % m;
    return r;
}

ll modinversephi(ll a, int m) {
    if (isprime(m)) return powmodk(a, m - 2, m);
    return powmodk(a, phi(m) - 1, m);
}

//compute mod inverse for all numbers from 1 to p-1 where p is a prime number
//p %i = p - (p / i) * i
void modinverserange(vector<int> &inv, int p) {
    inv.assign(p - 1, 1);
    for (int i = 2; i < p; i++)
        inv[i] = (p - (p / i) * inv[p % i] % p) % p; //expensive equation
}

//solves the congruence equation  ax=b (mod m) => ax-ym=b (diophantine)
void modularequation(vector<ll> &sol, ll a, ll b, ll m) {
    ll x, y, g;
    g = extendedeuclid(a, m, x, y);
    if (b % g != 0) {
        return; // no solutions
    }
    x = ((x * b / g) % m + m) % m;

    for (int i = 0; i < g; i++) { //bezout's identity
        sol.push_back((x + i * m / g) % m);
    }

    sort(sol.begin(), sol.end()); //optional
}

//returns the totient using prime factorization
//using the fact that p^(n-1)*(p-1)
int phi(int x) {
    int ptok, coprimes = 1;
    for (int i = 2, d = 1; i * i <= x; i += d, d = 2) {
        if (x % i == 0) {
            ptok = 1;
            while (x % i == 0)
                ptok *= i, x /= i;

            coprimes *= (ptok / i) * (i - 1);
        }
    }
    if (x != 1) coprimes *= (x - 1);
    return coprimes;
}

//using sieve
void phigenerator(int range) {
    bool primes[range + 1];
    int phi[range + 1];
    memset(primes, 1, sizeof(primes));
    for (int k = 0; k <= range; k++) {
        phi[k] = 1;
    }
    for (int i = 2; i <= range; i++) {
        if (primes[i]) {
            phi[i] = i - 1; //phi(prime)=p-1;
        }

        for (int j = i * 2; j <= range; j += i) {
            int x = j, ptok = 1;
            while (x % i == 0)
                ptok *= i, x /= i;
            phi[j] *= (ptok / i) * (i - 1);
        }
    }
}

//phi(n!)=(n is prime then n-1 else n) * (phi(n-1)!)
ll phifactorial(int x) {
    ll ret = 1;
    for (int i = 2; i <= x; i++)
        ret *= isprime(i) ? i - 1 : i;
    return ret;
}


//performing fast b^p
ll fastpow(ll b, ll p) {
    if (p == 0) return 1;
    if (p & 1)
        return b * fastpow(b * b, p >> 1);
    return fastpow(b * b, p >> 1);
}

// find the greatest common divisor of a and b
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);

}

// find the least common multiple of a and b
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// for solving ax+by=gcd(a,b) given a & b
ll extendedeuclid(ll a, ll b, ll &x, ll &y) {
    if (a < 0) {
        ll r = extendedeuclid(-a, b, x, y);
        x *= -1;
        return r;
    }
    if (b < 0) {
        ll r = extendedeuclid(a, -b, x, y);
        y *= -1;
        return r;
    }

    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    ll g = extendedeuclid(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

// for solving ax+by=c given a,b & c
ll diophantine(ll a, ll b, ll c, ll &x, ll &y, bool &found) {
    ll g = extendedeuclid(a, b, x, y);
    if ((found = (c % g == 0))) x *= c / g, y *= c / g;
    return g;
}


//chinese remainder theorem to solve system of congruence equations
ll crt(vector<ll> &rems, vector<ll> &mods) {
    ll rem = rems[0], mod = mods[0];

    for (int i = 1; i < rems.size(); i++) {
        ll x, y, found, a = mod, b = -mods[i], c = rems[i] - rem;
        ll g = diophantine(a, b, c, x, y, found);
        if (!found) return -1;
        rem += mod * x;          //evaluate previous congruence
        rem = mod / g * mods[i]; //merge mods with previous equation
        rem = (rem % mod + mod) % mod;
    }

    return rem;
}


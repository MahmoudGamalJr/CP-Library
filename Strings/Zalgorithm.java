
static int[] zAlgorithm(char[] s) {
    int n = s.length;
    int[] z = new int[n];
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = Math.min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            r = i + z[l = i] - 1;
    }
    return z;
}


static String getLongestPalindromePrefix(String s) {
    String tmp = s + new StringBuilder(s).reverse().toString();
    int[] z = zAlgorithm(tmp.toCharArray());
    for (int i = s.length(); i < z.length; i++)
        if (z[i] + i == z.length) return s.substring(0, z[i]);
    return "";
}

static String getLongestPalindromicSuffix(String s) {
    String tmp = new StringBuilder(s).reverse().toString() + s;
    int[] z = zAlgorithm(tmp.toCharArray());
    for (int i = s.length(); i < z.length; i++)
        if (z[i] + i == z.length) return s.substring(s.length() - z[i]);
    return "";
}


#include <iostream>
#include <numeric>

using namespace std;

long long powerMod(long long b, long long e, long long m) {
    long long res = 1;
    b %= m;

    while(e > 0) {
        if(e%2 == 1)
            res = (long long)((__int128)res * b % m);
        b = (long long)((__int128)b * b % m);
        e /= 2;
    }

    return res;
}

bool millerTest(long long n) {
    long long m = n - 1;
    long long k = 0;
    while(m%2 == 0) {
        m /= 2;
        k++;
    }

    long long a = 2 + rand() % (n - 3);
    long long t = powerMod(a, m, n);

    if(t == 1 || t == n - 1 || t == -1) 
        return true;
    
    for(long long p = 1; p <= k - 1; p++) {
        t = (t * t) % n;

        if(t == 1)
            return false;

        if(t == n - 1 || t == -1)
            return true;
    }

    return false;
}

long long genRandPrime(long long minimum, long long maximum) {
    long long num;
    int iterations = 5;
    bool isPrime = false;

    while(true) {
        num = minimum + rand() % (maximum - minimum + 1);

        if(num <= 1)
            continue;
        if(num == 2 || num == 3)
            return num;
        if(num % 2 == 0)
            continue;
        
        isPrime = true;
        for(int i = 0; i < iterations; i++) {
            if(!millerTest(num)) {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            return num;
    }
}

long long extendedEuclidean(long long b, long long m) {
    long long a1 = 1, a2 = 0, a3 = m;
    long long b1 = 0, b2 = 1, b3 = b;

    while(true) {
        if(b3 == 0) {
            cout << "NO INVERSE!\n";
            return -1;
        }

        if(b3 == 1) {
            return (b2 % m + m) % m;
        }

        long long q = a3 / b3;

        long long t1 = a1 - q * b1;
        long long t2 = a2 - q * b2;
        long long t3 = a3 - q * b3;

        a1 = b1;
        a2 = b2;
        a3 = b3;

        b1 = t1;
        b2 = t2;
        b3 = t3;
    }
}

int32_t main() {
    srand(time(0));

    long long p = genRandPrime(50, 150);
    long long q = genRandPrime(50, 150);

    while(p == q) {
        q = genRandPrime(50, 150);
    }

    cout << "(" << p << ", " << q << ") = (" << p << ", " << q << ")" << endl;

    long long n = p * q;
    cout << "n = " << n << endl;

    long long phi = (p - 1) * (q - 1);
    cout << "phi = " << phi << endl;

    long long e = 17; // 1 < e < phi(n)
    while(e < phi) {
        if(std::gcd(e, phi) == 1)
            break;
        e++;
    }

    cout << "e = " << e << endl;

    long long d = extendedEuclidean(e, phi);
    cout << "d = " << d << endl;

    cout << "Public Key: (" << e << ", " << n << ")" << endl; 
    cout << "Private Key: (" << d << ", " << n << ")" << endl;
    
    long long msg = 65;
    cout << "Original Message: " << msg << " (" << (char)msg << ")" << endl;

    long long c = powerMod(msg, e, n);
    cout << "Encrypted Message = " << c << endl; // c = m^e mod n

    long long decrypted = powerMod(c, d, n);
    cout << "Decrypted Message = " << decrypted << " (" << (char)decrypted << ")" << endl; // d = c^d % n
}
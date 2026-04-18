#include <iostream>

using namespace std;

struct Point {
    long long x, y;
};

long long mod(long long n, long long p) {
    return (n % p + p) % p;
}

long long power(long long base, long long exp, long long p) {
    long long res = 1LL;
    base = mod(base, p);

    while(exp > 0) {
        if(exp % 2 == 1) 
            res = mod(res * base, p);
        exp = exp / 2;
        base = mod(base * base, p);
    }
    return res;
}

long long modInverse(long long n, long long p) {
    return power(n, p - 2, p);
}

Point addPoint(Point P, Point Q, long long a, long long p) {
    // (-1, -1) represents the "point to infinity"
    if(P.x == -1 && P.y == -1)
        return Q;
    if(Q.x == -1 & Q.y == -1) 
        return P;
    
    long long lambda; // slope

    if(P.x == Q.x && P.y == Q.y) {
        // point doubling (P + P)

        if(P.y == 0) // tanget is vertical, goes to infinity
            return {-1, -1};
        long long numerator = mod(3 * P.x * P.x + a, p);
        long long denominator = modInverse(mod(2 * P.y, p), p);
        lambda = mod(numerator * denominator, p);
    } else {
        // point addition (P + Q)

        if(P.x == Q.x) // vertical line, goes to infinity
            return {-1, -1};
        long long numerator = mod(Q.y - P.y, p);
        long long denominator = modInverse(mod(Q.x - P.x, p), p);
        lambda = mod(numerator * denominator, p);
    }

    // new point
    long long x3 = mod(lambda * lambda - P.x - Q.x, p);
    long long y3 = mod(lambda * (P.x - x3) - P.y, p);

    return {x3, y3};
}

Point multiplyPoint(long long k, Point P, long long a, long long p) {
    // scalar multiplaction (k * point)

    Point R = {-1, -1}; // infinity
    Point Q = P;

    while(k > 0) {
        if(k % 2 == 1)
            R = addPoint(R, Q, a, p); // add
        Q = addPoint(Q, Q, a, p); // double
        k /= 2;
    }
    return R;
}

int main() {
    cout << "--- Experiment 08: Elliptic Curve Key Exchange ---" << endl << endl;

    long long p = 17;
    long long a = 2;
    long long b = 2;

    Point G = {5, 1};

    cout << "Public Curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")" << endl;
    cout << "Public Base Point G = (" << G.x << "," << G.y << ")" << endl << endl;

    long long alice_private_key = 3;
    Point alice_public_key = multiplyPoint(alice_private_key, G, a, p);
    cout << "Alice's Private Key = " << alice_private_key << endl;
    cout << "Alice's Public Key = (" << alice_public_key.x << ", " << alice_public_key.y << ")" << endl << endl;

    long long bob_private_key = 3;
    Point bob_public_key = multiplyPoint(bob_private_key, G, a, p);
    cout << "Bob's Private Key = " << bob_private_key << endl;
    cout << "Bob's Public Key = (" << bob_public_key.x << ", " << bob_public_key.y << ")" << endl << endl;

    Point alice_shared_secret = multiplyPoint(alice_private_key, bob_public_key, a, p);
    cout << "Alice's shared secret: (" << alice_shared_secret.x << ", " << alice_shared_secret.y << ")" << endl;

    Point bob_shared_secret = multiplyPoint(bob_private_key, alice_public_key, a, p);
    cout << "Bob's shared secret: (" << bob_shared_secret.x << ", " << bob_shared_secret.y << ")" << endl << endl;

    if(alice_shared_secret.x == bob_shared_secret.x && alice_shared_secret.y == bob_shared_secret.y) {
        cout << "Success! Both parties derived the exact same share secret point." << endl;
        // in real systems, the 'x' coordinate is hashed and used as the AES encryption key
        cout << "The shared symmetric key (x-coordinate) to use for encryption is: " << alice_shared_secret.x << endl;
    } else {
        cout << "Error: the secret keys do not match!" << endl;
    }

    
}
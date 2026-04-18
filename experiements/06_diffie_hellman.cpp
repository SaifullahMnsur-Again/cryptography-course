#include <iostream>

using namespace std;

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

int main() {
    cout << "--- Experiment 06: Diffie-Hellman Key Exchange ---" << endl << endl;
    long long p = 23;
    long long g = 5;

    cout << "Publicly shared variables:" << endl;
    cout << "Prime (p) = " << p << endl;
    cout << "Base/Generator (g) = " << g << endl << endl;

    long long alice_private_key = 4;
    cout << "Alice's Private Key = " << alice_private_key << endl;

    long long alice_public_key = power(g, alice_private_key, p);
    cout << "Alice's Public Key:" << alice_public_key << endl << endl;


    long long bob_private_key = 7;
    cout << "Bob's Private Key = " << bob_private_key << endl;

    long long bob_public_key = power(g, bob_private_key, p);
    cout << "Bob's Public Key: " << bob_public_key << endl << endl;


    long long alice_shared_secret = power(bob_public_key, alice_private_key, p);
    cout << "Alice's Shared Secret: " << alice_shared_secret << endl;
    
    long long bob_shared_secret = power(alice_public_key, bob_private_key, p);
    cout << "Bob's Shared Secret: " << bob_shared_secret<< endl << endl;

    if(alice_shared_secret == bob_shared_secret) {
        cout << "Success! Both parites have securely agreed on the same shared secret key: " << alice_shared_secret << endl;
    } else {
        cout << "Error: the secret keys do not match!" << endl;
    }


}
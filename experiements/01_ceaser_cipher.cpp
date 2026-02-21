#include <iostream>
#include <string>

using namespace std;

// Function to encrypt the text using Caesar Cipher
string encrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i]))
            result += char(int(text[i] + shift - 65) % 26 + 65);
        else if (islower(text[i]))
            result += char(int(text[i] + shift - 97) % 26 + 97);
        else
            result += text[i]; // Keep spaces and punctuation unchanged
    }
    return result;
}

// Function to decrypt the text using Caesar Cipher
string decrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i]))
            result += char(int(text[i] - shift - 65 + 26) % 26 + 65);
        else if (islower(text[i]))
            result += char(int(text[i] - shift - 97 + 26) % 26 + 97);
        else
            result += text[i];
    }
    return result;
}

// Function for Brute-Force cryptanalysis of Caesar Cipher
void bruteForceCryptanalysis(string cipherText) {
    cout << "\n--- Brute-Force Cryptanalysis ---" << endl;
    for (int shift = 1; shift <= 25; shift++) {
        cout << "Shift " << shift << ": " << decrypt(cipherText, shift) << endl;
    }
}

int main() {
    string text = "HELLO WORLD";
    int shift = 3;

    cout << "Original Text: " << text << endl;
    
    string cipherText = encrypt(text, shift);
    cout << "Encrypted Text (Shift " << shift << "): " << cipherText << endl;
    
    string decryptedText = decrypt(cipherText, shift);
    cout << "Decrypted Text: " << decryptedText << endl;

    // Perform Brute-Force attack
    bruteForceCryptanalysis(cipherText);

    return 0;
}
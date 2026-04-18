#include <iostream>
// #include <string>
#include <iomanip> // for hexa decimal printing

using namespace std;

const int BLOCK_SIZE = 8;

string pad(string data) {
    int pad_len = BLOCK_SIZE - (data.length() % BLOCK_SIZE);
    for(int i = 0; i < pad_len; i++) {
        data.push_back((char)pad_len);
    }
    // data.append(pad_len, (char)pad_len);
    return data;
}

string unpad(string data) {
    if(data.empty())
        return data;
    int pad_len = data.back();

    return data.substr(0, data.length() - pad_len);
}

string xor_block_op(string block, string key) {
    string xor_block = "";
    for(int i = 0; i < BLOCK_SIZE; i++) {
        xor_block += (block[i] ^ key[i]);
    }
    return xor_block;
}

// string decryptEcbBlock(string block, string key) {
//     string decipher_block = "";
//     for(int i = 0; i < BLOCK_SIZE; i++) {
//         decipher_block += (block[i] ^ key[i]);
//     }

//     return decipher_block;
// }

string encryptECB(string plaintext, string key) {
    plaintext = pad(plaintext);

    string ciphertext = "";
    for(int i = 0; i < plaintext.length(); i += BLOCK_SIZE) {
        string block = plaintext.substr(i, BLOCK_SIZE);
        ciphertext += xor_block_op(block, key);
    }
    return ciphertext;
}

string decryptECB(string ciphertext, string key) {
    string deciphertext = "";

    for(int i = 0; i < ciphertext.length(); i += BLOCK_SIZE) {
        string block = ciphertext.substr(i, BLOCK_SIZE);
        deciphertext += xor_block_op(block, key);
    }

    return unpad(deciphertext);
}

void printHex(string data) {
    for(int i = 0; i < data.length(); i++) {
        if(i > 0 && i % BLOCK_SIZE == 0)
            cout << " | ";
        cout << hex << setw(2) << setfill('0') << (int)(unsigned char)data[i] << " ";
    }
    cout << dec << endl;
}

int main() {
    cout << "--- ECB Mode Operation ---" << endl << endl;

    string plaintext = "HELLO WORLD!";
    string key = "ABCDEFGH"; // block size 8 byte = 64 bit

    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;

    string ciphertext = encryptECB(plaintext, key);
    cout << "Cipher Text: " << ciphertext << endl << endl;

    printHex(ciphertext);

    string deciphertext = decryptECB(ciphertext, key);
    cout << "Decipher Text: " << deciphertext << endl << endl;


}
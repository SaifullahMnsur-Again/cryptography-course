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

string encryptSingleBlock(string block, string key) {
    return xor_block_op(block, key);
}

string decryptSingleBlock(string block, string key) {
    return xor_block_op(block, key);
}

string encryptCBC(string plaintext, string key, string iv) {
    plaintext = pad(plaintext);

    string ciphertext = "";
    string prev_block = iv;

    for(int i = 0; i < plaintext.length(); i += BLOCK_SIZE) {
        string current_plaintext_block = plaintext.substr(i, BLOCK_SIZE);

        // chain
        string chained_block = xor_block_op(current_plaintext_block, prev_block);

        // encrypt
        string cipher_block = encryptSingleBlock(chained_block, key);

        ciphertext += cipher_block;

        // update
        prev_block = cipher_block;
    }
    return ciphertext;
}

string decryptCBC(string ciphertext, string key, string iv) {
    string deciphertext = "";
    string prev_block = iv;

    for(int i = 0; i < ciphertext.length(); i += BLOCK_SIZE) {
        string current_ciphertext_block = ciphertext.substr(i, BLOCK_SIZE);

        // decrypt
        string decipher_block = decryptSingleBlock(current_ciphertext_block, key);
        
        // unchain
        string unchained_block = xor_block_op(decipher_block, prev_block);

        deciphertext += unchained_block;

        // update
        prev_block = current_ciphertext_block;
    }

    return unpad(deciphertext);
}

void printHex(string data) {
    for(int i = 0; i < data.length(); i++) {
        if(i > 0 && i % BLOCK_SIZE == 0)
            cout << "| ";
        // hex = hexadecimal format
        // setw(2) = word width 2
        // setfill('0') = if generated word is less than 2 then fill with 0s from left
        // (int)(unsigned char)data[i] = convert the charecter to unsigned charecter and then the integer ascii
        // it prints the hexa decimal value of the charect
        cout << hex << setw(2) << setfill('0') << (int)(unsigned char)data[i] << " ";
    }
    cout << dec << endl;
}

int main() {
    cout << "--- ECB Mode Operation ---" << endl << endl;

    string plaintext = "ADMINISTRATOR   ADMINISTRATOR";
    string key = "ABCDEFGH"; // block size 8 byte = 64 bit
    string iv = "12345678";

    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "IV: " << iv << endl;

    string ciphertext = encryptCBC(plaintext, key, iv);
    cout << "Cipher Text: " << ciphertext << endl << endl;

    cout << "Cipher Text (hex): ";
    printHex(ciphertext);
    cout << endl;

    string deciphertext = decryptCBC(ciphertext, key, iv);
    cout << "Decipher Text: " << deciphertext << endl;

}
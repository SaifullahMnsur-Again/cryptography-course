#include <iostream>
// #include <string>
#include <iomanip> // for hexa decimal printing

using namespace std;

const int BLOCK_SIZE = 8; // 8 for DES, 16 for AES

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

string shiftRegister(string curr_reg, string feedback) {
    int shift_amount = feedback.length();
    string shifted = curr_reg.substr(shift_amount);
    return shifted + feedback;
}

string encryptCFB(string plaintext, string key, string iv, int s_bytes) {
    string ciphertext = "";
    string shift_reg = iv;

    for(int i = 0; i < plaintext.length(); i += s_bytes) {

        int segment_size = min(s_bytes, (int)plaintext.length() - i);
        string current_plaintext_segment = plaintext.substr(i, segment_size);

        string key_stream = encryptSingleBlock(shift_reg, key);

        string msb = key_stream.substr(0, segment_size);

        string cipher_segment = "";
        for(int j = 0; j < segment_size; j++) {
            cipher_segment += (current_plaintext_segment[j] ^ msb[j]);
        }

        ciphertext += cipher_segment;

        shift_reg = shiftRegister(shift_reg, cipher_segment);
    }
    return ciphertext;
}

string decryptCFB(string ciphertext, string key, string iv, int s_bytes) {
    string deciphertext = "";
    string shift_reg = iv;

    for(int i = 0; i < ciphertext.length(); i += s_bytes) {
        int segment_size = min(s_bytes, (int)ciphertext.length() - i);
        
        string current_ciphertext_segment = ciphertext.substr(i, segment_size);

        string key_stream = encryptSingleBlock(shift_reg, key);
        
        string msb = key_stream.substr(0, segment_size);

        string decipher_segment = "";
        for(int j = 0; j < segment_size; j++) {
            decipher_segment += (current_ciphertext_segment[j] ^ msb[j]);
        }

        deciphertext += decipher_segment;

        shift_reg = shiftRegister(shift_reg, current_ciphertext_segment);
    }

    return deciphertext;
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

    string ciphertext = encryptCFB(plaintext, key, iv, 8);
    cout << "Cipher Text: " << ciphertext << endl << endl;

    cout << "Cipher Text (hex): ";
    printHex(ciphertext);
    cout << endl;

    string deciphertext = decryptCFB(ciphertext, key, iv, 8);
    cout << "Decipher Text: " << deciphertext << endl;

}
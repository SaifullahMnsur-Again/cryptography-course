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

string processOFB(string input_text, string key, string nonce) {
    string output_text = "";
    string curr_input = nonce;

    for(int i = 0; i < input_text.length(); i += BLOCK_SIZE) {

        int u_bytes = min(BLOCK_SIZE, (int)input_text.length() - i);
        string curr_segment = input_text.substr(i, u_bytes);

        string key_stream = encryptSingleBlock(curr_input, key);

        string msb_u = key_stream.substr(0, u_bytes);

        string result_block = "";
        for(int j = 0; j < u_bytes; j++) {
            result_block += (curr_segment[j] ^ msb_u[j]);
        }

        output_text += result_block;

        curr_input = key_stream;
    }
    return output_text;
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
    cout << "--- OFB Mode Operation ---" << endl << endl;

    string plaintext = "ADMINISTRATOR   ADMINISTRATOR";
    string key = "ABCDEFGH"; // block size 8 byte = 64 bit
    string nonce = "12345678";

    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "Nonce: " << nonce << endl;

    string ciphertext = processOFB(plaintext, key, nonce);
    cout << "Cipher Text: " << ciphertext << endl << endl;

    cout << "Cipher Text (hex): ";
    printHex(ciphertext);
    cout << endl;

    string deciphertext = processOFB(ciphertext, key, nonce);
    cout << "Decipher Text: " << deciphertext << endl;

}
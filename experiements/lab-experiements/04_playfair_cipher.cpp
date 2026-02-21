#include <iostream>
#include <string>

using namespace std;

char matrix[5][5];

void generateMatrix(string key) {
    bool alphabet[26] = {false};
    int row = 0, col = 0;

    for(char c : key) {
        c = toupper(c);
        if(c == 'J')
            c = 'I'; // treat J as I
        if(!alphabet[c - 'A']) {
            matrix[row][col] = c;
            alphabet[c - 'A'] = true;
            col++;
            if(col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for(char c = 'A'; c <= 'Z'; c++) {
        if(c == 'J')
            continue;
        if(!alphabet[c - 'A']) {
            matrix[row][col] = c;
            alphabet[c - 'A'] = true;
            col++;
            if(col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

string formatText(string text) {
    string formatted = "";
    for(char c : text) {
        if(isalpha(c))
            formatted += toupper(c);
    }

    for(int i = 0; i < formatted.length(); i += 2) {
        if(i == formatted.length() - 1) {
            formatted += 'X'; // padding with x for odd length
        } else if(formatted[i] == formatted[i + 1]) {
            formatted.insert(i + 1, 1, 'X');
        }
    }
    return formatted;
}

void find(char ch, int &r, int &c) {
    if(ch == 'J')
        ch = 'I';
    
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(matrix[i][j] == ch) {
                r = i;
                c = j;
                return;
            }
        }
    }
}

string encrypt(string text) {
    string cipherText = "";

    for(int i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        find(text[i], r1, c1);
        find(text[i+1], r2, c2);

        if(r1 == r2) {
            cipherText += matrix[r1][(c1 + 1) % 5];
            cipherText += matrix[r2][(c2 + 1) % 5];
        } else if(c1 == c2) {
            cipherText += matrix[(r1 + 1) % 5][c1];
            cipherText += matrix[(r2 + 1) % 5][c2];
        } else {
            cipherText += matrix[r1][c2];
            cipherText += matrix[r2][c1];
        }
    }

    return cipherText;
}

string decrypt(string text) {
    string plaintText = "";
    for(int i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        find(text[i], r1, c1);
        find(text[i+1], r2, c2);

        if(r1 == r2) {
            plaintText += matrix[r1][(c1 + 4) % 5];
            plaintText += matrix[r2][(c2 + 4) % 5];
        } else if(c1 == c2) {
            plaintText += matrix[(r1 + 4) % 5][c1];
            plaintText += matrix[(r2 + 4) % 5][c2];
        } else {
            plaintText += matrix[r1][c2];
            plaintText += matrix[r2][c1];
        }
    }

    return plaintText;
}

int32_t main() {
    string key = "MONARCHY";
    string plaintext = "INSTRUMENTS";

    generateMatrix(key);

    cout << "Key: " << key << endl;

    string formatted = formatText(plaintext);
    cout << "Original Text: " << plaintext << endl;
    cout << "Formatted Text: " << formatted << endl;

    string cipherText = encrypt(formatted);
    cout << "Cipher Text: " << cipherText << endl;

    string decrypted = decrypt(cipherText);
    cout << "Decrypted text: " << decrypted << endl;
}
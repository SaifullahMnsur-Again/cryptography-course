#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string encrypt(string text, string key) {
    map<char, char> keyMap;
    for(int i = 0; i < key.size(); i++) {
        keyMap['A' + i] = key[i];
    }

    string cipher = "";
    for(char ch : text) {
        if(isalpha(ch))
            cipher += keyMap[toupper(ch)];
        else
            cipher += ch;
    }

    return cipher;
}

string decrypt(string text, string key) {
    map<char, char> keyMap;
    for(int i = 0; i < key.size(); i++) {
        keyMap[key[i]] = 'A' + i;
    }
    
    string decrypted = "";
    for(char ch : text) {
        if(isalpha(ch))
            decrypted += keyMap[toupper(ch)];
        else
            decrypted += ch;
    }

    return decrypted;
}

const string ENGLISH_FREQ = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

string frequencyAnalysis(string text) {
    vector<pair<int, char>> freq;
    for(int i = 0; i < 26; i++) {
        freq.push_back({0, 'A' + i});
    }
    for(char ch : text) {
        if(isalpha(ch))
            freq[toupper(ch) - 'A'].first++;
    }
    sort(freq.rbegin(), freq.rend()); // descending order sort
    
    map<char, char> attackMap;
    for(int i = 0; i < 26; i++) {
        attackMap[freq[i].second] = ENGLISH_FREQ[i];
    }

    string analysedText = "";
    for(char ch : text) {
        if(isalpha(ch))
            analysedText += attackMap[toupper(ch)];
        else
            analysedText += ch;
    }

    return analysedText;
}

int32_t main() {
    string key = "QWERTYUIOPASDFGHJKLZXCVBNM";
    // string plainText = "THIS IS MY LAST MESSAGE TO THE TEAM SO GOODBYE";
    string plainText = "DEFEND THE EAST WALL OF THE CASTLE AT DAWN. THE ENEMY IS APPROACHING FAST AND WE MUST HOLD THE LINE TO ENSURE OUR VICTORY.";


    cout << "Plain Text: " << plainText << endl;
    cout << "Encryption key: " << key << endl;

    string cipherText = encrypt(plainText, key);
    cout << "Cipher text: " << cipherText << endl;

    string decryptedText = decrypt(cipherText, key);
    cout << "Decrypted text: " << decryptedText << endl;

    string frequencyAnalysed = frequencyAnalysis(cipherText);
    cout << "Frequency analysed: " << frequencyAnalysed << endl;
}
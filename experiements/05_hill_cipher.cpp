#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<int> multiply(vector<vector<int>> keyMatrix, vector<int> textVector) {
    int n = keyMatrix.size();
    
    vector<int> result(n, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            result[i] += keyMatrix[i][j] * textVector[j];
        }
        result[i] = result[i] % 26;
    }
    return result;
}

// must pass reference(&) of tmp to update
void cofactor(vector<vector<int>> mat, vector<vector<int>>& tmp, int p, int q, int n) {
    int i = 0, j = 0;
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            if(row != p && col != q) {
                tmp[i][j++] = mat[row][col];
                if(j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(vector<vector<int>> mat, int n) {
    if(n == 1)
        return (mat[0][0] % 26 + 26) % 26;
    
    int det = 0;
    vector<vector<int>> tmp(n, vector<int>(n));
    int sign  = 1;

    for(int f = 0; f < n; f++) {
        cofactor(mat, tmp, 0, f, n);
        int subDet = determinant(tmp, n - 1);
        det = ((det + sign * mat[0][f] * subDet) % 26 + 26) % 26;
        sign = -sign;
    }

    return det;
}

void adjoint(vector<vector<int>> mat, vector<vector<int>>&adj) {
    int n = mat.size();
    if(n == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    vector<vector<int>> tmp(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cofactor(mat, tmp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = ((sign * determinant(tmp, n - 1)) % 26 + 26) % 26;
        }
    }
}

string encrypt(string text, vector<vector<int>> keyMatrix) {
    int n = keyMatrix.size();
    string cipherText = "";

    while(text.length()%n != 0)
        text += "X";
    
    for(int i = 0; i < text.length(); i += n) {
        vector<int> textVector(n);
        for(int j = 0; j < n; j++) {
            textVector[j] = text[i + j] - 'A';
        }

        vector<int> cipherVector = multiply(keyMatrix, textVector);

        for(int j = 0; j < n; j++) {
            cipherText += (char)(cipherVector[j] + 'A');
        }
    }

    return cipherText;
}

int modInv(int a, int m) {
    a = ((a % m) + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

vector<vector<int>> inverse(vector<vector<int>> keyMatrix) {
    int n = keyMatrix.size();
    vector<vector<int>> inverseMatrix(n, vector<int>(n, 0));

    int det = determinant(keyMatrix, n);

    int detInverse = modInv(det, 26);

    if(detInverse == -1) {
        cout << "Matrix has no inverse modulo 26! invalid key," << endl;
        exit(1);
    }
    vector<vector<int>> adj(n, vector<int>(n));
    adjoint(keyMatrix, adj);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            inverseMatrix[i][j] = ((adj[i][j] * detInverse) % 26 + 26) % 26;
        }
    }

    return inverseMatrix;
}

string decrypt(string text, vector<vector<int>> keyMatrix) {
    int n = keyMatrix.size();
    string plainText = "";

    vector<vector<int>> inverseKey = inverse(keyMatrix);

    for(int i = 0; i < text.length(); i += n) {
        vector<int> cipherVector(n);
        for(int j = 0; j < n; j++) {
            cipherVector[j] = text[i + j] - 'A';
        }

        vector<int> plainVector = multiply(inverseKey, cipherVector);

        for(int j = 0; j < n; j++) {
            plainText += (char)(plainVector[j] + 'A');
        }
    }
    return plainText;
}

int32_t main() {
    vector<vector<int>> keyMatrix = {{3, 3}, {2, 5}};
    string text = "HELP";

    cout << "Original Text: " << text << endl;
    cout << "Matrix:" << endl;
    cout << "[" << keyMatrix[0][0] << ", " << keyMatrix[0][1] << "]" << endl;
    cout << "[" << keyMatrix[1][0] << ", " << keyMatrix[1][1] << "]" << endl;

    string cipherText = encrypt(text, keyMatrix);
    cout << "Cipher Text: " << cipherText << endl;

    string decryptedText = decrypt(cipherText, keyMatrix);
    cout << "Decypted Text: " << decryptedText << endl;
}
#include "Shifr.h"
#include <iostream>
#include <string>

using namespace std;

string Shifr::encrypt(const string& input, int key)
{
    validateMessage(input, key);
    validateKey(input, key);

    int totalChars = input.length();
    int rows = (totalChars / key) + ((totalChars % key > 0) ? 1 : 0);
    int paddingSize = (totalChars % key) ? (key - totalChars % key) : 0;

    char** matrix = new char*[rows];
    for (int i = 0; i < rows; i++) matrix[i] = new char[key]();

    string result;

    for (int i = 0; i < paddingSize; i++) {
        matrix[rows - 1][(key - 1) - i] = '*';
    }

    int charIndex = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (matrix[i][j] != '*') {
                matrix[i][j] = input.at(charIndex++);
            }
        }
    }

    for (int i = 0; i < key; i++) {
        for (int j = 0; j < rows; j++) {
            if (matrix[j][(key - 1) - i] != '*') {
                result += matrix[j][(key - 1) - i];
            }
        }
    }

    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[] matrix;
    return result;
}

string Shifr::decrypt(const string& input, int key)
{
    validateMessage(input, key);
    validateKey(input, key);
    
    int rows = (input.length() / key) + ((input.length() % key > 0) ? 1 : 0);
    int paddingSize = (input.length() % key) ? (key - input.length() % key) : 0;

    char** matrix = new char*[rows];
    for (int i = 0; i < rows; i++) matrix[i] = new char[key]();

    string result;

    for (int i = 0; i < paddingSize; i++) {
        matrix[rows - 1][(key - 1) - i] = '*';
    }

    int charIndex = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < rows; j++) {
            if (matrix[j][(key - 1) - i] != '*') {
                matrix[j][(key - 1) - i] = input.at(charIndex++);
            }
        }
    }

    for (int i = 0; i < input.length(); i++) {
        int y = i / key;
        int x = (i % key);
        char c = matrix[y][x];
        if (c != '\0') {
            result += c;
        }
    }

    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[] matrix;
    return result;
}

void Shifr::validateKey(const string& input, int key)
{
    if (key <= 0) throw EncryptException("Invalid key");

    if (input.length() / 2 < key) {
        throw EncryptException("Key value is too high");
    }
}

void Shifr::validateMessage(const string& input, int key)
{
    if (input.empty()) throw EncryptException("Message cannot be empty");

    for (char c : input) {
        if (!isalpha(c)) throw EncryptException("Invalid character in message");
    }
}

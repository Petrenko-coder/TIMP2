#pragma once

#include <vector>
#include <string>
#include <map>
#include <stdexcept>

class ModAlphaCipher
{
private:
    std::wstring alphabet = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
    std::map<wchar_t, int> charToIndex;
    std::vector<int> key; // ключ

    std::vector<int> toVector(const std::wstring& str);
    std::wstring toString(const std::vector<int>& vec);
    std::wstring validateKey(const std::wstring& input);
    std::wstring validateOpenText(const std::wstring& input);
    std::wstring validateCipherText(const std::wstring& input);

public:
    ModAlphaCipher() = delete;
    ModAlphaCipher(const std::wstring& keyInput);
    std::wstring encrypt(const std::wstring& plaintext);
    std::wstring decrypt(const std::wstring& ciphertext);
};

class CipherError : public std::invalid_argument
{
public:
    explicit CipherError(const std::string& message)
        : std::invalid_argument(message) {}
    explicit CipherError(const char* message)
        : std::invalid_argument(message) {}
};

#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
using namespace std;
void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
        cipherText.front() = tolower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout<<"key="<<key<<endl;
        wcout<<Text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;
    } catch (const cipher_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
    }
}
int main(int argc, char **argv)
{
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    check(L"Ужлучшебытьполностьюсобойчемпритворятьсякем",L"Первый");
	check(L"Ужлучшебытьполностьюсобойчемпритворятьсякем",L"");
	check(L"Ужлучшебытьполностьюсобойчемпритворятьсякемт",L"АБВГ123");
	check(L"Уж лучше быть полностью собой чем притворяться кем",L"ВТОРОЙ");
	check(L"Ужлучшебытьполностьюсобойчемпритворятьсякем",L"ТРЕТИЙ",true);
	check(L"123",L"АБВГ");
    return 0;
}

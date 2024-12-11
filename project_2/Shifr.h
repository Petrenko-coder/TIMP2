#pragma once

#include <string>
#include <stdexcept>

class Shifr
{
public:
    std::string encrypt(const std::string& input, int key);
    std::string decrypt(const std::string& input, int key);
private:
    void validateKey(const std::string& input, int key);
    void validateMessage(const std::string& input, int key);
};

class EncryptException: public std::invalid_argument
{
public:
    explicit EncryptException(const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit EncryptException(const char* what_arg):
        std::invalid_argument(what_arg) {}
};

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <vector>
#include <iomanip>

#include "transaction.h"

inline unsigned char char_to_hex(const char &c){
    //I am certain there is a better way, I just don't know what it is.
    return 0x0f & (c >= 'a') ? ((c - 'a') + 10) : (c - '0');
}

int main(int argc, char **argv){
    if(argc != 2) throw std::runtime_error("invalid args");
    std::string str{argv[1]};
    if(str.size() % 2) throw std::runtime_error("odd number of hex char");
    if(std::find_if_not(str.begin(), str.end(), isxdigit) != str.end())
        throw std::runtime_error("non-hex digit");

    std::for_each(str.begin(), str.end(), [](char &c){ c = tolower(c); });

    std::vector<unsigned char> bytes(str.size() / 2, 0x00);

    //convert string of chars to bytes
    for(decltype(bytes.size()) i = 0; i != bytes.size(); ++i)
        bytes[i] |= (char_to_hex(str[i * 2]) << 4) | char_to_hex(str[i * 2 + 1]);

    Transaction tx(bytes);

    if(tx) std::cout << tx << std::endl;

    return 0;
}

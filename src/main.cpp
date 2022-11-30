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
    //check number of args passed to program
    if(argc != 2){
        std::cerr << "Invalid number of command line args." << std::endl;
        return 1;
    }

    //initalize a string object with the passed char array
    std::string str{argv[1]};

    //check for an even number of chars since 2 to a byte
    if(str.size() % 2){
        std::cerr << "Odd number of charaters in arg." << std::endl;
        return 1;
    }
    //check all chars in string are hex chars
    for(auto c: str){
        if(!isxdigit(c)){
            std::cerr << "Encountered non-hex digit '" << c << "'." << std::endl;
            return 1;
        }
    }

    //condition string to uniform case
    for(auto &c: str) c = tolower(c);

    //create vec to hold bytes, size determined by len of arg
    std::vector<unsigned char> bytes(str.size() / 2, 0x00);

    //convert string of chars to bytes
    for(decltype(bytes.size()) i = 0; i != bytes.size(); ++i)
        bytes[i] |= (char_to_hex(str[i * 2]) << 4) | char_to_hex(str[i * 2 + 1]);

    Transaction tx;

    if(!tx.parse(bytes)) return 1;

    std::cout << tx << std::endl;

    return 0;
}

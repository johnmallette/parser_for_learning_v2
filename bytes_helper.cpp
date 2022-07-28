#include <iomanip>

#include "bytes_helper.h"

std::runtime_error END_OF_BYTES("Parsing failed: Expected more bytes.");
std::runtime_error NOT_AT_END_OF_BYTES("Parsing failed: Bytes left over.");

std::vector<unsigned char>::size_type Bytes_Helper::read_compact_size(){
    unsigned char c;
    uint64_t size = 0;
    
    *this >> c;

    switch(c){
        case 0xfd:
            //change this, bad idea.
            *this >> *reinterpret_cast<uint16_t*>(&size);
            break;
        case 0xfe:
            *this >> *reinterpret_cast<uint32_t*>(&size);
            break;
        case 0xff:
            *this >> size;
            break;
        default:
            return c;
    }

    return size;
}

void Bytes_Helper::advance_current(std::vector<unsigned char>::size_type step){
    while(step--){
        if(end_of_bytes()) throw END_OF_BYTES;
        ++current;
    }
}

template<typename T> Bytes_Helper& operator>>(Bytes_Helper &lhs, T &rhs){
    auto stop = lhs.current;
    lhs.advance_current(sizeof(rhs));
    
    for(auto it = lhs.current; it != stop; --it){
        rhs <<= 8;
        rhs |= *(it - 1);
    }
    
    return lhs;
}

Bytes_Helper& operator>>(Bytes_Helper &lhs, std::vector<unsigned char> &rhs){
    auto start = lhs.current;
    lhs.advance_current(rhs.size());

    for(auto &b: rhs) b = *start++;

    return lhs;
}

std::ostream& operator<<(std::ostream &lhs, std::vector<unsigned char> &rhs){
    for(auto &c: rhs)
        lhs << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    return lhs;
}

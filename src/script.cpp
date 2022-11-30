#include "script.h"

void Script::parse(Bytes_Helper &helper){
    unsigned char b = 0x00;
    auto size = helper.read_compact_size();

    while(size--){
        helper >> b;
        uint16_t item_size = 0;
        unsigned char item_size_8 = 0;

        switch(b){
            case 0x4c:
                helper >> item_size_8;
                item_size = item_size_8;
                stack.push_back(std::vector<unsigned char>(item_size, 0x00));
                helper >> stack.back();
                break;
            case 0x4d:
                helper >> item_size;
                stack.push_back(std::vector<unsigned char>(item_size, 0x00));
                helper >> stack.back();
                break;
            default:
                if(b >= 0x01 && b <= 0x4b){
                    item_size = b;
                    stack.push_back(std::vector<unsigned char>(item_size, 0x00));
                    helper >> stack.back();
                    break;
                }
                stack.push_back(std::vector<unsigned char>{b});
        }
        size -= item_size;
    }
}

void Script::parse_witness(Bytes_Helper &helper){
    auto number_witness_items = helper.read_compact_size();

    while(number_witness_items--){
        auto size = helper.read_compact_size();
        stack.push_back(std::vector<unsigned char>(size, 0x00));
        helper >> stack.back();
    }
}

std::ostream& operator<<(std::ostream &lhs, const Script &rhs){
    for(auto &s: rhs.stack) lhs << "\n|   <" << s << '>' << std::flush;
    return lhs;
}

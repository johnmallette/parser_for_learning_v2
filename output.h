#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>

#include "bytes_helper.h"
#include "script.h"

struct Output{
    uint64_t amount = 0;
    Script script_pubkey;
};

inline
std::ostream &operator<<(std::ostream &lhs, const Output &rhs){
        lhs << "| amount: " << std::dec << rhs.amount << '\n'
            << "| script_pubkey:" << rhs.script_pubkey << std::flush;
        return lhs;
}


#endif



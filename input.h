#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "bytes_helper.h"
#include "script.h"

struct Input{
    std::vector<unsigned char> txid = std::vector<unsigned char>(32, 0x00);
    uint32_t index;
    Script script_sig;
    Script witness;
    uint32_t sequence;

    friend std::ostream& operator<<(std::ostream &lhs, const Input &rhs){
        lhs << "| txid: " << '\'' << rhs.txid << "\'\n"
            << "| vout: " << std::dec << rhs.index << '\n'
            << "| script_sig: " << rhs.script_sig << std::endl;
        if(!rhs.witness.empty()) lhs << "| witness: " << rhs.witness << std::endl;
        lhs << "| sequence: " << rhs.sequence << std::flush;
        return lhs;
    }
};

#endif

#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>

#include "bytes_helper.h"

class Script{
    friend std::ostream &operator<<(std::ostream&, const Script&);

    public:
        Script() = default;
        Script(Bytes_Helper &bh): Script() { parse(bh); }

        void parse(Bytes_Helper&);
        void parse_witness(Bytes_Helper&);
        bool empty() const { return stack.empty(); };
    private:
        std::vector<std::vector<unsigned char>> stack;
};

std::ostream &operator<<(std::ostream&, const Script&);

#endif

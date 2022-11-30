#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <iostream>

#include "input.h"
#include "output.h"
#include "script.h"
#include "bytes_helper.h"

class Transaction{
    friend std::ostream& operator<<(std::ostream&, const Transaction&);

    public:
        Transaction(uint32_t v, uint32_t l, unsigned char sw):
            version(v), locktime(l), segwit_flag(sw) {}
        Transaction(): Transaction(0, 0, 0) {}
        Transaction(const std::vector<unsigned char> &bytes):
            Transaction() { parse(bytes); }
        bool parse(const std::vector<unsigned char> &);

    private:
        uint32_t version;
        uint32_t locktime;
        unsigned char segwit_flag;
        std::vector<Input> inputs;
        std::vector<Output> outputs;
};

std::ostream& operator<<(std::ostream&, const Transaction&);

#endif

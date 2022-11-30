#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <iostream>

#include "input.h"
#include "output.h"
#include "script.h"
#include "bytes_helper.h"

class Transaction{
    friend std::ostream &operator<<(std::ostream&, const Transaction&);

    public:
        Transaction() : version(0), locktime(0), segwit_flag(0) { }
        Transaction(const std::vector<unsigned char> &bytes):
            Transaction() { parse(bytes); }

        void parse(const std::vector<unsigned char> &);

        explicit operator bool() { return !outputs.empty(); };

    private:
        uint32_t version;
        uint32_t locktime;
        unsigned char segwit_flag;
        std::vector<Input> inputs;
        std::vector<Output> outputs;
};

std::ostream& operator<<(std::ostream&, const Transaction&);

#endif

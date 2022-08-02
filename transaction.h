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
        Transaction() = default;
        bool parse(const std::vector<unsigned char> &);

    private:
        uint32_t version = 0;
        uint32_t locktime = 0;
        unsigned char segwit_flag = 0;
        std::vector<Input> inputs;
        std::vector<Output> outputs;
};

std::ostream& operator<<(std::ostream&, const Transaction&);

#endif

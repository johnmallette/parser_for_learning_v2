#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <iostream>

#include "input.h"
#include "output.h"
#include "script.h"
#include "bytes_helper.h"

class Transaction{
    public:
        Transaction(): version(0), locktime(0), segwit_flag(0){}
        bool parse(std::vector<unsigned char> &);
    private:
        uint32_t version;
        uint32_t locktime;
        unsigned char segwit_flag;
        std::vector<Input> inputs;
        std::vector<Output> outputs;

        friend std::ostream& operator<<(std::ostream&, Transaction&);
};

#endif

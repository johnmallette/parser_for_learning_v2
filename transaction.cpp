#include <iostream>
#include <iterator>
#include <stdexcept>

#include "transaction.h"

bool Transaction::parse(const std::vector<unsigned char> &bytes){
    Bytes_Helper helper{bytes.cbegin(), bytes.cend()};

    try{
        helper >> version;

        auto number_of_inputs = helper.read_compact_size();

        if(!number_of_inputs){
            helper >> segwit_flag;
            number_of_inputs = helper.read_compact_size();
        }

        while(number_of_inputs--) inputs.emplace_back(helper);

        for(auto i = helper.read_compact_size(); i > 0; --i)
            outputs.emplace_back(helper);

        if(segwit_flag) for(auto &i: inputs) i.witness.parse_witness(helper);

        helper >> locktime;

        helper.assert_end_of_bytes();
    } catch(std::runtime_error err){
        std::cerr << err.what() << std::endl;

        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream &lhs, const Transaction &rhs){
    lhs << "version: " <<  rhs.version << '\n' << std::endl
        << "inputs: " << rhs.inputs.size() << '\n' << std::endl;
    for(auto &i: rhs.inputs) lhs << i << '\n' << std::endl;
    lhs << "outputs: " << rhs.outputs.size() << '\n' << std::endl;
    for(auto &o: rhs.outputs) lhs << o << '\n' << std::endl;
    lhs << "locktime: " << rhs.locktime << std::endl;

    return lhs;
}

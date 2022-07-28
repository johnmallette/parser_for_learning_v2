#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>

#include "bytes_helper.h"

class Script{
    public:
        Script(){}
        void parse(Bytes_Helper&);
        void parse_witness(Bytes_Helper&);
        bool empty(){ return stack.empty(); };
    private:
        std::vector<std::vector<unsigned char>> stack;
        
        friend std::ostream& operator<<(std::ostream&, Script&);
};

#endif

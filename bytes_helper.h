#ifndef BYTES_HELPER_H
#define BYTES_HELPER_H

#include <stdexcept>
#include <vector>

extern std::runtime_error END_OF_BYTES;
extern std::runtime_error NOT_AT_END_OF_BYTES;

class Bytes_Helper{
    friend Bytes_Helper& operator>>(Bytes_Helper&, std::vector<unsigned char>&);

    template<typename T>
    friend Bytes_Helper& operator>>(Bytes_Helper&, T&);

    public:
        Bytes_Helper(std::vector<unsigned char>::const_iterator it,
                     std::vector<unsigned char>::const_iterator it_end):
                     current(it), end(it_end) {}
        
        std::vector<unsigned char>::size_type read_compact_size();
        void assert_end_of_bytes(){ if(!end_of_bytes()) throw NOT_AT_END_OF_BYTES;};
    private:
        std::vector<unsigned char>::const_iterator current;
        std::vector<unsigned char>::const_iterator end;
        void advance_current(std::vector<unsigned char>::size_type);
        bool end_of_bytes(){ return current == end;};
};

Bytes_Helper& operator>>(Bytes_Helper&, std::vector<unsigned char>&);

template<typename T>
Bytes_Helper& operator>>(Bytes_Helper&, T&);

std::ostream& operator<<(std::ostream&, const std::vector<unsigned char>&);
std::vector<unsigned char> reverse(const std::vector<unsigned char> &);

#endif

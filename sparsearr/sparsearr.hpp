#include <sdsl/int_vector.hpp>
#include <sdsl/vectors.hpp>
#include <string>
#include <vector>
#include <math.h>
#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>
#include "../bvselect/select.hpp"


class sparse_array {
public:
    sparse_array(uint64_t size, uint64_t num_filled);
    sparse_array(uint64_t size);
    ~sparse_array();
    void append(std::string elem, uint64_t pos);
    bool get_at_rank(uint64_t r, std::string& elem);
    bool get_at_index(uint64_t r, std::string& elem);
    uint64_t num_elem_at(uint64_t r);
    uint64_t size();
    uint64_t num_elem();
    void save(std::string& fname);
    void load(std::string& fname);
    
    sdsl::bit_vector * bv;
    std::vector<std::string> ar;
    rank_support * rs;
    select_support * ss;
};


sparse_array::sparse_array(uint64_t size, uint64_t num_filled) {
    //this method just exists for generating really big bit vectors
    //and putting stuff in them for testing.
    //updating rs on append is too slow for big million element vectors.

    bv = new sdsl::bit_vector(size,0);
    for (int i = 0; i < (num_filled); i++) {
        //std::cout << i*(size/num_filled) << std::endl;
        (*bv)[i*(size/num_filled)] = 1;
    }
    rs = new rank_support(bv);
    ss = new select_support(rs);
    std::vector<std::string> r;

    for (int i = 0; i < num_filled; i++) {
        std::string a = "n";
        r.push_back(a);
    }
    //std::cout << ar.size() << std::endl;
    ar = r;


}

sparse_array::sparse_array(uint64_t size) {

    bv = new sdsl::bit_vector(size,0);
    rs = new rank_support(bv);
    ss = new select_support(rs);
    std::vector<std::string> ar;

}
sparse_array::~sparse_array() {


}

void sparse_array::append(std::string elem, uint64_t pos) {
    (*bv)[pos] = 1;
    ar.push_back(elem);
    rs = new rank_support(bv);

}


bool sparse_array::get_at_rank(uint64_t r, std::string& elem) {
    if (r < ar.size()) {
        elem = ar[r];
        return true;
    }
    return false;



}
bool sparse_array::get_at_index(uint64_t r, std::string& elem) {
    if ((*bv)[r] == 0) {
        return false;
    }

    elem = ar[rs->rank1(r)-1];
    return true;

}

uint64_t sparse_array::num_elem_at(uint64_t r) {
    return rs->rank1(r);
    

}

uint64_t sparse_array::size() {
    return bv->size();

}

uint64_t sparse_array::num_elem() {
    return rs->rank1(bv->size());

}

void sparse_array::load(std::string& fname) {
    ss->load(fname);
    rs->load(fname);



} 

void sparse_array::save(std::string& fname) {
    rs->save(fname);
}




#include <sdsl/vectors.hpp>
#include <string>
#include <vector>
#include <math.h>
#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>
#include "../bvrank/rank.hpp"


class select_support {
public:
    
    select_support(rank_support * r);
    select_support(std::string& fname);
    ~select_support();
    uint64_t select1(uint64_t i);
    uint64_t overhead();
    void save(std::string& fname);
    select_support load(std::string& fname);

//private:
    rank_support * R;
    uint64_t select1_helper(uint64_t i, uint64_t k);
};

select_support::select_support(rank_support * r) {
    R = r;
}

select_support::select_support(std::string& fname) {
    R = new rank_support(fname);
}

select_support::~select_support() {


}

uint64_t select_support::select1_helper(uint64_t i, uint64_t k) {
    auto j = R->rank1(k);

    //std::cout << "i,k,j = " << i << "," << k << "," << j << std::endl;
    if (j == i) {
        if ((*(R->B))[k]) {
            return k;
        }

    } else if (j > i) {
        //std::cout << "asserting that j > i" << std::endl;
        return select1_helper(i,(k/2));

    } else {
        //std::cout << "asserting i > j" << std::endl;
        return select1_helper(i,k+(k/2));
    }
}

uint64_t select_support::select1(uint64_t i) {
    int dex = R->B->size()/2;
    return select1_helper(i,dex);
}



uint64_t select_support::overhead() {
    return R->overhead();
}

void select_support::save(std::string& fname) {
    R->save(fname);



}

select_support select_support::load(std::string& fname) {
    R->load(fname);

}






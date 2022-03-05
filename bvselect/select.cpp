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

private:
    rank_support * R;
    uint64_t select1_helper(uint64_t i, uint64_t k);
};

select_support::select_support(rank_support * r) {
    R = r;
}

select_support::select_support(std::string& fname) {


}

select_support::~select_support() {


}

uint64_t select_support::select1_helper(uint64_t i, uint64_t k) {
    auto j = R->rank1(k);
    if (j == i) {
        if ((*(R->B))[k]) {
            return k;
        } else {
            return select1_helper(i,k-1);
        }

    } else if (j > i) {
        return select1_helper(i,(k/2));

    } else { 
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



}

select_support select_support::load(std::string& fname) {



}




int main() {
    sdsl::bit_vector b(16,0);
    b[0] = 1;
    b[3] = 1;
    b[5] = 1;
    b[6] = 1;
    b[7] = 1;
    b[9] = 1;
    b[12] = 1;
    b[14] = 1;
    //let me test something about how get_int works:
    sdsl::bit_vector c(128,0);
    for (int i = 64; i < 128; i++) {
        c[i] = 1;
    }
    rank_support rs = rank_support(&b);
    //rs.print_B();
    //rs.print_Rs();
    //rs.print_Rb();
    std:: cout << rs.rank1(8) << std::endl;

    std:: cout << rs.overhead() << std::endl;

    select_support ss = select_support(&rs);
    //std::cout << ss.select1(2) << std::endl;


 


    return 0;
}


#include <sdsl/int_vector.hpp>
#include <sdsl/vectors.hpp>
#include <string>
#include <vector>
#include <math.h>
#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>

class rank_support {
public:
    
    rank_support(sdsl::bit_vector * b);
    ~rank_support();
    uint64_t rank1(uint64_t i);
    uint64_t overhead();
    void save(std::string& fname);
    rank_support load(std::string& fname);
    void print_Rs();
    void print_Rb();
    void print_B();

private:
    sdsl::bit_vector * B;
    sdsl::int_vector<> Rs;
    sdsl::int_vector<> Rb;
    uint64_t Rs_width;
    uint64_t Rb_width;
    uint64_t Rs_blocksize;
    uint64_t Rb_blocksize;

};

rank_support::rank_support(sdsl::bit_vector * b) {
    // first we need to make Rs, Rb
    // we do this in 2n time.
    //B = sdsl::bit_vector (b.size(),0);
    //for (int i = 0; i < b.size(); i++) {
    //    B[i] = b[i];
    //}
    B = b;
    Rs_blocksize = (log2(B->size())/2);
    Rb_blocksize = (pow(log2(B->size()),2)/2);
    Rs_width = (log2(B->size())/2)+64;
    Rb_width = (log2((pow(log2(B->size()),2)/2)))+64;

    Rs = sdsl::int_vector<0> (B->size()/(pow(log2(B->size()),2)/2),0,Rs_width);
    Rb = sdsl::int_vector<0> (B->size()/(log2(B->size())/2),0,Rb_width);
    std::cout << Rs.size() << std::endl;

    int prior_Rs = 0;
    int prior_Rb = 0;
    
    for (int i = 0; i < B->size(); i++) {
        int Rb_index = i/(log2(B->size())/2);
        int Rs_index = (i/(pow(log2(B->size()),2)/2));
        std::cout << Rs_index << std::endl;
        if ((*B)[i]) {
            //print_Rs();
            Rs[Rs_index+1] = Rs[Rs_index+1] + 1 ;
            Rb[Rb_index+1] = Rb[Rb_index+1] + 1;
            //print_Rs();
        }
        if (i == 0 || Rs_index != prior_Rs) {
           Rb[Rb_index] = 0;

        } else if (Rb_index != prior_Rb) {

            Rb[Rb_index] =Rb[Rb_index] + Rb[prior_Rb];
        }
        prior_Rs = Rs_index;
        prior_Rb = Rb_index;
    }

}


rank_support::~rank_support() {

}

void rank_support::print_B() { 
    for (int i = 0; i < B->size(); i++) {
        std::cout << (*B)[i] << " ";
    }
    std::cout << std::endl;
}

void rank_support::print_Rs() { 
    for (int i = 0; i < Rs.size(); i++) {
        std::cout << Rs[i] << " ";
    }
    std::cout << std::endl;
}

void rank_support::print_Rb() { 
    for (int i = 0; i < Rb.size(); i++) {
        std::cout << Rb[i] << " ";
    }
    std::cout << std::endl;
}

uint64_t rank_support::rank1(uint64_t i) {
   uint64_t Rb_block_size = (log2(B->size())/2);
   int Rb_index = i/(log2(B->size())/2);
   int Rs_index = i/(pow(log2(B->size()),2)/2);

   int i_Rb_block = Rb_index * (log2(B->size())/2);

   print_B();
   //we want to get the machine word starting at the beginning of i's Rb_index
   uint64_t j = B->get_int(i_Rb_block);
   //std::cout << std::bitset<64>(j) << std::endl;
   j = j << 64 - (Rb_block_size - 1 + (i % Rb_block_size));
   //std::cout << std::bitset<64>(j) << std::endl;
   return Rs[Rs_index] + Rb[Rb_index] + std::popcount(j);
 

}

uint64_t rank_support::overhead() {
    return (Rs.bit_size() + Rb.bit_size());


}

void save(std::string& fname) {


}

rank_support rank_support::load(std::string& fname) {
    std::cout << Rb.size() << std::endl;
    return *this;

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
    std:: cout << rs.rank1(12) << std::endl;
    std:: cout << rs.overhead() << std::endl;
    




return 0;
} 

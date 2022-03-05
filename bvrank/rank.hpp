#include <sdsl/int_vector.hpp>
#include <sdsl/vectors.hpp>
#include <string>
#include <vector>
#include <math.h>
#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <fstream>

class rank_support {
public:
    
    rank_support(sdsl::bit_vector * b);
    rank_support(std::string& fname);
    ~rank_support();
    uint64_t rank1(uint64_t i);
    uint64_t overhead();
    void save(std::string& fname);
    rank_support load(std::string& fname);
    void print_Rs();
    void print_Rb();
    void print_B();

//private:
    sdsl::bit_vector * B;
    sdsl::int_vector<0> Rs;
    sdsl::int_vector<0> Rb;
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
    Rs_width = (log2(B->size())/2) + (std::fmod(log2(B->size()),2) != 0)+1;
    Rb_width = (log2((pow(log2(B->size()),2)/2)))+ + (std::fmod(log2((pow(log2(B->size()),2))),2) != 0);

    Rs = sdsl::int_vector<0> (B->size()/(pow(log2(B->size()),2)/2),0,Rs_width);
    Rb = sdsl::int_vector<0> (B->size()/(log2(B->size())/2),0,Rb_width);
    
    
    //Rs = sdsl::int_vector<0> (B->size()/(pow(log2(B->size()),2)/2),0);
    //Rb = sdsl::int_vector<0> (B->size()/(log2(B->size())/2),0);
    

    int prior_Rs = 0;
    int prior_Rb = 0;
    
    for (int i = 0; i < B->size(); i++) {
        int Rb_index = i/(log2(B->size())/2);
        int Rs_index = (i/(pow(log2(B->size()),2)/2));
        if ((*B)[i]) {
            if (Rs_index+1 != Rs.size()) {
                Rs[Rs_index+1] = Rs[Rs_index+1] + 1 ;
            }
            if (Rb_index+1 != Rb.size()) {

                Rb[Rb_index+1] = Rb[Rb_index+1] + 1;
            }
        }
        if (i == 0 || Rs_index != prior_Rs) {
           Rb[Rb_index] = 0;

        } else if (Rb_index != prior_Rb) {
            Rb[Rb_index] = Rb[Rb_index] + Rb[prior_Rb];
        }
        prior_Rs = Rs_index;
        prior_Rb = Rb_index;
    }

}

rank_support::rank_support(std::string& fname) {


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

void rank_support::save(std::string& fname) {
    //what we will do is store B,Rs,Rb in order
    std::ofstream f(fname);
    B->serialize(f);
    //f << std::endl;
    Rs.serialize(f);
    Rb.serialize(f);
}

rank_support rank_support::load(std::string& fname) {
    sdsl::bit_vector b;
    std::ifstream f(fname);
    b.load(f);
    sdsl::int_vector<> new_rs;
    new_rs.load(f);
    sdsl::int_vector<> new_rb;
    new_rb.load(f);
    Rb = new_rb;
    Rs = new_rs;
    B = &b;
    return *this;
    
}







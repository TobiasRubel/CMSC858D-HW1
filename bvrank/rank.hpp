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


int ceil_log2(int x) {
  //this code taken from
  //https://stackoverflow.com/questions/3272424/compute-fast-log-base-2-ceiling/51351885#51351885
  //thanks to dgobbi for the fast code.
  static const unsigned long long t[6] = {
    0xFFFFFFFF00000000ull,
    0x00000000FFFF0000ull,
    0x000000000000FF00ull,
    0x00000000000000F0ull,
    0x000000000000000Cull,
    0x0000000000000002ull
  };

  int y = (((x & (x - 1)) == 0) ? 0 : 1);
  int j = 32;
  int i;

  for (i = 0; i < 6; i++) {
    int k = (((x & t[i]) == 0) ? 0 : j);
    y += k;
    x >>= k;
    j >>= 1;
  }

  return y;
}

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
    uint64_t Rb_numblocks;
    uint64_t Rs_numblocks;
    int n;

};

rank_support::rank_support(sdsl::bit_vector * b) {
    // first we need to make Rs, Rb
    // we do this in 2n time.
    //B = sdsl::bit_vector (b.size(),0);
    //for (int i = 0; i < b.size(); i++) {
    //    B[i] = b[i];
    //}
    B = b;
    n = B->size();
    //q = x/y + (x % y != 0);
    Rb_blocksize = ceil_log2(n);
    Rs_blocksize = (pow(Rb_blocksize,2));
    Rs_width = ceil_log2(Rs_blocksize)+1;
    Rb_width = ceil_log2(Rb_blocksize)+1;

    //Rs_width = 64;
    //Rb_width = 64;



    Rb_numblocks = n/Rb_blocksize + (n % Rb_blocksize != 0);
    Rs_numblocks = n/Rs_blocksize + (n % Rs_blocksize != 0);

    //std::cout << "Rb_blocksize = " << Rb_blocksize << std::endl;
    //std::cout << "Rs_blocksize = " << Rs_blocksize << std::endl;
    //std::cout << "Rs_width = " << Rs_width << std::endl;
    //std::cout << "Rb_width = " << Rb_width << std::endl;
    //std::cout << "Rs_numblocks = " << Rs_numblocks << std::endl;
    //std::cout << "Rb_numblocks = " << Rb_numblocks << std::endl;

    Rs = sdsl::int_vector<0> (Rs_numblocks,0,Rs_width);
    Rb = sdsl::int_vector<0> (Rb_numblocks,0,Rb_width);
    
    
    //Rs = sdsl::int_vector<0> (B->size()/(pow(log2(B->size()),2)/2),0);
    //Rb = sdsl::int_vector<0> (B->size()/(log2(B->size())/2),0);
    

    int prior_Rs = 0;
    int prior_Rb = 0;
    
    for (int i = 0; i < B->size(); i++) {
        int Rb_index = i/Rb_blocksize;
        int Rs_index = i/Rs_blocksize;

        if ((*B)[i]) {
            if (Rs_index+1 != Rs.size()) {
                Rs[Rs_index+1]++ ;
            }
            if (Rb_index+1 != Rb.size()) {
                Rb[Rb_index+1]++;
            }
        }
        if (Rb_index != prior_Rb) {
            Rb[Rb_index] += Rb[prior_Rb];         

        }
        if (i == 0 || Rs_index != prior_Rs) {
           Rs[Rs_index] += Rs[prior_Rs];
           Rb[Rb_index] = 0;
        }
        prior_Rs = Rs_index;
        prior_Rb = Rb_index;
    }

}

rank_support::rank_support(std::string& fname) {
    //copying code is bad, but I gave into temptation.
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
    n = B->size();
    //q = x/y + (x % y != 0);
    //
    Rb_blocksize = ceil_log2(n);
    Rs_blocksize = (pow(Rb_blocksize,2));
    Rs_width = ceil_log2(Rs_blocksize)+1;
    Rb_width = ceil_log2(Rb_blocksize)+1;

    //Rs_width = 64;
    //Rb_width = 64;



    Rb_numblocks = n/Rb_blocksize + (n % Rb_blocksize != 0);
    Rs_numblocks = n/Rs_blocksize + (n % Rs_blocksize != 0);

    //std::cout << "Rb_blocksize = " << Rb_blocksize << std::endl;
    //std::cout << "Rs_blocksize = " << Rs_blocksize << std::endl;
    //std::cout << "Rs_width = " << Rs_width << std::endl;
    //std::cout << "Rb_width = " << Rb_width << std::endl;
    //std::cout << "Rs_numblocks = " << Rs_numblocks << std::endl;
    //std::cout << "Rb_numblocks = " << Rb_numblocks << std::endl;

    Rs = sdsl::int_vector<0> (Rs_numblocks,0,Rs_width);
    Rb = sdsl::int_vector<0> (Rb_numblocks,0,Rb_width);
    
    
    //Rs = sdsl::int_vector<0> (B->size()/(pow(log2(B->size()),2)/2),0);
    //Rb = sdsl::int_vector<0> (B->size()/(log2(B->size())/2),0);
    

    int prior_Rs = 0;
    int prior_Rb = 0;
    
    for (int i = 0; i < B->size(); i++) {
        int Rb_index = i/Rb_blocksize;
        int Rs_index = i/Rs_blocksize;

        if ((*B)[i]) {
            if (Rs_index+1 != Rs.size()) {
                Rs[Rs_index+1]++ ;
            }
            if (Rb_index+1 != Rb.size()) {
                Rb[Rb_index+1]++;
            }
        }
        if (Rb_index != prior_Rb) {
            Rb[Rb_index] += Rb[prior_Rb];         

        }
        if (i == 0 || Rs_index != prior_Rs) {
           Rs[Rs_index] += Rs[prior_Rs];
           Rb[Rb_index] = 0;
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
   int Rb_index = i/Rb_blocksize;
   int Rs_index = i/Rs_blocksize;

   int i_Rb_block = (Rb_index) * Rb_blocksize;

   //print_B();
   //print_Rs();
   //print_Rb();
   //std::cout << "RB index of i = " << Rb_index << std::endl;
   //std::cout << "RS index of i = " << Rs_index << std::endl;
   //std::cout << "RB block of i = " << i_Rb_block << std::endl;

   //we want to get the machine word starting at the beginning of i's Rb_index
   uint64_t j = B->get_int(i_Rb_block);//,i%Rb_blocksize);
   //std::cout << std::bitset<64>(j) << std::endl;
   //std::cout << "shift offset = " << (i % Rb_blocksize) << std::endl;
   j = j << (64 - 1  -  (i % Rb_blocksize));
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
    Rs.serialize(f);
    Rb.serialize(f);
}

rank_support rank_support::load(std::string& fname) {
    sdsl::bit_vector b;
    std::ifstream f(fname);
    b.load(f);
    B = &b;
    sdsl::int_vector<> new_rs;
    new_rs.load(f);
    Rs = new_rs;
    sdsl::int_vector<> new_rb;
    new_rb.load(f);
    Rb = new_rb;
    return *this;
    
}








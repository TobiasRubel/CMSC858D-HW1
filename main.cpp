#include <sdsl/int_vector.hpp>
#include <sdsl/vectors.hpp>
#include <string>
#include <vector>
#include <math.h>
#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>
#include "sparsearr/sparsearr.hpp"
#include <ctime>


int main() {

      

  //first let's create arrays of 1000, 10000, 100000, 1000000
  //with sparsity 1, 5, 10.
  sparse_array a1s1(1000,10);

  sparse_array a1s2(1000,50);
  sparse_array a1s3(1000,100);

  sparse_array a2s1(10000,100);
  sparse_array a2s2(10000,500);
  sparse_array a2s3(10000,1000);

  sparse_array a3s1(100000,1000);
  sparse_array a3s2(100000,5000);
  sparse_array a3s3(100000,10000);

  sparse_array a4s1(1000000,10000);
  sparse_array a4s2(1000000,50000);
  sparse_array a4s3(1000000,100000);

  //lets create some lists to store things
  //
  std::vector<sparse_array> ars{a1s1, a1s2, a1s3,a2s1, a2s2, a2s3, a3s1, a3s2, a3s3, a4s1, a4s2, a4s3};

  std::vector<std::string> nms{"a1s1", "a1s2", "a1s3", "a2s1", "a2s2","a2s3", "a3s1", "a3s2", "a3s3", "a4s1", "a4s2", "a4s3"};

 
  
  //run experiments
  //************* Task 1 *************
  
  std::cout <<"rank1" << std::endl;
  for (int i = 0; i < ars.size(); i++) {
      auto nm = nms[i];
      auto a  = ars[i];
      clock_t start = clock();

      for (int i = 0; i < 1000; i++) {
        a.rs->rank1(i);
      }


      clock_t end = clock();

      std::cout << nm << " " << float(end - start) / CLOCKS_PER_SEC << "\n";
    
   }

  std::cout <<"rs overhead" << std::endl;
  for (int i = 0; i < ars.size(); i++) {
      auto nm = nms[i];
      auto a  = ars[i];

           
      std::cout << nm << " " <<  a.rs->overhead() << "\n";

    
   }
  //************* Task 2 *************
  //
  //since select support doesn't work when you call it on numbers of 1s not in the bit vector
  //(which we would want to guard against in a real-world code), we need to just run it on a
  //subset of our data
std::vector<sparse_array> ars_s{a2s3, a3s2, a4s1};

  std::vector<std::string> nms_s{"a2s3", "a3s2", "a4s1"};


 
   std::cout <<"select1" << std::endl;
  for (int i = 0; i < ars_s.size(); i++) {
      auto nm = nms_s[i];
      auto a  = ars_s[i];
      clock_t start = clock();

      for (int i = 1; i < 20; i++) {
        a.ss->select1(i);
      }


      clock_t end = clock();

      std::cout << nm << " " << float(end - start) / CLOCKS_PER_SEC << "\n";
    
   }

  std::cout <<"ss overhead" << std::endl;
  for (int i = 0; i < ars.size(); i++) {
      auto nm = nms[i];
      auto a  = ars[i];

           
      std::cout << nm << " " <<  a.ss->overhead() << "\n";

    
   }
  //************* Task 3 *************
  
  //now let's test different member functions 
  //we will issue 1000 get_at_rank calls, 1000 get_at_index calls, and 1000 num_elem_at calls.
  //
  //
  std::cout <<"get_at_rank" << std::endl;

  for (int i = 0; i < ars.size(); i++) {
      auto nm = nms[i];
      auto a  = ars[i];
      clock_t start = clock();

      for (int i = 0; i < 1000; i++) {
        std::string s = "";
        a.get_at_rank(i,s);
      }


      clock_t end = clock();

      std::cout << nm << " " << float(end - start) / CLOCKS_PER_SEC << "\n";
    
   }

  std::cout <<"get_at_index" << std::endl;

  for (int i = 0; i < ars.size(); i++) {
      auto nm = nms[i];
      auto a  = ars[i];
      //std::cout << a.ar.size() << std::endl;
      //std::cout << (a.bv)->size() << std::endl;
      clock_t start = clock();

      for (int i = 0; i < 1000; i++) {
        std::string s = "n";
        //std::cout << nm << std::endl;
        //std:: cout << "running get at index: " << i <<"," << s << std::endl;
        a.get_at_index(i,s);
      }


      clock_t end = clock();

      std::cout << nm << " " << float(end - start) / CLOCKS_PER_SEC << "\n";
    
   }

  std::cout <<"num_elem_at" << std::endl;

  for (int i = 0; i < ars.size(); i++) {
      auto nm = nms[i];
      auto a  = ars[i];
      //std::cout << a.ar.size() << std::endl;
      //std::cout << (a.bv)->size() << std::endl;
      clock_t start = clock();

      for (int i = 0; i < 1000; i++) {
        a.num_elem_at(i);
      }


      clock_t end = clock();

      std::cout << nm << " " << float(end - start) / CLOCKS_PER_SEC << "\n";
    
   }


   return 0;
}


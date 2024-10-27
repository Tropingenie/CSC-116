#include <iostream>
#include <vector>
#include <string>

void print_vector(std::vector<int> const &V) {
    for(auto x : V) {
        std::cout << x << ' ';
    }
}

void receive_input(std::vector<int>& input_set, std::vector<int>& set_1,std::vector<int>& set_2){
    int n {};
    while (std::cin >> n) input_set.push_back(n);//Creates a vector of ALL the inputs

    //I'd use a vector of vectors, but this is not a program for the general case
    //IE, I know there will be two data sets, max
    bool seen_negative_one {false};
    for (auto i:input_set){
        if (i == -1) seen_negative_one = true;
        else if (seen_negative_one) set_2.push_back(i);
        else set_1.push_back(i);
    }
    //data sets are set, let's check if they were initialised correctly (ie, debug)
    print_vector(set_1); std::cout << std::endl; print_vector(set_2); std::cout << std::endl;
}

bool delete_v_from_u (const std::vector<int>& v, std::vector<int>& u){//deletes the first instance of v from u, if there is any. Return is true if v was found
// (and, thus, deleted) in u, and false if it wasn't.
    
    //We want to check if set_1 appears in set_2
    //Check if v.at(i) == u.at(i) && v.at(i+1) == v.at(i+1) && ... && v.at(i+n) == u.at(i+n) where n = v.size()
    //Then, return the final address.
    std::cout << "Entered delete_v_from_u()" << std::endl;
    unsigned int address_to_start_delete {0};
    bool v_is_not_u {true};
    bool not_finished_yet {true};
    
    while (v_is_not_u && not_finished_yet){//this loop should run until a value of v is found within u, unless all of u has been lokked through
      std::cout << "Vector is "; print_vector(u); std::cout << std::endl;
      std::cout << "Entered while (v_is_not_u)" << std::endl;
      std::cout << "Currently, v_is_not_u returns " << v_is_not_u << std::endl;
      std::cout << "u.at() is " << u.at(address_to_start_delete) << std::endl;
      std::cout << "v.at(0) is " << v.at(0) << std::endl;
      //First, we need to step through u until v.at(0) shows up
      while (u.at(address_to_start_delete) != v.at(0) && not_finished_yet && address_to_start_delete < u.size()){
       address_to_start_delete++;
       std::cout << "Currently comparing " << u.at(address_to_start_delete) << " to " << v.at(0) << std::endl;
       }
       std::cout << "address_to_start_delete is " << address_to_start_delete << std::endl;
      if (address_to_start_delete >= u.size()-1) {
      not_finished_yet = false;
      break;//ie, if v never appears in u, return false
      }
      
      //Now we need to check if everything beyond address_to_start_delete matches v
      for (unsigned int i {0}; i < v.size(); i++){
        std::cout << "Entered for (unsigned int i {0}; i < v.size(); i++). Currently, " << i+1 << " out of " << v.size() << " interations in." << std::endl;
        std::cout << "v.at(i) = " << v.at(i) << std::endl;
        std::cout << "u.at( ) = " << u.at(address_to_start_delete + i) << std::endl;
        if (v.at(i) == u.at(address_to_start_delete + i)){ 
          v_is_not_u = false;
          }
        else {
        v_is_not_u = true;
        break;
        }
      }
      std::cout << "v_is_not_u returns " << v_is_not_u << std::endl;
      if (!v_is_not_u){//if v is not u, then delete all the elements from address_to_start_delete to address_to_start_delete + v.size()-1
        std::cout << "Entered if (v_is_not_u)" << std::endl;
        
        for (auto i {address_to_start_delete}; i < address_to_start_delete +v.size(); i++){
          std::cout<<"Vecotr is "; print_vector(u);std::cout<<std::endl;
          std::cout << "Erasing u.at(" << i <<") which is " << u.at(address_to_start_delete) << std::endl;
          u.erase(u.begin()+address_to_start_delete);//since, in deleting the entry at this address, the next entry to be deleted will also be at this
          //address. Confusing, but it works so don't mess with this.
        }
      }
      address_to_start_delete++;
    }
    //If the input data, v, contains only one element, than the last element of u is not parsed by the function. However, the
    //following line fixes that bug, such that the function behaves as intended.
    if (v.size() == 1) if (u.at(u.size()-1) == v.at(0)) u.erase(u.begin()+u.size()-1);
    return not_finished_yet;
}//This is a messy function, but it works as intended.


int main(){
    std::vector<int> input_set{}; std::vector<int> set_1{}; std::vector<int> set_2{};
    
    receive_input(input_set, set_1, set_2);
  std::vector<int> set_2_backup{set_2};

    //Now that we have our input down, we need to erase all instances of vector 1 in vector 2
    try{
      while(delete_v_from_u(set_1,set_2)){
        std::cout << "Iterating..." << std::endl;
        print_vector(set_2); std::cout << std::endl;
      }
    }catch (std::out_of_range & e){std::cout << std::endl << "Out of range has been thrown, ie end of vector 2 reached" << std::endl;}
    
    
    std::cout << "Done." << std::endl;
    print_vector(set_2_backup); std::cout << std::endl;
    print_vector(set_2); std::cout << std::endl;


    return 0;
}
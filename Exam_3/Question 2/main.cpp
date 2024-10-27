#include <iostream>
#include <string>
/* Code below written by Benjamin Lyne */
class Soup{
protected:
    std::string name;
public:
    std::string main_ingredient;
    std::string get_name(){
        return name;
    }
};
/* Above code written by Benjamin Lyne */
class Borscht: public Soup{
public:
    Borscht(){
        name = "Borscht";
        main_ingredient = "Beets";
    }
};
class Chowder: public Soup{
public:
    Chowder(std::string chowder_type){
        name = chowder_type + " Chowder";
        main_ingredient = chowder_type;
    }
};
class Minestrone: public Soup{
public:
    Minestrone(){
        name = "Minestrone";
        main_ingredient = "Tomatoes";
    }
};
void print_soup(Soup& S){
    std::cout << "Soup: " << S.get_name() << std::endl;
    std::cout << "Main ingredient: " << S.main_ingredient << std::endl;
}
int main(){
    Borscht B; Chowder C1("Clam"); Chowder C2("Corn");
    //Chowder C3;//This would cause a compile error if it was uncommented, because there is no default constructor
                 //ie, an argument is expected but none are given.
    Minestrone M;
    print_soup(B); print_soup(C1); print_soup(C2); print_soup(M); return 0;
}
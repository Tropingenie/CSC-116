#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <iomanip>

class list_node {
    std::string data;
    // TODO: change type to smart pointer
    std::shared_ptr<list_node> next;

public:
    list_node(std::string _st): data {_st}, next {nullptr} {};
    list_node() {};

    // TODO: update return type
    std::shared_ptr<list_node> get_next() {
        return next;
    };

    // TODO: update argument type
    void set_next(std::shared_ptr<list_node> n) {
        next = n;
    }
    void set(std::string _st) {
        data = _st;
    }
    std::string& get() {
        return data;
    }
};

class my_list {
    // TODO: change type to smart pointer
    std::shared_ptr<list_node> head;

    // TODO: change type to smart pointer
    std::shared_ptr<list_node> tail;

public:
    my_list() {
        head = nullptr;
        tail = nullptr;
    };

    /*
     * TODO: update destructor; what can we remove?
     * - Remember that one of the main goals of smart pointers is to free
     * the programmer from the responsibility of releasing memory!
    */
    ~my_list() { };
    bool empty() {
        return head == nullptr;
    };
    void push_back(std::string str) {
        /*
         * TODO: change type to smart pointer
         * - still need to allocate new node, and initialize it
        */
        // allocate new node, and initialize it
        auto node = std::make_shared<list_node>(str);

        if (empty()) {
            tail = node;
            head = node;
        } else {
            tail->set_next(node);
            tail = node;
        }
    };

    void push_front(std::string str) {
        /*
         * TODO: change type to smart pointer
         * - still need to allocate new node, and initialize it
        */
        // allocate new node and initialize it
        auto node = std::make_shared<list_node>(str);

        if (empty()) {
            tail = node;
            head = node;
        } else {
            node->set_next(head);
            head = node;
        }
    };

    /*
     * TODO: implement this function.
     * - Print the strings in the order they appear in the list, separated by " -> "
     * - Must iterate through entire list to get each string in order.
     *
     * Output example: "Tokyo -> Ottawa -> Washington -> London -> Madrid
    */
    void print() {
        // student implements
		auto current = head;
		
		while (current != nullptr){
			std::cout << current -> get();
			current = current -> get_next();
			if (current != nullptr){
				/*If current after following the pointer to the next element IS the nullptr,
				then it stands to reason that the previous element printed was the last one,
				thus there is no need to print the '->'. I opted to go with a "!= nullptr to
				eliminate an extraneous else statement.*/
				std::cout << " -> ";
			}
		}
    };

    /*
     * TODO: implement this function.
     * - Return true if the given string is in the list but false otherwise.
     * - Must iterate through entire list to look for given string.
    */
    bool exists(std::string str) {
        // student implements
		auto current = head;
		
		while (current != nullptr){
			if ((*current).get() == str) return true;
			else current = current -> get_next();
		}
		return false;
    }

    std::string &front() {
        // retrieve the string at the front of the list
        return head->get();
    };

    std::string &back() {
        // retrieve the string at the back of the list
        return tail->get();
    };

};


int main() {
    my_list list;

    std::string line;
    // read one string at a time and insert at the end of the list
    while (getline(std::cin, line)) {
        list.push_back(line);
    }

    std::cout << "Capitals:" << std::endl;

    list.print();

    std::cout << std::endl;

    std::cout << std::boolalpha << "is Ottawa in the list? "    << list.exists("Ottawa") << std::endl;
    std::cout << std::boolalpha << "is Brazilia in the list? "  << list.exists("Brazilia") << std::endl;

    // Let us test an empty list

    my_list emptyList;

    std::cout << "Print empty list:" << std::endl;

    emptyList.print();

    std::cout << std::boolalpha << "is anything in the list? "    << list.exists("") << std::endl;
}

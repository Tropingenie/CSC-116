/* linkedlist.hpp
   CSC 116 - Fall 2019

   B. Bird - 08/10/2019
   
   Modified: 
   Benjamin Lyne
   V00914888
   2019-12-13
   
   Task: Implement a singly linked list class
   
   Notes:
		This version attempts a number of simplifications to the code. This means
		there are some things that should be kept in mind while editing it:
		
		Firstly, the use of the prefix imcrement operator. I have attempted to abstract
		the behaviour of smart pointers into something similar to an iterator. The framework
		could be used later to properly implement iterators into this. Make sure to
		read over and understand the private functions that make this "conversion" before
		attempting to edit any of the public member functions.
		
		Secondly, the internal behaviour of this linked list: Though it is only singly linked,
		I found having a tail pointer to be quite useful for a few operations. There is also a
		"list_size" variable. Consider updating one or both of these if you implement other
		functions (like .erase() )
		
		Thirdly, recursion, or more accurately "internal function calls." There are a number
		of functions that call another private member function to do a task. Some of these use
		recursion, however their primary purpose is to "clean up" or "pseudo-decouple" the
		member functions. Make sure you read over and understand these private functions
		before attempting to edit any code that uses them.
*/

#include <functional>
#include <stdexcept>
#include <memory>
#include <initializer_list>
#include <iterator>//for rbegin() and rend()

//Important note: You may add other #include directives, but you are NOT
//permitted to use or include ANY of the standard collections, including
//std::list, std::vector, std::set, std::map, std::unordered_set, 
//std::forward_list, std::unordered_map, std::array 
//(or any derivatives thereof, such as std::queue)
//If you do so, your assignment will receive a mark of zero.
//You ARE permitted to use the specialized std::initializer_list collection,
//as indicated below in the constructor.

template<typename T>
class LinkedList{
public:
    /* Default constructor:
       Construct the list to be empty (size = 0)
    */
    LinkedList(){
        /* Your code here */
		head = nullptr;
		tail = nullptr;
		list_size = 0;
    }
    /* Initializer list constructor:
       Construct the list to contain all of the elements in the
       provided initializer list. Recall that you can use a for-each
       loop to iterate over initializer_list objects. */
    LinkedList( std::initializer_list<T> initial_contents ): LinkedList{} {
        /* Your code here */
		for(auto el = initial_contents.begin(); el != initial_contents.end(); el++){
			push_back(*el);
		}
    }
    /* Copy constructor:
       Construct the list to contain all of the elements in the provided
       other list. Note that a "deep copy" is needed, such that when the 
       operation completes there are two separate, independent lists.
    */
    LinkedList( LinkedList<T> const& other_list ): LinkedList{} {
		//Note that while we can use push_back and code that looks exactly like iterators (but isn't), since we want to use push_front
		//and not push_back, I will use recursion here.
		copy_list(other_list.head);
    }
    /* Destructor */
    ~LinkedList(){
        /* Your code here */
		//Since we are using smart pointers, the destructor is trivial
    }

    /* is_empty()
       Returns true if the list contains zero elements and false otherwise.
    */
    bool is_empty() const{
        /* Your code here */
		if (list_size == 0) return true;
		else return false;
    }

    /* size()
       Returns the number of elements in the list.
    */
    unsigned int size() const{
        /* Your code here */
		return list_size;
    }

    /* first() - Version 1
       If the list has at least one element, returns a reference to the first
       element (such that the result can be modified by the caller).
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T& first(){
        /* Your code here */
		if (is_empty()) throw std::runtime_error ("Error: Attempted to retrieve first element of an empty list");
		return head -> value;
    }

    /* first() - Version 2
       If the list has at least one element, returns a const reference to the
       first element.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T const& first() const {
        /* Your code here */
		if (is_empty()) throw std::runtime_error ("Error: Attempted to retrieve first element of an empty list");
		return head -> value;
    }
    
    /* last() - Version 1
       If the list has at least one element, returns a reference to the last
       element (such that the result can be modified by the caller).
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T& last(){
        /* Your code here */
		if (is_empty()) throw std::runtime_error ("Error: Attempted to retrieve last element of an empty list");
		return tail -> value;
    }

    /* last() - Version 2
       If the list has at least one element, returns a const reference to the
       last element.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T const& last() const {
        /* Your code here */
		if (is_empty()) throw std::runtime_error ("Error: Attempted to retrieve last element of an empty list");
		return tail -> value;
    }
    
    /* push_front(value)
       Add a copy of the provided value to the list as the first element.
    */
    void push_front(T const& value){
        /* Your code here */
		list_size++;
		if (list_size == 1){//instantiate from empty list
			head = std::make_shared<ListNode>(value, nullptr);
			tail = head;
		}
		else{
			auto old_head = head;
			head = std::make_shared<ListNode>(value, old_head);
		}
    }
    
    /* push_front(value)
       Add a copy of the provided value to the list as the last element.
    */
    void push_back(T const& value){
        /* Your code here */
		list_size++;
		if (list_size == 1){//instantiate from empty list
			head = std::make_shared<ListNode>(value, nullptr);
			tail = head;
		}
		else{
			//let's try a recursive function here:
			push_back(head, value);
		}
    }
    

    /* pop_front()
       If the list has at least one element, remove the first element and
       return a copy of its value.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T pop_front(){
        /* Your code here */
		T tmp;
		if (is_empty()) throw std::runtime_error("Error: Attempting to pop_front from an empty list");
		else if(list_size == 1){//a one element list is easy to do
			tmp = head -> value;
			head = nullptr;
			tail = nullptr;
		}
		else{
			tmp = head -> value;
			head = head -> next;
		}
		list_size--;
		return tmp;
    }
    
    /* pop_back()
       If the list has at least one element, remove the last element and
       return a copy of its value.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T pop_back(){
        /* Your code here */
		T tmp;
		if (is_empty()) throw std::runtime_error("Error: Attempting to pop_back from an empty list");
		//again, let's do this recursively (with a private member function)
		else if(list_size == 1){//a one element list is easy to do
			tmp = head -> value;
			head = nullptr;
			tail = nullptr;
		}
		else tmp = pop_back(head);
		list_size--;
		return tmp;
    }
    
    /* contains(element)
       Return true if any element of the list is equal (using the == operator) to 
       the provided element. Return false otherwise.
    */
    bool contains(T const& element) const{
        /* Your code here */
		//Recall that el is a ListNodePtr that I have coded to behave like an iterator
		/*if*/for (auto el = begin(); el != end(); ++el) if ( (*el).value == element) return true;
		/*else*/return false;
    }
    
    /* clear()
       Remove all elements from the list.
    */
    void clear(){
        /* Your code here */
		list_size = 0;
		head = nullptr;
		tail = nullptr;
    }
    
    /* operator==
       Return true if this list is equal to the provided other list.
       Two lists are considered equal if they have the same length and
       contain the same sequence of elements (in the same order). Use
       the == operator to compare individual elements to each other.
    */
    bool operator==(LinkedList<T> const& other_list) const{
        /* Your code here */
		if (list_size != other_list.list_size) return false;
		else{
			/*if*/for (auto el1 = begin(), el2 = other_list.begin(); el1 != end(); ++el1, ++el2) if ( (*el1).value != (*el2).value) return false;
		}//returns false if any one of the elements are different
		/*else*/return true;
    }
    
    /* operator!=
       Return true if this list is not equal to the provided other list.
       In this context, two lists are not equal if the operator== above
       returns false.
    */
    bool operator!=(LinkedList<T> const& other_list) const{
        /* Your code here */
		return !(operator==(other_list));
    }
    

    /* operator=
       Set this list to be a copy of the provided other list.
       (If this list already contains any values, remove all of them first).
    */
    LinkedList<T>& operator=(LinkedList<T> const& other_list){
        /* Your code here */
		copy_list(other_list.head);//since we defined this in the copy constructor, let's use it here as well.
		return *this;
    }
    
    /* apply(func) - Version 1
       Given a function that takes a single argument (which is a reference to an 
       element), call that function on each element of this list (in forward 
       order). Note that since the element is passed by non-const reference, the 
       provided function has the ability to modify the elements of the list.
    */
    void apply( std::function< void(T&) > func ){
        /* Your code here */
		for (auto el = begin(); el != end(); ++el) func(el->value);
    }
    
    /* apply(func) - Version 2
       Given a function that takes a single argument (which is a const reference 
       to an element), call that function on each element of this list (in 
       forward order).

       Note that the only difference between this and version 1 is that this
       is guaranteed not to modify the list elements (since the reference passed
       to the function is const). It will likely be possible to use almost
       identical code for this version as for version 1.
    */
    void apply( std::function< void(T const&) > func ) const{
        /* Your code here */
		for (auto el = begin(); el != end(); ++el) func(el->value);
    }

    /* remove_where(func)
       Given a function which takes a list element and returns a boolean value, remove
       all elements of the list where the provided function returns true 
    */
    void remove_where( std::function< bool(T const&) > condition_function ){
        /* Your code here */
		for (auto el = begin(); el != end(); ++el){
			if (condition_function(el -> value)) {
				delete_at(el);//delete_at handles the private member data
			}//end if
		}//end for
    }//end remove_where
    
    
    /* transform(func)
       Given a function that takes a single argument (which is a const reference 
       to an element of this list) and returns a value (of some type OutputType),
       call that function on each element of this list (in forward order), then
       add the result to a new list (of element type OutputType). Return the
       resulting list.
    */

    template<typename OutputType>
    LinkedList<OutputType> transform( std::function< OutputType(T const&) > transform_function ){
        /* Your code here */
		LinkedList<OutputType> transformed {};
		for (auto el = begin(); el != end(); ++el) transformed.push_back(transform_function(el -> value));
		return transformed;
    }

    

private:
	
    /* Note that since ListNode is a struct (not a class), all of its members will be
       public by default. */
    struct ListNode;
    using ListNodePtr = std::shared_ptr<ListNode>;
    struct ListNode{
        ListNode(T const& val, ListNodePtr next_node) {
			value = val;
			next = next_node;
        }
        T value;
        ListNodePtr next;
    };

    ListNodePtr head;
	ListNodePtr tail;

    /* You may add other private members as needed. */
	unsigned list_size;
	
	//private push_back using recursion
	void push_back (ListNodePtr point, T value){
		//note that this recursively does the push back operation ONLY. Things like updating list_size are done in the public function
		if (point -> next == nullptr){//base case, when point is the last node
			point -> next = std::make_shared<ListNode>(value, nullptr);
			tail = point -> next;//update tail
		}
		else push_back(point -> next, value);
	}
	
	//private pop_back using recursion
	T pop_back(ListNodePtr point){
		T tmp;
		//note that this recursively does the pop back operation ONLY. Things like updating list_size are done in the public function
		if (point -> next -> next == nullptr){//base case, true when "point" is the second to last node
			tmp = point -> next -> value;//save the value of the last node
			tail = point;//set tail to the second to last node
			point -> next = nullptr;//set the second to last node pointing away from the last node
		}
		else tmp = pop_back(point -> next);
		return tmp;
	}
	
	//private delete_at function, could be used to implement an erase() function much like standard containers have
	void delete_at(ListNodePtr here){
		
		if(here == head) pop_front();//addresses the case if con_func is true for the head
		else if(here == tail) pop_back();//same as above for the tail
		//the above two if statements prevent a seg fault; don't delete them
		else{
			//Step 1: Locate the pointer before "here"
			auto el = head;//this has to be outside the for loop so we can use it later
			for (; el->next != here; ++el);			
			//Step 2: "skip over" the "here" pointer
			el -> next = here -> next;//this should delete "here"
			list_size--;
		}
	}
	
	
	//Private function(s) to copy an entire list by being passed its head
	void copy_list_2(ListNodePtr node){
		if (node == nullptr) return;//base case, ie end of the list has been reached
		else copy_list_2(node -> next);//this is where the recursion happens
		push_front(node -> value);//this will always happen, the recursion just orders is so that the last el is pushed first
	}
	void copy_list(ListNodePtr node){
		head = nullptr; tail = nullptr; list_size = 0;//reset the private members so we can use this function for operator=
		copy_list_2(node);//this is where the recursion happens
	}
	
	//A few functions to make ListNodePtr behave more like an iterator
	ListNodePtr begin() const{
		return head;
	}
	ListNodePtr end() const{
		return nullptr;
	}
	void push_front(const ListNode& fake_iter){
        push_front(fake_iter.value);
    }
	void push_back(const ListNode& fake_iter){
        push_back(fake_iter.value);
    }
	friend void operator++(ListNodePtr& current){//helps make ListNodePtr behave more like an iterator by overloadin the postfix
		current = current -> next;
	}
};


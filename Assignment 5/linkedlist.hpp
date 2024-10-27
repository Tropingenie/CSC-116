/* linkedlist.hpp
   CSC 116 - Fall 2019

   B. Bird - 08/10/2019
*/

#include <functional>
#include <stdexcept>
#include <memory>
#include <initializer_list>

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
    LinkedList( std::initializer_list<T> initial_contents ){
        /* Your code here */
		
		//Step 1: Initialise two iterators and two pointers, "current" and "next"
		auto iter = initial_contents.begin();
		auto pntr_curr = std::make_shared<ListNode>((*iter), nullptr);//create a node with the first element
		head = pntr_curr;//Set head to point to the first node
		iter++;//The first element of the initializer list has been "pushed back," so increment.
		list_size++;//increment size (since the list now has 1 element and size defaults to 0)
		std::shared_ptr<ListNode> pntr_next;//Initialise a temporary "next pointer"
		
		//Step 2: Set the previous node's "next" value to the pntr to the newly created node
		while (iter != initial_contents.end()){
			pntr_next = std::make_shared<ListNode>((*iter), nullptr);
			(*pntr_curr).next = pntr_next;//Sets the "next" pointer of the previous node to the pointer to the next node
			pntr_curr = pntr_next;//Sets the current pointer to the next pointer, so focus is shifted to the next node
			iter++;//increment iterator
			list_size++;//increment size for ever iteration of this loop (since each iteration adds a node)
		}
		tail = pntr_curr;//sets tail to the last node
    }
    /* Copy constructor:
       Construct the list to contain all of the elements in the provided
       other list. Note that a "deep copy" is needed, such that when the 
       operation completes there are two separate, independent lists.
    */
    LinkedList( LinkedList<T> const& other_list ){
		//We want to "iterate" through other_list, however iterators don't really exist for these custom classes
		//Still, the behaviour should be as if we used iterators.
		
		auto pntr_iter = other_list.head;//note that this is actually a smart pointer to the head of the other list
		auto pntr_curr = std::make_shared<ListNode>((*pntr_iter).value, nullptr);//Creares the first node of our NEW list
		std::shared_ptr<ListNode> pntr_next;//instantiate pntr_next
		head = pntr_curr;//sets head to the pointer to the first node
		pntr_iter = pntr_iter -> next;//equivalent to iter++ in that it now points to the next node
		list_size++;//increment size
		
		while (pntr_iter != nullptr){
			pntr_next = std::make_shared<ListNode>((*pntr_iter).value, nullptr);
			(*pntr_curr).next = pntr_next;//Sets the "next" pointer of the previous node to the pointer to the next node
			pntr_curr = pntr_next;//Sets the current pointer to the next pointer, so focus is shifted to the next node
			pntr_iter = pntr_iter -> next;//increment "iterator"
			list_size++;//increment size for ever iteration of this loop (since each iteration adds a node)
		}
		tail = pntr_curr;//sets tail to the last node
    }
    /* Destructor */
    ~LinkedList(){
        /* Your code here */
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
		if (is_empty()) throw std::runtime_error ("Error: Attempted to return first element but list has 0 elements");
		else return (*head).value;
    }

    /* first() - Version 2
       If the list has at least one element, returns a const reference to the
       first element.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T const& first() const {
        /* Your code here */
		if (is_empty()) throw std::runtime_error ("Error: Attempted to return first element but list has 0 elements");
		else return (*head).value;
    }
    
    /* last() - Version 1
       If the list has at least one element, returns a reference to the last
       element (such that the result can be modified by the caller).
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T& last(){
        /* Your code here */
		if (is_empty()) throw std::runtime_error ("Error: Attempted to return last element but list has 0 elements");
		else return (*tail).value;
    }

    /* last() - Version 2
       If the list has at least one element, returns a const reference to the
       last element.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T const& last() const {
        /* Your code here */
		if (is_empty()) throw std::runtime_error ("Error: Attempted to return last element but list has 0 elements");
		else return (*tail).value;
    }
    


    /* push_front(value)
       Add a copy of the provided value to the list as the first element.
    */
    void push_front(T const& value){
        /* Your code here */
		if ( is_empty() ){//Instantiates the first node
			list_size++;
			head = std::make_shared<ListNode>(value, nullptr);
			tail = head;
		}
		else{
			list_size++;
			auto temp_ptr = head;//temp_ptr points to the current (soon to be old) first node
			head = std::make_shared<ListNode>(value, temp_ptr);//creates a new node, setting head to point to it, while its "next" value
															//points to the (formerly current) old first node
		}
    }
    
    /* push_back(value)
       Add a copy of the provided value to the list as the last element.
    */
    void push_back(T const& value){
        /* Your code here */
		if ( is_empty() ){//Instantiates the first node
			list_size++;
			head = std::make_shared<ListNode>(value, nullptr);
			tail = head;
		}
		else{
			list_size++;
			auto temp_ptr = tail;//back up the pointer
			tail = std::make_shared<ListNode>(value, nullptr);//overwrite tail with the pointer to the new last node
			(*temp_ptr).next = tail;//redirect the (formerly last) second to last node's "next" pointer to the new last node
		}
    }
    

    /* pop_front()
       If the list has at least one element, remove the first element and
       return a copy of its value.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T pop_front(){
        /* Your code here */
		if ( is_empty() ) throw std::runtime_error( "Error: Attempted to pop first element but list has 0 elements");
		else if ( list_size == 1 ){//ie a one-element list, since tail isn't handled below
			auto val = (*head).value;
			head = nullptr;
			tail = nullptr;
			list_size = 0;
			return val;
		}
		else{
			list_size--;
			auto val = (*head).value;
			head = head -> next;//sets head to the next element. The former head should be deleted b/c we are using smart pointers
			return val;
		}
    }
    
    /* pop_back()
       If the list has at least one element, remove the last element and
       return a copy of its value.
       If the list has zero elements, throw an exception of type std::runtime_error.
    */
    T pop_back(){
        /* Your code here */
		if ( is_empty() ) throw std::runtime_error( "Error: Attempted to pop last element but list has 0 elements");
		else if ( list_size == 1 ){//ie a one-element list, which caused a seg-fault to occur before I added this elif statement
			auto val = (*head).value;
			head = nullptr;
			tail = nullptr;
			list_size = 0;
			return val;
		}
		else{
			list_size--;
			auto val = (*tail).value;
			/*This is more complicated than the pop_front case because we need to do two (rather annoying) things:
			1. Set tail to point to the second to last element of the list
			2. Set the "next" pointer of the second to last element to point to nullptr
			Let's start by finding the second to last element*/
			auto pntr = head;
			while( (*pntr).next != tail){//when the address of next == the address of tail, the current pointer points to the 2ndtolast node
				pntr = pntr -> next;
			}
			//Now pntr points to the second to last element.
			(*pntr).next = nullptr;
			tail = pntr;
			//Now the formerly last node should be gone since we are using smart pointers
			return val;
		}
    }
    
    /* contains(element)
       Return true if any element of the list is equal (using the == operator) to 
       the provided element. Return false otherwise.
    */
    bool contains(T const& element) const{
        /* Your code here */
		auto pntr_iter = head;
		
		while (pntr_iter != nullptr){
			if ( (*pntr_iter).value == element ) return true;
			else pntr_iter = pntr_iter -> next;
		}
		
		return false;
    }
    
    /* clear()
       Remove all elements from the list.
    */
    void clear(){
        /* Your code here */
		if ( !is_empty() ){//no need to clear if already an empty list
			head = nullptr;
			tail = nullptr;
			list_size = 0;
			//Since we are using smart pointers, the rest of the nodes should go die now.
		}
    }
    
    /* operator==
       Return true if this list is equal to the provided other list.
       Two lists are considered equal if they have the same length and
       contain the same sequence of elements (in the same order). Use
       the == operator to compare individual elements to each other.
    */
    bool operator==(LinkedList<T> const& other_list) const{
        /* Your code here */
		if ( size() != other_list.size() ) return false;
		auto pntr_this = head;
		auto pntr_other = other_list.head;
		while (pntr_this != nullptr){
			if ( (*pntr_this).value != (*pntr_other).value ) return false;
			else{
				pntr_this = pntr_this -> next;
				pntr_other = pntr_other -> next;
			}
		}
		return true;
    }
    
    /* operator!=
       Return true if this list is not equal to the provided other list.
       In this context, two lists are not equal if the operator== above
       returns false.
    */
    bool operator!=(LinkedList<T> const& other_list) const{
        /* Your code here */
		return !( *this == other_list );
    }
    

    /* operator=
       Set this list to be a copy of the provided other list.
       (If this list already contains any values, remove all of them first).
    */
    LinkedList<T>& operator=(LinkedList<T> const& other_list){
        /* Your code here */
		clear();
		auto pntr = other_list.head;
		while (pntr != nullptr){
			push_back( (*pntr).value );
			pntr = pntr -> next;
		}
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
		auto pointer_current = head;
		while (pointer_current != nullptr){
			T& data = pointer_current -> value;//creates a reference to the value stored in the current node
			func(data);
			pointer_current = pointer_current -> next;//sets the pointer pointing to the next node
		}
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
		auto pointer_current = head;
		while (pointer_current != nullptr){
			T& data = pointer_current -> value;//creates a reference to the value stored in the current node
			func(data);
			pointer_current = pointer_current -> next;//sets the pointer pointing to the next node
		}
    }

    /* remove_where(func)
       Given a function which takes a list element and returns a boolean value, remove
       all elements of the list where the provided function returns true 
    */
    void remove_where( std::function< bool(T const&) > condition_function ){
        /* Your code here */
		auto& func = condition_function;//condition_function has too many letters
		bool delete_prev = false;//flag to be used later
		//Since we need to keep track of the "previous pointer," there needs to be a special case for if the function holds true
		//for the first and last elements.
		while ( func( head -> value ) ){
			//set the pointer of head to the next node.
			head = head -> next;
		}
		auto pointer_current = head -> next;//should point to the second node here
		auto pointer_previous = head;
		
		while (pointer_current != nullptr){
			T& data = pointer_current -> value;//creates a reference to the value stored in the current node
			if(func(data)){
				//Set the pointer of the previous node to the next node, then delete the current node. Also keep track
				//of whether you're at the end of the list or not.
				if (pointer_current == tail){//ie, this is the last node and you want to delete it
					tail = pointer_previous;
					(tail -> next) = nullptr;//now nothing should point to the node, and it will be deleted
					return;//I use return here for safety: if we've deleted the element tail points to, the function has parsed
					//every element in the list, and as such should exit ASAP.
				}
				else{
					(pointer_previous -> next) = pointer_current -> next;
					delete_prev = true;
				}
			}
			pointer_current = pointer_current -> next;//sets the pointer pointing to the next node
			if (!delete_prev) pointer_previous = pointer_previous -> next;//only updates this if previous hasn't been modified yet
			else delete_prev = false;//reset the flag and do nothing else
		}
    }
    
    
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
		LinkedList<OutputType> new_list;
		auto pointer_current = head;
		
		while(pointer_current != nullptr){
			auto tmp = transform_function( pointer_current -> value );
			new_list.push_back(tmp);
			pointer_current = pointer_current -> next;
		}
		
		return new_list;
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

    /* You may add other private members as needed. */
	unsigned long long list_size;
	ListNodePtr tail;
};

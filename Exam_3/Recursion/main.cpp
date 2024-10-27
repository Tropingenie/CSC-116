/* raw_lists.cpp by B. Bird - 11/20/2019 */
#include <iostream>
#include <memory>
#include <functional>
class Node;
using NodePtr = std::shared_ptr<Node>;
struct Node{
    Node( NodePtr nxt, int v ){
        value = v;
        next = nxt;
    }
    NodePtr next;
    int value;
};

void insert_at_front( NodePtr& head, int new_value ){
    NodePtr new_node = std::make_shared<Node>( head, new_value );
    head = new_node;
}

void insert_at_end( NodePtr& head, int new_value ){
    /* Recursive */
    if (head == nullptr){
        head = std::make_shared<Node>( nullptr, new_value);
    }else{
        insert_at_end(head->next, new_value);
    }
}

void print_list(NodePtr head){
    if (head == nullptr){
        std::cout << std::endl;
    }else{
        std::cout << head->value << " ";
        print_list(head->next);
    }
}

void print_reverse_internal(NodePtr head){
    if (head == nullptr)
        return;
    print_reverse_internal(head->next);
    std::cout << head->value << " ";
}
void print_reverse(NodePtr head){
    /* Recursive */
    auto internal = [head](NodePtr i,std::function<void( j){
      if (i == nullptr) return;
      else j(i -> next);
        std::cout << head->value << " ";
    };
    internal(head, internal);
    std::cout << std::endl;
}

int count_elements(NodePtr head){
    /* Recursive */
    if (head == nullptr)
        return 0;
    return 1 + count_elements(head->next);
}

int sum_list(NodePtr head){
    /* Recursive */
    if (head == nullptr)
        return 0;
    return head->value + sum_list(head->next);
}

int main(){
    NodePtr L1_head = nullptr;
    std::cout << "Part A" << std::endl;
    insert_at_front(L1_head, 6);
    insert_at_front(L1_head, 10);
    insert_at_front(L1_head, 17);

    print_list(L1_head);
    print_reverse(L1_head);

    std::cout << "Part B" << std::endl;
    insert_at_end(L1_head, 10);
    insert_at_end(L1_head, 10);
    insert_at_end(L1_head, 10);

    print_list(L1_head);

    std::cout << "Part C" << std::endl;
    std::cout << "Number of elements: " << count_elements(L1_head) << std::endl;
    std::cout << "Sum of elements: " << sum_list(L1_head) << std::endl;
    return 0; }
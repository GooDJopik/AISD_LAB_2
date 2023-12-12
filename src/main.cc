#include "../include/List.h"

#include<cmath>
#include <iostream>

int main() {
    CyclicList<int> list;

    list.push_tail(4);
    list.push_tail(5);
    list.push_tail(6);
    list.push_head(3);
    list.push_head(2);
    list.push_head(1);

    std::cout << "Original list: ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.reverse();

    std::cout << "Reversed list: ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;


    list.pop_head();
    list.pop_tail();

    std::cout << "Reversed list with pop_head() and pop_tail(): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.reverse();

    std::cout << "Original list with pop_head() and pop_tail(): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.delete_node(3);

    std::cout << "List with 'delete_node()': ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;



    CyclicList<int> rand_list(10, 2, 12);

    std::cout << "Original list: ";
    for (size_t i = 0; i < rand_list.size(); i++) {
        std::cout << rand_list[i] << " ";
    }
    std::cout << std::endl;

    rand_list.reverse();

    std::cout << "Reversed list: ";
    for (size_t i = 0; i < rand_list.size(); i++) {
        std::cout << rand_list[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
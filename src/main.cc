#include "../include/List.h"

#include<cmath>
#include <iostream>

int main() {
    system("chcp 65001");
    CyclicList<int> list;

    list.push_tail(5);
    list.push_tail(6);
    list.push_tail(7);
    list.push_tail(8);
    list.push_head(4);
    list.push_head(3);
    list.push_head(2);
    list.push_head(1);

    std::cout << "\xE2\x98\xAD" << "Original: ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    reverse(list);

    std::cout << "\xE2\x98\xAD" << "Reversed: ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;


    list.pop_head();
    list.pop_tail();

    std::cout << "\xE2\x99\xAB" << "Reversed with pop_head() and pop_tail(): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    reverse(list);

    std::cout << "\xE2\x99\xAB" << "Original with pop_head() and pop_tail(): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.delete_node(4);

    std::cout << "\xE2\x99\xAB" << "List with delete_node(): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    list.push_head(list);

    std::cout << "\xE2\x99\xAB" << "List with push_head(): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;



    CyclicList<int> rand_list(10, 2, 12);

    std::cout << "\xE2\x99\x9B" << "Original: ";
    for (size_t i = 0; i < rand_list.size(); i++) {
        std::cout << rand_list[i] << " ";
    }
    std::cout << std::endl;

    reverse(rand_list);

    std::cout << "\xE2\x99\x9B" << "Reversed: ";
    for (size_t i = 0; i < rand_list.size(); i++) {
        std::cout << rand_list[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
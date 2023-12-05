#ifndef LIST_INCLUDE_LIST_H
#define LIST_INCLUDE_LIST_H

#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>

template <typename T>
struct Node {
    Node* next, * prev;
    T data;

    Node(T data) : data(data), prev(nullptr), next(nullptr) {};
};

template <typename T>
class CyclicList {
    Node<T>* _head, * _tail;
    size_t _size;
public:
    CyclicList() : _head(nullptr), _tail(nullptr), _size(0) {};

    CyclicList(size_t size, T lower_bound, T upper_bound) :CyclicList() {
        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(lower_bound, upper_bound);

            for (size_t i = 0; i < size; ++i) {
                T data = dist(gen);
                push_tail(data);
            }
            _size = size;
        }
        else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(lower_bound, upper_bound);

            for (size_t i = 0; i < size; ++i) {
                T data = dist(gen);
                push_tail(data);
            }
            _size = size;
        }
    }

    CyclicList(const CyclicList& other) {
        _head = nullptr;
        _tail = nullptr;
        Node<T>* tmp = other._head;
        this->push_tail(*tmp);
        tmp = tmp->next;
        while (tmp != other._head) {
            Node<T>* new_tmp = new Node<T>(*tmp);

            this->push_tail(*new_tmp);
            tmp = tmp->next;
        }
    }

    CyclicList& operator=(const CyclicList& other) {
        if (this != &other) {
            clear();
            Node<T>* tmp = other._head;
            while (tmp != nullptr) {
                push_tail(tmp->data);
                tmp = tmp->next;
            }
        }
        return *this;
    }

    void push_head(T data) {
        Node<T>* tmp = new Node<T>(data);
        if (_head == nullptr) {
            _head = tmp;
            _tail = tmp;
            tmp->next = tmp;
            tmp->prev = tmp;
        }
        else {
            tmp->prev = _tail;
            tmp->next = _head;
            _tail->next = tmp;
            _head->prev = tmp;
            _head = tmp;
        }
        _size++;
    }

    void push_tail(T data) {
        Node<T>* tmp = new Node<T>(data);
        if (_head == nullptr) {
            _head = tmp;
            _tail = tmp;
            tmp->next = tmp;
            tmp->prev = tmp;
        }
        else {
            tmp->prev = _tail;
            tmp->next = _head;
            _tail->next = tmp;
            _head->prev = tmp;
            _tail = tmp;
        }
        _size++;
    }

    void push_head(const CyclicList<T>& other) {
        Node<T>* other_tail_next = other._tail->next;
        Node<T>* head_prev = _head->prev;

        other._tail->next = _head;
        _head->prev = other._tail;
        other._head->prev = _tail;
        _tail->next = other._head;

        _head = other._head;
        _tail = other_tail_next->prev;

        _head->prev = head_prev;
        head_prev->next = _head;
    }

    void push_tail(const CyclicList<T>& other) {
        Node<T>* other_head_prev = other._head->prev;
        Node<T>* tail_next = _tail->next;


        other._head->prev = _tail;
        _tail->next = _head;
        other._tail->next = _head;
        _head->prev = other._tail;

        _tail = other._tail;
        _head = other_head_prev->next;

        _head->prev = _tail;
        _tail->next = _head;
    }

    int get_len() {
        if (_head == nullptr)
            return 0;
        int len = 1;
        Node<T>* node = _head->next;
        while (node != _head) {
            len += 1;
            node = node->next;
        }
        return len;
    }


    void delete_node(T data) {
        Node <T>* tmp = _head;
        int len = this->get_len();
        for (int i = 0; i < len; i++) {
            if (tmp->data == data) {
                if (tmp == _head)
                {
                    this->pop_head();
                }
                else if (tmp == _tail)
                {
                    this->pop_tail();
                }
                else
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                }
            }
            tmp = tmp->next;
        }
    }

    size_t size() const {
        return _size;
    }
};

template<typename T>
std::uniform_int_distribution<T> getDice(std::true_type)
{
    return std::uniform_int_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template<typename T>
std::uniform_real_distribution<T> getDice(std::false_type)
{
    return std::uniform_real_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template<typename T>
T random()
{
    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    auto dice = getDice<T>(std::integral_constant<bool, std::numeric_limits<T>::is_integer>());
    return dice(generator);
}


#endif
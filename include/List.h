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
    Node* next;
    Node* prev;
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
        push_tail(tmp->data); // Исправленный вызов функции push_tail
        tmp = tmp->next;
        while (tmp != other._head) {
            Node<T>* new_tmp = new Node<T>(tmp->data);
            push_tail(new_tmp->data); // Исправленный вызов функции push_tail
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
        if (other.empty()) {
            return;
        }
        if (empty()) {
            *this = other;
            return;
        }
        // Создание новых узлов для добавляемого списка
        Node<T>* other_head = other._head;
        Node<T>* new_head = new Node<T>(other_head->data);
        Node<T>* new_tail = new_head;
        other_head = other_head->next;

        // Добавление остальных элементов добавляемого списка
        while (other_head != other._head) {
            Node<T>* new_node = new Node<T>(other_head->data);
            new_node->next = new_head;
            new_node->prev = new_tail;
            new_tail->next = new_node;
            new_tail = new_node;
            other_head = other_head->next;
        }

        // Обновление связей текущего списка
        new_tail->next = _head;
        _head->prev = new_tail;
        _head = new_head;

   
        _size += other.size();
    }

    void push_tail(const CyclicList<T>& other) {
        if (other.empty()) {
            return;
        }
        if (empty()) {
            *this = other;
            return;
        }
        Node<T>* other_head = other._head;
        Node<T>* other_tail = other._tail->prev;

        while (other_head != other._tail) {
            Node<T>* new_node = new Node<T>(other_head->data);
            new_node->prev = _tail->prev;
            new_node->next = _tail;
            _tail->prev->next = new_node;
            _tail->prev = new_node;
            other_head = other_head->next;
        }

      
        _size += other.size();
    }
    

    int get_len() const {
        if (_head == nullptr) {
            return 0;
        }

        int len = 1;
        Node<T>* current = _head->next;

        while (current != _head) {
            len += 1;
            current = current->next;
        }

        return len;
    }

    void pop_head() {
        if (_head == nullptr) {
            return;
        }
        if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Node<T>* new_head = _head->next;
            new_head->prev = _tail;
            _tail->next = new_head;
            delete _head;
            _head = new_head;
        }
        _size--;
    }

    void pop_tail() {
        if (_tail == nullptr) {
            return;
        }
        if (_head == _tail) {
            delete _tail;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Node<T>* new_tail = _tail->prev;
            new_tail->next = _head;
            _head->prev = new_tail;
            delete _tail;
            _tail = new_tail;
        }
        _size--;
    }

    void delete_node(T data) {
        Node <T>* tmp = _head;
        int len = this->get_len();
        for (int i = 0; i < len; i++) {
            if (tmp->data == data) {
                if (tmp == _head)
                {
                    this->pop_head();
                    break;
                }
                else if (tmp == _tail)
                {
                    this->pop_tail();
                    break;
                }
                else
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    delete tmp;
                    _size--;
                    break;
                    
                }
                
            }
            tmp = tmp->next;
        }
        
    }
    

    size_t size() const {
        return _size;
    }

    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = _head;

        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = _head;
        
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }
    
    Node<T>* getHead() const {
        return _head;
    }

    Node<T>* getTail() const {
        return _tail;
    }

    void setHead(Node<T>* head) {
        _head = head;
    }

    void setTail(Node<T>* tail) {
        _tail = tail;
    }

    void clear() {
        while (!empty()) {
            pop_head();
        }
    }

    ~CyclicList() {
        clear();
    }

    bool empty() const {
        return (_size == 0);
    }

};

template<typename T>
void reverse(CyclicList<T>& list) {
    if (list.getHead() == nullptr || list.getHead() == list.getTail()) {
        return;
    }

    Node<T>* current = list.getHead();
    Node<T>* next_node = nullptr;

    do {
        Node<T>* temp_prev = current->prev;

        current->prev = current->next;
        current->next = temp_prev;

        next_node = current->prev;
        current = next_node;
    } while (current != list.getHead());

    Node<T>* temp_head = list.getHead();
    list.setHead(list.getTail());
    list.setTail(temp_head);
}

#endif
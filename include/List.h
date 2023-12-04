#ifndef LIST_INCLUDE_LIST_H
#define LIST_INCLUDE_LIST_H

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
    CyclicList() : _head(nullptr), _tail(nullptr) {};

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

    void push_head(const T& data) {
        Node<T>* tmp = new Node<T>{ nullptr, nullptr, data };
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
    }

    void push_tail(const T& data) {
        Node<T>* tmp = new Node<T>{ nullptr, nullptr, data };
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

    void delete_node(T data) {
        Node <T>* tmp = _head;
        while (tmp != nullptr) {
            if (tmp->data == data) {
                if (tmp == _head)
                {
                    Node<T>* new_head = _head->next;
                    new_head->prev = nullptr;
                    delete _head;
                    _head = new_head;
                }
                else if (tmp == _tail)
                {
                    Node<T>* new_tail = _tail->prev;
                    new_tail->next = nullptr;
                    delete _tail;
                    _tail = new_tail;
                }
                else
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    delete tmp;
                }
            }
            tmp = tmp->next;
        }
    }
};
#endif
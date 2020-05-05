#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <string>
#include <exception>
#include "MyCircularLinkedList.hpp"

using namespace std;

class MyLLInvalidAccessException : public exception {
private:
    int code;
    string msg;
public:
    MyLLInvalidAccessException(int code){
        this->code = code;
        
        switch(code) {
            case 1:
                this->msg = "Invalid head() call: empty list";
                break;
            case 11:
                this->msg = "Invalid next() call: hasNext() false";
                break;
            case 12:
                this->msg = "Invalid previous() call: hasPrevious() false";
                break;
            case 13:
                this->msg = "Invalid isAtBegin() call: empty list";
                break;
            case 14:
                this->msg = "Invalid goToBegin() call: empty list";
                break;
            case 15:
                this->msg = "Invalid set(T v) call: empty list";
                break;
        }
    }
    
    int getCode() {
        return this->code;
    }
    
    string getMessage() {
        return this->msg;
    }
};

template <class T> class MyCircularList;
template <class T> class MyCircularListIterator;
template <class T> class Node;

using namespace std;
template <class T> class Node {
    friend class MyCircularList<T>;
    friend class MyCircularListIterator<T>;
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
    
    Node(T v)
    {
        this->data = v;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

template <class T> class MyCircularListIterator {
    friend class MyCircularList<T>;
    friend class Node<T>;
private:
    Node<T>* current = nullptr;
    MyCircularList<T>* ch;
public:
    MyCircularListIterator<T>(MyCircularList<T> &a) : ch(&a){};
    
    bool isEmpty() {
        return (ch->_head == nullptr) ? true : false;
    }
    
    T next() {
        if(!isEmpty()) {
            current = ch->_head->next;
            ch->_head = ch->_head->next;
            return current->data;
        }
        MyLLInvalidAccessException e(11);
        throw e;
        return NULL;
    }
    
    T previous() {
        if(!isEmpty() && current->prev != nullptr) {
            current = current->prev;
            return current->data;
        }
        MyLLInvalidAccessException e(12);
        throw e;
        return NULL;
    }
    
    bool isAtBegin() {
        if(isEmpty()) {
            MyLLInvalidAccessException e(13);
            throw e;
            return false;
        }
        return true;
    }
    
    void goToBegin() {
        Node<T>* head = current;
        current = current->next;
        if(!isEmpty()) {
            while(current != head) {

                cout << current->data << endl;
                current = current->next;
            }
            cout << current->data << endl;
            return;
        }
        MyLLInvalidAccessException e(14);
        throw e;
    }
    
    void set (T v) {
        if(isEmpty()) {
            MyLLInvalidAccessException e(15);
            throw e;
            return;
        }
        current->data = v;
    }
};


template <class T> class MyCircularList {
    friend class MyCircularListIterator<T>;
private:
    Node<T>* _head;
public:
    MyCircularList() {
        _head = nullptr;
    }
    
    MyCircularList(T v) {
        Node<T>* new_node = new Node<T>(v);
        _head = new_node;
    }
    
    MyCircularList(T v[]) {
        _head = nullptr;
        for(int i = 0; i < sizeof(*v); i++) {
            if(sizeof(&v) == 1) {
                Node<T>* new_node = new Node<T>(v[i]);
                _head = new_node;
                return;
            }
            
            if(_head == nullptr) {
                
                Node<T>* new_node = new Node<T>(v[i]);
                Node<T>* next_new_node = new Node<T>(v[i+ 1]);
                
                _head = new_node;
                next_new_node->prev = new_node;
                _head->next = next_new_node;
                _head->next->next = _head;
                _head->prev = _head->next;
                i = 1;
            }
            else append(v[i]);
        }
    }
    
    void print(MyCircularList<T> list, int size) {
        int i = 0;
        Node<T>* current = list._head;
        while(current != nullptr && i < size) {
            cout << current->data << endl;
            current = current->next;
            i++;
        }
    }
    
    MyCircularList<T> copy() {
        MyCircularList<T> result = *this;
        return result;
    }
    
    T head() {
        if(_head != nullptr)
            return _head->data;
        MyLLInvalidAccessException e(1);
        throw e;
    }
    
    vector<T> toVector() {
        vector<T> w;
        Node<T>* current = _head;
        
        while(current != nullptr && current->next != _head) {
            w.push_back(current->data);
            current = current->next;
        }
        w.push_back(current->data);
        return w;
    }
    
    void append(T e) {
        Node<T>* new_node = new Node<T>(e);
        Node<T>* current_node = _head->next;
        while(current_node != NULL && current_node->next != _head)
            current_node = current_node -> next;
        _head->prev = new_node;
        new_node->next = _head;
        new_node->prev = current_node;
        current_node->next = new_node;
        new_node->prev = current_node;
    }
    
    void concat(MyCircularList<T> lc) {
        if(lc._head == nullptr) return;
        if(_head == nullptr) return;
        append(lc._head->data);
        Node<T>* current_lc_node = lc._head->next;
        
        while(current_lc_node != nullptr && current_lc_node != lc._head) {
            append(current_lc_node->data);
            current_lc_node = current_lc_node->next;
        }
    }
    
    MyCircularListIterator<T> iterator() {
        MyCircularListIterator<T> it(*this);
        it.current = _head;
        return it;
    }
};

#pragma once

#include <string>
#include <iostream>

class Node {
    public:
        int data;
        Node* next;

        Node(int _data, Node* _next)
            : data(_data), next(_next) {}
};

class SingleLinkedList {
    private:
        Node* head;
        Node* tail;
    
    public:
        // constructors and deconstructors
        SingleLinkedList();
        ~SingleLinkedList();

        // accessors and mutators
        Node* get_head() const {return head;}

        // core functions
        void add_front(int data);
        void add_end(int data);
        void insert_after(int key, int data);
        void insert_before(int key, int data);
        void insert_at(int n, int data);

        void clear();
        void delete_front();
        void delete_end();
        void delete_this(int key);
        void delete_at(int n);


        void detail_print();
        std::string string_repr();
        bool is_empty();
        int length();

        int length(Node* temp);
        void swap(int key1, int key2);
        
        void pair_swap();
};
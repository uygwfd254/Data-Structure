#include "single_linkedlist.h"

// constructors
SingleLinkedList::SingleLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// deconstructors (deleting the linked list)
SingleLinkedList::~SingleLinkedList() {
    clear();
}


// core functions
// adding
void SingleLinkedList::add_front(int data) {
    Node* temp = head;
    head = new Node(data, temp);
}

void SingleLinkedList::add_end(int data) {
    if (is_empty()) {
        add_front(data);
        tail = head;
    } else {
        tail->next = new Node(data, nullptr);
        tail = tail->next;
    }
}

void SingleLinkedList::insert_after(int key, int data) {
    Node* temp = head;
    Node* next;
    while (temp->data != key)
        temp = temp->next;
    next = temp->next;
    temp->next = new Node(data, next);
}

void SingleLinkedList::insert_before(int key, int data) {
    Node* temp = head;
    Node* prev = nullptr;
    while (temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == nullptr)
        add_front(data); return;
    prev->next = new Node(data, temp);
}

void SingleLinkedList::insert_at(int n, int data) {
    Node* temp = head;
    for (int i = 0; i < n; i++)
        temp = temp->next;
    temp->next = new Node(data, temp->next);
}

// deleting
void SingleLinkedList::clear() {
    Node* prev;
    while (!(is_empty())) {
        prev = head;
        head = head->next;
        delete prev;
    }
}

void SingleLinkedList::delete_front() {
    Node* temp = head->next;
    delete head;
    head = temp;
}

void SingleLinkedList::delete_end() {
    // to delete end, you have to traverse the list
    // again which is inefficent
    Node* temp = head;
    while (temp->next != tail)
        temp = temp->next;

    delete tail;
    temp->next = nullptr;
    tail = temp;
}

void SingleLinkedList::delete_this(int key) {
    Node* temp = head;
    Node* prev = nullptr;
    while (temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == nullptr)
        delete_front(); return;
    prev->next = temp->next;
    delete temp;
}



// displaying
// considered to be useless
void SingleLinkedList::detail_print() {
    Node* temp = head;
    std::cout << "head: " << temp << std::endl;
    while(temp != nullptr) {
        std::cout << "addr: " << temp << " "
                  << "data: " << temp->data << " "
                  << "next: " << temp->next
                  << std::endl;
        temp = temp->next;
    }
    std::cout << "tail: " << tail << std::endl;
}

std::string SingleLinkedList::string_repr() {
    std::string s = "";
    Node* temp = head;
    while(temp != nullptr) {
        s += std::to_string(temp->data) + " ";
        temp = temp->next;
    }
    return s;
}

bool SingleLinkedList::is_empty() {
    return head == nullptr;
}

int SingleLinkedList::length() {
    // iterative
    Node* temp = head;
    int n = 0;
    while (temp != nullptr) {
        temp = temp->next;
        n++;
    }
    return n;
}

int SingleLinkedList::length(Node* temp) {
    // recursive
    if (temp == nullptr)
        return 0;
    else
        return 1 + length(temp->next);
}


void SingleLinkedList::swap(int key1, int key2) {
    // we assume key1 is before key2
    Node* temp1 = head;
    Node* temp2 = head;
    Node* prev1=nullptr, * prev2, * next1;

    while (temp2->data != key2) {
        prev2 = temp2;
        temp2 = temp2->next;
    }
    
    while (temp1->data != key1) {
        prev1 = temp1;
        temp1 = temp1->next;
    }
    next1 = temp1->next;
    // edge case
    if (prev1 == nullptr) {
        head->next = temp2;
        head = temp2;
    } else
        prev1->next = temp2;

    temp1->next = temp2->next;
    temp2->next = next1;
    prev2->next = temp1;
}

void SingleLinkedList::pair_swap() {
    // iterative
    Node* temp = head;

    while (temp->next != nullptr || temp->next->next != nullptr) {
        

        // move
        temp = temp->next->next;
    }
}

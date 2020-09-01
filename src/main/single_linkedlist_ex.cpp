#include "../linked_list/single_linkedlist.h"
#include <iostream>

void SingleLinkedListExample() {
    SingleLinkedList sll;

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 1)
            sll.add_front(i);
    }
    std::cout << sll.string_repr() << "\n";
    sll.delete_front();
    std::cout << sll.string_repr() << "\n";
    sll.insert_after(7, 2);
    std::cout << sll.string_repr() << "\n";
    sll.clear();

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0)
            sll.add_end(i);
    }
    std::cout << sll.string_repr() << "\n";
    sll.delete_end();
    std::cout << sll.string_repr() << "\n";
    sll.insert_before(0, 10);
    std::cout << sll.string_repr() << "\n";
    sll.insert_at(2, 9);
    std::cout << sll.string_repr() << "\n";
    sll.delete_this(10);
    std::cout << sll.string_repr() << "\n";
    std::cout << "length " << sll.length() << "|" << sll.length(sll.get_head()) << "\n";
    sll.swap(0, 4);
    std::cout << sll.string_repr() << "\n";
    
}
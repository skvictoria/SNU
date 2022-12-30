#ifndef EE205_LIST_HPP
#define EE205_LIST_HPP

#include "ListNode.hpp"

#include <cstddef>

class List {
    private:
        ListNode* head;
        std::size_t length;

    public:
        // Initializes the list
        List();

        // Performs a deep copy, copying each node of the other list
        // into this one
        List(const List& other);

        // Performs a move, moving the internal list from the other
        // vector to this one, and invalidates the other list pointer
        // for its memory
        List(List&& other);

        // Deallocates the memory in this list.
        ~List();

        // For all of the following functions,
        // throw a const char* (string) if the index is out of
        // the bounds of the list.

        // Appends a ListNode onto the end of the list
        //
        // Throw a const char* if the index is out of bounds
        void append(int num);

        // Inserts a ListNode before the index
        //
        // Throw a const char* if the index is out of bounds.
        // Appending at the end is valid (e.g. insert(list.size(), 0)
        // is valid)
        void insert(int index, int num);

        // Removes the ListNode at the index
        //
        // Throw a const char* if the index is out of bounds.
        void remove(int index);

        // Returns the int at the index
        //
        // Throw a const char* if the index is out of bounds.
        int get(int index) const;

        // Returns the length of the list
        std::size_t size() const;

        // Reutrns a readable/writeable reference to the element at index
        //
        // Throw a const char* if the index is out of bounds.
        int& operator[](int index);
};

#endif // EE205_LIST_HPP

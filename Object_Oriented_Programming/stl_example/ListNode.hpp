#pragma once
#ifndef EE205_NODE_HPP
#define EE205_NODE_HPP


class ListNode {
private:
    int data;
    ListNode* next;

public:
    // Regular constructor with data
    ListNode(int data);
    // Copy constructor
    ListNode(const ListNode& other);
    // Move constructor
    ListNode(ListNode&& other);

    // Getters
    int get_data() const;
    ListNode* get_next() const;

    // Setters
    void set_next(ListNode* ptr);
    void set_data(int num);

    friend class List;
};

#endif // EE205_NODE_HPP

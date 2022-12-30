#include "ListNode.hpp"

#include <utility>

ListNode::ListNode(int num) :
    data(num),
    next(nullptr) {

}

ListNode::ListNode(const ListNode& other) :
    data(other.data),
    next(other.next) {}

ListNode::ListNode(ListNode&& other) :
    data(std::move(other.data)),
    next(std::move(other.next)) {}

int ListNode::get_data() const {
    return this->data;
}

ListNode* ListNode::get_next() const {
    return this->next;
}

void ListNode::set_next(ListNode* ptr) {
    this->next = ptr;
}

void ListNode::set_data(int num) {
    this->data = num;
}



#include "ListNode.hpp"	
#include "List.hpp"

// Initializes the list
List::List() {
	this->head = NULL;
	this->length = 0;
}
// Performs a deep copy, copying each node of the other list
// into this one 
List::List(const List& other) {
	ListNode* ptr = other.head;
	ListNode* tmp = new ListNode(ptr->data);
	ListNode* tmp2;
	this->head = tmp;
	this->length = other.length;
	ptr = ptr->next;
	for (unsigned int i = 1; i < other.length; i++) {
		tmp2 = new ListNode(ptr->data);
		tmp->next = tmp2;
		ptr = ptr->next;
		tmp = tmp->next;
	}
}
// Performs a move, moving the internal list from the other
// vector to this one, and invalidates the other list pointer
// for its memory
List::List(List&& other) {
	ListNode* ptr = other.head;
}

// Deallocates the memory in this list.

List::~List() {
	ListNode* ptr = this->head;
	ListNode* del;
	for (int j = 0; j < this->length; j++) {
		del = ptr;
		ptr = ptr->next;
		delete(del);
	}
	this->head = NULL;
	this->length = 0;
}
// For all of the following functions,
// throw a const char* (string) if the index is out of
// the bounds of the list.

// Appends a ListNode onto the end of the list
//
// Throw a const char* if the index is out of bounds
void List::append(int num) {
	if (this->head == null) {
		this->head = new ListNode(num);
	}
	else {
		ListNode* tmp = this->head;
		while (tmp.next != NULL) {
			tmp = tmp.next;
		}
		tmp.next = new ListNode(num);
	}
	this->length++;
}

// Inserts a ListNode before the index
//
// Throw a const char* if the index is out of bounds.
// Appending at the end is valid (e.g. insert(list.size(), 0)
// is valid)
void List::insert(int index, int num) {
	if (this->length < index) return;
	ListNode* ptr = this->head;
	for (int i = 0; i < index; i++) ptr = ptr->next;
	ListNode* ins = new ListNode(num);
	ins->next = ptr->next;
	ptr->next = ins;
}


// Removes the ListNode at the index
//
// Throw a const char* if the index is out of bounds.
void List::remove(int index) {
	
}

// Returns the int at the index
//
// Throw a const char* if the index is out of bounds.
int List::get(int index) const {
	
	return 0;
}

// Returns the length of the list
std::size_t List::size() const {
	return this->length;
}

// Reutrns a readable/writeable reference to the element at index
//
// Throw a const char* if the index is out of bounds.
int& List::operator[](int index) {
	
	return index;
}


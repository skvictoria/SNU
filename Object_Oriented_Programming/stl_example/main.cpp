#include <iostream>

#include "List.hpp"
#include "ListNode.hpp"

void main(void)
{
	List l1;
	l1.append(0);
	l1.append(1);
	l1.append(2);

	List l2(l1);
}

## Cashier Project

**Serves a customer by taking them off the queue, and possibly putting an order, if valid, onto the order stack.**

1. Retrieves the customer from the queue, popping them off.
2. Receives the customer's desired order items in string format:
  > [number-of-items] [name-of-item-with-no-spaces]
  
3. Multiple items are separated simply by a space
4. If the Cashier detects an order for an invalid item that is not on the menu, it must expel() the customer.
5. Must calculate the cost of all the items ordered, and charge the customer.
6. If the customer does not have enough money to pay, do not charge the customer, but instead, expel() them.
7. Once paid for, the order items must be consolidated into an Order, which is tagged with the unique customer ID generated at the beginning of this function
8. push it onto the stack.

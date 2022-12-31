#include "Order.hpp"

Order::Order(std::size_t id_, std::vector<std::string> items_) :
    id(id_),
    items(items_) {
}

std::size_t Order::get_id() const { return id; }

std::vector<std::string> Order::get_items() const { return items; }

bool operator== (const Order& lhs, const Ord& rhs) {
    return lhs.get_id() == rhs.get_id() &&
        lhs.get_items() == rhs.get_items();
}

bool operator!= (const Order& lhs, const Order& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& lhs, const Order& rhs) {
    lhs << "Order(" << rhs.id;
    for (const auto& it : rhs.get_items()) {
        lhs << "|" << it;
    }
    lhs << ")";
    return lhs;
}

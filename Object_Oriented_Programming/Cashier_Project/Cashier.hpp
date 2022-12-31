#pragma once

#ifndef EE205_CASHIER_HPP
#define EE205_CASHIER_HPP

#include <iostream>
#include <string>

class Cashier {
private:
    
    int uid_count;
    double money;

public:
    
    Cashier(double money_);
    double get_money() const;
    void serve_customer();
    
};



#endif // EE205_CASHIER_HPP
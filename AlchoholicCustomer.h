//
// Created by sharon on 2/22/20.
//

#ifndef FINALHW1_ALCHOHOLICCUSTOMER_H
#define FINALHW1_ALCHOHOLICCUSTOMER_H


#include "Customer.h"

class AlchoholicCustomer : public Customer {
public:
    AlchoholicCustomer(std::string name, int id);
    virtual ~AlchoholicCustomer() = default;
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
    bool reachedMax;
    int lastPrice;
};


#endif //FINALHW1_ALCHOHOLICCUSTOMER_H

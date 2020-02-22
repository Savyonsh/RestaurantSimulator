//
// Created by sharon on 2/22/20.
//

#ifndef FINALHW1_CHEAPCUSTOMER_H
#define FINALHW1_CHEAPCUSTOMER_H


#include "Customer.h"

class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    virtual ~CheapCustomer() = default;
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
    bool ordered;
};

#endif //FINALHW1_CHEAPCUSTOMER_H

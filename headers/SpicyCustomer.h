#ifndef FINALHW1_SPICYCUSTOMER_H
#define FINALHW1_SPICYCUSTOMER_H

#include "Customer.h"

class SpicyCustomer : public Customer {
public:
    SpicyCustomer(std::string name, int id);
    virtual ~SpicyCustomer() = default;
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
    bool ordered;
};


#endif //FINALHW1_SPICYCUSTOMER_H

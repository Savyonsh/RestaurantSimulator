#ifndef FINALHW1_VEGETARIANCUSTOMER_H
#define FINALHW1_VEGETARIANCUSTOMER_H


#include "Customer.h"

class VegetarianCustomer : public Customer {
public:
    VegetarianCustomer(std::string name,int id);
    virtual ~VegetarianCustomer() = default;
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
};

#endif //FINALHW1_VEGETARIANCUSTOMER_H

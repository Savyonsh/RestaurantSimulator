#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"


class Customer{
public:
    Customer(std::string c_name, int c_id);
    Customer(const Customer &other);
    virtual ~Customer()=0;
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;

private:
    const std::string name;
    const int id;
};

#endif
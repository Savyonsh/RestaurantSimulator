//
// Created by sharon on 2/22/20.
//

#include "CheapCustomer.h"
using namespace std;

CheapCustomer::CheapCustomer(string name, int id): Customer(std::move(name),id),ordered(false) {}

vector<int> CheapCustomer::order(const vector<Dish> &menu) {
    vector<int> ret;
    if(!ordered) {
        int minPrice = INT32_MAX;
        int cheapestDish = -1;
        for (unsigned int i = 0; i < menu.size(); i++) {
            if (menu[i].getPrice() < minPrice) {
                minPrice = menu[i].getPrice();
                cheapestDish = menu[i].getId();
            }
        }
        if (cheapestDish != -1)
            ret.push_back(cheapestDish);
        ordered = true;
    }
    return ret;
}
string CheapCustomer::toString() const {return to_string(getId())+" "+getName();}


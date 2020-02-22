//
// Created by sharon on 2/22/20.
//

#include "VegetarianCustomer.h"

using namespace std;

VegetarianCustomer::VegetarianCustomer(string name, int id): Customer(std::move(name),id) {}

vector<int> VegetarianCustomer::order(const vector<Dish> &menu) {

    vector<int> ret;
    bool found = false;

    for (unsigned int i = 0; i < menu.size(); i++) {
        if (menu[i].getType() == VEG) {
            ret.push_back(menu[i].getId());
            found = true;
            break;
        }
    }
    if (found) {
        int maxPrice = -1;
        int maxBevId = -1;
        for (unsigned int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == BVG) {
                if (menu[i].getPrice() > maxPrice) {
                    maxPrice = menu[i].getPrice();
                    maxBevId = menu[i].getId();
                }
            }
        }
        ret.push_back(maxBevId);
    }
    return ret;
}
string VegetarianCustomer::toString() const {
    return std::to_string(getId())+" "+getName();
}

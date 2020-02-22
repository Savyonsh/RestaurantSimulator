//
// Created by sharon on 2/22/20.
//

#include "../headers/SpicyCustomer.h"

using namespace std;

SpicyCustomer::SpicyCustomer(string name, int id):Customer(std::move(name),id),ordered(false){}

vector<int> SpicyCustomer::order(const vector<Dish> &menu) {
    vector<int> ret;
    if (!ordered) {
        int maxPriceSpc = 0;
        int mostExpSpcId = -1;
        for (unsigned int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == SPC) {
                if (menu[i].getPrice() > maxPriceSpc) {
                    maxPriceSpc = menu[i].getPrice();
                    mostExpSpcId = menu[i].getId();
                }
            }
        }
        if (mostExpSpcId != -1) {
            ret.push_back(mostExpSpcId);
            ordered = true;
        }
        return ret;

    } else {
        int minPriceBvg = INT32_MAX;
        int cheapestBvgId = -1;
        for (unsigned int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == BVG) {
                if (menu[i].getPrice() < minPriceBvg) {
                    minPriceBvg = menu[i].getPrice();
                    cheapestBvgId = menu[i].getId();
                }
            }
        }
        if (cheapestBvgId != -1)
            ret.push_back(cheapestBvgId);
        else
            ret.erase(ret.begin());
    }
    return ret;
}

std::string SpicyCustomer::toString() const {    return std::to_string(getId())+" "+getName();}



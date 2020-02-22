//
// Created by sharon on 2/22/20.
//

#include "AlchoholicCustomer.h"

using namespace std;

AlchoholicCustomer::AlchoholicCustomer(string name, int id): Customer(std::move(name),id),reachedMax(false),lastPrice(-1){}

vector<int> AlchoholicCustomer::order(const vector<Dish> &menu) {
    vector<int> ret;
    int cheapestAlcID = -1;
    if (lastPrice == -1) {//initialing first order with the cheapest one on the menu
        lastPrice = INT32_MAX;
        for (auto i : menu)
            if (i.getPrice() < lastPrice && i.getType() == ALC) {
                lastPrice = i.getPrice();
                cheapestAlcID = i.getId();
            }
        ret.push_back(cheapestAlcID);
        return ret;
    }
    if (!reachedMax) {
        for (unsigned int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == ALC && menu[i].getPrice() > lastPrice) {
                cheapestAlcID = menu[i].getId();
                lastPrice = menu[i].getPrice();
                break;
            }
        }
        if (cheapestAlcID != -1) {
            ret.push_back(cheapestAlcID);
        } else { reachedMax = false; }
    }
    return ret;
}

string AlchoholicCustomer::toString() const {return to_string(getId())+" "+getName();}

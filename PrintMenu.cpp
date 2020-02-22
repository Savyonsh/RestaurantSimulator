
#include "Restaurant.h"
#include "Action.h"
#include "Dish.h"
#include <vector>
#include <iostream>

PrintMenu::PrintMenu() : BaseAction() {}

inline std::string checkEnum(int i) {
    if (i == 0)
        return "VEG";
    if (i == 1)
        return "SPC";
    if (i == 2)
        return "BVG";
    if (i == 3)
        return "ALC";
    return "";
}

void PrintMenu::act(Restaurant &restaurant) {
    for (const auto &i : restaurant.getMenu())
        std::cout <<i.getName() <<" "<< checkEnum(i.getType()) <<" " << i.getPrice() << "NIS" << std::endl;
    complete();
}

std::string PrintMenu::toString() const {
    std::string toString = "menu";
    if (getStatus() == COMPLETED)
        toString += " Completed";
    if (getStatus() == PENDING)
        toString += " Pending";
    return toString;
}

PrintMenu* PrintMenu::clone() const { return new PrintMenu(*this);}
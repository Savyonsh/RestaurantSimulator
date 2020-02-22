#include "Action.h"
#include "Restaurant.h"
#include "typeinfo"
#include <iostream>
#include <vector>

PrintActionsLog::PrintActionsLog() : BaseAction() {}

void PrintActionsLog::act(Restaurant &restaurant) {
    for (auto i : restaurant.getActionsLog()) {
        std::cout << i->toString() << std::endl;
    }
    complete();
}

std::string PrintActionsLog::toString() const {
    std::string toString = "log";
    if (getStatus() == COMPLETED)
        toString += " Completed";
    if (getStatus() == PENDING)
        toString += " Pending";
    return toString;
}

PrintActionsLog* PrintActionsLog::clone() const {return new PrintActionsLog(*this);}
#include "../headers/Restaurant.h"
#include "../headers/Action.h"

extern Restaurant* backup;

RestoreResturant::RestoreResturant() : BaseAction() {}

void RestoreResturant::act(Restaurant &restaurant) {
    if (backup == nullptr)
        error("No backup available");
    else {
        restaurant = *backup;
        complete();
    }
}

std::string RestoreResturant::toString() const {
    std::string toString;
    if(getStatus() == COMPLETED)
        return "restore Completed";
    else
        return "restore Pending";
}

RestoreResturant* RestoreResturant::clone() const { return new RestoreResturant(*this);}
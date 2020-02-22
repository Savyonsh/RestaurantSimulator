#include "../headers/Action.h"
#include "../headers/Restaurant.h"

extern Restaurant* backup;

BackupRestaurant::BackupRestaurant() : BaseAction() {}

void BackupRestaurant::act(Restaurant &restaurant) {
    backup = new Restaurant(restaurant);
    complete();
}

std::string BackupRestaurant::toString() const {
    std::string toString;
    if(getStatus() == COMPLETED)
        return "backup Completed";
    else
        return "backup Pending";
}

BackupRestaurant* BackupRestaurant::clone() const {return new BackupRestaurant(*this);}
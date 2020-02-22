#include "../headers/Action.h"
#include "../headers/Restaurant.h"

CloseAll::CloseAll() : BaseAction() {}

void CloseAll::act(Restaurant &restaurant) {
    int tableId = 0;
    for (auto i : restaurant.getTables()) {
        if (i->isOpen() && tableId < restaurant.getNumOfTables()) {
            Table *tmp = restaurant.getTable(tableId);
            std::cout << "Table " << tableId << " " << "was closed." << " " << tmp->getBill() << "NIS" << std::endl;
            tmp->closeTable();
        }
        tableId++;
    }
    restaurant.close();
    complete();
}

std::string CloseAll::toString() const {
std::string toReturn = "close all ";
if(getStatus()==COMPLETED)
    return  toReturn += "Completed";
else
    return toReturn += "Pending";
}

CloseAll* CloseAll::clone() const {return new CloseAll(*this);}
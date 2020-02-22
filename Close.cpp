#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
#include <iostream>
#include <vector>
#include "Customer.h"

Close::Close(int id) : BaseAction() , tableId(id) {}

void Close::act(Restaurant &restaurant) {
    Table* tmp = restaurant.getTable(tableId);
    if(tmp == nullptr)
        error("Table does not exist or not open");
    else if(!tmp->isOpen())
        error("Table does not exist or not open");
    else
    {
        std::cout << "Table "<< tableId <<" " << "was closed." <<" "<< tmp->getBill() << "NIS" << std::endl;
        tmp->closeTable();
        complete();
    }
}

std::string Close::toString() const {
    std::string toReturn = "close " + std::to_string(tableId);
    if(getStatus() == COMPLETED)
        toReturn += "Completed";
    else if(getStatus() == ERROR)
        toReturn += "Error: " + getErrorMsg();
    else if(getStatus() == PENDING)
        toReturn += "Pending";
    return toReturn;
}

Close* Close::clone() const {return new Close(*this);}
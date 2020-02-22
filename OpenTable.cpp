#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
#include "VegetarianCustomer.h"
#include "AlchoholicCustomer.h"
#include "CheapCustomer.h"
#include "SpicyCustomer.h"
#include <vector>
#include <iostream>


OpenTable::OpenTable(int id, std::vector<Customer *> &customersList) : BaseAction(), tableId(id), customers(customersList) {}

OpenTable::~OpenTable() {
    for (auto i : customers)
        delete i;
}

void OpenTable::act(Restaurant &restaurant) {
        Table* tmp = restaurant.getTable(tableId);
        if(tmp!= nullptr) {
            if (tableId < 0 || tableId > restaurant.getNumOfTables())
                error("Table does not exist or is already open");
            else if (tmp->isOpen())
                error("Table does not exist or is already open");
            else if ((unsigned)tmp->getCapacity() < customers.size())
                error("This table cannot contain all of the customers");
            else {
                tmp->openTable();
                for (auto i : customers) {
                    tmp->addCustomer(i);
                }
                complete();
            }
        }
}

std::string OpenTable::toString() const {
    std::string toReturn = "open " + std::to_string(tableId);
    for (auto i : customers) {
        if (dynamic_cast<VegetarianCustomer *>(i))
            toReturn += +" " + i->getName() + ",veg";
        if (dynamic_cast<AlchoholicCustomer *>(i))
            toReturn += +" " + i->getName() + ",alc";
        if (dynamic_cast<CheapCustomer *>(i))
            toReturn += +" " + i->getName() + ",chp";
        if (dynamic_cast<SpicyCustomer *>(i))
            toReturn += +" " + i->getName() + ",spc";
    }
    if (getStatus() == COMPLETED)
        toReturn += " Completed";
    else if (getStatus() == ERROR)
        toReturn += " Error: " + getErrorMsg();
    else if (getStatus() == PENDING)
        toReturn += " Pending";

    return toReturn;
}

OpenTable* OpenTable::clone() const {return new OpenTable(*this);}



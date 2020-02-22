#include "../headers/Action.h"
#include "../headers/Table.h"
#include "../headers/Restaurant.h"
#include "../headers/Customer.h"
#include <iostream>
#include <vector>

PrintTableStatus::PrintTableStatus(int id) : BaseAction() , tableId(id) {}

void PrintTableStatus::act(Restaurant &restaurant) {
    if ((unsigned)tableId < restaurant.getTables().size()) {
            Table *tmp = restaurant.getTable(tableId);
        if (tmp != nullptr) {
            if (!tmp->isOpen()) std::cout << "Table " << tableId << " status: closed" << std::endl;
            else {
                std::cout << "Table " << tableId << " status: open \nCustomers:" << std::endl;
                for (auto i : tmp->getCustomers())
                    std::cout << i->getId() <<" " << i->getName() << std::endl;
                std::cout << "Orders:" << std::endl;
                for (auto i : tmp->getOrders())
                    std::cout << i.second.getName() <<" " << i.second.getPrice() << " "<< i.first << std::endl;
                std::cout << "Current bill: " << std::to_string(tmp->getBill()) <<"NIS" << std::endl;
            }
            complete();
        }
    }
}

std::string PrintTableStatus::toString() const {
    std::string toString = "status " + std::to_string(tableId);
    if (getStatus() == COMPLETED)
        toString += " Completed";
    if (getStatus() == PENDING)
        toString += " Pending";
    return toString;
}

PrintTableStatus* PrintTableStatus::clone() const {return new PrintTableStatus(*this);}
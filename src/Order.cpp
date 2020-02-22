#include "../headers/Action.h"
#include "../headers/Table.h"
#include "../headers/Restaurant.h"

using namespace std;

Order::Order(int id) : BaseAction(), tableId(id) {}

void Order::act(Restaurant &restaurant) {
    Table *tmp = restaurant.getTable(tableId);
    if (tmp != nullptr) {
        if (tmp->isOpen()) {
            tmp->order(restaurant.getMenu());
            complete();
        } else
            error("Table does not exist or not open");
    }
}

string Order::toString() const {
    string toReturn = "order " + to_string(tableId) + " ";
    if(getStatus() == COMPLETED)
        toReturn += "Completed";
    else if(getStatus() == ERROR)
        toReturn += "Error: " + getErrorMsg();
    else if(getStatus() == PENDING)
        toReturn += "Pending";
    return toReturn;
}

Order* Order::clone() const {return new Order(*this);}

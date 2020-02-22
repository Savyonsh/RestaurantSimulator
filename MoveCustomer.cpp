#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
#include "Customer.h"

using namespace std;
MoveCustomer::MoveCustomer(int src, int dst, int customerId) : BaseAction(), srcTable(src), dstTable(dst), id(customerId) {}

void MoveCustomer::act(Restaurant &restaurant) {
    Table *destinationTable = restaurant.getTable(dstTable);
    if (destinationTable == nullptr)
        error("Cannot move customer");
    else if ((unsigned)destinationTable->getNumOfCus() == destinationTable->getCapacity() || !destinationTable->isOpen())
        error("Cannot move customer");
    else {
        Table *src = restaurant.getTable(srcTable);
        Customer *toAdd = src->getCustomer(id);
        if (toAdd != nullptr) {
            for (const auto &i : src->getOrders())
                if (i.first == id)
                    destinationTable->getOrders().push_back(i);
            destinationTable->addCustomer(toAdd);
            src->removeCustomer(id);
            complete();
        } else { error("Cannot move customer"); }
    }
}

std::string MoveCustomer::toString() const {
    std::string toString = "move " + std::to_string(srcTable) +" " + std::to_string(dstTable) +" "+ std::to_string(id);
    if (getStatus() == COMPLETED)
        toString += " Completed";
    if (getStatus() == PENDING)
        toString += " Pending";
    if (getStatus() == ERROR)
        toString += " Error: " + getErrorMsg();
    return toString;
}

MoveCustomer* MoveCustomer::clone() const {return new MoveCustomer(*this);}
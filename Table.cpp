#include <iostream>
#include "Table.h"
#include "AlchoholicCustomer.h"
#include "SpicyCustomer.h"
#include "CheapCustomer.h"
#include "VegetarianCustomer.h"
#include <vector>

using namespace std;

Table::Table(int t_capacity) : capacity(t_capacity),open(false),customersList(),orderList(),currentNumOfCustomers(0) {}

//move constructor
Table::Table(Table &&other) : Table(other.capacity) {
    capacity = other.capacity;
    open = other.open;
    other.customersList=std::move(customersList);
    other.orderList=std::move(orderList);
}
//move assignment
Table& Table::operator=(Table &&other) {
    if(this!=&other)
    {
        capacity = other.capacity;
        open = other.open;
        other.customersList=std::move(customersList);
        other.orderList=std::move(orderList);
    }
    return  *this;
}
//copy assignment
Table Table::operator=(Table &other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}

Table::Table(const Table &other) : Table(other.getCapacity()) {copy(other);}

void Table::copy(const Table &other) {
    capacity = other.capacity;
    open = other.open;
    for (auto i: other.customersList) {
        if (dynamic_cast<AlchoholicCustomer *>(i))
            customersList.push_back(new AlchoholicCustomer(i->getName(), i->getId()));
        if (dynamic_cast<VegetarianCustomer *>(i))
            customersList.push_back(new VegetarianCustomer(i->getName(), i->getId()));
        if (dynamic_cast<SpicyCustomer *>(i))
            customersList.push_back(new SpicyCustomer(i->getName(), i->getId()));
        if (dynamic_cast<CheapCustomer *>(i))
            customersList.push_back(new CheapCustomer(i->getName(), i->getId()));
    }

    for (auto i : other.orderList) {
        OrderPair x(i.first, i.second);
        orderList.push_back(x);
    }
}

int Table::getCapacity() const { return capacity;}

void Table::addCustomer(Customer *customer) {
    if (currentNumOfCustomers < capacity)
        customersList.push_back(customer);
}

void Table::closeTable() {
    customersList.clear();
    orderList.clear();
    open = false;
    currentNumOfCustomers = 0;
}

int Table::getBill(){
    int currentBill = 0;
    for (auto i:orderList)
        currentBill += i.second.getPrice();
    return currentBill;
}

int Table::getNumOfCus() const { return currentNumOfCustomers;}

Customer* Table::getCustomer(int id) {
    for (auto i : customersList)
        if(i->getId() == id)
            return i;

    return nullptr;
}

void Table::order(const std::vector<Dish> &menu) {
    vector<int> ordersId;
    for (auto i : customersList) {
        ordersId = i->order(menu);
        for (auto j : ordersId) {
            for (auto k : menu)
                if (k.getId() == j) {
                    OrderPair orderUp = OrderPair(i->getId(), k);
                    orderList.push_back(orderUp);
                    cout << i->getName() << " ordered " << k.getName() << endl;
                }
        }
    }
}

void Table::openTable() {open = true;}

bool Table::isOpen() { return  open;}

void Table::removeCustomer(int id) {
    int placeOfCustomer = -1;

//Finding place of customer in vector of customers
    for (unsigned int size_c = 0; size_c < customersList.size(); size_c++) {
        if (customersList[size_c]->getId() == id) {
            placeOfCustomer = size_c;
        }
        //If found, deleting him from Customers and updating orders list
        if (placeOfCustomer != -1) {
            customersList.erase(customersList.begin() + placeOfCustomer);
            std::vector<OrderPair> updatedOrders;
            for (auto i : orderList) {
                if (i.first != id)
                    updatedOrders.push_back(i);
            }
            orderList.clear();
            orderList.swap(updatedOrders);

        }
    }
}

std::vector<Customer*>& Table::getCustomers() { return customersList;}

std::vector<OrderPair>& Table::getOrders() { return orderList;}



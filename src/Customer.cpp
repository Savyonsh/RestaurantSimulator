#include "../headers/Customer.h"
#include "../headers/Dish.h"

using namespace std;

//constructor
Customer::Customer(std::string c_name, int c_id) : name(c_name),id(c_id){}
//destructor
Customer::~Customer() = default;
//copy_constructor
Customer::Customer(const Customer &other):name(other.name),id(other.id) {}

std::string Customer::getName() const {return name;}

int Customer::getId() const { return id;}





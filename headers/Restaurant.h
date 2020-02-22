#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{
public:
    Restaurant();
    Restaurant(const std::string &configFilePath);
    Restaurant(const Restaurant &other);
    ~Restaurant();
    Restaurant(Restaurant &&other);
    Restaurant & operator = (Restaurant &&other);
    Restaurant operator = (Restaurant &other);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu();
    const std::vector<Table*> getTables();
    void close();

private:
    bool open;
    int numOfTables;
    int customersId;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    void copy(const Restaurant &other);
    void clear();
};

#endif
#include "../headers/Restaurant.h"
#include "../headers/Dish.h"
#include "../headers/Action.h"
#include "../headers/Table.h"
#include "../headers/Customer.h"
#include "../headers/AlchoholicCustomer.h"
#include "../headers/VegetarianCustomer.h"
#include "../headers/CheapCustomer.h"
#include "../headers/SpicyCustomer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace std;

Restaurant::Restaurant() : open(false),numOfTables(0),customersId(0),tables(),menu(),actionsLog() {}

inline std::string clearText(std::string &toClear) {
    if (toClear[0] == ' ' || toClear[0] == '\r') toClear = &toClear[1];
    if (toClear[toClear.size() - 1] == ' ' || toClear[toClear.size() - 1] == '\r') toClear[toClear.size() - 1] = 0;
    return toClear;
}

Restaurant::Restaurant(const std::string &configFilePath) : Restaurant() {
    std::ifstream x;
    x.open(configFilePath);
    std::string configFile;
    //Initializing tables and menu
    long p = 0;
    long n = 0;
    int counter = 0;
    int placeInText = 0;
    int menuId = 0;
    std::string currentLine;
    //Reading line by line from the string

    while (!x.eof()) {
        getline(x,currentLine);
        if (!currentLine.empty() && currentLine.at(0) != '\r' && currentLine.at(0) != '#') {
            if (placeInText == 0) {//Number of tables
                clearText(currentLine);
                numOfTables = stoi(currentLine);
                placeInText++;
            } else if (placeInText == 1) {//Table description
                int toIsert = 0;
                while (p != -1 && n != -1 && toIsert < numOfTables) {
                    n = currentLine.find(',', p);
                    std::string tableD = currentLine.substr((unsigned)p, (unsigned)(n - p));
                    clearText(tableD);
                    int def = stoi(tableD);
                    tables.push_back(new Table(def));
                    p = n + 1;
                }
                placeInText++;
            } else {//This is the menu
                p = 0;
                n = 0;
                counter = 0;
                std::string d_name;
                int d_price = 0;
                DishType d_type;
                while (p != -1 && n != -1) {
                    n = currentLine.find(',', p);
                    std::string dishPart = currentLine.substr((unsigned)p, (unsigned)(n - p));
                    clearText(dishPart);
                    if (counter == 0)
                        d_name = dishPart;
                    if (counter == 1)//Dish Type
                    {
                        if (dishPart == "VEG")
                            d_type = VEG;
                        if (dishPart == "SPC")
                            d_type = SPC;
                        if (dishPart == "BVG")
                            d_type = BVG;
                        if (dishPart == "ALC")
                            d_type = ALC;
                    }
                    if (counter == 2)
                        d_price = stoi(dishPart);
                    counter++;
                    p = n + 1;
                }
                Dish y = Dish(menuId, d_name, d_price, d_type);
                menu.push_back(y);
                menuId++;

            }

        }
    }
    x.close();
}

void Restaurant::copy(const Restaurant &other) {
    open = other.open;
    numOfTables = other.numOfTables;
    customersId = other.customersId;
    std::vector<Dish> menuToCopy;
    for (const auto &i : other.menu) {
        Dish x(i.getId(), i.getName(), i.getPrice(), i.getType());
        menu.push_back(x);
    }
    for (const auto &i : other.tables) {
        Table *x = new Table(*i);
        tables.push_back(x);
    }

    for (const auto &i : other.actionsLog) {
        string analyze = i->toString();
        string action, tableId;
        int tabId;
        unsigned long p = analyze.find(' ');
        action = analyze.substr(0, p);
        //the new tables already copied new customers
        if (action == "open") {
            tableId = analyze.substr(p,analyze.size()-p);
            p = tableId.find(' ');
            tableId.substr(0,p);
            tabId = stoi(tableId);
            actionsLog.push_back(new OpenTable(tabId, tables[tabId]->getCustomers()));
        }
        else
            actionsLog.push_back(i->clone());
    }
}

//copy constractor
Restaurant::Restaurant(const Restaurant &other) : Restaurant() { copy(other);}

//move constractor
Restaurant::Restaurant(Restaurant &&other) : Restaurant()  {

    other.tables = std::move(tables);
    other.menu = std::move(menu);
    other.actionsLog = std::move(actionsLog);
}

void Restaurant::clear() {
    open = false;
    numOfTables = 0;
    customersId = 0;
    for (auto i : tables)
        delete i;
    for (auto i : actionsLog)
        delete i;
}

//copy assignment operator
Restaurant& Restaurant::operator=(Restaurant &&other) {
    if(this!=&other) {
        copy(other);
    }
    return *this;
}

//move assignment operator
Restaurant Restaurant::operator=(Restaurant &other) {
    if (this != &other) {
        clear();
        open = other.open;
        customersId = other.customersId;
        numOfTables = other.numOfTables;
        tables = move(other.tables);
        menu = move(other.menu);
        actionsLog = move(other.actionsLog);
    }
    return *this;
}

//destractor
Restaurant::~Restaurant() {clear();}

inline void initializingFromInput(std::string &action, std::vector<std::string> &args) {
    std::string line;
    std::getline(std::cin, line);
    long p = 0;
    p = line.find(' ');
    if (p == -1 || line.empty()) {
        action = line;
        return;
    } else {
        action = line.substr(0, (unsigned) p);
        line.erase(0, (unsigned) (p + 1));
        p = 0;
        while (p != -1) {
            p = line.find(' ');
            if (p == -1)
                args.push_back(line);
            else
                args.push_back(line.substr(0, (unsigned) p));
            line.erase(0, (unsigned) (p + 1));
        }
    }

}

inline Customer* analyzeTypeOfCustomer(std::string &customer, int &id) {//This function's input is a substring from the action open table
    //It analyze the type of customer by the value that has been inserted (i.e:veg)
    //The function's output is a pointer to a created object type Customer according to the analyze.
    long p = 0;
    p = customer.find(',');
    if (p != -1) {
        std::string customerName = customer.substr(0, p);//name
        customer.erase(0, (unsigned) p + 1);//type
        clearText(customer);
        clearText(customerName);
        if (customer == "ALC" || customer == "alc")
            return new AlchoholicCustomer(customerName, id);
        if (customer == "veg" || customer == "VEG")
            return new VegetarianCustomer(customerName, id);
        if (customer == "chp" || customer == "CHP")
            return new CheapCustomer(customerName, id);
        if (customer == "spc" || customer == "SPC")
            return new SpicyCustomer(customerName, id);

    }
    return nullptr;
}

void Restaurant::start() {
    open = true;
    std::cout << "The restaurant is now open!" << std::endl;
    std::cout << "The actions are: \n 1. Close the system - Syntax: closall \n"
                 "2.Open table - Syntax: open <table_id> <customer_1>,<customer_1_strategy> ...\n"
                 "      <customer_ strategy> is the 3-letter code for the ordering strategy as follows: \n"
                 "      veg (Vegetarian Customer)| chp (Cheap Customer)| spc (Spicy Customer)| alc (Alcoholic Customer) \n"
                 "3. Order - Syntax: order <table_id>.\n"
                 "4. Move Costumer - Syntax: move <origin_table_id> <dest_table_id> <customer_id>\n"
                 "5. Close table - Syntax: close <table_id>\n"
                 "6. Print menu - Syntax: menu\n"
                 "7. Print table status - Syntax: status <table_id>\n"
                 "8. Print action log - Syntax: log\n"
                 "9. Backup restaurant - Syntax: backup \n"
                 "10. Restore restaurant – Syntax: restore\n" << std::endl;
    std::string action;
    std::vector<std::string> args;
    initializingFromInput(action, args);
    while (action != "closeall") {
        if (action == "open") {
            int tableId = stoi(args[0]);
            //deleting the argument for tableId
            args.erase(args.begin() + 0);
            std::vector<Customer *> customerList;
            for (auto i: args) {
                Customer *x = analyzeTypeOfCustomer(i, customersId);
                customerList.push_back(x);
                customersId++;
            }
            BaseAction *op = new OpenTable(tableId, customerList);
            op->act(*this);
            if (op->getStatus() == ERROR) {
                for (unsigned int size_c = 0;size_c<customerList.size();size_c++) {
                    customersId--;
                }
            }
            actionsLog.push_back(op);
        }
        if (action == "order") {
            int tableId = stoi(args[0]);
            BaseAction *ord = new Order(tableId);
            ord->act(*this);
            actionsLog.push_back(ord);
        }
        if (action == "move") {
            int srcTable = stoi(args[0]);
            int dstTable = stoi(args[1]);
            int cosId = stoi(args[2]);
            BaseAction *mov = new MoveCustomer(srcTable, dstTable, cosId);
            mov->act(*this);
            actionsLog.push_back(mov);
        }
        if (action == "close") {
            int tableId = stoi(args[0]);
            Close cl(tableId);
            cl.act(*this);
            actionsLog.push_back(&cl);

        }
        if (action == "menu") {
            BaseAction *pMenu = new PrintMenu();
            pMenu->act(*this);
            actionsLog.push_back(pMenu);
        }
        if (action == "status") {
            int tableId = stoi(args[0]);
            BaseAction *pTableS = new PrintTableStatus(tableId);
            pTableS->act(*this);
            actionsLog.push_back(pTableS);
        }
        if (action == "log") {
            BaseAction *pActionLog = new PrintActionsLog();
            pActionLog->act(*this);
            actionsLog.push_back(pActionLog);
        }
        if (action == "backup") {
            BaseAction *buRes = new BackupRestaurant();
            buRes->act(*this);
            actionsLog.push_back(buRes);
        }
        if (action == "restore") {
            BaseAction *resRes = new RestoreResturant();
            resRes->act(*this);
            actionsLog.push_back(resRes);
        }
        args.clear();
        action = "";
        initializingFromInput(action, args);
    }
    BaseAction *cl = new CloseAll();
    cl->act(*this);
    actionsLog.push_back(cl);
}

std::vector<Dish>& Restaurant::getMenu() { return menu;}

int Restaurant::getNumOfTables() const { return numOfTables;}

Table* Restaurant::getTable(int ind) {
    if ((unsigned)ind < tables.size() && ind >= 0)
        return tables[ind];
    return nullptr;
}

void Restaurant::close() {open = false;}

const std::vector<BaseAction*>& Restaurant::getActionsLog() const {return actionsLog;}

const std::vector<Table*> Restaurant::getTables() {return tables;}
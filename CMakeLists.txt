cmake_minimum_required(VERSION 3.12)
project(FinalHW1)

set(CMAKE_CXX_STANDARD 14)

add_executable(FinalHW1 src/BackupRestaurant.cpp src/BaseAction.cpp src/Close.cpp src/CloseAll.cpp src/Customer.cpp src/Dish.cpp src/MoveCustomer.cpp src/OpenTable.cpp src/Order.cpp src/PrintActionsLog.cpp src/PrintTableStatus.cpp src/PrintMenu.cpp src/Restaurant.cpp src/RestoreResturant.cpp src/Table.cpp main.cpp src/AlchoholicCustomer.cpp src/SpicyCustomer.cpp headers/SpicyCustomer.h src/CheapCustomer.cpp headers/CheapCustomer.h src/VegetarianCustomer.cpp headers/VegetarianCustomer.h src/AlchoholicCustomer.cpp headers/AlchoholicCustomer.h)
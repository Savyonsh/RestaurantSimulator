#include "../headers/Action.h"
#include <string>
#include <iostream>

BaseAction::BaseAction() :errorMsg("") ,status(PENDING){}

void BaseAction::error(std::string errorMsg) {
    std::cout << "Error: " << errorMsg << std::endl;
    status = ERROR;
    this->errorMsg = errorMsg;
}

void BaseAction::complete() {status = COMPLETED;}

std::string BaseAction::getErrorMsg() const { return errorMsg;}

ActionStatus BaseAction::getStatus() const { return status;}
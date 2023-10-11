#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Enums.h"
#include "Commands.h"

class Controller
{
    public:
    ECommandResult HandleCommand(ICommand* cmd);
    private:
    ECommandResult HandleAuthorize(Authorize* cmd);
};

#endif

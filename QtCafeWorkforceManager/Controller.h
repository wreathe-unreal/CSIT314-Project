#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Commands.h"

class Controller
{
    public:
        void HandleCommand(ICommand* cmd);
};

#endif

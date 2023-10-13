#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Enums.h"
#include "Commands.h"
#include "Response.h"

class Controller
{
    public:
    Response HandleCommand(ICommand* cmd);
    private:
    Response HandleAuthorize(Authorize* cmd);

};

#endif

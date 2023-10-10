#include "Controller.h"
#include "Commands.h"


class Command;

void Controller::HandleCommand(ICommand* Cmd)
{
    if(Update* UpdateCmd = dynamic_cast<Update*>(Cmd))
    {
        //HandleUpdate(arg1, arg2);
        //Serialize();
    }
    
    if(Authorize* AuthorizeCmd = dynamic_cast<Authorize*>(Cmd))
    {

    }
};

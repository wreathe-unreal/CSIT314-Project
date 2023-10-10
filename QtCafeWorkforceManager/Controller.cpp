

void Controller::HandleCommand(Command* Cmd)
{
    if(Update* UpdateCmd = dynamic_cast<UpdateComponent*>(Cmd))
    {
        //handle Update
    }
    
    if(Authorize* AuthorizeCmd = Dynamic_cast<Authorize*>(Cmd))
    {
        //handle Authorize
    }
};
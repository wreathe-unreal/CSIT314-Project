enum ECommandType
{
    ECT_Update,
    ECT_Authorize
};
class ICommand 
{
    public:
        ECommandType CommandType;
        virtual void execute() = 0;
};

class Update : ICommand
{
    public:
        int UserID
        int AttributeID;
};

class Authorize : ICommand
{
    string Username;
    string Password;    
};
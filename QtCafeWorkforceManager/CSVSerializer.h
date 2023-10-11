#ifndef CSVSERIALIZER_H
#define CSVSERIALIZER_H
#include "UserTypes.h"
#include <vector>


class CSVSerializer
{
    private:
    std::string UserTableFilename;
    std::string ShiftTableFilename;

    public:
    static void SerializeUser(User* user, const string& filepath);
    static std::vector<User*> DeserializeUsers(const std::string& filePath);

};

#endif // CSVSERIALIZER_H

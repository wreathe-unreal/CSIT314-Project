#ifndef SERIALIZE_H
#define SERIALIZE_H
#include "UserTypes.h"
#include <vector>


class CSVSerializer
{
public:
    static std::vector<S_UserData> Serialize(const std::string& filename);
};

#endif // DESERIALIZE_H

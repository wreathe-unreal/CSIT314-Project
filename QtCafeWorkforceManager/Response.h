#ifndef RESPONSE_H
#define RESPONSE_H


#include "Enums.h"
template <typename T>
class Response
{
    public:
        Response() { this->Result = EDatabaseResult::EDR_UNINITIALIZED; }
        ~Response(){ }
        EDatabaseResult Result;
        T Data;
};

// Specialization for void
template <>
class Response<void>
{
    public:
        Response(){this->Result = EDatabaseResult::EDR_UNINITIALIZED;}
        ~Response(){}
        EDatabaseResult Result;
        // No 'data' member for void specialization
};

#endif // RESPONSE_H


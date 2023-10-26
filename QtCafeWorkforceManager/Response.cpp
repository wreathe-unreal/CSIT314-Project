#include "Response.h"


template<typename T>
Response<T>::Response()
{
    this->Result = EDatabaseResult::EDR_UNINITIALIZED;
}

Response<void>::Response()
{
    this->Result = EDatabaseResult::EDR_UNINITIALIZED;
}

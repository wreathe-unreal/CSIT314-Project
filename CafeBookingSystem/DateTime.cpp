#include "DateTime.h"


void DateTime::Parse(string& DateString)
{
    // Check the length for a valid format
    if (DateString.size() != 10)
    {
        cerr <<"Incorrect format (DD-MM-YYYY).";
        cout <<"Please enter a date:";
        DateString = cin.getline;
        Parse(DateString);
        return;
    }

    // Check the positions of dashes
    if (DateString[2] != '-' || DateString[5] != '-')
    {
        cerr <<"Incorrect format (DD-MM-YYYY).";
        cout <<"Please enter a date:";
        DateString = cin.getline;
        Parse(DateString);
        return;
    }

    // Extract day, month, and year using a stringstream
    std::stringstream ss(DateString);
    
    char dash;  // to hold the '-' characters
    
    ss >> Day >> dash >> Month >> dash >> Year;
    return;
}

void DateTime::ValidateHour()
{
}

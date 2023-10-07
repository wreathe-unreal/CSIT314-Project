#include "DateTime.h"

#include "Bid.h"


void DateTime::Parse(string& DateString)
{
    // Check the length for a valid format
    if (DateString.size() != 10)
    {
        cerr <<"Incorrect format (DD-MM-YYYY).";
        cout <<"Please enter a date:";
        DateString = cin.get();
        Parse(DateString);
        return;
    }

    // Check the positions of dashes
    if (DateString[2] != '-' || DateString[5] != '-')
    {
        cerr <<"Incorrect format (DD-MM-YYYY).";
        cout <<"Please enter a date:";
        DateString = cin.get();
        Parse(DateString);
        return;
    }

    for(int i = 0 ; i < DateString.length(); i++)
    {
        if(!isdigit(DateString[i] && i != 2 && i != 5))
        {
            cerr <<"Incorrect format (DD-MM-YYYY).";
            cout <<"Please enter a date:";
            DateString = cin.get();
            Parse(DateString);
            return;    
        }
    }
        
    // Extract day, month, and year using a stringstream
    std::stringstream ss(DateString);
    
    char dash;  // to hold the '-' characters
    
    ss >> Day >> dash >> Month >> dash >> Year;
    
    return;
}

bool DateTime::ValidateHour(Bid& bid)
{
    if(Hour > 24) //unsigned no need to check < 0
    {
        return false;
    }

    if(Hour < bid.CafeLocation->OpenHour || Hour >= bid.CafeLocation->CloseHour)
    {
        return false;
    }

    
}

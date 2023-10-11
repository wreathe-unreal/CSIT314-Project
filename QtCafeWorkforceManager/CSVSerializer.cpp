#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <qDebug>
#include "UserTypes.h"
#include "Shift.h"
#include "CSVSerializer.h"
#include "Enums.h"
#include <QDir>
#include "QApplicationGlobal.h"

std::vector<std::string> split(const std::string &s, char delimiter) 
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

void CSVSerializer::DeserializeUsers()
{
    string filePath = "../QtCafeWorkforceManager/UserTable.csv";
    std::ifstream file(filePath);
    std::string line;

    if(file.good())
    {
        qDebug() << "File exists.";
    }
    else
    {
        qDebug() << "File does not exist.";
    }
    if (!file.is_open())
    {
        qDebug() << "Error: Could not open file - " << filePath;
    }

    qDebug() << "Current directory:" << QDir::currentPath();

    // Read and discard the header
    if (!std::getline(file, line)) {
        // Handle error: even the header could not be read, the file might be empty
        std::cerr << "Error: File is empty or cannot be read" << std::endl;
        return; // or handle this appropriately
    }

    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        std::string item;

        std::getline(ss, item, ',');
        qDebug() << item;
        EUserType userType = IntToEUserType(std::stoi(item));

        std::getline(ss, item, ',');
        int userID = stoi(item);

        std::getline(ss, item, ',');
        std::string username = item;

        std::getline(ss, item, ',');
        std::string hashedPassword = item;

        std::getline(ss, item, ',');
        EStaffRole staffRole = IntToEStaffRole(stoi(item));

        std::getline(ss, item, ',');
        std::vector<std::string> shiftDates = split(item, '%');

        std::getline(ss, item, ',');
        std::vector<std::string> shiftStatusStrings = split(item, '%');
        std::vector<EShiftStatus> shiftStatusEnums;
        for(auto shiftString: shiftStatusStrings)
        {
            shiftStatusEnums.emplace_back(IntToEShiftStatus(std::stoi(item)));
        }

        for(int i = 0; i < shiftDates.size(); i++)
        {
            QApplicationGlobal::Shifts.emplace_back(new Shift(shiftDates[i], shiftStatusEnums[i]));
        }


        switch (userType) 
        {
            case EUserType::EUT_SysAdmin:
            QApplicationGlobal::Users.push_back(new SysAdmin(userID, username, hashedPassword));
                break;
            case EUserType::EUT_CafeOwner:
                QApplicationGlobal::Users.push_back(new CafeOwner(userID, username, hashedPassword));
                break;
            case EUserType::EUT_CafeManager:
                QApplicationGlobal::Users.push_back(new CafeManager(userID, username, hashedPassword));
                break;
            case EUserType::EUT_CafeStaff:
                QApplicationGlobal::Users.push_back(new CafeStaff(userID, username, hashedPassword,  QApplicationGlobal::Shifts));
                break;
        }
    }
}




//OLD SERIALIZE - new method = update objects = serialize everything on exit


//void CSVSerializer::SerializeUser(User* user, const string& filepath)
//{
//    // Check user type and cast appropriately
//    CafeStaff* staff = dynamic_cast<CafeStaff*>(user);
    
//    // Determine user type
//    EUserType userType;
//    if (dynamic_cast<SysAdmin*>(user))
//    {
//        userType = EUserType::EUT_SysAdmin;
//    }
//    else if (dynamic_cast<CafeOwner*>(user))
//    {
//        userType = EUserType::EUT_CafeOwner;
//    }
//    else if (dynamic_cast<CafeManager*>(user))
//    {
//        userType = EUserType::EUT_CafeManager;
//    }
//    else if (staff)
//    {
//        userType = EUserType::EUT_CafeStaff;
//    }
//    else
//    {
//        // Unknown user type
//        return;
//    }

//    // Open file and ensure it's ready for writing
//    ifstream inFile(filepath);
//    if (!inFile.good())
//    {
//        std::cerr << "Error opening file!" << std::endl;
//        return;
//    }

//    stringstream buffer;
//    buffer << inFile.rdbuf();
//    inFile.close();

//    // Check if user exists
//    string line;
//    bool userExists = false;
//    string replacement;

//    // Read and discard the header
//    if (!std::getline(inFile, line)) {
//        // Handle error: even the header could not be read, the file might be empty
//        std::cerr << "Error: File is empty or cannot be read" << std::endl;
//        return; // or handle this appropriately
//    }

//    while (getline(buffer, line))
//{
//        stringstream ss(line);
//        string item;

//        getline(ss, item, ','); // User type
//        getline(ss, item, ','); // User ID
//        int existingUserID = std::stoi(item);
//        if (existingUserID == user->UserID)
//        {
//            userExists = true;
//            // Prepare the CSV line
//            replacement = std::to_string(static_cast<int>(userType)) + "," +
//                          std::to_string(user->UserID) + "," +
//                          user->Username + "," +
//                          user->HashedPassword + "," +
//                          std::to_string(static_cast<int>(user->Role)) + ",";
//            if (staff)
//            {
//                for (const auto& shift : staff->Shifts)
//                {
//                    replacement += shift.Date + "%";
//                }
//                replacement += ',';
//                for (const auto& shift : staff->Shifts)
//                {
//                    replacement += to_string(EShiftStatusToInt(shift.Status)) + "%";
//                }
//            }
//            replacement.pop_back(); // Remove trailing comma
//            replacement += "\n";
//            break;
//        }
//    }

//    // Append or overwrite user data
//    ofstream outFile;
//    if (userExists)
//    {
//        // Replace line in buffer
//        string content = buffer.str();
//        size_t pos = content.find(line);
//        if (pos != string::npos)
//        {
//            content.replace(pos, line.length(), replacement);
//        }

//        outFile.open(filepath, std::ios::out | std::ios::trunc); // Open with truncate mode to overwrite
//        outFile << content;
//    }
//    else
//    {
//        outFile.open(filepath, std::ios::out | std::ios::app); // Open in append mode
//        if (!userExists)
//        {
//            // If user doesn't exist, create new entry
//            outFile << std::to_string(static_cast<int>(userType)) << ","
//                    << user->UserID << ","
//                    << user->Username << ","
//                    << user->HashedPassword << ","
//                    << static_cast<int>(user->Role);
//            if (staff)
//            {
//                for (const auto& shift : staff->Shifts)
//                {
//                    outFile << "," << shift.Date << "%";
//                }
//                outFile << ",";
//                for (const auto& shift : staff->Shifts)
//                {
//                    outFile << "," << to_string(EShiftStatusToInt(shift.Status)) << "%";
//                }
//            }
//            outFile << "\n";
//        }
//    }

//    // Close the file
//    outFile.close();
//}

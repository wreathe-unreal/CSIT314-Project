// Shift.h
#ifndef SHIFT_H
#define SHIFT_H
#include "Entity.h"
#include <QDate>

class Shift : public IEntity
{

public:
    Shift();
    ~Shift();

    int getNumChefs() const;
    void setNumChefs(int newNumChefs);

    int getShiftID() const;

    QDate getShiftDate() const;
    void setShiftDate(const QDate &newShiftDate);

    int getShiftNumber() const;
    void setShiftNumber(int newShiftNumber);

    bool getbFull() const;
    void setbFull(bool newBFull);

    int getCurChefs() const;
    void setCurChefs(int newCurChefs);

    int getNumbChefs() const;
    void setNumbChefs(int newNumbChefs);

    int getNumCashiers() const;
    void setNumCashiers(int newNumCashiers);

    int getCurCashiers() const;
    void setCurCashiers(int newCurCashiers);

    int getNumWaiters() const;
    void setNumWaiters(int newNumWaiters);

    int getCurWaiters() const;
    void setCurWaiters(int newCurWaiters);

private:
    int ShiftID;
    QDate ShiftDate;
    int ShiftNumber;
    bool bFull;
    int NumChefs;
    int CurChefs;
    int NumCashiers;
    int CurCashiers;
    int NumWaiters;
    int CurWaiters;
};

#endif // SHIFT_H

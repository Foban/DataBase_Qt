#include "cartage.h"

Cartage::Cartage():
    year(0)
{
    repairtime.day = 0;
    repairtime.month = 0;
    repairtime.year = 0;
}

Cartage::Cartage(QString newMark, QString newColor, short int newYear, QString newStatus, Data newTime):
    mark(newMark), color(newColor), year(newYear), status(newStatus), repairtime(newTime)
{
}

Cartage::~Cartage()
{
}


///////////////////////////////////////////////////


QString Cartage::getMark()
{
    return mark;
}

QString Cartage::getColor()
{
    return color;
}

short int Cartage::getYear()
{
    return year;
}

QString Cartage::getStatus()
{
    return status;
}

Data Cartage::getRepairTime()
{
    return repairtime;
}

///////////////////////////////////////////////

void Cartage::putColor(QString newColor)
{
    color = newColor;
}

void Cartage::putMark(QString newMark)
{
    mark = newMark;
}

void Cartage::putYear(short int newYear)
{
    year = newYear;
}

void Cartage::putStatus(QString newStatus)
{
    status = newStatus;
}

void Cartage::putRepairTime(Data newRepairTime)
{
    repairtime.day = newRepairTime.day;
    repairtime.month = newRepairTime.month;
    repairtime.year = newRepairTime.year;
}

void Cartage::putRepairTime(short int day, short int month, short int year)
{
    repairtime.day = day;
    repairtime.month = month;
    repairtime.year = year;
}

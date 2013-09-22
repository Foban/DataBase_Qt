#ifndef CARTAGE_H
#define CARTAGE_H

#include <QString>

struct Data{
    short int year, month, day;
};

class Cartage
{
public:
    Cartage();
    Cartage(QString, QString, short int, QString, Data);
    ~Cartage();

    QString getMark();
    QString getColor();
    short int getYear();
    QString getStatus();
    Data getRepairTime();



    void putMark(QString);
    void putColor(QString);
    void putYear(short int);
    void putStatus(QString);
    void putRepairTime(Data);
    void putRepairTime(short int, short int, short int);

private:
    QString mark;
    QString color;
    short int year;
    QString status;
    Data repairtime;
};

#endif // CARTAGE_H

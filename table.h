#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QTableWidget>
#include <QByteArray>
#include <QFile>
#include <QDialog>
#include <QFileDialog>

#include "cartage.h"
#include "mylist.h"

class Table : public QWidget
{
    Q_OBJECT
public:
    Table(QWidget *parent = 0);
    ~Table();


private:
    QPushButton *newcartage;
    QPushButton *save;
    QPushButton *open;
    QDialog *deleted;
    void from_list_to_table();
    void after_sort();

    QTableWidget *table;
    QGridLayout *mainlayout;

    MyList data;
    int tableSize;
signals:

public slots:
    void makeNewCartage();
    void changeData(int, int);
    void openTable();
    void saveTable();
    void sortTable(int);
    void deleteDialogCartage();
    void deleteCartage();

};

#endif // TABLE_H

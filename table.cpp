#include "table.h"

Table::Table(QWidget *parent) :
    QWidget(parent),tableSize(0)
{
    table = new QTableWidget(0,5,this);
    QStringList labels;
    labels << "Mark" << "Color" << "Year" << "Status" << "Date of last repair";
    table->setHorizontalHeaderLabels(labels);

    newcartage = new QPushButton ("New cartage");
    save = new QPushButton ("Save");
    open = new QPushButton ("Open");

    connect(newcartage, SIGNAL(clicked()), this, SLOT(makeNewCartage()));
    connect(save, SIGNAL(clicked()), this, SLOT(saveTable()));
    connect(open, SIGNAL(clicked()), this, SLOT(openTable()));
    connect((QObject*)table->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortTable(int)));
    connect((QObject*)table->verticalHeader(), SIGNAL(sectionDoubleClicked(int)), this,SLOT(deleteDialogCartage()));
    connect(table, SIGNAL(cellChanged(int,int)), this, SLOT(changeData(int,int)));

    mainlayout = new QGridLayout;
    mainlayout->addWidget(table,0,0,1,3);
    mainlayout->addWidget(newcartage,1,0);
    mainlayout->addWidget(save,1,1);
    mainlayout->addWidget(open,1,2);
    setLayout(mainlayout);

}

Table::~Table(){
    delete table;
    delete mainlayout;
}

//////////////////////////

void Table::from_list_to_table()
{
    Cartage work;
    int day, month, year;
    QTableWidgetItem *tableItems[5];
    data.set_current(0);
    work = data.read(Current);
    for(int i = 0; i < tableSize; ++i){
        tableItems[0] = new QTableWidgetItem(work.getMark());
        tableItems[1] = new QTableWidgetItem(work.getColor());
        if(year = work.getYear() > 0)
            tableItems[2] = new QTableWidgetItem(QString::number(year));
        else
            tableItems[2] = new QTableWidgetItem;
        tableItems[3] = new QTableWidgetItem(work.getStatus());
        if(day = work.getRepairTime().day > 0 && (month = work.getRepairTime().month) > 0 && (year = work.getRepairTime().year) > 0)
            tableItems[4] = new QTableWidgetItem(QString("%1/%2/%3").arg(day).arg(month).arg(year));
        else
            tableItems[4] = new QTableWidgetItem;

        table->setItem(i, 0, tableItems[0]);
        table->setItem(i, 1, tableItems[1]);
        table->setItem(i, 2, tableItems[2]);
        table->setItem(i, 3, tableItems[3]);
        table->setItem(i, 4, tableItems[4]);

        work = data.read(Next);
    }
}

void Table::after_sort()
{
    Cartage work;
    int day, month, year;
    data.set_current(0);
    work = data.read(Current);
    for(int i = 0; i < tableSize; ++i){
        table->item(i,0)->setText(work.getMark());
        table->item(i, 1)->setText(work.getColor());
        if(year = work.getYear() > 0)
            table->item(i, 2)->setText(QString::number(year));
        else
            table->item(i, 2)->setText("");
        table->item(i, 3)->setText(work.getStatus());
        if(day = work.getRepairTime().day > 0 && (month = work.getRepairTime().month) > 0 && (year = work.getRepairTime().year) > 0)
            table->item(i, 4)->setText(QString("%1/%2/%3").arg(day).arg(month).arg(year));
        else
            table->item(i, 4)->setText("");
        work = data.read(Next);
    }
}

/////////////////////////


void Table::makeNewCartage()
{
    table->insertRow(tableSize);
    data.push_back();
    QTableWidgetItem *tableItems[5];
    for(int i = 0; i < 5; ++i){
        tableItems[i] = new QTableWidgetItem;
        table->setItem(tableSize, i, tableItems[i]);
    }
    ++tableSize;
}

void Table::changeData(int row, int column){
    Cartage *changedCartage = data.to_change(row);
    switch (column) {
    case 0:
        changedCartage->putMark(table->item(row, column)->text());
        break;
    case 1:
        changedCartage->putColor(table->item(row, column)->text());
        break;
    case 2:
        changedCartage->putYear(table->item(row, column)->text().toInt());
        break;
    case 3:
        changedCartage->putStatus(table->item(row, column)->text());
        break;
    case 4:{
        QString work = table->item(row, column)->text();
        changedCartage->putRepairTime(work.section('/',0,0).toInt(), work.section('/', 1, 1).toInt(), work.section('/', 2, 2).toInt());
        }
        break;
    default:
        break;
    }
}

void Table::openTable()
{
    QString fromFile, mark, color, status;
    int size;
    short year;
    Data time;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Database (*.mdb)"));
    if (fileName != ""){
        for(;tableSize; --tableSize)
            table->removeRow(0);
        data.clear();
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly ))
            return;
        while (!file.atEnd())
        {
            file.read((char*) &size, sizeof(int));
            fromFile = file.read(size);
            file.read((char*) &year, sizeof(short));
            file.read((char*) &time, sizeof(Data));
            mark = fromFile.section('|',0,0);
            color = fromFile.section('|',1,1);
            status = fromFile.section('|',2,2);
            table->insertRow(tableSize);
            data.push_back(Cartage(mark, color, year, status, time));
            ++tableSize;
        }
        from_list_to_table();
    }
}

void Table::saveTable()
{
    QByteArray intoFile;
    Cartage work;
    short int year;
    int size;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Database (*.mdb);)"));
    if (fileName != ""){
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly ))
            return;
        data.set_current(0);
        work = data.read(Current);
        for(int i = 0; i < tableSize; ++i){
            intoFile.append(work.getMark()+'|'+work.getColor()+'|'+work.getStatus());
            year = work.getYear();
            size = intoFile.length();
            file.write((char*) &size, sizeof(int));
            file.write(intoFile);
            file.write((char*) &year, sizeof(short int));
            file.write((char*) &(work.getRepairTime()), sizeof(Data));
            intoFile.clear();
            work = data.read(Next);
        }
    }
}

void Table::sortTable(int column)
{
    data.sort(column);
    after_sort();
}

void Table::deleteDialogCartage()
{
    deleted = new QDialog;
    deleted->setFixedSize(300, 80);
    QGridLayout *layout = new QGridLayout;
    QPushButton *yes = new QPushButton("Yes");
    QPushButton *no = new QPushButton("No");
    QLabel *label = new QLabel("Are you sure that you want to delete this line?");
    label->setAlignment(Qt::AlignCenter);

    connect(no, SIGNAL(clicked()), deleted, SLOT(close()));
    connect(yes, SIGNAL(clicked()), deleted, SLOT(close()));
    connect(yes, SIGNAL(clicked()), this, SLOT(deleteCartage()));


    layout->addWidget(label, 0, 0, 1 , 2);
    layout->addWidget(yes, 1, 0);
    layout->addWidget(no, 1, 1);

    deleted->setLayout(layout);

    deleted->show();
}

void Table::deleteCartage()
{
    int row = table->currentRow();
    data.deleting(row);
    table->removeRow(row);
    --tableSize;
}

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(560, 400);
    table = new Table;
    setCentralWidget(table);
}

MainWindow::~MainWindow()
{
    delete table;
}

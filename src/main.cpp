/**
 * @file main.cpp
 *
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 * @author Ondrej Koumar, xkouma02
 * @author Marek Konecny, xkonec85
 *
 * @brief This file contains definitions and functions for Qt GUI so the app can work properly.
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

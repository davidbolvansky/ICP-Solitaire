/**
* @file     main.cpp
* @brief    entry point of app
* @author   Katarina Gresova xgreso00
*/

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <unistd.h>
#include "QBoard.h"
#include "QSolitaire.h"

/**
 * @brief main  entry function
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget mainWidget;
    new QSolitaire(&mainWidget);

    return a.exec();
}

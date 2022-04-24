/**
 * @file mainwindow.h
 *
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 * @author Ondrej Koumar, xkouma02
 * @author Marek Konecny, xkonec85
 *
 * @brief Header with declarations of Mainwindow class methods.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "matlib.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow is a constructor of application window.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief ~MainWindow is a destructor of application window.
     */
    ~MainWindow();

    /**
     * @brief keyPressEvent Detects pressed keyboard keys and performs calculator actions according to which key was pressed.
     * @param QKeyEvent * event Detects, what keyboard key was pressed.
     */
    void keyPressEvent(QKeyEvent * event);

private slots:

    /**
     * @brief on_btnNum_clicked retypes pushed button into a QString type so it can be processed.
     */
    void on_btnNum_clicked();

    /**
     * @brief on_btnOper_clicked Detects whether operation button was clicked and then the operation is processed by calling processOper function.
     */
    void on_btnOper_clicked();

    /**
     * @brief on_btnClear_clicked Removes everything from display and memory so that a completely new equation can start.
     */
    void on_btnClear_clicked();

    /**
     * @brief on_btnEquals_clicked Processes inserted operands and saves them as firstOperand and secondOperand.
     * It then calls calculate function that will do the mathematics.
     */
    void on_btnEquals_clicked();

    /**
     * @brief on_btnHelp_clicked Shows .html document in browser as a simulation of a webpage that tells the user how to operate the calculator.
     */
    void on_btnHelp_clicked();

private:
    Ui::MainWindow *ui;

    /**
     * @brief processOper Processes operation that was last clicked so it can be calculated with equals event.
     * This operation also decides whether the calculator should wait for another operand or not and should be displayed on the lower display.
     * @param oper Is the lettering on application buttons and is transformed into characters so they can be processed on equals event.
     */
    void processOper(QString oper);

    /**
     * @brief updateEquDisplay Updates the higher display with inserted numbers and operands so that way it is clearer
     * what numbers and operator were inserted.
     */
    void updateEquDisplay();

    /**
     * @brief calculate Actually calculates inserted equation and checks if the inputs are correct according to matlib.cpp.
     * If not, lower display will show what is the issue.
     */
    void calculate();

    /**
     * @brief processNumber displays numbers on the lower display according to whether the input number is first or second operand.
     * @param QString key Variable that is retyped by on_btn_num_clicked and processed in this function.
     */
    void processNumber(QString key);

    Matlib math;

    double firstOperand;
    double secondOperand = 0;
    int wasEqual = 0;
    int addNumbers;
    char operation;
    //QString clickedBtn;
};
#endif // MAINWINDOW_H

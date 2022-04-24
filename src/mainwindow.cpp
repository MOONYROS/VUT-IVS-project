/**
 * @file mainwindow.cpp
 *
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 * @author Ondrej Koumar, xkouma02
 * @author Marek Konecny, xkonec85
 *
 * @brief Implementation of working CalculandumMachina window with all the processes.
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "matlib.h"

#include <QKeyEvent>
#include <QIcon>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addNumbers = 0;
    firstOperand = 0;
    operation = ' ';
    secondOperand = 0;
    wasEqual = 0;

    setWindowIcon(QIcon(":/img/mainLogo"));
    setWindowTitle("Calculandum Machina");

    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->calcDisplay->setReadOnly(true);
    ui->calcDisplay->setAlignment(Qt::AlignRight);

    ui->equDisplay->setReadOnly(true);

    connect(ui->btn0, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn3, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn4, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn5, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn6, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn7, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn8, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btn9, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));
    connect(ui->btnDot, SIGNAL(clicked()), this, SLOT(on_btnNum_clicked()));

    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnMinus, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnMult, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnDiv, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnPow, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnRoot, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnLog, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));

    connect(ui->btnFact, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));

    ui->calcDisplay->setPlainText("0");
    ui->calcDisplay->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QString key("?");

    switch (event->key())
    {
        case Qt::Key_0:
            key = "0"; break;
        case Qt::Key_1:
            key = "1"; break;
        case Qt::Key_2:
            key = "2"; break;
        case Qt::Key_3:
            key = "3"; break;
        case Qt::Key_4:
            key = "4"; break;
        case Qt::Key_5:
            key = "5"; break;
        case Qt::Key_6:
            key = "6"; break;
        case Qt::Key_7:
            key = "7"; break;
        case Qt::Key_8:
            key = "8"; break;
        case Qt::Key_9:
            key = "9"; break;
        case Qt::Key_Period:
        case Qt::Key_Comma:
            key = "."; break;

        case Qt::Key_Plus:
            processOper("+"); break;
        case Qt::Key_Minus:
            processOper("-"); break;
        case Qt::Key_Asterisk:
            processOper("×"); break;
        case Qt::Key_Slash:
            processOper("÷"); break;
        case Qt::Key_P:
            processOper("x"); break;
        case Qt::Key_R:
            processOper("√x"); break;
        case Qt::Key_F:
            processOper("x!"); break;
        case Qt::Key_L:
            processOper("ln x"); break;

        case Qt::Key_C:
            on_btnClear_clicked(); break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            on_btnEquals_clicked(); break;
        case Qt::Key_Question:
        case Qt::Key_H:
            on_btnHelp_clicked(); break;
    }

    QString nums("0123456789.");
    if(nums.indexOf(key) >= 0)
    {
        processNumber(key);
    }
}

void MainWindow::on_btnNum_clicked()
{
    processNumber(((QPushButton *)sender())->text());
}

void MainWindow::processNumber(QString key)
{
    if(key == "." && ui->calcDisplay->toPlainText().indexOf(".") >= 0)
        return;
    if(addNumbers)
    {
        ui->calcDisplay->insertPlainText(key);
        ui->calcDisplay->setAlignment(Qt::AlignRight);
        updateEquDisplay();
    }
    else
    {
        ui->calcDisplay->setPlainText(key);
        ui->calcDisplay->setAlignment(Qt::AlignRight);
        addNumbers = 1;
        if(wasEqual)
            ui->equDisplay->clear();
        else
            updateEquDisplay();
    }
    ui->calcDisplay->moveCursor(QTextCursor::End);
}

void MainWindow::processOper(QString oper)
{
    if(operation != ' ' && wasEqual == 0)
    {
        on_btnEquals_clicked();
    }
    if(oper == "+")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '+';
    }
    else if(oper == "-")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '-';
    }
    else if(oper == "×")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '*';
    }
    else if(oper == "÷")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '/';
    }
    else if(oper == "x")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = 'x';
    }
    else if(oper == "√x")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = 'R';
    }
    try
    {
        if(oper == "x!")
        {
            // zkontrolovat zaporna a desetinna cisla
            if (ui->calcDisplay->toPlainText().contains('.') || ui->calcDisplay->toPlainText().contains('-'))
            {
                ui->calcDisplay->setPlainText("ERROR");
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            else
            {
                unsigned short operand = ui->calcDisplay->toPlainText().toUInt();
                unsigned long long result = math.factorial(operand);
                ui->calcDisplay->setPlainText(QString::number(result));
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            addNumbers = 0;
            operation = ' ';
        }
        if(oper == "ln x")
        {
            unsigned short operand = ui->calcDisplay->toPlainText().toUInt();
            if (operand < 0)
            {
                ui->calcDisplay->setPlainText("ERROR");
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            else
            {
                double result = math.ln(operand);
                ui->calcDisplay->setPlainText(QString::number(result));
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            addNumbers = 0;
            operation = ' ';
        }
    }
    catch(const std::out_of_range& oor)
    {
        ui->calcDisplay->setPlainText(QString("ERROR: ") + oor.what());
    }
    wasEqual = 0;
    updateEquDisplay();
}

void MainWindow::on_btnOper_clicked()
{
    processOper(((QPushButton *)sender())->text());
}

void MainWindow::on_btnClear_clicked()
{
    addNumbers = 0;
    operation = ' ';
    firstOperand = 0;
    secondOperand = 0;
    wasEqual = 0;

    ui->calcDisplay->clear();
    ui->equDisplay->clear();
    ui->calcDisplay->setPlainText("0");
    ui->calcDisplay->setAlignment(Qt::AlignRight);

    updateEquDisplay();
}

void MainWindow::calculate()
{
    double result = ui->calcDisplay->toPlainText().toDouble();
    int err = 0;

    try
    {
        switch (operation)
        {
            case '+':
                result = math.add(firstOperand, secondOperand);
                break;
            case '-':
                result = math.sub(firstOperand, secondOperand);
                break;
            case '*':
                result = math.mul(firstOperand, secondOperand);
                break;
            case '/':
                result = math.div(firstOperand, secondOperand);
                break;
            case 'x':
                result = math.power(firstOperand, secondOperand);
                break;
            case 'R':
                result = math.root(firstOperand, secondOperand);
                break;
            default:
                operation = ' ';
                break;
        }
    }
    catch(const std::out_of_range& oor)
    {
        err = 1;
        ui->calcDisplay->setPlainText(QString("ERROR: ") + oor.what());
    }
    catch(const std::invalid_argument& ia)
    {
        err = 1;
        ui->calcDisplay->setPlainText(QString("ERROR: ") + ia.what());
    }


    if(!err)
    {
        ui->calcDisplay->setPlainText(QString::number(result));
        ui->calcDisplay->setAlignment(Qt::AlignRight);
    }
    addNumbers = 0;

    updateEquDisplay();
}

void MainWindow::on_btnEquals_clicked()
{
    if(wasEqual)
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
    else
        secondOperand = ui->calcDisplay->toPlainText().toDouble();

    wasEqual = 1;
    calculate();
}

void MainWindow::updateEquDisplay()
{
    ui->equDisplay->clear();
    if(operation != ' ')
    {
        ui->equDisplay->setAlignment(Qt::AlignRight);
        ui->equDisplay->insertPlainText(QString::number(firstOperand));
    }
    QString opName(operation);
    switch (operation)
    {
        case '*':
            opName = "×"; break;
        case '/':
            opName = "÷"; break;
        case 'x':
            opName = "^"; break;
        case 'R':
            opName = "ROOT"; break;
    }

    if(operation != ' ')
        ui->equDisplay->insertPlainText(QString(" ") + opName + " ");
    if(wasEqual)
    {
        ui->equDisplay->setAlignment(Qt::AlignRight);
        ui->equDisplay->insertPlainText(QString::number(secondOperand));
        ui->equDisplay->insertPlainText(QString(" ="));
    }
}

void MainWindow::on_btnHelp_clicked()
{
    QString link = "help.html";
    QDesktopServices::openUrl(QUrl::fromLocalFile(link));
}

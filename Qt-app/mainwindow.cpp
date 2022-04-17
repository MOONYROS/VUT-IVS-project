#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "matlib.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addNumbers = 0;
    firstOperand = 0;
    operation = ' ';

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

    connect(ui->btnFact, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QString key;

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
            key = "."; break;
        default:
            key = "?"; break;
    }

    ui->calcDisplay->insertPlainText(key);
    ui->calcDisplay->moveCursor(QTextCursor::End);

}



void MainWindow::on_btnNum_clicked()
{
    if(addNumbers)
    {
        ui->calcDisplay->insertPlainText(((QPushButton *)sender())->text());
    }
    else
    {
        ui->calcDisplay->setPlainText(((QPushButton *)sender())->text());
        addNumbers = 1;
    }

    ui->calcDisplay->moveCursor(QTextCursor::End);
}

void MainWindow::on_btnOper_clicked()
{
    if(((QPushButton *)sender())->text() == "+")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '+';
    }
    else if(((QPushButton *)sender())->text() == "-")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '-';
    }
    else if(((QPushButton *)sender())->text() == "×")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '*';
    }
    else if(((QPushButton *)sender())->text() == "÷")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '/';
    }
    else if(((QPushButton *)sender())->text() == "x")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = 'x';
    }
    else if(((QPushButton *)sender())->text() == "√x")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = 'R';
    }
    else if(((QPushButton *)sender())->text() == "x!")
    {
        // zkontrolovat zaporna a desetinna cisla
        if (ui->calcDisplay->toPlainText().contains('.') || ui->calcDisplay->toPlainText().contains('-'))
            ui->calcDisplay->setPlainText("ERROR");
        else
        {
            unsigned short operand = ui->calcDisplay->toPlainText().toUInt();
            unsigned long long result = math.factorial(operand);
            ui->calcDisplay->setPlainText(QString::number(result));
        }
        addNumbers = 0;
        operation = ' ';
    }
    else if(((QPushButton *)sender())->text() == "ln x")
    {
        unsigned short operand = ui->calcDisplay->toPlainText().toUInt();
        if (operand < 0)
            ui->calcDisplay->setPlainText("ERROR");
        else
        {
            unsigned long long result = math.ln(operand);
            ui->calcDisplay->setPlainText(QString::number(result));
        }
        addNumbers = 0;
        operation = ' ';
    }
}

void MainWindow::on_btnClear_clicked()
{
    ui->calcDisplay->clear();
    ui->equDisplay->clear();
    ui->calcDisplay->setAlignment(Qt::AlignRight);
}

void MainWindow::on_btnEquals_clicked()
{
    double result = 0;
    int err = 0;
    double secondOperand = ui->calcDisplay->toPlainText().toDouble();
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
            err = 1;
            operation = ' ';
            break;
    }
    if(err)
        ui->calcDisplay->setPlainText("ERROR");
    else
        ui->calcDisplay->setPlainText(QString::number(result));

    addNumbers = 0;
}

void MainWindow::on_btnHelp_clicked()
{
    ui->calcDisplay->setPlainText("DIS NO WORK YET");
}

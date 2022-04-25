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

    // Setting up variables that will be used in multiple functions.
    addNumbers = 0;
    firstOperand = 0;
    operation = ' ';
    secondOperand = 0;
    wasEqual = 0;

    // Setting up window icon and window title.
    setWindowIcon(QIcon(":/img/mainLogo"));
    setWindowTitle("Calculandum Machina");

    // Setting up basic app functions like non-resizable window or read-only display.
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->calcDisplay->setReadOnly(true);
    ui->calcDisplay->setAlignment(Qt::AlignRight);

    ui->equDisplay->setReadOnly(true);

    // Making connections for numeric buttons.
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

    // Making connections for operation buttons.
    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnMinus, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnMult, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnDiv, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnPow, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnRoot, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnLog, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));
    connect(ui->btnFact, SIGNAL(clicked()), this, SLOT(on_btnOper_clicked()));

    // Setting up the display so it shows 0 on the start.
    ui->calcDisplay->setPlainText("0");
    ui->calcDisplay->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    // Destructor deletes all the components of UI.
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    // Setting up pressed keyboard key as unknown so it does not make any mishaps in the future.
    QString key("?");

    // Detecting which key was pressed and then saving it to a key variable.
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

        // If operation key was pressed, we have to detect it as operation and work with operands.
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

        // If any other extra calculator key was pressed, we call its function.
        case Qt::Key_C:
            on_btnClear_clicked(); break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            on_btnEquals_clicked(); break;
        case Qt::Key_Question:
        case Qt::Key_H:
            on_btnHelp_clicked(); break;
    }

    // Detecting if a pressed key was numeric and then processing it.
    QString nums("0123456789.");
    if(nums.indexOf(key) >= 0)
    {
        processNumber(key);
    }
}

void MainWindow::on_btnNum_clicked()
{
    // With every pressed numberbutton we process the displayed text with processnumber function.
    processNumber(((QPushButton *)sender())->text());
}

void MainWindow::processNumber(QString key)
{
    // Period can be activated only once per number.
    if(key == "." && ui->calcDisplay->toPlainText().indexOf(".") >= 0)
        return;

    // If we can still add numbers, we insert them on the lower display and update the upper display.
    if(addNumbers)
    {
        ui->calcDisplay->insertPlainText(key);
        ui->calcDisplay->setAlignment(Qt::AlignRight);
        updateEquDisplay();
    }
    // Otherwise we check whether equal was pressed and we forbid inserting any other numbers.
    else
    {
        ui->calcDisplay->setPlainText(key);
        ui->calcDisplay->setAlignment(Qt::AlignRight);
        addNumbers = 1;
        if(wasEqual)
            ui->equDisplay->clear();    // Clearing the upper display.
        else
            updateEquDisplay();         // Updating upper display.
    }
    ui->calcDisplay->moveCursor(QTextCursor::End);  // Moving cursor to the end so we dont overwrite the last inserted number.
}

void MainWindow::processOper(QString oper)
{
    // If theres operation and the equals wasnt pressed, we call its click function.
    if(operation != ' ' && wasEqual == 0)
        on_btnEquals_clicked();
    // If the the pressed button text  is + (QString) we set the operation as +.
    if(oper == "+")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '+';
    }
    // If the the pressed button text  is - (QString) we set the operation as -.
    else if(oper == "-")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '-';
    }
    // If the the pressed button text  is × (QString) we set the operation as *.
    else if(oper == "×")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '*';
    }
    // If the pressed button text is ÷ (QString) we set the operation as /.
    else if(oper == "÷")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = '/';
    }
    // If the the pressed button text is x (power) (QString) we set the operation as /.
    else if(oper == "x")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = 'x';
    }
    // If the the pressed button text is √x (power) (QString) we set the operation as R (Root).
    else if(oper == "√x")
    {
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
        addNumbers = 0;
        operation = 'R';
    }
    // Here we try to catch any mistakes that were included with the matlib.
    try
    {
        if(oper == "x!")
        {
            // We check if there are any decimal numbers or negative number. If the case, we call error.
            if (ui->calcDisplay->toPlainText().contains('.') || ui->calcDisplay->toPlainText().contains('-'))
            {
                ui->calcDisplay->setPlainText("ERROR: Number is negative or non-integer");
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            // If it is not the case, we make the operation and show the result.
            else
            {
                unsigned short operand = ui->calcDisplay->toPlainText().toUInt();
                unsigned long long result = math.factorial(operand);
                ui->calcDisplay->setPlainText(QString::number(result));
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            // We forbid any other number inserts since the factorial function is unary operation.
            addNumbers = 0;
            operation = ' ';
        }
        if(oper == "ln x")
        {
            // We retype the text to unsigned int and save it to the operand.
            double operand = ui->calcDisplay->toPlainText().toDouble();

            // If the inserted number is lower than 0 we call error.
            if (operand < 0)
            {
                ui->calcDisplay->setPlainText("ERROR: Number lower than 0");
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            // If the inserted number is correct, we make the operation and show the result.
            else
            {
                double result = math.ln(operand);
                ui->calcDisplay->setPlainText(QString::number(result));
                ui->calcDisplay->setAlignment(Qt::AlignRight);
            }
            // We forbid any other number inserts since the natural logarithm function is unary operation.
            addNumbers = 0;
            operation = ' ';
        }
    }
    // If the error is the type out_of_range we show error and display its exception text.
    catch(const std::out_of_range& oor)
    {
        ui->calcDisplay->setPlainText(QString("ERROR: ") + oor.what());
    }
    // We disable wasEqual becaause it wasnt pressed and update the upper display.
    wasEqual = 0;
    updateEquDisplay();
}

void MainWindow::on_btnOper_clicked()
{
    // We call processOper function for the text of pressed operation button.
    processOper(((QPushButton *)sender())->text());
}

void MainWindow::on_btnClear_clicked()
{
    // If the C (Clear) button was pressed we set every variable to its original state, including the displays.
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
    // We retype the display text to double and disable any errors.
    double result = ui->calcDisplay->toPlainText().toDouble();
    int err = 0;

    try
    {
        // We perform the operation according to what we saved into operation varible earlier.
        switch (operation)
        {
            // If the operation was + we make addition.
            case '+':
                result = math.add(firstOperand, secondOperand);
                break;
            // If the operation was - we make subtraction.
            case '-':
                result = math.sub(firstOperand, secondOperand);
                break;
            // If the operation was * we make multiplication.
            case '*':
                result = math.mul(firstOperand, secondOperand);
                break;
            // If the operation was / we make division.
            case '/':
                result = math.div(firstOperand, secondOperand);
                break;
            // If the operation was x (power) we make power.
            case 'x':
                result = math.power(firstOperand, secondOperand);
                break;
            // If the operation was R we make root.
            case 'R':
                result = math.root(firstOperand, secondOperand);
                break;
            // We dont do anything when theres no operation.
            default:
                operation = ' ';
                break;
        }
    }
    // If the error is the type out_of_range we show error and display its exception text.
    catch(const std::out_of_range& oor)
    {
        err = 1;
        ui->calcDisplay->setPlainText(QString("ERROR: ") + oor.what());
    }
    // If the error is the type invalid_argument we show error and display its exception text.
    catch(const std::invalid_argument& ia)
    {
        err = 1;
        ui->calcDisplay->setPlainText(QString("ERROR: ") + ia.what());
    }

    // If theres no error we show the result we saved into result variable earlier.
    if(!err)
    {
        ui->calcDisplay->setPlainText(QString::number(result));
        ui->calcDisplay->setAlignment(Qt::AlignRight);
    }
    // We disable any other number inputs and update the upper display.
    addNumbers = 0;
    updateEquDisplay();
}

void MainWindow::on_btnEquals_clicked()
{
    // If wasEqual is enabled we save inserted number into the firstOperand variable.
    if(wasEqual)
        firstOperand = ui->calcDisplay->toPlainText().toDouble();
    // If wasEqual is disabled we save inserted number into the firstOperand variable.
    else
        secondOperand = ui->calcDisplay->toPlainText().toDouble();

    // We enable wasEqual and calculate the result.
    wasEqual = 1;
    calculate();
}

void MainWindow::updateEquDisplay()
{
    // This operation works only with the upper display.
    // We check whether any operation was inserted.
    ui->equDisplay->clear();
    if(operation != ' ')
    {
        // If not, we display the first operand.
        ui->equDisplay->setAlignment(Qt::AlignRight);
        ui->equDisplay->insertPlainText(QString::number(firstOperand));
    }
    // Then we display the operation logo.
    QString opName(operation);
    // This operation just retypes operation characters into QStrings, that are much easier to recognise.
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

    // If theres no empty operation, we insert the operation with spaces around.
    if(operation != ' ')
        ui->equDisplay->insertPlainText(QString(" ") + opName + " ");
    // If equals button was pressed, we show the second operand and equals character.
    if(wasEqual)
    {
        ui->equDisplay->setAlignment(Qt::AlignRight);
        ui->equDisplay->insertPlainText(QString::number(secondOperand));
        ui->equDisplay->insertPlainText(QString(" ="));
    }
}

void MainWindow::on_btnHelp_clicked()
{
    // We save the filename into variable.
    QString link = "help.html";
    // We then open the filename. In this case we open .html file with.
    QDesktopServices::openUrl(QUrl::fromLocalFile(link));
}

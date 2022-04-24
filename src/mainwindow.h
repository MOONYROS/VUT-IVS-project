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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent * event);

private slots:
    void on_btnNum_clicked();

    void on_btnOper_clicked();

    void on_btnClear_clicked();
    void on_btnEquals_clicked();
    void on_btnHelp_clicked();

private:
    Ui::MainWindow *ui;

    Matlib math;

    double firstOperand;
    int addNumbers;
    char operation;
};
#endif // MAINWINDOW_H
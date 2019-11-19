#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNumber;
bool secondNumberB = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->number_0,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_1,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_2,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_3,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_4,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_5,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_6,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_7,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_8,SIGNAL(clicked()), this,SLOT(digitPressed()));
    connect(ui->number_9,SIGNAL(clicked()), this,SLOT(digitPressed()));

    connect(ui->button_p_or_m,SIGNAL(clicked()), this,SLOT(functionPressed()));
    connect(ui->button_percent,SIGNAL(clicked()), this,SLOT(functionPressed()));

    connect(ui->button_add,SIGNAL(clicked()), this,SLOT(operatorPressed()));
    connect(ui->button_minus,SIGNAL(clicked()), this,SLOT(operatorPressed()));
    connect(ui->button_multi,SIGNAL(clicked()), this,SLOT(operatorPressed()));
    connect(ui->button_divide,SIGNAL(clicked()), this,SLOT(operatorPressed()));

    ui->button_add->setCheckable(true);
    ui->button_minus->setCheckable(true);
    ui->button_multi->setCheckable(true);
    ui->button_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitPressed()
{
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;
    if(ui->label->text()== "0")
    {
        labelNumber = button->text().toDouble();
        newLabel = QString::number(labelNumber);
    }
    else if((ui->button_add->isChecked() || ui->button_minus->isChecked()
        || ui->button_multi->isChecked() || ui->button_divide->isChecked()) && (!secondNumberB))
    {
        labelNumber = button->text().toDouble();
        newLabel = QString::number(labelNumber);
        secondNumberB = true;
    }
    else if(secondNumberB == true)
    {
        labelNumber = button->text().toDouble();
        newLabel = QString::number(labelNumber);
    }
    else
    {
        labelNumber = (ui->label->text() + button->text()).toDouble();
        newLabel = QString::number(labelNumber);
    }
    ui->label->setText(newLabel);
}

void MainWindow::on_button_point_clicked()
{
    if(ui->label->text()== "0"){
        ui->label->setText(QString::fromStdString("."));
    }
    else{
        ui->label->setText(ui->label->text() + ".");
    }
}

void MainWindow::functionPressed()
{
    QPushButton * button = (QPushButton*)sender();
    double label;
    QString newLabel;
    if(button->text()== "-/+"){
        label = ui->label->text().toDouble();
        label = label * -1;
        newLabel = QString::number(label);
        ui->label->setText(newLabel);
    }
    else if(button->text()== "%")
    {
        label = ui->label->text().toDouble();
        label = label * 0.01;
        newLabel = QString::number(label);
        ui->label->setText(newLabel);
    }
}

void MainWindow::on_button_clear_clicked()
{
    ui->button_add->setChecked(false);
    ui->button_minus->setChecked(false);
    ui->button_multi->setChecked(false);
    ui->button_divide->setChecked(false);

    secondNumberB = false;

    ui->label->setText("0");
    ui->label_2->setText("");
}

void MainWindow::on_button_equals_clicked()
{
    double label, secondNumber;
    QString newLabel;
    secondNumber = ui->label->text().toDouble();

    ui->label_2->setText(ui->label_2->text() + " " + ui->label->text() + " = ");

    if(ui->button_add->isChecked())
    {
        label = firstNumber + secondNumber;
        newLabel = QString::number(label);
        ui->label->setText(newLabel);
        ui->button_add->setChecked(false);
    }
    else if(ui->button_minus->isChecked())
    {
        label = firstNumber - secondNumber;
        newLabel = QString::number(label);
        ui->label->setText(newLabel);
        ui->button_minus->setChecked(false);
    }
    else if(ui->button_divide->isChecked())
    {
        label = firstNumber / secondNumber;
        newLabel = QString::number(label);
        ui->label->setText(newLabel);
        ui->button_divide->setChecked(false);
    }
    else if(ui->button_multi->isChecked())
    {
        label = firstNumber * secondNumber;
        newLabel = QString::number(label);
        ui->label->setText(newLabel);
        ui->button_multi->setChecked(false);
    }

    secondNumberB = false;
}

void MainWindow::operatorPressed()
{
    QPushButton * button = (QPushButton*)sender();
    button->setChecked(true);
    static QString previousOperator;
    if(secondNumberB == true)
    {
        if(previousOperator == "+")
            firstNumber = firstNumber + ui->label->text().toDouble();
        else if(previousOperator == "-")
            firstNumber = firstNumber - ui->label->text().toDouble();
        else if(previousOperator == "/")
            firstNumber = firstNumber / ui->label->text().toDouble();
        else if(previousOperator == "x")
            firstNumber = firstNumber * ui->label->text().toDouble();
        previousOperator = button->text();
    }
    else
    {
        firstNumber = ui->label->text().toDouble();
    }

    if(secondNumberB == false)
        previousOperator = button->text();
    ui->label_2->setText(ui->label_2->text() + " " + ui->label->text() + " " + button->text());
}

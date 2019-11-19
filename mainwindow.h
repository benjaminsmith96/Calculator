#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void digitPressed();
    void functionPressed();
    void operatorPressed();

    void on_button_point_clicked();

    void on_button_clear_clicked();

    void on_button_equals_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

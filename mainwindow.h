#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <vector>
#include <QPalette>
#include <string>
#include <map>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPlainTextEdit *currentPlainText;
    int currentVecIndex = 0;
    QString currentSign;
    
    std::vector<QPlainTextEdit*> vec;
    

private slots:
    void setSignStyle();
    void setNumStyle();
    void setDefaultSettings();
    void setOutputStyle();
    void blockLetters();
    void unblockLetters();

    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_A_clicked();
    void on_pushButton_B_clicked();
    void on_pushButton_C_clicked();
    void on_pushButton_D_clicked();
    void on_pushButton_E_clicked();
    void on_pushButton_F_clicked();

    void on_pushButton_0_pressed();
    void on_pushButton_1_pressed();
    void on_pushButton_2_pressed();
    void on_pushButton_3_pressed();
    void on_pushButton_4_pressed();
    void on_pushButton_5_pressed();
    void on_pushButton_6_pressed();
    void on_pushButton_7_pressed();
    void on_pushButton_8_pressed();
    void on_pushButton_9_pressed();
    void on_pushButton_A_pressed();
    void on_pushButton_B_pressed();
    void on_pushButton_C_pressed();
    void on_pushButton_D_pressed();
    void on_pushButton_E_pressed();
    void on_pushButton_F_pressed();

    void on_pushButton_Right_clicked();
    void on_pushButton_Left_clicked();
    void on_pushButton_ClearAll_clicked();
    void on_pushButton_Delete_clicked();

    void on_pushButton_Right_pressed();
    void on_pushButton_Left_pressed();
    void on_pushButton_ClearAll_pressed();
    void on_pushButton_Delete_pressed();

    void on_pushButton_Division_clicked();
    void on_pushButton_Multiply_clicked();
    void on_pushButton_Sum_clicked();
    void on_pushButton_Sub_clicked();
    void on_pushButton_Equal_clicked();

    void on_pushButton_Division_pressed();
    void on_pushButton_Multiply_pressed();
    void on_pushButton_Sum_pressed();
    void on_pushButton_Sub_pressed();
    void on_pushButton_Equal_pressed();    
};
#endif // MAINWINDOW_H

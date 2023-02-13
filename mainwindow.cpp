#include "mainwindow.h"
#include "./ui_mainwindow.h"

std::map<char, int> Alfabet() {
    std::map<char, int> m;
    m['0'] = 0;
    m['1'] = 1;
    m['2'] = 2;
    m['3'] = 3;
    m['4'] = 4;
    m['5'] = 5;
    m['6'] = 6;
    m['7'] = 7;
    m['8'] = 8;
    m['9'] = 9;
    m['A'] = 10;
    m['B'] = 11;
    m['C'] = 12;
    m['D'] = 13;
    m['E'] = 14;
    m['F'] = 15;
    return m;
};

std::map<std::string, int> Signs() {
    std::map<std::string, int> m;
    m["+"] = 1;
    m["−"] = 2;
    m["×"] = 3;
    m["÷"] = 4;
    return m;
};

static std::map<char, int> alfabet_ = std::move(Alfabet());
static std::map<std::string, int> signs_ = std::move(Signs());

QString answer_;
void MainWindow::Answer(long long a, long long b, std::string sign) { //подсчет ответа
    switch (signs_[sign])
    {
    case 1:
        answer_ = QString::number(a + b);
        break;
    case 2:
        answer_ = QString::number(a - b);
        break;
    case 3:
        answer_ = QString::number(a * b);
        break;
    case 4:
        answer_ = QString::number(round(((double)a / (double)b)*1000)/1000);
        break;
    default:
        break;
    }
}

long long Pow(int a, int n) { //возведение в степень
    if (n == 0) return 1;
    if (n % 2 == 0)
        return Pow((a * a), n / 2);
    else
        return (a * Pow(a, n - 1));
}

long long To_dec(std::string num, int sys) { //перевод в десятичную СС
    long long res = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[num.length() - i - 1] != '0')
            res += alfabet_[num[num.length() - i - 1]] * Pow(sys, i);
    }
    return res;
}

bool Pair_check(std::string num, int sys) { //проверка принадлежности числа своей СС
    for (int i = 0; i < num.length(); i++) {
        if (alfabet_[num[i]] >= sys) return false;
    }
    return true;
}

bool Num_input_check(std::string num) {
    return !(num.length() == 0 || (num[0] == '0' && num.length() > 1));
}

bool Sys_input_check(std::string sys) {
    return To_dec(sys, 10) <= 16 && Num_input_check(sys);
}
bool Division_check(int num) {
    return num != 0;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setDefaultSettings();
}

MainWindow::~MainWindow() {
    delete ui;
}

bool lettersBlocked = false;
bool rightMoveBlocked = false;
bool leftMoveBlocked = true;
QString mainWindowColor = "background-color: #000000";
QString signColorOff = "border-radius: 20px;"
"background-color: #F29C07 ;"
"color: #FEFEFE;"
"text-align: centre;"
"border: none;";
QString signColorOn = "border-radius: 20px;"
"background-color:#FEFEFE ;"
"color: #F29C07;"
"border: none;";
QString signColorPressed = "border-radius: 20px;"
"background-color:#FBC98E ;"
"color: #FEFFFE;"
"border: none;";
QString numColorPressed = "border-radius: 20px;"
"background-color: #737373;"
"color: #FEFEFE;"
"border: none;";
QString numColorOff = "border-radius: 20px;"
"background-color: #333333;"
// "background-color: #6E6C6F;"
"color: #FEFEFE;"
"border: none;";
QString numColorBlocked = "border-radius: 20px;"
"background-color: #000000;"
"color: #6E6C6F;"
"border: 2px solid #6E6C6F;";
QString operationColorOff = "border-radius: 20px;"
"background-color: #A5A5A5;"
"color: #000000;"
"border: none;";
QString operationColorBlocked = "border-radius: 20px;"
"border: 2px solid #A5A5A5;"
"background-color: #000000;"
"color: #A5A5A5;";
QString operationColorPressed = "border-radius: 20px;"
"background-color: #D9D9D9;"
"color: #000000;"
"border: none;";
QString outputColor = "border-radius: 5px;"
"background-color: #333333;"
"color: #FFFFFF;"
"border-style: outset;";
QString outputColorActive = "border-radius: 5px;"
"background-color: #333333;"
"color: #FFFFFF;"
"border: 2px solid white;"
"border-style: outset;";
QString signColor = "background-color: #000000;"
"color: #FFFFFF;"
"border: 2px solid black;";
QString outputColorError = "border-radius: 5px;"
"background-color: #333333;"
"color: #FFFFFF;"
"border: 2px solid #FF0000;";

void MainWindow::setDefaultSettings() {
    vec.clear();
    vec.push_back(ui->plainTextEdit_Num1);
    vec.push_back(ui->plainTextEdit_System1);
    vec.push_back(ui->plainTextEdit_Num2);
    vec.push_back(ui->plainTextEdit_System2);
    currentVecIndex = 0;
    currentPlainText = vec[currentVecIndex];
    unblockLetters();
    setSignStyle();
    setNumStyle();
    setOutputStyle();
    ui->label_Sign->setStyleSheet(signColor);
    ui->plainTextEdit_Answer->setStyleSheet(outputColor);
    ui->label->setStyleSheet("color: #FFFFFF;");
    currentPlainText->setStyleSheet(outputColorActive);

    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_Sign->setAlignment(Qt::AlignCenter);

    setArrowsStatus();
}
void MainWindow::setOutputStyle() {
    ui->plainTextEdit_Num1->setStyleSheet(outputColor);
    ui->plainTextEdit_Num2->setStyleSheet(outputColor);
    ui->plainTextEdit_System1->setStyleSheet(outputColor);
    ui->plainTextEdit_System2->setStyleSheet(outputColor);
}
void MainWindow::setNumStyle() {
    ui->pushButton_0->setStyleSheet(numColorOff);
    ui->pushButton_1->setStyleSheet(numColorOff);
    ui->pushButton_2->setStyleSheet(numColorOff);
    ui->pushButton_3->setStyleSheet(numColorOff);

    ui->pushButton_4->setStyleSheet(numColorOff);
    ui->pushButton_5->setStyleSheet(numColorOff);
    ui->pushButton_6->setStyleSheet(numColorOff);
    ui->pushButton_7->setStyleSheet(numColorOff);

    ui->pushButton_8->setStyleSheet(numColorOff);
    ui->pushButton_9->setStyleSheet(numColorOff);

    if (!lettersBlocked) {
        ui->pushButton_A->setStyleSheet(numColorOff);
        ui->pushButton_B->setStyleSheet(numColorOff);

        ui->pushButton_C->setStyleSheet(numColorOff);
        ui->pushButton_D->setStyleSheet(numColorOff);
        ui->pushButton_E->setStyleSheet(numColorOff);
        ui->pushButton_F->setStyleSheet(numColorOff);
    }

    ui->pushButton_ClearAll->setStyleSheet(operationColorOff);
    if (!rightMoveBlocked) {
        ui->pushButton_Right->setStyleSheet(operationColorOff);
    }
    if (!leftMoveBlocked) {
        ui->pushButton_Left->setStyleSheet(operationColorOff);
    }
    ui->pushButton_Delete->setStyleSheet(operationColorOff);
}
void MainWindow::setSignStyle() {
    this->setStyleSheet(mainWindowColor);
    ui->pushButton_Multiply->setStyleSheet(signColorOff);
    ui->pushButton_Division->setStyleSheet(signColorOff);
    ui->pushButton_Sub->setStyleSheet(signColorOff);
    ui->pushButton_Sum->setStyleSheet(signColorOff);
    ui->pushButton_Equal->setStyleSheet(signColorOff);
    ui->label_Sign->setStyleSheet(signColor);
}

void MainWindow::blockLeft() {
    ui->pushButton_Left->setEnabled(false);
    ui->pushButton_Left->setStyleSheet(operationColorBlocked);
}
void MainWindow::blockRight() {
    ui->pushButton_Right->setEnabled(false);
    ui->pushButton_Right->setStyleSheet(operationColorBlocked);
}
void MainWindow::unblockLeft() {
    ui->pushButton_Left->setEnabled(true);
    ui->pushButton_Left->setStyleSheet(operationColorOff);
}
void MainWindow::unblockRight() {
    ui->pushButton_Right->setEnabled(true);
    ui->pushButton_Right->setStyleSheet(operationColorOff);
}

void MainWindow::on_plainTextEdit_Num1_selectionChanged() {
    currentVecIndex = 0;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
}
void MainWindow::on_plainTextEdit_Num2_selectionChanged() {
    currentVecIndex = 2;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
}
void MainWindow::on_plainTextEdit_System1_selectionChanged() {
    currentVecIndex = 1;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
}
void MainWindow::on_plainTextEdit_System2_selectionChanged() {
    currentVecIndex = 3;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
}

void MainWindow::blockLetters() {
    ui->pushButton_A->setEnabled(false);
    ui->pushButton_B->setEnabled(false);
    ui->pushButton_C->setEnabled(false);
    ui->pushButton_D->setEnabled(false);
    ui->pushButton_E->setEnabled(false);
    ui->pushButton_F->setEnabled(false);
    ui->pushButton_A->setStyleSheet(numColorBlocked);
    ui->pushButton_B->setStyleSheet(numColorBlocked);
    ui->pushButton_C->setStyleSheet(numColorBlocked);
    ui->pushButton_D->setStyleSheet(numColorBlocked);
    ui->pushButton_E->setStyleSheet(numColorBlocked);
    ui->pushButton_F->setStyleSheet(numColorBlocked);
    lettersBlocked = true;
}
void MainWindow::unblockLetters() {
    ui->pushButton_A->setEnabled(true);
    ui->pushButton_B->setEnabled(true);
    ui->pushButton_C->setEnabled(true);
    ui->pushButton_D->setEnabled(true);
    ui->pushButton_E->setEnabled(true);
    ui->pushButton_F->setEnabled(true);
    ui->pushButton_A->setStyleSheet(numColorOff);
    ui->pushButton_B->setStyleSheet(numColorOff);
    ui->pushButton_C->setStyleSheet(numColorOff);
    ui->pushButton_D->setStyleSheet(numColorOff);
    ui->pushButton_E->setStyleSheet(numColorOff);
    ui->pushButton_F->setStyleSheet(numColorOff);
    lettersBlocked = false;
    // setNumStyle();
}
void MainWindow::setArrowsStatus() {
    currentPlainText = vec[currentVecIndex];
    switch (currentVecIndex)
    {
    case 0:
        blockLeft();
        unblockRight();
        unblockLetters();
        leftMoveBlocked = true;
        rightMoveBlocked = false;
        break;
    case 1:
        unblockLeft();
        unblockRight();
        blockLetters();
        leftMoveBlocked = false;
        rightMoveBlocked = false;
        break;
    case 2:
        unblockLeft();
        unblockRight();
        unblockLetters();
        leftMoveBlocked = false;
        rightMoveBlocked = false;
        break;
    case 3:
        unblockLeft();
        blockRight();
        blockLetters();
        leftMoveBlocked = false;
        rightMoveBlocked = true;
        break;

    default:
        break;
    }

    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
}

void MainWindow::on_plainTextEdit_Num1_clicked() {
    currentVecIndex = 0;
}
void MainWindow::on_plainTextEdit_System1_clicked() {
    currentVecIndex = 1;
}
void MainWindow::on_plainTextEdit_Num2_clicked() {
    currentVecIndex = 2;
}
void MainWindow::on_plainTextEdit_System2_clicked() {
    currentVecIndex = 3;
}

void MainWindow::on_pushButton_Division_pressed() {
    ui->pushButton_Division->setStyleSheet(signColorPressed);
};
void MainWindow::on_pushButton_Multiply_pressed() {
    ui->pushButton_Multiply->setStyleSheet(signColorPressed);
};
void MainWindow::on_pushButton_Sum_pressed() {
    ui->pushButton_Sum->setStyleSheet(signColorPressed);
};
void MainWindow::on_pushButton_Sub_pressed() {
    ui->pushButton_Sub->setStyleSheet(signColorPressed);
};
void MainWindow::on_pushButton_Equal_pressed() {
    ui->pushButton_Equal->setStyleSheet(signColorPressed);
};

void MainWindow::on_pushButton_ClearAll_clicked() {
    ui->plainTextEdit_Num1->setPlainText("");
    ui->plainTextEdit_Num2->setPlainText("");
    ui->plainTextEdit_System1->setPlainText("");
    ui->plainTextEdit_System2->setPlainText("");
    ui->label_Sign->setText("");
    ui->plainTextEdit_Answer->setPlainText("");
    currentSign = "";
    setDefaultSettings();
};
void MainWindow::on_pushButton_Right_clicked() {
    currentVecIndex++;
    setArrowsStatus();    
}
void MainWindow::on_pushButton_Left_clicked() {
    currentVecIndex--;
    setArrowsStatus();
}
void MainWindow::on_pushButton_Delete_clicked() {
    QString text = currentPlainText->toPlainText();
    text.resize(text.size() - 1);
    currentPlainText->setPlainText(text);
    setNumStyle();
}

void MainWindow::on_pushButton_ClearAll_pressed() {
    ui->pushButton_ClearAll->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Right_pressed() {
    ui->pushButton_Right->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Left_pressed() {
    ui->pushButton_Left->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Delete_pressed() {
    ui->pushButton_Delete->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Division_clicked() {
    currentSign = "÷";
    ui->label_Sign->setText(currentSign);
    setSignStyle();
    ui->pushButton_Division->setStyleSheet(signColorOn);
};
void MainWindow::on_pushButton_Multiply_clicked() {
    currentSign = "×";
    ui->label_Sign->setText(currentSign);
    setSignStyle();
    ui->pushButton_Multiply->setStyleSheet(signColorOn);
};
void MainWindow::on_pushButton_Sum_clicked() {
    currentSign = "+";
    ui->label_Sign->setText(currentSign);
    setSignStyle();
    ui->pushButton_Sum->setStyleSheet(signColorOn);
};
void MainWindow::on_pushButton_Sub_clicked() {
    currentSign = "−";
    ui->label_Sign->setText(currentSign);
    setSignStyle();
    ui->pushButton_Sub->setStyleSheet(signColorOn);
};
void MainWindow::on_pushButton_Equal_clicked() {
    setSignStyle();
    setOutputStyle();
    QString num1 = ui->plainTextEdit_Num1->toPlainText(), num2 = ui->plainTextEdit_Num2->toPlainText(),
        system1 = ui->plainTextEdit_System1->toPlainText(), system2 = ui->plainTextEdit_System2->toPlainText();

    if (!Num_input_check(num1.toStdString())) ui->plainTextEdit_Num1->setStyleSheet(outputColorError);
    else if (!Num_input_check(num2.toStdString())) ui->plainTextEdit_Num2->setStyleSheet(outputColorError);
    else if (!Sys_input_check(system1.toStdString())) ui->plainTextEdit_System1->setStyleSheet(outputColorError);
    else if(!Sys_input_check(system2.toStdString())) ui->plainTextEdit_System2->setStyleSheet(outputColorError);
    else if (!Pair_check(num1.toStdString(), system1.toInt())) {
        ui->plainTextEdit_Num1->setStyleSheet(outputColorError);
        ui->plainTextEdit_System1->setStyleSheet(outputColorError); 
    } else if(!Pair_check(num2.toStdString(), system2.toInt())) {
        ui->plainTextEdit_Num2->setStyleSheet(outputColorError);
        ui->plainTextEdit_System2->setStyleSheet(outputColorError);
    } else if (currentSign == "÷" && !Division_check(num2.toInt()) || currentSign == "") {
        ui->label_Sign->setStyleSheet(outputColorError);
    } else {
        setOutputStyle();
        Answer(To_dec(num1.toStdString(), system1.toInt()), To_dec(num2.toStdString(), system2.toInt()), currentSign.toStdString());
        ui->plainTextEdit_Answer->setPlainText(answer_);
    }
};

void MainWindow::on_pushButton_0_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "0");
    setNumStyle();
}
void MainWindow::on_pushButton_1_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "1");
    setNumStyle();
}
void MainWindow::on_pushButton_2_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "2");
    setNumStyle();
}
void MainWindow::on_pushButton_3_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "3");
    setNumStyle();
}
void MainWindow::on_pushButton_4_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "4");
    setNumStyle();
}
void MainWindow::on_pushButton_5_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "5");
    setNumStyle();
}
void MainWindow::on_pushButton_6_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "6");
    setNumStyle();
}
void MainWindow::on_pushButton_7_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "7");
    setNumStyle();
}
void MainWindow::on_pushButton_8_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "8");
    setNumStyle();
}
void MainWindow::on_pushButton_9_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "9");
    setNumStyle();
}
void MainWindow::on_pushButton_A_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "A");
    setNumStyle();
}
void MainWindow::on_pushButton_B_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "B");
    setNumStyle();
}
void MainWindow::on_pushButton_C_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "C");
    setNumStyle();
}
void MainWindow::on_pushButton_D_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "D");
    setNumStyle();
}
void MainWindow::on_pushButton_E_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "E");
    setNumStyle();
}
void MainWindow::on_pushButton_F_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "F");
    setNumStyle();
}

void MainWindow::on_pushButton_0_pressed() {
    ui->pushButton_0->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_1_pressed() {
    ui->pushButton_1->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_2_pressed() {
    ui->pushButton_2->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_3_pressed() {
    ui->pushButton_3->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_4_pressed() {
    ui->pushButton_4->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_5_pressed() {
    ui->pushButton_5->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_6_pressed() {
    ui->pushButton_6->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_7_pressed() {
    ui->pushButton_7->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_8_pressed() {
    ui->pushButton_8->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_9_pressed() {
    ui->pushButton_9->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_A_pressed() {
    ui->pushButton_A->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_B_pressed() {
    ui->pushButton_B->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_C_pressed() {
    ui->pushButton_C->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_D_pressed() {
    ui->pushButton_D->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_E_pressed() {
    ui->pushButton_E->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_F_pressed() {
    ui->pushButton_F->setStyleSheet(numColorPressed);
}
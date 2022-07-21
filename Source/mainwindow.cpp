#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"
#include <QClipboard>
#include <QTextCursor>



QString ans = "0";
QString history[20];
int actual=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->insert_math->viewport()->setAutoFillBackground(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    cur_pos = event->globalPosition().toPoint();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event){
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x()+new_pos.x(),y()+new_pos.y());
        cur_pos = event->globalPosition().toPoint();
}

void MainWindow::on_btn_exit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_btn_minimize_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}


void MainWindow::on_insert_dot_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + ".");
}


void MainWindow::on_insert_0_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "0");
}


void MainWindow::on_clear_btn_clicked()
{
    ui->insert_math->setText("");
    ui->labelResult->setText("");
}


void MainWindow::on_insert_1_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "1");
}


void MainWindow::on_insert_2_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "2");
}


void MainWindow::on_insert_3_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "3");
}


void MainWindow::on_insert_plus_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "+");
}


void MainWindow::on_insert_minus_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "-");
}


void MainWindow::on_insert_4_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "4");
}


void MainWindow::on_insert_5_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "5");
}


void MainWindow::on_insert_6_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "6");
}


void MainWindow::on_insert_multiplication_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "*");
}


void MainWindow::on_insert_division_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "/");
}


void MainWindow::on_insert_7_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "7");
}


void MainWindow::on_insert_8_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "8");
}


void MainWindow::on_insert_9_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "9");
}


void MainWindow::on_insert_lb_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "(");
}


void MainWindow::on_insert_rb_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + ")");
}


void MainWindow::on_insert_enter_clicked()
{
    QString data = ui->insert_math->toPlainText();
    std::string eq = data.toStdString();
    calculate a(eq);
    a.calcOperation();
    RESULTINFO ress = a.returnResult();
    if(ress.error){
        QString valueAsString = QString::fromStdString(ress.error_desc);
        ui->labelResult->setStyleSheet("color:#eee;text-align: right;font-family: \"Segoe UI\";font-size: 12px;");
        ui->labelResult->setText(valueAsString);
    }
    else{
     ui->labelResult->setStyleSheet("color:#eee;text-align: right;font-family: \"Segoe UI\";font-size: 22px;");
     QString valueAsString = QString::number(ress.result, 'g', 15);
     ui->labelResult->setText(valueAsString);
     ans = valueAsString;
    }


}


void MainWindow::on_insert_ans_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + ans);
}





void MainWindow::on_insert_cos_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "cos(");
}


void MainWindow::on_insert_ctan_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "ctan(");
}


void MainWindow::on_insert_log_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "log(");
}


void MainWindow::on_insert_sin_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "sin(");
}


void MainWindow::on_insert_tan_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "tan(");
}


void MainWindow::on_insert_arccos_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "arccos(");
}


void MainWindow::on_insert_arcsin_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "arcsin(");
}


void MainWindow::on_insert_arctan_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "arctan(");
}


void MainWindow::on_insert_ln_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "ln(");
}


void MainWindow::on_insert_pow_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "pow(");
}


void MainWindow::on_insert_cbrt_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "cbrt(");
}


void MainWindow::on_insert_e_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "e");
}


void MainWindow::on_insert_pi_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "pi");
}


void MainWindow::on_insert_sqrt_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + "sqrt(");
}


void MainWindow::on_insert_sred_clicked()
{
    ui->insert_math->setText(ui->insert_math->toPlainText() + ";");
}


void MainWindow::on_copy_btn_clicked()
{

    QClipboard *clip = QApplication::clipboard();
    clip->setText(ui->labelResult->text());

}

void MainWindow::on_return_btn_clicked()
{
    if(actual!=0){
        ui->insert_math->setText(history[actual-1]);
        actual--;

    }
}


void MainWindow::on_next_btn_clicked()
{
    if(actual!=19 && history[actual+1]!=""){
        ui->insert_math->setText(history[actual+1]);
        actual++;
    }
}


void MainWindow::on_btn_question_clicked()
{
    system("start manual.pdf");

}


void MainWindow::on_btn_color1_clicked()
{
    ui->display_bar->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(161, 40, 255, 255), stop:1 rgba(255, 92, 176, 255));");
    ui->btn_question->setStyleSheet("QPushButton{background-color: #eee; color: rgba(161, 40, 255, 255);} QPushButton:hover{color: #eee;background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(161, 40, 255, 255), stop:1 rgba(255, 92, 176, 255));}");
}


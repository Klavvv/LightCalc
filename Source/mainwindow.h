#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btn_exit_clicked();

    void on_btn_minimize_clicked();

    void on_insert_dot_clicked();

    void on_insert_0_clicked();

    void on_clear_btn_clicked();

    void on_insert_1_clicked();

    void on_insert_2_clicked();

    void on_insert_3_clicked();

    void on_insert_minus_clicked();

    void on_insert_plus_clicked();

    void on_insert_4_clicked();

    void on_insert_5_clicked();

    void on_insert_6_clicked();

    void on_insert_division_clicked();

    void on_insert_multiplication_clicked();

    void on_insert_7_clicked();

    void on_insert_8_clicked();

    void on_insert_9_clicked();

    void on_insert_lb_clicked();

    void on_insert_rb_clicked();

    void on_insert_enter_clicked();

    void on_insert_ans_clicked();

    void on_pushButton_27_clicked();

    void on_insert_cos_clicked();

    void on_insert_ctan_clicked();

    void on_insert_log_clicked();

    void on_insert_sin_clicked();

    void on_insert_tan_clicked();

    void on_insert_arccos_clicked();

    void on_insert_arcsin_clicked();

    void on_insert_arctan_clicked();

    void on_insert_ln_clicked();

    void on_insert_pow_clicked();

    void on_insert_cbrt_clicked();

    void on_insert_e_clicked();

    void on_insert_pi_clicked();

    void on_insert_sqrt_clicked();

    void on_insert_sred_clicked();

    void on_copy_btn_clicked();

    void on_return_btn_clicked();

    void on_next_btn_clicked();

    void on_btn_question_clicked();

    void on_btn_color1_clicked();

private:
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
};
#endif // MAINWINDOW_H

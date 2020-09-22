#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pb_random_clicked();

    void on_pb_reset_clicked();

    void on_pb_merge_clicked();

    void on_te_input_returnPressed();

    void on_pb_insert_clicked();

    void on_pb_back_clicked();

    void on_pb_sort_clicked();

private:
    Ui::MainWindow *ui;
    int A[100];
    int B[100];
    int C[200];
    int n_a;
    int n_b;
    int n_c;
    struct {
        int data[1000];
        int top;
    } pos_stk_a, pos_stk_b;
    void randomAB();
    void updateData();
    void resetData();
    int static cmp(const void *a,const void *b);
    int insertSort(int *a, int size, int data);
    void insertNum();
    void backNum();
    void merge();
    void deleteNum();
    void deleteNum(int *a, int size, int p);
};
#endif // MAINWINDOW_H

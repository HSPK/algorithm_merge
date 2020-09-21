#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::merge() {
    int i, j, k;
    i = j = k = 0;
    while (i < n_a && j < n_b)
        C[k++] = A[i] > B[j] ? B[j++] : A[i++];
    if (i == n_a)
        while (j < n_b) C[k++] = B[j++];
    while (i < n_a) C[k++] = A[i++];
    n_c = n_a + n_b;
}

void MainWindow::updateData() {
    QString string_a;
    QString string_b;
    QString string_c;
    for (int i = 0; i < n_a; i++) {
        string_a.append(QString::number(A[i]));
        string_a.append('\n');
    }
    ui->label_a->setText(string_a);
    for (int i = 0; i < n_b; i++) {
        string_b.append(QString::number(B[i]));
        string_b.append('\n');
    }
    ui->label_b->setText(string_b);
    for (int i = 0; i < n_c; i++) {
        string_c.append(QString::number(C[i]));
        string_c.append('\n');
    }
    ui->label_m->setText(string_c);
    ui->lb_cnt_a->setNum(n_a);
    ui->lb_cnt_b->setNum(n_b);
    ui->lb_cnt_c->setNum(n_c);
}

void MainWindow::resetData() {
    n_a = n_b = n_c = 0;
    memset(pos_stk.data, 0, sizeof(pos_stk.data));
    pos_stk.top = -1;
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    memset(C, 0, sizeof(C));
    updateData();
}

int MainWindow::cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void MainWindow::randomAB() {
    resetData();
    n_a = ui->te_num_a->text().toInt();
    n_b = ui->te_num_b->text().toInt();
    int min = ui->te_min->text().toInt();
    int max = ui->te_max->text().toInt();

    srand(time(NULL));
    for (int i = 0; i < n_a; i++) A[i] = rand() % (max - min + 1) + min;
    for (int j = 0; j < n_b; j++) B[j] = rand() % (max - min + 1) + min;
    std::qsort(A, n_a, sizeof(int), cmp);
    std::qsort(B, n_b, sizeof(int), cmp);
    updateData();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resetData();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_random_clicked()
{
    resetData();
    randomAB();
    updateData();
}

void MainWindow::on_pb_reset_clicked()
{
    resetData();
}

void MainWindow::on_pb_merge_clicked()
{
    merge();
    updateData();
}

int MainWindow::insertSort(int *a, int size, int data) {
    int p = 0;
    while (a[p] < data && p < size) p++;
    for (int i = size; i > p; i--) a[i] = a[i - 1];
    a[p] = data;
    return p;
}

void MainWindow::insertNum() {
    int tmp = ui->te_input->text().toInt();
    if (ui->rb_a->isChecked()) {
        pos_stk.data[++pos_stk.top] = insertSort(A, n_a++, tmp);
    } else {
        pos_stk.data[++pos_stk.top] = insertSort(B, n_b++, tmp);
    }
    ui->te_input->clear();
    updateData();
}

void MainWindow::deleteNum(int *a, int size, int p)
{
    for (int i = p; i < size; i++) a[i] = a[i+1];
}

void MainWindow::backNum() {
    if (pos_stk.top <= -1) return;
    if (ui->rb_a->isChecked()) {
        deleteNum(A, n_a--, pos_stk.data[pos_stk.top--]);
    } else {
        deleteNum(B, n_b--, pos_stk.data[pos_stk.top--]);
    }
    updateData();
}

void MainWindow::on_te_input_returnPressed()
{
    insertNum();
}

void MainWindow::on_pb_insert_clicked()
{
    insertNum();
}

void MainWindow::on_pb_back_clicked()
{
    backNum();
}

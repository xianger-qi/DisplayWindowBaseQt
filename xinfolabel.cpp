#include "xinfolabel.h"
#include "ui_xinfolabel.h"
#include  <QDebug>
XInfoLabel::XInfoLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XInfoLabel)
{
    ui->setupUi(this);
    this->setVisible(false);
    this->setWindowFlag(Qt::FramelessWindowHint);

}

XInfoLabel::~XInfoLabel()
{
    delete ui;
}

void XInfoLabel::SetPos(int row, int col)
{
    ui->label_pos->setText("row:" + QString::number(row) + ", col:" +QString::number(col));
}

void XInfoLabel::SetRGB(int r, int g, int b)
{
    QString strR = (r == -1 ? "_, " : QString::number(r) + ", ");
    QString strG = (g == -1 ? "_, " : QString::number(g) + ", ");
    QString strB = (b == -1 ? "_)" : QString::number(b) + ")");

    ui->label_rgb->setText((QString("rgb: (") + strR + strG + strB));
}

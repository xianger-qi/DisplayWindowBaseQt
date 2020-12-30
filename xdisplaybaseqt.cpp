#include "xdisplaybaseqt.h"
#include "ui_xdisplaybaseqt.h"
#include "xdisplaybaseqtimpl.h"
#include <QDebug>
XDisplayBaseQT::XDisplayBaseQT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XDisplayBaseQT)
{
    ui->setupUi(this);
}

void XDisplayBaseQT::DispObject(const HalconCpp::HObject &hobject)
{
    ui->label->DispObject(hobject);
}

void XDisplayBaseQT::DispObject(const QImage &img)
{
    ui->label->DispObject(img);
}

void XDisplayBaseQT::DispObject(const cv::Mat &img)
{
    ui->label->DispObject(img);
}

void XDisplayBaseQT::DispRegion(const QVector<QPoint> &vecPoints)
{
    ui->label->DispRegion(vecPoints);
}

void XDisplayBaseQT::DispRegion(const QPolygon &regoin)
{
    ui->label->DispRegion(regoin);
}

QPoint XDisplayBaseQT::GetCurPosInImageCord()
{
    return ui->label->GetPosInImageCord();
}

XDisplayBaseQT::~XDisplayBaseQT()
{
    delete ui;
}

void XDisplayBaseQT::mousePressEvent(QMouseEvent *event)
{
    ui->label->GetPosInImageCord();
}



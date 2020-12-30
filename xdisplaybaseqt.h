#ifndef XDISPLAYBASEQT_H
#define XDISPLAYBASEQT_H

#if defined(XDISPLAYBASEQT_LIBRARY)
#  define XDISPLAYBASEQTSHARED_EXPORT __declspec(dllexport)
#else
#  define XDISPLAYBASEQTSHARED_EXPORT __declspec(dllimport)
#endif

#include <QWidget>
#include <memory>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>
#include <halconcpp/HalconCpp.h>
class XDisplayBaseQTImpl;
namespace Ui {
class XDisplayBaseQT;
}

class XDISPLAYBASEQTSHARED_EXPORT XDisplayBaseQT : public QWidget
{
    Q_OBJECT

public:
    explicit XDisplayBaseQT(QWidget *parent = 0);
    void DispObject(const HalconCpp::HObject &hobject);
    void DispObject(const QImage &img);
    void DispObject(const cv::Mat &img);
    void DispRegion(const QVector<QPoint> &vecPoints);
    void DispRegion(const QPolygon &regoin);
    QPoint GetCurPosInImageCord();
    ~XDisplayBaseQT();
protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    Ui::XDisplayBaseQT *ui;
};

#endif // XDISPLAYBASEQT_H

#ifndef XDISPLAYBASEQTIMPL_H
#define XDISPLAYBASEQTIMPL_H

#include <QLabel>
#include <QImage>
#include <QWheelEvent>
#include <QMouseEvent>
#include <halconcpp/HalconCpp.h>
#include <opencv2/opencv.hpp>
namespace Ui {
class XDisplayBaseQTImpl;
}
const int ZOOMOUT_LIMIT = 2048;
const double ZOOMIN_LIMIT = 1/32;

class vtkImageViewer2;
class vtkRenderer;
class XInfoLabel;
class XDisplayBaseQTImpl : public QLabel
{
    Q_OBJECT
    enum EZOOM_WAY
    {
        ZOOM_IN, //放大
        ZOOM_OUT //缩小
    };

    enum EMOUSE_MODE
    {
        MOUSE_TRANSLATE,
        MOUSE_DRAW
    };
public:
    explicit XDisplayBaseQTImpl(QWidget *parent = 0);
    void DispObject(const QImage &img);
    void DispObject(const HalconCpp::HObject &hobject);
    void DispObject(const cv::Mat &img);
    void DispRegion(const QVector<QPoint> &vecPoints);
    void DispRegion(const QPolygon &region);
    QPoint GetPosInImageCord() ;
    ~XDisplayBaseQTImpl();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void SetViewPart(double top, double left, double bottom, double right);
    void SetViewPart(const QRectF &viewPart);
    void Zoom(EZOOM_WAY way);
    void CalcOriginalViewPart(QRectF *part);
    void Translate();
    QRgb GetGrayVal(const QPoint &pos);
    QImage TransFromHobject(const HalconCpp::HObject &hobj, int channels);
    QImage TransFromMat(const cv::Mat &mat, int channles);
    void UpdateScreenOffLine();

private:
    Ui::XDisplayBaseQTImpl *ui;
    QImage m_curDisplayedImg;
    QRectF m_curViewPart;
    bool m_isInsertImage;
    float m_dCurrCoeff;
    float m_dCoeff;
    QRectF m_InitRectDisp;
    double m_zoominLimit;
    double m_zoomoutLimit;
    QPoint m_mousePressPoint;
    XInfoLabel *m_infoLabel;
    bool m_ismouseLeftPress;
    HalconCpp::HObject m_obj;
    QPolygon m_vecPoly;
    QPolygon m_curDispRegion;
    EMOUSE_MODE m_mouseMode;
    QPixmap m_mainPixmap;
    QPixmap m_bufferPixmap;     //双缓冲

    bool m_isDrawing;
};

#endif // XDISPLAYBASEQTIMPL_H

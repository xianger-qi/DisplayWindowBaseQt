#include "xdisplaybaseqtimpl.h"
#include "ui_xdisplaybaseqtimpl.h"
#include <xinfolabel.h>
#include <QDebug>
#include <QPainter>
#include <XLogger.h>
#include <QBuffer>
#include <opencv2/opencv.hpp>
#include <QTime>
#include <QRegion>
//坐标系 分为 X, Y轴，竖向为Y轴， 横向为X轴
XDisplayBaseQTImpl::XDisplayBaseQTImpl(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::XDisplayBaseQTImpl),
    m_isInsertImage(false),
    m_dCurrCoeff(0.0),
    m_infoLabel(new XInfoLabel(this)),
    m_dCoeff(0.0),
    m_ismouseLeftPress(false),
    m_mouseMode(MOUSE_DRAW),
    m_isDrawing(false)
{
    ui->setupUi(this);
}

void XDisplayBaseQTImpl::DispObject(const QImage &img)
{

    {
        XTimer start("sadsad");
        m_curDisplayedImg = img;
        //m_mainPixmap = QPixmap::fromImage(img);
        QRectF curViewPart;
        CalcOriginalViewPart(&curViewPart);
        SetViewPart(curViewPart);
        m_isInsertImage = true;
    }

    this->repaint();
}

void XDisplayBaseQTImpl::DispObject(const HalconCpp::HObject &hobject)
{
    m_obj = hobject;
    HalconCpp::HTuple htChannel;
    HalconCpp::CountChannels(hobject, &htChannel);
    if(htChannel == HalconCpp::HTuple(0))
    {
        //region
    }
    else if(htChannel == HalconCpp::HTuple(1))
    {
        //单通道
        DispObject(TransFromHobject(hobject, 1));
    }
    else if(htChannel == HalconCpp::HTuple(3))
    {
        //3通道
        DispObject(TransFromHobject(hobject, 3));
    }
}

void XDisplayBaseQTImpl::DispObject(const cv::Mat &img)
{
    if(1 == img.channels())
    {
        //单通道
        DispObject(TransFromMat(img, 1));
    }
    else if(3 == img.channels())
    {
        //三通道
        DispObject(TransFromMat(img, 3));
    }
}

void XDisplayBaseQTImpl::DispRegion(const QVector<QPoint> &vecPoints)
{
    if(m_isInsertImage)
    {
        m_vecPoly.clear();
        m_vecPoly.append(vecPoints);
        UpdateScreenOffLine();
    }
}

void XDisplayBaseQTImpl::DispRegion(const QPolygon &region)
{
    if(m_isInsertImage)
    {
        m_vecPoly.clear();
        m_vecPoly.swap(QPolygon());
        m_vecPoly = region;
        UpdateScreenOffLine();
    }
}

QPoint XDisplayBaseQTImpl::GetPosInImageCord()
{
    double row1 = m_curViewPart.top() ;
    double col1 = m_curViewPart.left();
    double row2 = m_curViewPart.bottom();
    double col2 = m_curViewPart.right();

    QPoint p = mapFromGlobal(this->cursor().pos());
    double width = col2 - col1;
    double height = row2 - row1;
    QSize size = this->size();
    double stepWidth = width/(size.width() * 1.0);  //一个视口像素代表多少个窗口像素
    double stepHeight = height/(size.height() * 1.0);
    double x = stepWidth * p.x() + col1 - 0.5;
    double y = stepHeight * p.y() + row1 - 0.5;
    return QPointF(x, y).toPoint();
}

XDisplayBaseQTImpl::~XDisplayBaseQTImpl()
{
    delete ui;
}

void XDisplayBaseQTImpl::wheelEvent(QWheelEvent *event)
{
    if(event->delta() < 0)
    {
        //滚向自己
        Zoom(EZOOM_WAY::ZOOM_IN);
    }
    else
    {
        //滚向远方
        Zoom(EZOOM_WAY::ZOOM_OUT);
    }
    QWidget::wheelEvent(event);
}

void XDisplayBaseQTImpl::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_ismouseLeftPress = true;
        m_mousePressPoint = GetPosInImageCord();
    }
    QLabel::mousePressEvent(event);
}

void XDisplayBaseQTImpl::mouseMoveEvent(QMouseEvent *event)
{
    if(m_ismouseLeftPress)
    {
        if(m_mouseMode == MOUSE_DRAW)
        {
            QPoint movePos = GetPosInImageCord();
            m_curDispRegion = QPolygon(QRect(m_mousePressPoint, QSize(movePos.x() - m_mousePressPoint.x(), movePos.y() - m_mousePressPoint.y())));
            m_isDrawing = true;
            this->repaint();
        }
        else if(m_mouseMode == MOUSE_TRANSLATE)
        {
            Translate();
            QLabel::mouseMoveEvent(event);
        }
    }
    else
    {
        m_infoLabel->setVisible(true);
        QPoint pos = GetPosInImageCord();
        QRgb rgb = GetGrayVal(pos);
        m_infoLabel->SetPos(pos.y(), pos.x());
        m_infoLabel->SetRGB(qRed(rgb), qGreen(rgb), qBlue(rgb));
        m_infoLabel->move(event->pos().x() + 10, event->pos().y() + 10);
    }
}

void XDisplayBaseQTImpl::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_ismouseLeftPress = false;
        if(m_mouseMode == MOUSE_DRAW)
        {
            m_isDrawing = false;
            this->repaint();
        }
    }
    m_infoLabel->setVisible(false);
    QLabel::mouseReleaseEvent(event);
}

void XDisplayBaseQTImpl::paintEvent(QPaintEvent *event)
{
    XTimer start;
    if(m_isInsertImage)
    {
        QPainter painter_screen(this);
        painter_screen.setViewport(this->rect());
        QPen pen("blue");
        pen.setWidth(0);
        painter_screen.setPen(pen);

        painter_screen.setWindow(m_curViewPart.toRect());
        painter_screen.drawImage(m_curDisplayedImg.rect(), m_curDisplayedImg);
        //painter_screen.drawPixmap(m_mainPixmap.rect(), m_mainPixmap);
        if(m_isDrawing)
        {
            //m_bufferPixmap = m_mainPixmap;
//            QPainter pp(&m_bufferPixmap);
//            pp.setPen(pen);
            painter_screen.drawPolygon(m_curDispRegion);
            //painter.drawPixmap(0, 0, m_bufferPixmap);
        }
        else
        {
//            QPainter pp(&m_mainPixmap);
//            QPen pen1("blue");
//            pen1.setWidth(0);
//            pp.setPen(pen1);
//            pp.drawPolygon(m_curDispRegion);
           // painter_screen.drawPolygon(m_vecPoly);
        }
//        QPainter bufferPainter(&m_bufferPixmap);
//        bufferPainter.setPen(pen);
//        bufferPainter.drawPolygon(m_curDispRegion);
//        painter.drawPixmap(0, 0, m_bufferPixmap);
    }
}

void XDisplayBaseQTImpl::SetViewPart(double top, double left, double bottom, double right)
{
    m_curViewPart = QRectF(left, top, (right - left), (bottom - top));
}


void XDisplayBaseQTImpl::SetViewPart(const QRectF &viewPart)
{
    m_curViewPart = viewPart;
}

void XDisplayBaseQTImpl::Zoom(XDisplayBaseQTImpl::EZOOM_WAY way)
{
    double coeffEnlarge = 1.2;
    if(way == EZOOM_WAY::ZOOM_OUT)
    {
        //缩小
        if(m_curViewPart.bottom() - m_curViewPart.top() > m_zoominLimit ||\
           m_curViewPart.right() - m_curViewPart.left() > m_zoominLimit)
            return;
    }
    else
    {
        //放大
        coeffEnlarge = 1.0 / coeffEnlarge;      //取coeffEnlaige 的倒数
        if(m_curViewPart.bottom() - m_curViewPart.top() < m_zoomoutLimit ||\
           m_curViewPart.right() - m_curViewPart.left() < m_zoomoutLimit)
            return;
    }
    QPoint curPos = GetPosInImageCord();
    double col = curPos.x();
    double row = curPos.y();
    double left = ((m_curViewPart.left() - col) * coeffEnlarge) + col;
    double right = ((m_curViewPart.right() - col) * coeffEnlarge) + col;
    double top = ((m_curViewPart.top() - row) * coeffEnlarge) + row;
    double bottom = ((m_curViewPart.bottom() - row) * coeffEnlarge) + row;
    QRectF zoomPart;
    zoomPart.setTop(top);
    zoomPart.setBottom(bottom);
    zoomPart.setLeft(left);
    zoomPart.setRight(right);
    SetViewPart(zoomPart);
    this->repaint();
}

void XDisplayBaseQTImpl::CalcOriginalViewPart(QRectF *part)
{
    int imgWidth = m_curDisplayedImg.width();
    int imgHeight = m_curDisplayedImg.height();
    int windowWidth = this->width();
    int windowHeight = this->height();
    m_zoominLimit = (imgHeight * 1.0 / ZOOMIN_LIMIT);
    m_zoomoutLimit = (imgHeight * 1.0 / ZOOMOUT_LIMIT);
    //横纵向缩放比例
    double coeffW = imgWidth * 1.0 / windowWidth;
    double coeffH = imgHeight * 1.0 / windowHeight;
    if(coeffW <= coeffH)
    {
        //以图片的高自适应窗口
        part->setLeft((coeffW - coeffH) / 2 * (windowWidth * 1.0));
        part->setRight((coeffW + coeffH) / 2 * (windowWidth * 1.0));
        part->setTop(0);
        part->setBottom(imgHeight - 1);
        return;
    }
    else
    {
        //以图片的宽自适应窗口
        part->setLeft(0);
        part->setRight(imgWidth -1);
        part->setTop((-coeffW + coeffH) / 2 * (windowHeight * 1.0));
        part->setBottom((coeffW + coeffH) / 2 * (windowHeight * 1.0));
        return;
    }
}

void XDisplayBaseQTImpl::Translate()
{
    QPoint movePoint = GetPosInImageCord();
    int row = movePoint.y() - m_mousePressPoint.y();
    int col = movePoint.x() - m_mousePressPoint.x();
    double top = m_curViewPart.top() - row;
    double bottom = m_curViewPart.bottom() - row;
    double left = m_curViewPart.left() - col;
    double right = m_curViewPart.right() - col;
    SetViewPart(top, left, bottom, right);
    this->repaint();
}

QRgb XDisplayBaseQTImpl::GetGrayVal(const QPoint &pos)
{
    return m_curDisplayedImg.pixel(pos);
}

QImage XDisplayBaseQTImpl::TransFromHobject(const HalconCpp::HObject &hobj, int channels)
{
    if(1 == channels || 0 == channels)
    {
        HalconCpp::HTuple htPtr, htType, htWidth, htHeight;
        HalconCpp::GetImagePointer1(hobj, &htPtr, &htType, &htWidth, &htHeight);
        return QImage ((uchar *)(htPtr.L()), htWidth.D(), htHeight.D(), QImage::Format_Grayscale8);
    }
    else if(3 == channels)
    {
        HalconCpp::HTuple htPR, htPG, htPB, htType, htWidth, htHeight;
        HalconCpp::GetImagePointer3(hobj, &htPR, &htPG, &htPB, &htType, &htWidth, &htHeight);
        cv::Mat matR(htHeight.D(), htWidth.D(), CV_8UC1,(uchar *)(htPR.L()));
        cv::Mat matG(htHeight.D(), htWidth.D(), CV_8UC1,(uchar *)(htPG.L()));
        cv::Mat matB(htHeight.D(), htWidth.D(), CV_8UC1,(uchar *)(htPB.L()));
        std::vector<cv::Mat> vecMats;
        vecMats.reserve(3);
        vecMats.emplace_back(matR);
        vecMats.emplace_back(matG);
        vecMats.emplace_back(matB);
        cv::Mat resMat;
        cv::merge(vecMats, resMat);
        return QImage(resMat.data, resMat.cols, resMat.rows, resMat.cols * resMat.channels(), QImage::Format_RGB888).copy();
    }
    else
    {
        return QImage();
    }
}

QImage XDisplayBaseQTImpl::TransFromMat(const cv::Mat &mat, int channles)
{
    if(1 == channles)
    {
        //单通道
        return QImage(mat.data, mat.cols, mat.rows, QImage::Format_Grayscale8).copy();
    }
    else if(3 == channles)
    {
        //三通道
        cv::Mat matColorSwap;
        cv::cvtColor(mat, matColorSwap, CV_RGB2BGR);
        return QImage(matColorSwap.data, matColorSwap.cols, matColorSwap.rows, matColorSwap.cols * matColorSwap.channels(), QImage::Format_RGB888).copy();
    }
    else
    {
        return QImage();
    }
}

void XDisplayBaseQTImpl::UpdateScreenOffLine()
{
    QPainter painter(&m_mainPixmap);
    painter.drawPolygon(m_vecPoly);
    this->repaint();
}


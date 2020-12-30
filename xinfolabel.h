#ifndef XINFOLABEL_H
#define XINFOLABEL_H

#include <QWidget>

namespace Ui {
class XInfoLabel;
}

class XInfoLabel : public QWidget
{
    Q_OBJECT

public:
    explicit XInfoLabel(QWidget *parent = 0);
    ~XInfoLabel();
    void SetPos(int row, int col);
    void SetRGB(int r, int g, int b);
private:
    Ui::XInfoLabel *ui;
};

#endif // XINFOLABEL_H

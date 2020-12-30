/********************************************************************************
** Form generated from reading UI file 'xinfolabel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XINFOLABEL_H
#define UI_XINFOLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XInfoLabel
{
public:
    QGridLayout *gridLayout;
    QLabel *label_pos;
    QLabel *label_3;
    QLabel *label_rgb;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *XInfoLabel)
    {
        if (XInfoLabel->objectName().isEmpty())
            XInfoLabel->setObjectName(QStringLiteral("XInfoLabel"));
        XInfoLabel->resize(165, 60);
        XInfoLabel->setMaximumSize(QSize(165, 60));
        XInfoLabel->setStyleSheet(QStringLiteral("QWidget{background-color:red}"));
        gridLayout = new QGridLayout(XInfoLabel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(4, -1, -1, -1);
        label_pos = new QLabel(XInfoLabel);
        label_pos->setObjectName(QStringLiteral("label_pos"));
        label_pos->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label_pos, 0, 1, 1, 1);

        label_3 = new QLabel(XInfoLabel);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/icon/RGB.png")));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_rgb = new QLabel(XInfoLabel);
        label_rgb->setObjectName(QStringLiteral("label_rgb"));

        gridLayout->addWidget(label_rgb, 1, 1, 1, 1);

        label = new QLabel(XInfoLabel);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icon/cood.png")));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        retranslateUi(XInfoLabel);

        QMetaObject::connectSlotsByName(XInfoLabel);
    } // setupUi

    void retranslateUi(QWidget *XInfoLabel)
    {
        XInfoLabel->setWindowTitle(QApplication::translate("XInfoLabel", "Form", Q_NULLPTR));
        label_pos->setText(QApplication::translate("XInfoLabel", "(-,-)", Q_NULLPTR));
        label_3->setText(QString());
        label_rgb->setText(QApplication::translate("XInfoLabel", "(-,-,-)", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class XInfoLabel: public Ui_XInfoLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XINFOLABEL_H

/********************************************************************************
** Form generated from reading UI file 'xdisplaybaseqt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDISPLAYBASEQT_H
#define UI_XDISPLAYBASEQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "xdisplaybaseqtimpl.h"

QT_BEGIN_NAMESPACE

class Ui_XDisplayBaseQT
{
public:
    QGridLayout *gridLayout;
    XDisplayBaseQTImpl *label;

    void setupUi(QWidget *XDisplayBaseQT)
    {
        if (XDisplayBaseQT->objectName().isEmpty())
            XDisplayBaseQT->setObjectName(QStringLiteral("XDisplayBaseQT"));
        XDisplayBaseQT->resize(451, 368);
        gridLayout = new QGridLayout(XDisplayBaseQT);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new XDisplayBaseQTImpl(XDisplayBaseQT);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(XDisplayBaseQT);

        QMetaObject::connectSlotsByName(XDisplayBaseQT);
    } // setupUi

    void retranslateUi(QWidget *XDisplayBaseQT)
    {
        XDisplayBaseQT->setWindowTitle(QApplication::translate("XDisplayBaseQT", "Form", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class XDisplayBaseQT: public Ui_XDisplayBaseQT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDISPLAYBASEQT_H

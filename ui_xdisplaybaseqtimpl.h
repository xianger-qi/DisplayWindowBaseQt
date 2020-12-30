/********************************************************************************
** Form generated from reading UI file 'xdisplaybaseqtimpl.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDISPLAYBASEQTIMPL_H
#define UI_XDISPLAYBASEQTIMPL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XDisplayBaseQTImpl
{
public:
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *XDisplayBaseQTImpl)
    {
        if (XDisplayBaseQTImpl->objectName().isEmpty())
            XDisplayBaseQTImpl->setObjectName(QStringLiteral("XDisplayBaseQTImpl"));
        XDisplayBaseQTImpl->resize(523, 450);
        XDisplayBaseQTImpl->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(XDisplayBaseQTImpl);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));






        retranslateUi(XDisplayBaseQTImpl);

        QMetaObject::connectSlotsByName(XDisplayBaseQTImpl);
    } // setupUi

    void retranslateUi(QWidget *XDisplayBaseQTImpl)
    {
        XDisplayBaseQTImpl->setWindowTitle(QApplication::translate("XDisplayBaseQTImpl", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XDisplayBaseQTImpl: public Ui_XDisplayBaseQTImpl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDISPLAYBASEQTIMPL_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *PageChat;
    QHBoxLayout *horizontalLayout_14;
    QFrame *frame;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *btnLogout;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_13;
    QTextEdit *MessageArea;
    QListWidget *UserList;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *Message;
    QPushButton *btnSendMessege;
    QWidget *PageLogin;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnIPAddress;
    QLineEdit *IPAddress;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnNickName;
    QLineEdit *NickName;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnLogin;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 616);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        PageChat = new QWidget();
        PageChat->setObjectName("PageChat");
        horizontalLayout_14 = new QHBoxLayout(PageChat);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        frame = new QFrame(PageChat);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frame);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        horizontalLayout_12->addWidget(label_3);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_11);

        btnLogout = new QPushButton(frame);
        btnLogout->setObjectName("btnLogout");

        horizontalLayout_12->addWidget(btnLogout);


        verticalLayout_7->addLayout(horizontalLayout_12);

        verticalSpacer_5 = new QSpacerItem(20, 28, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_5);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        MessageArea = new QTextEdit(frame);
        MessageArea->setObjectName("MessageArea");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MessageArea->sizePolicy().hasHeightForWidth());
        MessageArea->setSizePolicy(sizePolicy);
        MessageArea->setMinimumSize(QSize(256, 512));
        MessageArea->setMaximumSize(QSize(512, 512));

        horizontalLayout_13->addWidget(MessageArea);

        UserList = new QListWidget(frame);
        UserList->setObjectName("UserList");
        sizePolicy.setHeightForWidth(UserList->sizePolicy().hasHeightForWidth());
        UserList->setSizePolicy(sizePolicy);
        UserList->setMinimumSize(QSize(0, 512));
        UserList->setMaximumSize(QSize(128, 512));

        horizontalLayout_13->addWidget(UserList);


        verticalLayout_7->addLayout(horizontalLayout_13);

        verticalSpacer_6 = new QSpacerItem(20, 17, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        Message = new QLineEdit(frame);
        Message->setObjectName("Message");

        horizontalLayout_11->addWidget(Message);

        btnSendMessege = new QPushButton(frame);
        btnSendMessege->setObjectName("btnSendMessege");

        horizontalLayout_11->addWidget(btnSendMessege);


        verticalLayout_7->addLayout(horizontalLayout_11);


        verticalLayout_8->addLayout(verticalLayout_7);


        horizontalLayout_14->addWidget(frame);

        stackedWidget->addWidget(PageChat);
        PageLogin = new QWidget();
        PageLogin->setObjectName("PageLogin");
        verticalLayout_3 = new QVBoxLayout(PageLogin);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(PageLogin);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";\n"
"color: rgb(0, 255, 127);"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnIPAddress = new QPushButton(PageLogin);
        btnIPAddress->setObjectName("btnIPAddress");

        horizontalLayout->addWidget(btnIPAddress);

        IPAddress = new QLineEdit(PageLogin);
        IPAddress->setObjectName("IPAddress");

        horizontalLayout->addWidget(IPAddress);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnNickName = new QPushButton(PageLogin);
        btnNickName->setObjectName("btnNickName");

        horizontalLayout_2->addWidget(btnNickName);

        NickName = new QLineEdit(PageLogin);
        NickName->setObjectName("NickName");

        horizontalLayout_2->addWidget(NickName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        btnLogin = new QPushButton(PageLogin);
        btnLogin->setObjectName("btnLogin");

        horizontalLayout_4->addWidget(btnLogin);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(verticalLayout_2);

        stackedWidget->addWidget(PageLogin);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\350\277\233\345\205\245\350\201\212\345\244\251\345\256\244", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        btnSendMessege->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\346\235\245\345\210\260\350\201\212\345\244\251\345\256\244", nullptr));
        btnIPAddress->setText(QCoreApplication::translate("MainWindow", "IP\345\234\260\345\235\200", nullptr));
        btnNickName->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#include "MainWindow.h"
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
// 引入功能界面头文件
#include "PatientWidget.h"
#include "DepartmentWidget.h"
#include "DoctorWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // ========== 1. 窗口基础设置 ==========
    setWindowTitle("医院管理系统--占鹏辉2023414290138");  // 窗口标题
    setMinimumSize(1000, 600);      // 最小尺寸，避免窗口过小
    setMaximumSize(1600, 900);      // 可选：设置最大尺寸

    // ========== 2. 顶部功能切换按钮 ==========
    QWidget *btnBarWidget = new QWidget(this);  // 按钮栏容器
    QHBoxLayout *btnLayout = new QHBoxLayout(btnBarWidget);
    btnLayout->setSpacing(30);                  // 按钮间距
    btnLayout->setContentsMargins(20, 10, 20, 10); // 边距

    // 初始化三个功能按钮
    m_btnPatient = new QPushButton("管理患者", this);
    m_btnDept = new QPushButton("管理科室", this);
    m_btnDoctor = new QPushButton("管理医生", this);

    // 设置按钮样式（可选：美化按钮）
    m_btnPatient->setFixedSize(120, 40);
    m_btnDept->setFixedSize(120, 40);
    m_btnDoctor->setFixedSize(120, 40);

    // 按钮加入布局
    btnLayout->addWidget(m_btnPatient);
    btnLayout->addWidget(m_btnDept);
    btnLayout->addWidget(m_btnDoctor);
    btnLayout->addStretch();  // 右侧留白，按钮靠左

    // ========== 3. 堆叠窗口（管理多个功能界面） ==========
    m_stackWidget = new QStackedWidget(this);

    // 初始化三个功能界面
    m_patientWidget = new PatientWidget();    // 患者管理界面（已有）
    m_deptWidget = new DepartmentWidget();    // 科室管理界面（新增）
    m_docWidget = new DoctorWidget();         // 医生管理界面（新增）

    // 将界面加入堆叠窗口（按顺序：0=患者，1=科室，2=医生）
    m_stackWidget->addWidget(m_patientWidget);
    m_stackWidget->addWidget(m_deptWidget);
    m_stackWidget->addWidget(m_docWidget);

    // ========== 4. 主布局组装 ==========
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0); // 去除整体边距
    mainLayout->setSpacing(0);                  // 布局间距为0

    // 按钮栏 + 堆叠窗口 加入主布局
    mainLayout->addWidget(btnBarWidget);
    mainLayout->addWidget(m_stackWidget);

    // 设置中央部件
    setCentralWidget(centralWidget);

    // ========== 5. 按钮点击切换界面 ==========
    // 管理患者按钮
    connect(m_btnPatient, &QPushButton::clicked, this, [=]() {
        m_stackWidget->setCurrentWidget(m_patientWidget);
        // 可选：按钮选中态
        m_btnPatient->setStyleSheet("background-color: #409EFF; color: white;");
        m_btnDept->setStyleSheet("");
        m_btnDoctor->setStyleSheet("");
    });

    // 管理科室按钮
    connect(m_btnDept, &QPushButton::clicked, this, [=]() {
        m_stackWidget->setCurrentWidget(m_deptWidget);
        // 可选：按钮选中态
        m_btnDept->setStyleSheet("background-color: #409EFF; color: white;");
        m_btnPatient->setStyleSheet("");
        m_btnDoctor->setStyleSheet("");
    });

    // 管理医生按钮
    connect(m_btnDoctor, &QPushButton::clicked, this, [=]() {
        m_stackWidget->setCurrentWidget(m_docWidget);
        // 可选：按钮选中态
        m_btnDoctor->setStyleSheet("background-color: #409EFF; color: white;");
        m_btnPatient->setStyleSheet("");
        m_btnDept->setStyleSheet("");
    });

    // 默认选中“管理患者”界面
    m_stackWidget->setCurrentWidget(m_patientWidget);
    m_btnPatient->setStyleSheet("background-color: #409EFF; color: white;");
}

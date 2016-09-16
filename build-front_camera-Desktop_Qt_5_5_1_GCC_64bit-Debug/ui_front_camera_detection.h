/********************************************************************************
** Form generated from reading UI file 'front_camera_detection.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRONT_CAMERA_DETECTION_H
#define UI_FRONT_CAMERA_DETECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frontcamera_dlg
{
public:
    QGraphicsView *orgimage_view;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QRadioButton *rd_input_mode_img;
    QRadioButton *rd_input_mode_net;
    QRadioButton *rd_input_mode_loc;
    QRadioButton *rd_input_mode_usb;
    QPushButton *bt_start_stop;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *ck_savemode_org;
    QCheckBox *ck_savemode_out;
    QGraphicsView *outimage_view;
    QPushButton *bt_file_dialog;
    QFrame *line;
    QLineEdit *ed_image_source;
    QFrame *line_2;
    QGroupBox *traffic_signal;
    QLabel *label_3;
    QGraphicsView *signal_view;
    QGraphicsView *signal_color_view;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *ed_signal;
    QGroupBox *groupBox_3;
    QGraphicsView *sign_view;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QGroupBox *groupBox_4;
    QGraphicsView *pedestrian_view;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QLabel *label_7;
    QGroupBox *groupBox_5;
    QCheckBox *ck_mission_signal;
    QCheckBox *ck_mission_sign;
    QCheckBox *ck_mission_pedestrian;

    void setupUi(QWidget *frontcamera_dlg)
    {
        if (frontcamera_dlg->objectName().isEmpty())
            frontcamera_dlg->setObjectName(QStringLiteral("frontcamera_dlg"));
        frontcamera_dlg->resize(889, 829);
        orgimage_view = new QGraphicsView(frontcamera_dlg);
        orgimage_view->setObjectName(QStringLiteral("orgimage_view"));
        orgimage_view->setGeometry(QRect(40, 50, 554, 291));
        label = new QLabel(frontcamera_dlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 111, 17));
        label_2 = new QLabel(frontcamera_dlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 370, 111, 17));
        groupBox = new QGroupBox(frontcamera_dlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 700, 311, 61));
        rd_input_mode_img = new QRadioButton(groupBox);
        rd_input_mode_img->setObjectName(QStringLiteral("rd_input_mode_img"));
        rd_input_mode_img->setGeometry(QRect(240, 30, 117, 22));
        rd_input_mode_net = new QRadioButton(groupBox);
        rd_input_mode_net->setObjectName(QStringLiteral("rd_input_mode_net"));
        rd_input_mode_net->setGeometry(QRect(1, 31, 90, 22));
        rd_input_mode_net->setChecked(false);
        rd_input_mode_loc = new QRadioButton(groupBox);
        rd_input_mode_loc->setObjectName(QStringLiteral("rd_input_mode_loc"));
        rd_input_mode_loc->setGeometry(QRect(97, 31, 66, 22));
        rd_input_mode_usb = new QRadioButton(groupBox);
        rd_input_mode_usb->setObjectName(QStringLiteral("rd_input_mode_usb"));
        rd_input_mode_usb->setGeometry(QRect(169, 31, 58, 22));
        rd_input_mode_usb->setChecked(true);
        rd_input_mode_net->raise();
        rd_input_mode_loc->raise();
        rd_input_mode_usb->raise();
        rd_input_mode_img->raise();
        bt_start_stop = new QPushButton(frontcamera_dlg);
        bt_start_stop->setObjectName(QStringLiteral("bt_start_stop"));
        bt_start_stop->setGeometry(QRect(40, 780, 211, 41));
        groupBox_2 = new QGroupBox(frontcamera_dlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(410, 700, 221, 61));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 175, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        ck_savemode_org = new QCheckBox(layoutWidget);
        ck_savemode_org->setObjectName(QStringLiteral("ck_savemode_org"));
        ck_savemode_org->setChecked(true);

        horizontalLayout_2->addWidget(ck_savemode_org);

        ck_savemode_out = new QCheckBox(layoutWidget);
        ck_savemode_out->setObjectName(QStringLiteral("ck_savemode_out"));
        ck_savemode_out->setChecked(true);

        horizontalLayout_2->addWidget(ck_savemode_out);

        outimage_view = new QGraphicsView(frontcamera_dlg);
        outimage_view->setObjectName(QStringLiteral("outimage_view"));
        outimage_view->setGeometry(QRect(40, 400, 554, 291));
        bt_file_dialog = new QPushButton(frontcamera_dlg);
        bt_file_dialog->setObjectName(QStringLiteral("bt_file_dialog"));
        bt_file_dialog->setGeometry(QRect(380, 780, 211, 41));
        line = new QFrame(frontcamera_dlg);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 760, 1031, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        ed_image_source = new QLineEdit(frontcamera_dlg);
        ed_image_source->setObjectName(QStringLiteral("ed_image_source"));
        ed_image_source->setGeometry(QRect(420, 20, 171, 27));
        ed_image_source->setReadOnly(true);
        line_2 = new QFrame(frontcamera_dlg);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(610, 20, 20, 721));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        traffic_signal = new QGroupBox(frontcamera_dlg);
        traffic_signal->setObjectName(QStringLiteral("traffic_signal"));
        traffic_signal->setGeometry(QRect(630, 20, 291, 201));
        label_3 = new QLabel(traffic_signal);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 30, 131, 17));
        signal_view = new QGraphicsView(traffic_signal);
        signal_view->setObjectName(QStringLiteral("signal_view"));
        signal_view->setGeometry(QRect(10, 60, 161, 51));
        signal_color_view = new QGraphicsView(traffic_signal);
        signal_color_view->setObjectName(QStringLiteral("signal_color_view"));
        signal_color_view->setGeometry(QRect(10, 150, 41, 41));
        widget = new QWidget(traffic_signal);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 120, 195, 29));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        ed_signal = new QLineEdit(widget);
        ed_signal->setObjectName(QStringLiteral("ed_signal"));
        ed_signal->setReadOnly(true);

        horizontalLayout->addWidget(ed_signal);

        groupBox_3 = new QGroupBox(frontcamera_dlg);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(630, 230, 221, 161));
        sign_view = new QGraphicsView(groupBox_3);
        sign_view->setObjectName(QStringLiteral("sign_view"));
        sign_view->setGeometry(QRect(10, 60, 101, 81));
        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 60, 81, 27));
        lineEdit_2->setReadOnly(true);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 131, 17));
        groupBox_4 = new QGroupBox(frontcamera_dlg);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(630, 390, 261, 291));
        pedestrian_view = new QGraphicsView(groupBox_4);
        pedestrian_view->setObjectName(QStringLiteral("pedestrian_view"));
        pedestrian_view->setGeometry(QRect(10, 60, 121, 221));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 30, 131, 17));
        lineEdit_3 = new QLineEdit(groupBox_4);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(140, 80, 113, 27));
        lineEdit_3->setReadOnly(true);
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(140, 50, 61, 17));
        groupBox_5 = new QGroupBox(frontcamera_dlg);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(640, 690, 251, 71));
        ck_mission_signal = new QCheckBox(groupBox_5);
        ck_mission_signal->setObjectName(QStringLiteral("ck_mission_signal"));
        ck_mission_signal->setGeometry(QRect(0, 20, 121, 22));
        ck_mission_sign = new QCheckBox(groupBox_5);
        ck_mission_sign->setObjectName(QStringLiteral("ck_mission_sign"));
        ck_mission_sign->setGeometry(QRect(120, 20, 111, 22));
        ck_mission_pedestrian = new QCheckBox(groupBox_5);
        ck_mission_pedestrian->setObjectName(QStringLiteral("ck_mission_pedestrian"));
        ck_mission_pedestrian->setGeometry(QRect(0, 40, 101, 22));

        retranslateUi(frontcamera_dlg);

        QMetaObject::connectSlotsByName(frontcamera_dlg);
    } // setupUi

    void retranslateUi(QWidget *frontcamera_dlg)
    {
        frontcamera_dlg->setWindowTitle(QApplication::translate("frontcamera_dlg", "Front Camera", 0));
        label->setText(QApplication::translate("frontcamera_dlg", "Original Image", 0));
        label_2->setText(QApplication::translate("frontcamera_dlg", "Output Image", 0));
        groupBox->setTitle(QApplication::translate("frontcamera_dlg", "image input mode", 0));
        rd_input_mode_img->setText(QApplication::translate("frontcamera_dlg", "Image", 0));
        rd_input_mode_net->setText(QApplication::translate("frontcamera_dlg", "Network", 0));
        rd_input_mode_loc->setText(QApplication::translate("frontcamera_dlg", "Local", 0));
        rd_input_mode_usb->setText(QApplication::translate("frontcamera_dlg", "USB", 0));
        bt_start_stop->setText(QApplication::translate("frontcamera_dlg", "Start Button", 0));
        groupBox_2->setTitle(QApplication::translate("frontcamera_dlg", "Save Mode", 0));
        ck_savemode_org->setText(QApplication::translate("frontcamera_dlg", "Original", 0));
        ck_savemode_out->setText(QApplication::translate("frontcamera_dlg", "Output", 0));
        bt_file_dialog->setText(QApplication::translate("frontcamera_dlg", "File Dialog", 0));
        traffic_signal->setTitle(QApplication::translate("frontcamera_dlg", "Traffic Signal", 0));
        label_3->setText(QApplication::translate("frontcamera_dlg", "Traffic Signal ROI", 0));
        label_4->setText(QApplication::translate("frontcamera_dlg", "Signal", 0));
        groupBox_3->setTitle(QApplication::translate("frontcamera_dlg", "Traffic Sign", 0));
        label_5->setText(QApplication::translate("frontcamera_dlg", "Traffic Sign ROI", 0));
        groupBox_4->setTitle(QApplication::translate("frontcamera_dlg", "Pedestrian", 0));
        label_6->setText(QApplication::translate("frontcamera_dlg", "Pedestrain ROI", 0));
        label_7->setText(QApplication::translate("frontcamera_dlg", "Position", 0));
        groupBox_5->setTitle(QApplication::translate("frontcamera_dlg", "Mission", 0));
        ck_mission_signal->setText(QApplication::translate("frontcamera_dlg", "Traffic Signal", 0));
        ck_mission_sign->setText(QApplication::translate("frontcamera_dlg", "Traffic Sign", 0));
        ck_mission_pedestrian->setText(QApplication::translate("frontcamera_dlg", "Pedestrian", 0));
    } // retranslateUi

};

namespace Ui {
    class frontcamera_dlg: public Ui_frontcamera_dlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRONT_CAMERA_DETECTION_H

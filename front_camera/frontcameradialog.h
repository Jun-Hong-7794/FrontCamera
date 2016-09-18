#ifndef FRONTCAMERADIALOG
#define FRONTCAMERADIALOG

/////////////////////////////////////////////////
///////////////////Qt Lib////////////////////////
#include <QtWidgets>
#include <QThread>

/////////////////////////////////////////////////
///////////////////Basic////////////////////////
#include <stdio.h>

/////////////////////////////////////////////////
///////////////////OpenCv////////////////////////
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>

/////////////////////////////////////////////////
///////////////////CNetImg///////////////////////
#include"CNetImg/CNetImg.h"

/////////////////////////////////////////////////
///////////////////Dialog////////////////////////
#include "classification.hpp"
#include "ui_front_camera_detection.h"


/////////////////////////////////////////////////
///////////////////Image Thread//////////////////
#include "CImage_Thread/CImage_Thread.h"

/////////////////////////////////////////////////
///////////////////Mission////////////////////////
#include "CMission/CMission.h"

/////////////////////////////////////////////////
///////////////////LCM////////////////////////
#include "CLCM/CLCM.h"


class CImage_Thread : public QThread{
    Q_OBJECT
public:
    CImage_Thread();

private://Dialog
    bool fl_Image_mode;
    bool fl_stream;
    bool fl_segment_end;

    unsigned int m_capture_mode;
    unsigned int m_save_mode;

    QString m_avi_path;
    QString m_img_path;
    QString m_lcm_log_path;

public://Dialog
    void Set_Segment_Flag(bool);

private://LCM
    CLCM m_log_play_lcm;

private://OpenCv
    cv::Mat m_orgimg;
    cv::Mat m_outimg;

    cv::VideoCapture *mp_video;
    cv::VideoCapture m_cam;
public://OpenCv
    void Image_Capture(cv::Mat&);
    void Image_Capture_Close();

private:
    CNetImg m_net_image;

signals:
    void Get_Image(cv::Mat);

public slots:
    void Set_Image_Capture_Mode(unsigned int _cap_mode,
                                unsigned int _save_mode,
                                QString _path);

public:
    void Start_Img_Thread();
    void Stop_Img_Thread();

protected:
    void run();
};


class FRONT_CAMERA : public QDialog, public Ui::frontcamera_dlg
{
    Q_OBJECT

public:
    FRONT_CAMERA(QWidget *parent = 0);
    ~FRONT_CAMERA();


private://Dialog
    bool fl_stream;
    CImage_Thread *mp_img_thread;

//    QImage m_org_qimg;
//    QPixmap m_org_qpix;
    QGraphicsScene *mp_org_qgraphic;

//    QImage m_out_qimg;
//    QPixmap m_out_qpix;
    QGraphicsScene *mp_out_qgraphic;

//    QImage m_mission_qimg_signal;
//    QPixmap m_mission_qpix_signal;
    QGraphicsScene *mp_mission_qgraphic_signal;
    QGraphicsScene *mp_mission_qgraphic_signal_color;

//    QImage m_mission_qimg_sign;
//    QPixmap m_mission_qpix_sign;
    QGraphicsScene *mp_mission_qgraphic_sign;

//    QImage m_mission_qimg_pedestrian;
//    QPixmap m_mission_qpix_pedestrian;
    QGraphicsScene *mp_mission_qgraphic_pedestrian;

    int m_view_width;
    int m_view_height;

    unsigned int m_capture_mode;
    unsigned int m_save_mode;
private:
    QString m_str_avi_path;
    QString m_str_img_path;
    QString m_str_lcm_log_path;

private://Opencv
    cv::Mat m_orgimg;
    cv::Mat m_outimg;
    cv::Mat m_segment_img;

private:
    CLabel m_clabel;
    CMission m_cmission;

private://Caffe
    Classifier_segnet *mp_segnet;

    string m_model_file;
    string m_weight_file;

private slots:
    void Click_Start_Button();
    void File_Dialog();

public slots:
    void Set_Image(cv::Mat);
public:
    void Mission();
public:
    cv::Mat Image_Segment(cv::Mat);
    void Display_Image(cv::Mat,QGraphicsScene*,QGraphicsView*);
    QImage Mat2QImage(cv::Mat src);

signals:
    void Get_Image_Capture_Mode(unsigned int _cap_mode,
                                unsigned int _save_mode,
                                QString _path);
};



#endif // FRONTCAMERADIALOG


#include "frontcameradialog.h"

//////////////////////////Image Thread/////////////////////////////////////////
 CImage_Thread::CImage_Thread(){

     fl_stream = false;
     fl_Image_mode = false;

     m_capture_mode = 0;
     m_save_mode = 0;

 }

 void CImage_Thread::Image_Capture(cv::Mat &_img){

     if(m_capture_mode == 1){
//        (*mp_video) >> _img;
         //cv::waitKey(80);

     }

     if(m_capture_mode == 2){
        (*mp_video) >> _img;
         //cv::waitKey(80);
     }

     if(m_capture_mode == 3){
        m_cam >> _img;
     }

     if(m_capture_mode == 4){
         std::string current_locale_text = m_img_path.toLocal8Bit().constData();
        _img = cv::imread(current_locale_text);
     }
     if(m_capture_mode == 5){
         m_log_play_lcm.LCM_Log_Subscribe(m_lcm_log_path,_img);
     }

 }

void CImage_Thread::Set_Image_Capture_Mode(unsigned int _capture_mode,unsigned int _save_mode, QString _path){

    m_capture_mode = _capture_mode;

    m_save_mode = _save_mode;

    if((_capture_mode == 2))
        m_avi_path = _path;

    else if((_capture_mode == 4))
        m_img_path = _path;

    else if((_capture_mode == 5))
        m_lcm_log_path = _path;

    else{
        m_img_path = "Not Selected";
        m_avi_path = "Not Selected";
        m_lcm_log_path = "Not Selected";
    }

}

void CImage_Thread::Start_Img_Thread(){
    fl_stream = true;

    if(m_capture_mode == 1){
        mp_client = new CClient;
        mp_client->socket_init((char *)"192.168.3.6",1234,(char *)"192.168.3.5",1234);
    }
    if(m_capture_mode == 2){
        std::string current_locale_text = m_avi_path.toLocal8Bit().constData();
        mp_video = new cv::VideoCapture(current_locale_text);
    }
    if(m_capture_mode == 3){
        m_cam.open(0);
    }

    if(m_capture_mode == 4){
        //m_cam.open(0);
    }


    if((m_save_mode & 0x01)){

    }
    if((m_save_mode & 0x10)){

    }
}

void CImage_Thread::Stop_Img_Thread(){

    if(m_capture_mode == 1){
        if(mp_client != 0){
            delete mp_client;
            mp_client = 0;
        }
    }
    if(m_capture_mode == 2){
        if(mp_video == 0){
            delete mp_video;
            mp_video = 0;
        }
    }
    if(m_capture_mode == 3){
        m_cam.release();
    }


    if((m_save_mode & 0x01)){

    }
    if((m_save_mode & 0x10)){

    }

    fl_stream = false;
}

void CImage_Thread::Set_Segment_Flag(bool _tmp){
    fl_segment_end = _tmp;
}

void CImage_Thread::run(){
    while(fl_stream){

        Image_Capture(m_orgimg);
        if(fl_segment_end){
            Set_Segment_Flag(false);

            emit Get_Image(m_orgimg);

            if((m_capture_mode == 4))
                break;
        }
        else
            continue;
    }
}


//////////////////////////Front Camera/////////////////////////////////////////

FRONT_CAMERA::~FRONT_CAMERA(){
    mp_img_thread->Stop_Img_Thread();
}

FRONT_CAMERA::FRONT_CAMERA(QWidget *parent)
    :QDialog(parent){

    setupUi(this);
    qRegisterMetaType<QString>("QString");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    fl_stream = false;
    mp_segnet = 0;

    m_save_mode = 0;
    m_capture_mode = 0;

    m_model_file = "/home/jun/caffe-segnet/examples/segnet/segnet_inference_input.prototxt";
    m_weight_file = "/home/jun/caffe-segnet/examples/segnet/Inference/test_weights_front_camera.caffemodel";

    m_str_avi_path = " ";
    m_str_img_path = " ";

    mp_segnet = new Classifier_segnet(m_model_file,m_weight_file);

    mp_img_thread = new CImage_Thread;

    m_view_width = orgimage_view->geometry().width();
    m_view_height = orgimage_view->geometry().height();

    mp_org_qgraphic = new QGraphicsScene(QRectF(0, 0, m_view_width, m_view_height), 0);
    mp_out_qgraphic = new QGraphicsScene(QRectF(0, 0, m_view_width, m_view_height), 0);

    mp_mission_qgraphic_signal = new QGraphicsScene(
                QRectF(0, 0, signal_view->geometry().width(), signal_view->geometry().height()), 0);
    mp_mission_qgraphic_signal_color = new QGraphicsScene(
                QRectF(0, 0, signal_color_view->geometry().width(), signal_color_view->geometry().height()), 0);
    mp_mission_qgraphic_sign = new QGraphicsScene(
                QRectF(0, 0, sign_view->geometry().width(), sign_view->geometry().height()), 0);
    mp_mission_qgraphic_pedestrian = new QGraphicsScene(
                QRectF(0, 0, pedestrian_view->geometry().width(), pedestrian_view->geometry().height()), 0);

    connect(bt_start_stop,SIGNAL(clicked()),this,SLOT(Click_Start_Button()));
    connect(bt_file_dialog,SIGNAL(clicked()),this,SLOT(File_Dialog()));
    connect(this,SIGNAL(Get_Image_Capture_Mode(unsigned int,unsigned int,QString)),
            mp_img_thread,SLOT(Set_Image_Capture_Mode(unsigned int,unsigned int,QString)));
    connect(mp_img_thread,SIGNAL(Get_Image(cv::Mat)),this,SLOT(Set_Image(cv::Mat)),Qt::QueuedConnection);

}

void FRONT_CAMERA::Click_Start_Button(){

    if(!fl_stream){//Qt Thread Start!

        if(rd_input_mode_net->isChecked()){
            m_capture_mode = 1;
            ed_image_source->setText("Image From Network");
        }
        if(rd_input_mode_loc->isChecked()){
            m_capture_mode = 2;
            ed_image_source->setText("Image From Avi");
        }
        if(rd_input_mode_usb->isChecked()){
            m_capture_mode = 3;
            ed_image_source->setText("Image From Webcam");
        }
        if(rd_input_mode_img->isChecked()){
            m_capture_mode = 4;
            ed_image_source->setText("Image From image");
        }

        if(rd_input_mode_lcm_log_play->isChecked()){
            m_capture_mode = 5;
            ed_image_source->setText("Image From LCM Log");
        }

        if(ck_savemode_org->isChecked()){
            m_save_mode |= 0x01;
        }
        if(ck_savemode_out->isChecked()){
            m_save_mode |= 0x10;
        }

        if(m_capture_mode == 2){

            if(m_str_avi_path == " "){
                QMessageBox::information(this, tr("Avi Load Warning"), tr("Cannot load Avi File"));
                return;
            }
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, m_str_avi_path);
        }
        else if(m_capture_mode == 4){

            if(m_str_img_path == " "){
                QMessageBox::information(this, tr("Image Load Warning"), tr("Cannot load Image File"));
                return;
            }
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, m_str_img_path);

            mp_img_thread->Start_Img_Thread();
            mp_img_thread->start();

            return;
        }
        else if (m_capture_mode == 5){
            if(m_str_lcm_log_path == " "){
                QMessageBox::information(this, tr("LCM Log Load Warning"), tr("Cannot load LCM log File"));
                return;
            }
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, m_str_lcm_log_path);
        }

        else{
            QString tmp_str = "Not Selected";
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, tmp_str);
        }

        bt_start_stop->setText("Stop Button");
        fl_stream = true;

        mp_img_thread->Start_Img_Thread();
        mp_img_thread->start();

        rd_input_mode_net->setEnabled(false);
        rd_input_mode_loc->setEnabled(false);
        rd_input_mode_usb->setEnabled(false);
        rd_input_mode_img->setEnabled(false);

        ck_savemode_org->setEnabled(false);
        ck_savemode_out->setEnabled(false);

        bt_file_dialog->setEnabled(false);
    }
    else{//Stop Qt Thread

        bt_start_stop->setText("Start Button");
        fl_stream = false;

        m_save_mode = 0;

        mp_img_thread->Stop_Img_Thread();

        rd_input_mode_net->setEnabled(true);
        rd_input_mode_loc->setEnabled(true);
        rd_input_mode_usb->setEnabled(true);
        rd_input_mode_img->setEnabled(true);

        ck_savemode_org->setEnabled(true);
        ck_savemode_out->setEnabled(true);

        bt_file_dialog->setEnabled(true);
        sleep(1);
    }

    return;
}

void FRONT_CAMERA::Set_Image(cv::Mat _img){

    if(_img.rows == 0 || _img.cols == 0){
        mp_img_thread->Set_Segment_Flag(true);
        return;
    }
    m_orgimg = _img;
    cv::Size tmp_org_size;

    tmp_org_size.width = _img.cols;
    tmp_org_size.height = _img.rows;

    Display_Image(_img,mp_org_qgraphic, orgimage_view);
    m_segment_img = Image_Segment(_img);
    cv::resize(m_segment_img,m_segment_img,tmp_org_size);
    Display_Image(m_segment_img,mp_out_qgraphic,outimage_view);

    Mission();

    mp_img_thread->Set_Segment_Flag(true);

    cv::waitKey(80);
}

void FRONT_CAMERA::Mission(){

    if(ck_mission_signal->isChecked()){
        cv::Mat crop_rst;
        cv::Mat crop_signal;
        int signal_num = -1;

        m_cmission.Mission_Traffic_signal(m_orgimg,m_segment_img,signal_num,crop_rst,crop_signal);

        if(signal_num == 0)
            ed_signal->setText("Red");
        else if(signal_num == 1)
            ed_signal->setText("Yellow");
        else if(signal_num == 2)
            ed_signal->setText("Green(Left)");
        else if(signal_num == 3)
            ed_signal->setText("Green");
        else
            ed_signal->setText("Can not Find");

        Display_Image(crop_rst,mp_mission_qgraphic_signal,signal_view);
        Display_Image(crop_signal,mp_mission_qgraphic_signal_color,signal_color_view);
    }

    if(ck_mission_sign->isChecked()){
        cv::Mat crop_sign;
        int rst = 0;

        m_cmission.Mission_Traffic_sign(m_orgimg,m_segment_img,rst,crop_sign);

        Display_Image(crop_sign,mp_mission_qgraphic_sign,sign_view);
    }

    if(ck_mission_pedestrian->isChecked()){
        cv::Mat crop_pedestrian;
        int rst = 0;

        m_cmission.Mission_Pedestrian(m_orgimg,m_segment_img,rst,crop_pedestrian);

        Display_Image(crop_pedestrian,mp_mission_qgraphic_pedestrian,pedestrian_view);
    }

    //cv::imshow("Segment Image", m_segment_img);
    return;
}

cv::Mat FRONT_CAMERA::Image_Segment(cv::Mat _img){

    cv::Mat tmp_resize;
    cv::Size tmp_segnet_input_size;

    tmp_segnet_input_size.width = 480;
    tmp_segnet_input_size.height = 360;

    cv::resize(_img,tmp_resize,tmp_segnet_input_size);

    return mp_segnet->Classify(tmp_resize);
}

void FRONT_CAMERA::Display_Image(cv::Mat _img, QGraphicsScene* _graphics_scene,QGraphicsView * _graphics_view){

    if(_img.rows <= 1 || _img.cols <= 1)
        return;

    cv::resize(_img,_img,cv::Size(),0.5,0.5);

    QImage tmp_qimg;
    QPixmap tmp_qpix;

    tmp_qimg = this->Mat2QImage(_img);
    tmp_qpix.convertFromImage(tmp_qimg);

    _graphics_scene->clear();
    //_graphics_scene = new QGraphicsScene(QRectF(0, 0, width, height), 0);
    _graphics_scene->addPixmap(tmp_qpix.scaled(QSize(
                        (int)_graphics_scene->width(), (int)_graphics_scene->height()),
                        Qt::KeepAspectRatio, Qt::SmoothTransformation));

    _graphics_view->fitInView(
                QRectF(0, 0, _graphics_view->geometry().width(), _graphics_view->geometry().height()),
                    Qt::KeepAspectRatio);

    _graphics_view->setScene(_graphics_scene);
    _graphics_view->show();

    //delete _graphics_scene;
}

QImage FRONT_CAMERA::Mat2QImage(cv::Mat src)
{
    cv::Mat temp; // make the same cv::Mat
    cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}

void FRONT_CAMERA::File_Dialog(){

    QFileDialog dialog(this);
    QStringList fileName;
    if(rd_input_mode_loc->isChecked() || rd_input_mode_img->isChecked())
        dialog.setFileMode(QFileDialog::AnyFile);
    else if(rd_input_mode_lcm_log_play->isChecked())
        dialog.setFileMode(QFileDialog::DirectoryOnly);
    else
        return;

    dialog.setOption(QFileDialog::ShowDirsOnly);
    //dialog.show();
    if(dialog.exec())
        fileName = dialog.selectedFiles();
    else
        return;

    if(rd_input_mode_loc->isChecked())
        m_str_avi_path = fileName[0];
    else if(rd_input_mode_img->isChecked())
        m_str_img_path = fileName[0];
    else if(rd_input_mode_lcm_log_play->isChecked())
        m_str_lcm_log_path = fileName[0];

    fileName[0];
    return;
}

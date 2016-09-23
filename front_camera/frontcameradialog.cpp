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
         m_net_image.Image_From_Net(_img);
     }

     if(m_capture_mode == 2){
        (*mp_video) >> _img;
         //cv::waitKey(80);
        QThread::msleep(80);
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
        if(!m_net_image.Socket_Init((char *)"192.168.3.6",1234)){
            std::cout << "m_net_image Init Fail!" << std::endl;
            fl_stream = false;
        }
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
        m_net_image.Socket_Close();
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

            msleep(5);
        }
        else{
            msleep(5);
            continue;
        }
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
    m_fps_current_time = 0.0;
    m_fps_previous_time = 0.0;

    m_start_ticks = 0;
    m_end_ticks = 0;
    m_delta_ticks = 0;
    m_elapsed_ticks = 0;
    m_frame_count = 0;

    m_frame_rate = 0.0;

    m_model_file  = "/home/jun/Workspace/Learning_Model_Weight/2016-09-20/segnet_inference_input.prototxt";
    m_weight_file = "/home/jun/Workspace/Learning_Model_Weight/2016-09-20/test_weights.caffemodel";

    m_str_avi_path = " ";
    m_str_img_path = " ";
    m_str_lcm_log_path = " ";

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
    mp_mission_qgraphic_dummy_car = new QGraphicsScene(
                QRectF(0, 0, dummy_car_view->geometry().width(), dummy_car_view->geometry().height()), 0);
    mp_mission_qgraphic_normal_car= new QGraphicsScene(
                QRectF(0, 0, normal_car_view->geometry().width(), normal_car_view->geometry().height()), 0);

    ed_fps->setText("0");

    connect(bt_start_stop,SIGNAL(clicked()),this,SLOT(Click_Start_Button()));
    connect(bt_lcm_data_send,SIGNAL(clicked()),this,SLOT(Click_LCM_Data_Send()));
    connect(bt_file_dialog,SIGNAL(clicked()),this,SLOT(File_Dialog()));
    connect(this,SIGNAL(Get_Image_Capture_Mode(unsigned int,unsigned int,QString)),
            mp_img_thread,SLOT(Set_Image_Capture_Mode(unsigned int,unsigned int,QString)));
    connect(mp_img_thread,SIGNAL(Get_Image(cv::Mat)),this,SLOT(Set_Image(cv::Mat)),Qt::QueuedConnection);

}

double clockToMillisecnods(clock_t _ticks){

    return (_ticks/(double)CLOCKS_PER_SEC)*1000.0;
}

void FRONT_CAMERA::fps_start(){

    m_start_ticks = clock();
}

double FRONT_CAMERA::fps_end(){

    m_end_ticks = clock();

    m_delta_ticks = m_end_ticks - m_start_ticks;
    m_elapsed_ticks += m_delta_ticks;
    m_frame_count++;

    if(clockToMillisecnods(m_elapsed_ticks) > 1000.0){

        m_frame_rate = (double)m_frame_count*0.5 + m_frame_rate*0.5;

        m_frame_count = 0;
        m_elapsed_ticks = 0;
    }

    return m_frame_rate;
}

void FRONT_CAMERA::Click_Start_Button(){

    if(!fl_stream){//Qt Thread Start!

        if(rd_input_mode_net->isChecked()){
            m_capture_mode = 1;

            ed_image_source->setText("Image From Network");
            mp_img_thread->Set_Segment_Flag(true);
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, " " );
        }
        if(rd_input_mode_loc->isChecked()){
            m_capture_mode = 2;

            if(m_str_avi_path == " "){
                QMessageBox::information(this, tr("Avi Load Warning"), tr("Cannot load Avi File"));
                return;
            }

            ed_image_source->setText("Image From Avi");
            mp_img_thread->Set_Segment_Flag(true);
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, m_str_avi_path);
        }
        if(rd_input_mode_usb->isChecked()){
            m_capture_mode = 3;

            ed_image_source->setText("Image From Webcam");
            mp_img_thread->Set_Segment_Flag(true);
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, " " );
        }
        if(rd_input_mode_img->isChecked()){
            m_capture_mode = 4;

            if(m_str_img_path == " "){
                QMessageBox::information(this, tr("Image Load Warning"), tr("Cannot load Image File"));
                return;
            }

            ed_image_source->setText("Image From image");


            mp_img_thread->Set_Segment_Flag(true);
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, m_str_img_path);
            mp_img_thread->Start_Img_Thread();
            mp_img_thread->start();

            return;
        }
        if(rd_input_mode_lcm_log_play->isChecked()){
            m_capture_mode = 5;

            if(m_str_lcm_log_path == " "){
                QMessageBox::information(this, tr("LCM Log Load Warning"), tr("Cannot load LCM log File"));
                return;
            }

            ed_image_source->setText("Image From LCM Log");
            mp_img_thread->Set_Segment_Flag(true);
            emit Get_Image_Capture_Mode(m_capture_mode, m_save_mode, m_str_lcm_log_path);
        }


        if(ck_savemode_org->isChecked()){
            m_save_mode |= 0x000001;
            m_save_org_image.Save_Folder_Init("org",IMG_TYPE_ORIGINAL);
        }
        if(ck_savemode_out->isChecked()){
            m_save_mode |= 0x000010;
            m_save_seg_image.Save_Folder_Init("seg",IMG_TYPE_SEGMENT);
        }
        if(ck_traffic_img_log->isChecked()){
            m_save_mode |= 0x000100;
            m_save_trf_image.Save_Folder_Init("trf",IMG_TYPE_TRAFFIC_SIGNAL);
        }
        if(ck_sign_img_log->isChecked()){
            m_save_mode |= 0x001000;
            m_save_sig_image.Save_Folder_Init("sig",IMG_TYPE_SIGN);
        }
        if(ck_pedestrian_img_log->isChecked()){
            m_save_mode |= 0x010000;
            m_save_ped_image.Save_Folder_Init("ped",IMG_TYPE_PEDESTRIAN);
        }

        bt_start_stop->setText("Stop Button");
        fl_stream = true;

        mp_img_thread->Start_Img_Thread();
        mp_img_thread->start();

        rd_input_mode_net->setEnabled(false);
        rd_input_mode_loc->setEnabled(false);
        rd_input_mode_usb->setEnabled(false);
        rd_input_mode_img->setEnabled(false);
        rd_input_mode_lcm_log_play->setEnabled(false);

        ck_savemode_org->setEnabled(false);
        ck_savemode_out->setEnabled(false);

        ck_traffic_img_log->setEnabled(false);
        ck_sign_img_log->setEnabled(false);
        ck_pedestrian_img_log->setEnabled(false);

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
        rd_input_mode_lcm_log_play->setEnabled(true);

        ck_savemode_org->setEnabled(true);
        ck_savemode_out->setEnabled(true);

        ck_traffic_img_log->setEnabled(true);
        ck_sign_img_log->setEnabled(true);
        ck_pedestrian_img_log->setEnabled(true);

        bt_file_dialog->setEnabled(true);

        if(ck_savemode_org->isChecked()){
            m_save_org_image.Close_Folder();
        }
        if(ck_savemode_out->isChecked()){
            m_save_seg_image.Close_Folder();
        }
        if(ck_traffic_img_log->isChecked()){
            m_save_trf_image.Close_Folder();
        }
        if(ck_sign_img_log->isChecked()){
            m_save_sig_image.Close_Folder();
        }
        if(ck_pedestrian_img_log->isChecked()){
            m_save_ped_image.Close_Folder();
        }

        ed_fps->setText("0");

        sleep(1);
    }

    return;
}

void FRONT_CAMERA::Click_LCM_Data_Send(){

    m_front_cam_data.car_distance += 0.1;

    if(m_front_cam_data.fl_car == 0)
        m_front_cam_data.fl_car = 1;
    else
        m_front_cam_data.fl_car = 0;

    if(m_front_cam_data.fl_pedestrian == 0)
        m_front_cam_data.fl_pedestrian = 1;
    else
        m_front_cam_data.fl_pedestrian = 0;

    m_front_cam_data.sign += 1;

    if(m_front_cam_data.sign > 5)
        m_front_cam_data.sign = 1;

    m_front_cam_data.traffic_signal += 1;

    if(m_front_cam_data.traffic_signal > 5)
        m_front_cam_data.traffic_signal = 1;


    m_front_cam_data.timestamp += 10;

    m_front_cam_lcm.LCM_Publish(m_front_cam_data);
}

void FRONT_CAMERA::Set_Image(cv::Mat _img){

    if(_img.rows == 0 || _img.cols == 0){
        mp_img_thread->Set_Segment_Flag(true);
        return;
    }

    fps_start();

    m_orgimg = _img;
    cv::Size tmp_org_size;

    tmp_org_size.width = _img.cols;
    tmp_org_size.height = _img.rows;

    Display_Image(_img,mp_org_qgraphic, orgimage_view);
    m_segment_img = Image_Segment(_img);
    cv::resize(m_segment_img,m_segment_img,tmp_org_size);
    Display_Image(m_segment_img,mp_out_qgraphic,outimage_view);

    Mission();

    Save_Image();

    mp_img_thread->Set_Segment_Flag(true);

    cv::waitKey(10);

    ed_fps->setText(QString::number(fps_end()));
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
            ed_signal->setText("Not Detected");

        if(signal_num == -1){
            Display_Image(crop_rst,mp_mission_qgraphic_signal,signal_view,true);
            Display_Image(crop_signal,mp_mission_qgraphic_signal_color,signal_color_view,true);
        }
        else{
            ed_signal_ratio->setText(QString::number(((double)crop_rst.rows / (double)crop_rst.cols)));
            Display_Image(crop_rst,mp_mission_qgraphic_signal,signal_view);
            Display_Image(crop_signal,mp_mission_qgraphic_signal_color,signal_color_view);
        }

        if(ck_traffic_img_log->isChecked()){
            m_save_trf_image.Save_Image(crop_rst);
        }
    }

    if(ck_mission_sign->isChecked()){
        cv::Mat crop_sign;
        int rst = 0;
        float rst_prob = 0.0;
        QString str_rst = "";

        m_cmission.Mission_Traffic_sign(m_orgimg, m_segment_img,
                                        rst, rst_prob, crop_sign, ck_sign_img_log->isChecked(), &m_save_sig_image);

        if(rst == 0) str_rst = "Unknown";
        else if(rst == 1) str_rst = "P1";
        else if(rst == 2) str_rst = "P2";
        else if(rst == 3) str_rst = "P3";
        else if(rst == 4) str_rst = "P4";
        else if(rst == 5) str_rst = "Stop Sign";
        else if(rst == -1) str_rst = "Not Detected";
        else str_rst = "Unknown";

        if(rst == -1)
            Display_Image(crop_sign,mp_mission_qgraphic_sign,sign_view,true);
        else{
            ed_sign_ratio->setText(QString::number(((double)crop_sign.rows / (double)crop_sign.cols)));
            Display_Image(crop_sign,mp_mission_qgraphic_sign,sign_view);
        }
        ed_traffic_sign->setText(str_rst);
        ed_traffic_sign_prob->setText(QString::number(rst_prob));
    }

    if(ck_mission_pedestrian->isChecked()){
        cv::Mat crop_pedestrian;
        int rst = 0;

        m_cmission.Mission_Pedestrian(m_orgimg,m_segment_img,rst,crop_pedestrian);

        Display_Image(crop_pedestrian,mp_mission_qgraphic_pedestrian,pedestrian_view);

        if(ck_pedestrian_img_log->isChecked()){
            m_save_ped_image.Save_Image(crop_pedestrian);
        }
    }

    if(ck_mission_dummy_car->isChecked()){
        cv::Mat crop_dummy_car;
        int rst = 0;

        m_cmission.Mission_Dummy_Car(m_orgimg,m_segment_img,rst,crop_dummy_car);

        if(rst < 0){
            ed_dummy_car->setText("Not Detected");
            Display_Image(crop_dummy_car,mp_mission_qgraphic_dummy_car,dummy_car_view,true);
        }
        else{
            ed_dummy_car_ratio->setText(QString::number(((double)crop_dummy_car.rows / (double)crop_dummy_car.cols)));
            ed_dummy_car->setText("Dummy Car Detected");
            Display_Image(crop_dummy_car,mp_mission_qgraphic_dummy_car,dummy_car_view);
        }
//        if(ck_dummy_car_img_log->isChecked()){
//            m_save_ped_image.Save_Image(crop_dummy_car);
//        }
    }

    if(ck_mission_normal_car->isChecked()){
        cv::Mat crop_normal_car;
        int rst = 0;

        m_cmission.Mission_Normal_Car(m_orgimg,m_segment_img,rst,crop_normal_car);

        if(rst < 0){
            ed_normal_car->setText("Not Detected");
            Display_Image(crop_normal_car,mp_mission_qgraphic_normal_car,normal_car_view,true);
        }
        else{
            ed_normal_car_ratio->setText(QString::number(((double)crop_normal_car.rows / (double)crop_normal_car.cols)));
            ed_normal_car->setText("Normal Car Detected");
            Display_Image(crop_normal_car,mp_mission_qgraphic_normal_car,normal_car_view);
        }
//        if(ck_dummy_car_img_log->isChecked()){
//            m_save_ped_image.Save_Image(crop_dummy_car);
//        }
    }

    //cv::imshow("Segment Image", m_segment_img);
    return;
}

void FRONT_CAMERA::Save_Image(){
    if(m_save_mode && SAVE_MODE_ORIGINAL){
        m_save_org_image.Save_Image(m_orgimg);
    }
    if(m_save_mode && SAVE_MODE_SEGMENT){
        m_save_seg_image.Save_Image(m_segment_img);
    }
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

void FRONT_CAMERA::Display_Image(cv::Mat _img, QGraphicsScene* _graphics_scene,QGraphicsView * _graphics_view,bool _fl_clear){

    if(_fl_clear){
        _graphics_scene->clear();
        _graphics_view->viewport()->update();
        return;
    }
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

    return;
}

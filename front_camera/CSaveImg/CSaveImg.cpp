#include "CSaveImg.h"

CSaveImg::CSaveImg(){
    m_current_dir = QDir::currentPath().section("/",0,-2);
    m_current_dir += "/Save_Image";

    if(!m_qdir.mkdir(m_current_dir))
        std::cout << "Have made Save_Image Folder" << std::endl;

    m_folder_path = " ";

    m_file_index = 0;

    fl_time_stamp_option = false;
}

CSaveImg::~CSaveImg(){

}

QString CSaveImg::Current_Time_to_String(){

    QString date_and_time = "";

    date_and_time += QString::number(QDateTime::currentDateTime().date().year());
    date_and_time += "-";
    date_and_time += QString::number(QDateTime::currentDateTime().date().month());
    date_and_time += "-";
    date_and_time += QString::number(QDateTime::currentDateTime().date().day());
    date_and_time += "-";

    date_and_time += QString::number(QDateTime::currentDateTime().time().hour());
    date_and_time += "-";
    date_and_time += QString::number(QDateTime::currentDateTime().time().minute());
    date_and_time += "-";
    date_and_time += QString::number(QDateTime::currentDateTime().time().second());
    date_and_time += "-";
    date_and_time += QString::number(QDateTime::currentDateTime().time().msec());

    return date_and_time;
}


void CSaveImg::Save_Folder_Init(QString _folder_name, int _img_type, bool _using_time_stamp_name){

    if(_img_type == IMG_TYPE_ORIGINAL){
        m_folder_path = m_current_dir + "/Original_Image";// + _folder_name;
    }
    else if(_img_type == IMG_TYPE_SEGMENT){
        m_folder_path = m_current_dir + "/Segment_Image";// + _folder_name;
    }
    else if(_img_type == IMG_TYPE_TRAFFIC_SIGNAL){
        m_folder_path = m_current_dir + "/Traffic_Signal_Image";// + _folder_name;
    }
    else if(_img_type == IMG_TYPE_SIGN){
        m_folder_path = m_current_dir + "/Sign_Image";// + _folder_name;
    }
    else if(_img_type == IMG_TYPE_PEDESTRIAN){
        m_folder_path = m_current_dir + "/Pedestrian_Image";// + _folder_name;
    }
    else{
        m_folder_path = m_current_dir + "/Unknown_Type_Image";
        std::cout<<"Wrong Image Type!"<<std::endl;
    }

    if(!m_qdir.mkdir(m_folder_path))
        std::cout << "Have made Traffic_Signal_Image Folder" << std::endl;

    m_folder_path += ("/" + _folder_name + "_" + Current_Time_to_String());
    if(!m_qdir.mkdir(m_folder_path))
        std::cout << "Have made this folder"  << std::endl;


    fl_time_stamp_option = _using_time_stamp_name;
}

void CSaveImg::Save_Image(cv::Mat _img ,int _time_stamp){

    std::string current_locale_path;
    if(_time_stamp == 0){
        QString file_name = m_folder_path + "/" + QString::number(m_file_index) + ".jpg";
        current_locale_path = file_name.toLocal8Bit().constData();
        m_file_index++;
    }
    else{
        QString file_name = m_folder_path + "/" + QString::number(_time_stamp) + ".jpg";
        current_locale_path = file_name.toLocal8Bit().constData();
    }

    cv::imwrite(current_locale_path,_img);
}

void CSaveImg::Close_Folder(){
    m_folder_path = " ";

    m_file_index = 0;

    fl_time_stamp_option = false;
}


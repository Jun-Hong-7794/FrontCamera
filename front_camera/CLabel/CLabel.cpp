#include "CLabel.h"


cv::Rect CLabel::Image_Label(cv::Mat _img_org, int _label_class){

    int max_size_label_num = 0;
    int max_size_label = 0;//width * height

    cv::Mat org_img;
    cv::Mat bin_img;

    _img_org.copyTo(org_img);

    bin_img = Binary_Scale_Down(org_img, _label_class);

    if(bin_img.rows == 0 || bin_img.cols == 0)
        return cv::Rect();

    cv::cvtColor(bin_img,bin_img,cv::COLOR_BGR2GRAY);
    cv::Mat labels_img,states,centroids;
    cv::Mat kernel(3,3,CV_8UC1,cv::Scalar(255));

    cv::erode(bin_img,bin_img,kernel);
    cv::erode(bin_img,bin_img,kernel);

    int numOfLabels = cv::connectedComponentsWithStats(bin_img,labels_img,
                                                       states,centroids);

    if(numOfLabels == 0)
        return cv::Rect();

    for(int i = 1; i < numOfLabels;i++){

        int width = states.at<int>(i, cv::CC_STAT_WIDTH);
        int height = states.at<int>(i, cv::CC_STAT_HEIGHT);

        if(max_size_label < width*height){
            max_size_label = width*height;
            max_size_label_num = i;
        }
    }

//    cout<< "Biggest Label Number : " << max_size_label_num << endl;

//    int area = states.at<int>(max_size_label_num, cv::CC_STAT_AREA);
    int left = states.at<int>(max_size_label_num, cv::CC_STAT_LEFT);
    int top = states.at<int>(max_size_label_num, cv::CC_STAT_TOP);
    int width = states.at<int>(max_size_label_num, cv::CC_STAT_WIDTH);
    int height = states.at<int>(max_size_label_num, cv::CC_STAT_HEIGHT);
//    int max = states.at<int>(max_size_label_num, cv::CC_STAT_MAX);

//    cout<< "Area : " << area << endl;
//    cout<< "Left : " << left << endl;
//    cout<< "Top : " << top << endl;
//    cout<< "Width : " << width << endl;
//    cout<< "Height : " << height << endl;
//    cout<< "Max : " << max << endl << endl;


    return cv::Rect(left,top,width,height);
}

bool CLabel::Image_Label(cv::Mat _img_org, int _label_class,
                 cv::Rect *_rect_ary, int _max_label_num, int &_label_number,
                 int _label_max_size, int _label_min_size){

    cv::Mat org_img;
    cv::Mat bin_img;

    _img_org.copyTo(org_img);

    bin_img = Binary_Scale_Down(org_img, _label_class);

    if(bin_img.rows == 0 || bin_img.cols == 0)
        return false;

    cv::cvtColor(bin_img,bin_img,cv::COLOR_BGR2GRAY);
    cv::Mat labels_img,states,centroids;
    cv::Mat kernel(3,3,CV_8UC1,cv::Scalar(255));

    cv::erode(bin_img,bin_img,kernel);
    cv::erode(bin_img,bin_img,kernel);

    int numOfLabels = cv::connectedComponentsWithStats(bin_img,labels_img,
                                                       states,centroids);

    if(numOfLabels == 0)
        return false;

    int *label_sort = new int[numOfLabels];
    int *label_sort_zero = new int[numOfLabels-1];

    memset(label_sort, 0, sizeof(int) * numOfLabels);
    memset(label_sort_zero, 0, sizeof(int) * (numOfLabels-1));

    for(int i = 0; i < numOfLabels; i++)
        label_sort[i] = i;

    for(int i = 0; i < numOfLabels;i++){
        for(int j = i; j < numOfLabels;j++){

            int area_i = states.at<int>(label_sort[i], cv::CC_STAT_WIDTH) *
                    states.at<int>(label_sort[i], cv::CC_STAT_HEIGHT);
            int area_j = states.at<int>(label_sort[j], cv::CC_STAT_WIDTH) *
                    states.at<int>(label_sort[j], cv::CC_STAT_HEIGHT);

            if(area_i < area_j){
                int cur_i = label_sort[i];
                label_sort[i] = label_sort[j];
                label_sort[j] = cur_i;
            }
        }
    }

    std::memcpy(&label_sort_zero[0], &label_sort[1], sizeof(int) * (numOfLabels-1));

    int total_label_number = 0;
    int valide_label_number = 0;

    if(numOfLabels > _max_label_num)
        total_label_number = _max_label_num;
    else
        total_label_number = numOfLabels;

    for(int i = 0; i < total_label_number; i++){

        int area_i = states.at<int>(label_sort_zero[i], cv::CC_STAT_WIDTH) *
                states.at<int>(label_sort_zero[i], cv::CC_STAT_HEIGHT);

        if(area_i > _label_max_size || area_i < _label_min_size){
            _rect_ary[i].width  = 0;
            _rect_ary[i].height = 0;
            _rect_ary[i].x      = 0;
            _rect_ary[i].y      = 0;
            continue;
        }
        else{
            _rect_ary[i].width  = states.at<int>(label_sort_zero[i], cv::CC_STAT_WIDTH);
            _rect_ary[i].height = states.at<int>(label_sort_zero[i], cv::CC_STAT_HEIGHT);
            _rect_ary[i].x      = states.at<int>(label_sort_zero[i], cv::CC_STAT_LEFT);
            _rect_ary[i].y      = states.at<int>(label_sort_zero[i], cv::CC_STAT_TOP);
            valide_label_number++;
        }
    }

    delete[] label_sort;
    delete[] label_sort_zero;

    if(valide_label_number == 0)
        return false;
    else
        _label_number = valide_label_number;

    return true;
}

cv::Mat CLabel::Binary_Scale_Down(cv::Mat _img_org, unsigned int _label_class){

    unsigned char *img_data = (unsigned char*)_img_org.data;
    unsigned int pixel_data = 0x00000000;

    for(int i = 0; i < _img_org.rows; i++){
            for(int j = 0; j < _img_org.cols*3; j += 3){

                pixel_data = (unsigned int)(img_data[i*_img_org.cols*3 + j + 0])            //B
                           + (unsigned int)(img_data[i*_img_org.cols*3 + j + 1] <<  8)      //G
                           + (unsigned int)(img_data[i*_img_org.cols*3 + j + 2] << 16);     //R

                if(pixel_data == _label_class){
                    img_data[i*_img_org.cols*3 + j + 0] = 0xff;
                    img_data[i*_img_org.cols*3 + j + 1] = 0xff;
                    img_data[i*_img_org.cols*3 + j + 2] = 0xff;
                }
                else{
                    img_data[i*_img_org.cols*3 + j + 0] = 0x00;
                    img_data[i*_img_org.cols*3 + j + 1] = 0x00;
                    img_data[i*_img_org.cols*3 + j + 2] = 0x00;
                }

                pixel_data = 0x000000;
            }
    }

    return _img_org;
}

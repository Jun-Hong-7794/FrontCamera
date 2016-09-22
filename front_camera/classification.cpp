/*
 * classification.cpp
 *
 *  Created on: Jul 19, 2016
 *      Author: jung
 */
#include "classification.hpp"

Classifier_segnet::Classifier_segnet(const string& model_file,
                       const string& trained_file)
{

  Caffe::set_mode(Caffe::GPU);

  /* Load the network. */
  net_.reset(new Net<float>(model_file, TEST));
  net_->CopyTrainedLayersFrom(trained_file);

  Blob<float>* input_layer = net_->input_blobs()[0];

  num_channels_ = input_layer->channels();
  input_geometry_.width = input_layer->width();
  input_geometry_.height = input_layer->height();


}

/* Return the top N predictions. */
cv::Mat Classifier_segnet::Classify(const cv::Mat& img) {
  return Predict(img);
}


cv::Mat Classifier_segnet::Predict(const cv::Mat& img) {
	Blob<float>* input_layer = net_->input_blobs()[0];
	input_layer->Reshape(1, num_channels_,
	                       input_geometry_.height, input_geometry_.width);
	/* Forward dimension change to all layers. */
	net_->Reshape();
	std::vector<cv::Mat> input_channels;
	WrapInputLayer(&input_channels);
	Preprocess(img, &input_channels);
	net_->ForwardPrefilled();


	float* data_addr = input_layer->mutable_cpu_data();
	vector<cv::Mat> img_RGB_channel;
	for(int channel=0;channel< num_channels_;channel++)
	{
	  cv::Mat img_f(input_geometry_.height,input_geometry_.width,CV_32FC1,data_addr);
	  cv::Mat img_single_channel;
	  img_f.convertTo(img_single_channel,CV_8UC3);
	  img_RGB_channel.push_back(img_single_channel);
	  data_addr += input_geometry_.width*input_geometry_.height;
	}

	cv::Mat color_img;

	merge(img_RGB_channel,color_img);
//	imshow("output",color_img);



	const shared_ptr<Blob<float> > prob = net_->blob_by_name("prob");
	float* prob_addr = prob->mutable_cpu_data();

	vector<cv::Mat> prob_color_channel;



	vector<int* > label;

	int Sky[3]={128,128,128};
	int Building[3]={128,0,0};
	int Pole[3]={192,192,128};
	int Road[3]={128,64,128};
	int Pavement[3]={60,40,222};
	int Tree[3]={128,128,0};
	int SignSymbol[3]={192,128,128};
	int Road_marking[3]={255,69,0};
	int Car[3]={64,0,128};
	int Pedestrian[3]={64,64,0};
	int Bicyclist[3]={0,128,192};
    int DummyCar[3]={255,255,255};
    int Fence[3]={64,64,128};
    int Unknown[3]={0,0,0};

	label.push_back(Sky);
	label.push_back(Building);
	label.push_back(Pole);
	label.push_back(Road);
	label.push_back(Pavement);
	label.push_back(Tree);
	label.push_back(SignSymbol);
	label.push_back(Road_marking);
	label.push_back(Car);
	label.push_back(Pedestrian);
	label.push_back(Bicyclist);
    label.push_back(DummyCar);
    label.push_back(Fence);
    label.push_back(Unknown);


	cv::Mat result_img(input_geometry_.height,input_geometry_.width,CV_8UC3);

    cv::Mat prob_max = cv::Mat::zeros(input_geometry_.height,input_geometry_.width,CV_32FC2);
	cv::Mat max_value(input_geometry_.height,input_geometry_.width,CV_32FC1);

    for(int channel=0;channel<prob->channels();channel++)
    {
      cv::Mat prob_f(input_geometry_.height,input_geometry_.width,CV_32FC1,prob_addr);
      cv::Mat prob_single_channel(input_geometry_.height,input_geometry_.width,CV_8UC3);
      for(int x=0;x<prob_f.size().width;x++)
      {

          for(int y=0;y<prob_f.size().height;y++)
          {
              if (prob_f.at<float>(y,x) > prob_max.at<cv::Vec2f>(y,x)[0])
              {
                  prob_max.at<cv::Vec2f>(y,x)[0] = prob_f.at<float>(y,x);
                  prob_max.at<cv::Vec2f>(y,x)[1] = channel;
              }
              if(channel == prob->channels()-1)
              {
                  result_img.at<cv::Vec3b>(y,x)[0] = label.at(prob_max.at<cv::Vec2f>(y,x)[1])[2];
                  result_img.at<cv::Vec3b>(y,x)[1] = label.at(prob_max.at<cv::Vec2f>(y,x)[1])[1];
                  result_img.at<cv::Vec3b>(y,x)[2] = label.at(prob_max.at<cv::Vec2f>(y,x)[1])[0];
              }
          }

      }
      prob_addr += input_geometry_.width*input_geometry_.height;
    }


//	for(int channel=0;channel<prob->channels();channel++)
//	{
//	  cv::Mat prob_f(input_geometry_.height,input_geometry_.width,CV_32FC1,prob_addr);
//	  cv::Mat prob_single_channel(input_geometry_.height,input_geometry_.width,CV_8UC3);
//	  for(int x=0;x<prob_f.size().width;x++)
//	  {

//		  for(int y=0;y<prob_f.size().height;y++)
//		  {
//			  if(prob_f.at<float>(y,x)>THRES_NUM)
//			  {
//				  prob_single_channel.at<cv::Vec3b>(y,x)[0] = label.at(channel)[2];
//				  prob_single_channel.at<cv::Vec3b>(y,x)[1] = label.at(channel)[1];
//				  prob_single_channel.at<cv::Vec3b>(y,x)[2] = label.at(channel)[0];

//				  result_img.at<cv::Vec3b>(y,x)[0] = label.at(channel)[2];
//				  result_img.at<cv::Vec3b>(y,x)[1] = label.at(channel)[1];
//				  result_img.at<cv::Vec3b>(y,x)[2] = label.at(channel)[0];
//			  }
//		  }

//	  }
//	  prob_addr += input_geometry_.width*input_geometry_.height;
//	}

	return result_img;

}


void Classifier_segnet::WrapInputLayer(std::vector<cv::Mat>* input_channels) {
	  Blob<float>* input_layer = net_->input_blobs()[0];

	  int width = input_layer->width();
	  int height = input_layer->height();
	  float* input_data = input_layer->mutable_cpu_data();
	  for (int i = 0; i < input_layer->channels(); ++i) {
	    cv::Mat channel(height, width, CV_32FC1, input_data);
	    input_channels->push_back(channel);
	    input_data += width * height;
	  }


}

void Classifier_segnet::Preprocess(const cv::Mat& img,
                            std::vector<cv::Mat>* input_channels) {
  /* Convert the input image to the input image format of the network. */
  cv::Mat sample;
  if (img.channels() == 3 && num_channels_ == 1)
    cv::cvtColor(img, sample, cv::COLOR_BGR2GRAY);
  else if (img.channels() == 4 && num_channels_ == 1)
    cv::cvtColor(img, sample, cv::COLOR_BGRA2GRAY);
  else if (img.channels() == 4 && num_channels_ == 3)
    cv::cvtColor(img, sample, cv::COLOR_BGRA2BGR);
  else if (img.channels() == 1 && num_channels_ == 3)
    cv::cvtColor(img, sample, cv::COLOR_GRAY2BGR);
  else
    sample = img;

  cv::Mat sample_resized;
  if (sample.size() != input_geometry_)
    cv::resize(sample, sample_resized, input_geometry_);
  else
    sample_resized = sample;

  cv::Mat sample_float;
  if (num_channels_ == 3)
    sample_resized.convertTo(sample_float, CV_32FC3);
  else
    sample_resized.convertTo(sample_float, CV_32FC1);


  cv::split(sample_float, *input_channels);

  CHECK(reinterpret_cast<float*>(input_channels->at(0).data)
        == net_->input_blobs()[0]->cpu_data())
    << "Input channels are not wrapping the input layer of the network.";
}

// lenet_car







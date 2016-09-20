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


	cv::Mat result_img(input_geometry_.height,input_geometry_.width,CV_8UC3);


	cv::Mat max_value(input_geometry_.height,input_geometry_.width,CV_32FC1);
	for(int channel=0;channel<prob->channels();channel++)
	{
	  cv::Mat prob_f(input_geometry_.height,input_geometry_.width,CV_32FC1,prob_addr);
	  cv::Mat prob_single_channel(input_geometry_.height,input_geometry_.width,CV_8UC3);
	  for(int x=0;x<prob_f.size().width;x++)
	  {

		  for(int y=0;y<prob_f.size().height;y++)
		  {
			  if(prob_f.at<float>(y,x)>THRES_NUM)
			  {
				  prob_single_channel.at<cv::Vec3b>(y,x)[0] = label.at(channel)[2];
				  prob_single_channel.at<cv::Vec3b>(y,x)[1] = label.at(channel)[1];
				  prob_single_channel.at<cv::Vec3b>(y,x)[2] = label.at(channel)[0];

				  result_img.at<cv::Vec3b>(y,x)[0] = label.at(channel)[2];
				  result_img.at<cv::Vec3b>(y,x)[1] = label.at(channel)[1];
				  result_img.at<cv::Vec3b>(y,x)[2] = label.at(channel)[0];
			  }
		  }

	  }
	  prob_addr += input_geometry_.width*input_geometry_.height;
	}

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

void Classifier_lenet_car::net_initialize(const string& model_file,
                       const string& trained_file,
                       const string& mean_file,
                       const string& label_file) {
#ifdef CPU_ONLY
  Caffe::set_mode(Caffe::CPU);
#else
  Caffe::set_mode(Caffe::GPU);
#endif


  /* Load the network. */
  net_.reset(new Net<float>(model_file, TEST));
  net_->CopyTrainedLayersFrom(trained_file);

  CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
  CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";

  Blob<float>* input_layer = net_->input_blobs()[0];
  num_channels_ = input_layer->channels();
  CHECK(num_channels_ == 3 || num_channels_ == 1)
    << "Input layer should have 1 or 3 channels.";
  input_geometry_ = cv::Size(input_layer->width(), input_layer->height());

  /* Load the binaryproto mean file. */
  SetMean(mean_file);

  /* Load labels. */
  std::ifstream labels(label_file.c_str());
  CHECK(labels) << "Unable to open labels file " << label_file;
  string line;
  while (std::getline(labels, line))
    labels_.push_back(string(line));

  Blob<float>* output_layer = net_->output_blobs()[0];
  CHECK_EQ(labels_.size(), output_layer->channels())
    << "Number of labels is different from the output layer dimension.";
}

static bool PairCompare(const std::pair<float, int>& lhs,
                        const std::pair<float, int>& rhs) {
  return lhs.first > rhs.first;
}

/* Return the indices of the top N values of vector v. */
static std::vector<int> Argmax(const std::vector<float>& v, int N) {
  std::vector<std::pair<float, int> > pairs;
  for (size_t i = 0; i < v.size(); ++i)
    pairs.push_back(std::make_pair(v[i], i));
  std::partial_sort(pairs.begin(), pairs.begin() + N, pairs.end(), PairCompare);

  std::vector<int> result;
  for (int i = 0; i < N; ++i)
    result.push_back(pairs[i].second);
  return result;
}

/* Return the top N predictions. */
std::vector<Prediction> Classifier_lenet_car::Classify(const cv::Mat& img, int N) {
  std::vector<float> output = Predict(img);

  N = std::min<int>(labels_.size(), N);
  std::vector<int> maxN = Argmax(output, N);
  std::vector<Prediction> predictions;
  for (int i = 0; i < N; ++i) {
    int idx = maxN[i];
    predictions.push_back(std::make_pair(labels_[idx], output[idx]));
  }

  return predictions;
}

/* Load the mean file in binaryproto format. */
void Classifier_lenet_car::SetMean(const string& mean_file) {
  BlobProto blob_proto;
  ReadProtoFromBinaryFileOrDie(mean_file.c_str(), &blob_proto);

  /* Convert from BlobProto to Blob<float> */
  Blob<float> mean_blob;
  mean_blob.FromProto(blob_proto);
  CHECK_EQ(mean_blob.channels(), num_channels_)
    << "Number of channels of mean file doesn't match input layer.";

  /* The format of the mean file is planar 32-bit float BGR or grayscale. */
  std::vector<cv::Mat> channels;
  float* data = mean_blob.mutable_cpu_data();
  for (int i = 0; i < num_channels_; ++i) {
    /* Extract an individual channel. */
    cv::Mat channel(mean_blob.height(), mean_blob.width(), CV_32FC1, data);
    channels.push_back(channel);
    data += mean_blob.height() * mean_blob.width();
  }

  /* Merge the separate channels into a single image. */
  cv::Mat mean;
  cv::merge(channels, mean);

  /* Compute the global mean pixel value and create a mean image
   * filled with this value. */
  cv::Scalar channel_mean = cv::mean(mean);
  mean_ = cv::Mat(input_geometry_, mean.type(), channel_mean);
}

std::vector<float> Classifier_lenet_car::Predict(const cv::Mat& img) {
  Blob<float>* input_layer = net_->input_blobs()[0];
  input_layer->Reshape(1, num_channels_,
                       input_geometry_.height, input_geometry_.width);
  /* Forward dimension change to all layers. */
  net_->Reshape();

  std::vector<cv::Mat> input_channels;
  WrapInputLayer(&input_channels);

  Preprocess(img, &input_channels);

  net_->ForwardPrefilled();

  /* Copy the output layer to a std::vector */
  Blob<float>* output_layer = net_->output_blobs()[0];
  const float* begin = output_layer->cpu_data();
  const float* end = begin + output_layer->channels();
  return std::vector<float>(begin, end);
}

/* Wrap the input layer of the network in separate cv::Mat objects
 * (one per channel). This way we save one memcpy operation and we
 * don't need to rely on cudaMemcpy2D. The last preprocessing
 * operation will write the separate channels directly to the input
 * layer. */
void Classifier_lenet_car::WrapInputLayer(std::vector<cv::Mat>* input_channels) {
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

void Classifier_lenet_car::Preprocess(const cv::Mat& img,
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

  cv::Mat sample_normalized;
  cv::subtract(sample_float, mean_, sample_normalized);

  /* This operation will write the separate BGR planes directly to the
   * input layer of the network because it is wrapped by the cv::Mat
   * objects in input_channels. */
  cv::split(sample_normalized, *input_channels);

  CHECK(reinterpret_cast<float*>(input_channels->at(0).data)
        == net_->input_blobs()[0]->cpu_data())
    << "Input channels are not wrapping the input layer of the network.";
}

vector<string> car_classifier(Classifier_lenet_car classifier, cv::Mat inputimg) {
//  ::google::InitGoogleLogging("trafficsign_recog");

  cv::Mat img = inputimg;

  std::vector<Prediction> predictions = classifier.Classify(img);
  vector<string> output;
  Prediction p = predictions[0];
  string output_val;
  std::ostringstream strs;
  strs<<p.second;
  output_val = strs.str();
  output.push_back(p.first);
  output.push_back(output_val);
  return output;
//  /* Print the top N predictions. */
//  for (size_t i = 0; i < predictions.size(); ++i) {
//    Prediction p = predictions[i];
//    std::cout << std::fixed << std::setprecision(8) << p.second << " - \""
//              << p.first << "\"" << std::endl;
//  }
}








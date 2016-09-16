/*
 * classification.hpp
 *
 *  Created on: Jul 19, 2016
 *      Author: jung
 */

#ifndef CLASSIFICATION_HPP_
#define CLASSIFICATION_HPP_

#include <caffe/caffe.hpp>
#include <caffe/proto/caffe.pb.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <typeinfo>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <boost/array.hpp>
#include <time.h>
#include <limits.h>
#define THRES_NUM 0.7

using namespace caffe;  // NOLINT(build/namespaces)
using std::string;
using namespace std;


/* Pair (label, confidence) representing a prediction. */
typedef std::pair<string, float> Prediction;

class Classifier_segnet {
 public:
  Classifier_segnet(const string& model_file,
             const string& trained_file);

  cv::Mat Classify(const cv::Mat& img);

 private:
  cv::Mat Predict(const cv::Mat& img);

  void WrapInputLayer(std::vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img,
                  std::vector<cv::Mat>* input_channels);

 private:
  shared_ptr<Net<float> > net_;
  cv::Size input_geometry_;
  int num_channels_;
  cv::Mat mean_;
  std::vector<string> labels_;
};

class Classifier_lenet_car {
 public:
    void net_initialize(const string& model_file,
            const string& trained_file,
            const string& mean_file,
            const string& label_file);

  std::vector<Prediction> Classify(const cv::Mat& img, int N = 5);

  void SetMean(const string& mean_file);

  std::vector<float> Predict(const cv::Mat& img);

  void WrapInputLayer(std::vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img,
                  std::vector<cv::Mat>* input_channels);

 private:
  shared_ptr<Net<float> > net_;
  cv::Size input_geometry_;
  int num_channels_;
  cv::Mat mean_;
  std::vector<string> labels_;
};
#endif /* CLASSIFICATION_HPP_ */

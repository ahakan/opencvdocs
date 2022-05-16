/**
 * @file onnx.h
 * @author ahakan (ahmethakan@pm.me)
 * @brief 
 * @version 0.1
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ONNX_H
#define ONNX_H

#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>

class Onnx
{
    private:
        cv::dnn::Net                net;
        std::vector<std::string>    class_names;

        void                        init(std::string model, std::string labels);
        void                        getModel(std::string model);
        void                        getLabels(std::string labels);
        
        void                        setLabel(cv::Mat& img, 
                                                const std::string label, 
                                                const cv::Point& point);


    public:
                                    Onnx(std::string model, 
                                            std::string labels);
                                    ~Onnx();

        void                        inference(std::string img);
};

#endif
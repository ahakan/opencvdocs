#include "../include/onnx.h"

/**
 * @brief Construct a new Onnx::Onnx object
 * 
 * @param model 
 * @param labels 
 */
Onnx::Onnx(std::string model, std::string labels)
{
    std::cout << "Constructor" << std::endl;

    init(model, labels);
}

/**
 * @brief Destroy the Onnx::Onnx object
 * 
 */
Onnx::~Onnx()
{
    std::cout << "Destructor" << std::endl;
}

/**
 * @brief Init the net object
 * 
 * @param model 
 */
void Onnx::init(std::string model, std::string labels)
{
    std::cout << "init" << std::endl;

    getModel(model);

    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    getLabels(labels);
}

/**
 * @brief Get model
 * 
 * @param model 
 */
void Onnx::getModel(std::string model)
{
    net = cv::dnn::readNetFromONNX(model);

    if (net.empty())
        std::cout << "Failed to read ONNX model." << std::endl;
}

/**
 * @brief Get labels
 * 
 * @param labels 
 */
void Onnx::getLabels(std::string labels)
{
    std::ifstream ifs(labels.c_str());

    std::string line;
    
    while (getline(ifs, line))
    {
        std::string newstr="";
 
        for (unsigned int i=10; i<line.length(); i++){
    
            newstr+=std::string(1,line[i]);
            
        }
        class_names.push_back(newstr);
    }
}

/**
 * @brief Set image label
 * 
 * @param img 
 * @param label 
 * @param point 
 */
void Onnx::setLabel(cv::Mat& img, const std::string label, const cv::Point& point)
{
    int fontface        = cv::FONT_HERSHEY_SIMPLEX;
    int thickness       = 1;
    int baseline        = 0;
    double scale        = 0.9;


    cv::Size text = cv::getTextSize(label, 
                                    fontface, 
                                    scale, 
                                    thickness, 
                                    &baseline);

    cv::rectangle(img, 
                    point + cv::Point(0, baseline), 
                    point + cv::Point(text.width, - text.height),
                    cv::Scalar(0, 0, 0),
                    -1);
    
    cv::putText(img,
                label, 
                point, 
                fontface, 
                scale, 
                cv::Scalar(255, 255, 255), 
                thickness, 
                2);
}

/**
 * @brief Inference
 * 
 * @param img 
 */
void Onnx::inference(std::string img)
{
    cv::Mat imageBGR = cv::imread(img, cv::ImreadModes::IMREAD_COLOR);

    cv::Mat blob;

    cv::dnn::blobFromImage(imageBGR, 
                            blob, 
                            0.01, 
                            cv::Size(224, 224), 
                            cv::Scalar(104, 117, 123));
    
    net.setInput(blob);

    cv::Mat outputs = net.forward(); 

    cv::Point classIdPoint;

    double minVal; 
    double maxVal; 

    cv::Point minLoc; 
    cv::Point maxLoc;

    cv::minMaxLoc(outputs,
                    &minVal, 
                    &maxVal, 
                    &minLoc, 
                    &maxLoc );

    std::cout << "Min val: " << minVal << std::endl;
    std::cout << "Max val: " << maxVal << std::endl;

    int label_id = maxLoc.x;

    std::string out_text = cv::format("%s, %.3f", (class_names[label_id].c_str()), maxVal);

    setLabel(imageBGR, out_text, cv::Point(25, 40));

    imshow("Image", imageBGR);

    imwrite("result_image.jpg", imageBGR);
}
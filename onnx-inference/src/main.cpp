/**
 * @file main.cpp
 * @author ahakan (ahmethakan@pm.me)
 * @brief 
 * @version 0.1
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <string>
#include <memory>

#include "../include/onnx.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    /**
     * @brief Models
     * 
     * ../data/model/resnet50-v1-12.onnx
     * ../data/model/shufflenet-v2-12.onnx
     * ../data/model/squeezenet1.1-7.onnx
     *
     */
    std::string model   = "../data/model/resnet50-v1-12.onnx";

    /**
     * @brief Labels
     * 
     * ../data/labels/synset.txt
     *
     */
    std::string labels  = "../data/labels/synset.txt";

    /**
     * @brief Images
     * 
     * ../data/labels/synset.txt
     *
     * ../data/bear.jpg
     * ../data/bee.jpg
     * ../data/cat.jpg
     * ../data/dog.jpg
     * ../data/tiger.jpg
     *
     */
    std::string image   = "../data/tiger.jpg";

    /**
     * @brief Create Onnx object
     * 
     * @param Onnx
     * @param model
     * @param labels
     * @return std::shared_ptr<Onnx> 
     */
    std::shared_ptr<Onnx> 
        pOnnx(new Onnx(model, labels));


    /**
     * @brief Call inference function with image
     * 
     */
    pOnnx->inference(image);

 
    return 0;
}
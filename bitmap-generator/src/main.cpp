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

#include "../include/bitmap.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    /**
     * @brief Images
     * 
     * ../data/bear.jpg
     * ../data/bee.jpg
     * ../data/cat.jpg
     * ../data/dog.jpg
     * ../data/tiger.jpg
     *
     */
    std::string image   = "../data/dog.jpg";

    /**
     * @brief Create bitmap object
     * 
     * @param Bitmap 
     * @return std::shared_ptr<Bitmap> 
     */
    std::shared_ptr<Bitmap> 
        pBitmap(new Bitmap());


    /**
     * @brief Call mat to bitmap function with image path
     * 
     */
    pBitmap->mat_to_bitmap(image);

 
    return 0;
}
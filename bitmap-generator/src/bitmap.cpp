#include "../include/bitmap.h"

/**
 * @brief Construct a new Bitmap::Bitmap object
 * 
 */
Bitmap::Bitmap()
{
    // std::cout << "Constructor" << std::endl;
}

/**
 * @brief Destroy the Bitmap::Bitmap object
 * 
 */
Bitmap::~Bitmap()
{
    std::cout << "Destructor" << std::endl;
}

/**
 * @brief Convert mat object type to string
 * 
 * @param type 
 * @return std::string 
 */
std::string Bitmap::type2str(int type) 
{
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) 
  {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

/**
 * @brief Dec to hex
 * 
 * @param a Alpha
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return uint32_t 
 */
uint32_t Bitmap::create_ARGB(int a, int r, int g, int b)
{
    return ((a & 0xff) << 24) 
            + ((r & 0xff) << 16) 
            + ((g & 0xff) << 8)
            + (b & 0xff);
}

/**
 * @brief Bitmap generator
 * 
 * @param filename 
 * @param width 
 * @param height 
 * @param data 
 * @return true 
 * @return false 
 */
bool Bitmap::bmp_generator(const char *filename, int width, int height, uint32_t *data)
{
    BITMAPFILEHEADER bmp_head;
    BITMAPINFOHEADER bmp_info;
    int size = width * height * 4;

    bmp_head.bfType = 0x4D42; // 'BM'
    bmp_head.bfSize= size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // 32 + head + info no quad
    bmp_head.bfReserved1 = bmp_head.bfReserved2 = 0;
    bmp_head.bfOffBits = bmp_head.bfSize - size;
    // finish the initial of head

    bmp_info.biSize = 40;
    bmp_info.biWidth = width;
    bmp_info.biHeight = height;
    bmp_info.biPlanes = 1;
    bmp_info.biBitCount = 32; // bit(s) per pixel, 32 is true color
    bmp_info.biCompress = 0;
    bmp_info.biSizeImage = size;
    bmp_info.biXPelsPerMeter = 3780;
    bmp_info.biYPelsPerMeter = 3780;
    bmp_info.biClrUsed = 0 ;
    bmp_info.biClrImportant = 0;
    // finish the initial of infohead;

    // copy the data
    FILE *fp;
    if (!(fp = fopen(filename,"wb"))) return 0;

    fwrite(&bmp_head, 1, sizeof(BITMAPFILEHEADER), fp);
    fwrite(&bmp_info, 1, sizeof(BITMAPINFOHEADER), fp);
    fwrite(data, 1, size, fp);
    fclose(fp);

    return 1;
}

/**
 * @brief Mat to bitmap
 * 
 * @param img path
 */
void Bitmap::mat_to_bitmap(std::string img)
{
    cv::Mat imgRGB = cv::imread(img, cv::ImreadModes::IMREAD_COLOR);

    std::string ty = type2str(imgRGB.type());

    std::cout << "Image: " << ty << " " << imgRGB.cols << "x" << imgRGB.rows << std::endl;

    // x, 0 => Blue
    // x, 1 => Green
    // x, 2 => Red

    uint32_t x[imgRGB.rows][imgRGB.cols];

    for(int r = 0; r < imgRGB.rows; r++)
    {
        for(int c = 0; c < imgRGB.cols; c++)
        {
            // ARGB
            uint32_t i = create_ARGB(255,
                            static_cast<int>(imgRGB.at<uchar>(r, c*3+2)),
                            static_cast<int>(imgRGB.at<uchar>(r, c*3+1)),
                            static_cast<int>(imgRGB.at<uchar>(r, c*3)));
            
            x[imgRGB.rows-r-1][c] = i;
        }
    }

    std::string fileName = "./a.bmp";

    bmp_generator(fileName.c_str(), imgRGB.cols, imgRGB.rows, (uint32_t*)x);
}

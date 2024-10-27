/* compare_images.cpp

   B. Bird - 11/02/2019
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <list>
#include "image.hpp"


int main(int argc, const char** argv){

    std::vector< std::string > args {};
    for(int i = 1; i < argc; i++){
        args.push_back(argv[i]);
    }

    if (args.size() != 2){
        std::cout << "Usage: ./compare_images <image1> <image2>" << std::endl;
        std::cout << "  e.g. ./compare_images my_image.png my_other_image.png" << std::endl;
        return 1;
    }

    std::string image1_filename {args.at(0)}, image2_filename {args.at(1)};
    

    Image image1 {image1_filename};
    Image image2 {image2_filename};

    if (image1.get_width() != image2.get_width()){
        std::cout << "Images do not match: widths differ (" << image1.get_width() << " vs. " << image2.get_width() << ")" << std::endl;
        return 0;
    }

    if (image1.get_height() != image2.get_height()){
        std::cout << "Images do not match: heights differ (" << image1.get_height() << " vs. " << image2.get_height() << ")" << std::endl;
        return 0;
    }

    //If the widths and heights match up, compare each pixel.

    int w = image1.get_width();
    int h = image1.get_height();

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            Image::Pixel p1 = image1.at(x,y);
            Image::Pixel p2 = image2.at(x,y);
            if (p1 != p2){
                std::cout << "Images do not match: pixel (" << x << ", " << y << ") differs." << std::endl;
                std::cout << "  In " << image1_filename << ": (" << (int)p1.r << ", " << (int)p1.g << ", " << (int)p1.b << ")" << std::endl;
                std::cout << "  In " << image2_filename << ": (" << (int)p2.r << ", " << (int)p2.g << ", " << (int)p2.b << ")" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "Images match." << std::endl;
    

    return 0;
}
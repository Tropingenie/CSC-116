/* fill.cpp
   CSC 116 - Fall 2019
   
  Coded:
	Benjamin Lyne
	V00914888
	2019-11-05
   
   Task: Implement the  "bucket fill" operation
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <list>
#include "image.hpp"

using std::pair;
using Pixel = Image::Pixel;
using uchar = unsigned char;
using uint = unsigned;

void bucket_fill(Image& I, const Pixel& RGB, pair<uchar,uchar> coord);

void check_cardinals(Image& I, std::list<pair<uchar,uchar>>& queue,const pair<uchar,uchar>& coord, const Pixel& oRGB, const Pixel& RGB, const std::pair<uint,uint>& dim);

//Some fancy "set equal" function since operator= must be defined in the class
void set_equal(Pixel& current, const Pixel& other){
			current.r = other.r;
			current.g = other.g;
			current.b = other.b;
		}

int main(int argc, const char** argv){

    std::vector< std::string > args {};
    for(int i = 1; i < argc; i++){
        args.push_back(argv[i]);
    }

    if (args.size() != 7){
        std::cout << "Usage: ./fill <input image> <output image> <x> <y> <r> <g> <b>" << std::endl;
        return 1;
    }

    std::string input_filename {args.at(0)}, output_filename {args.at(1)};
    unsigned int start_x = std::stoi(args.at(2));
    unsigned int start_y = std::stoi(args.at(3));

    unsigned char r = std::stoi(args.at(4));
    unsigned char g = std::stoi(args.at(5));
    unsigned char b = std::stoi(args.at(6));
    
	//Initialise
	if ( r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255){
		std::cout << "Error: Invalid RGB fill colour";
		return 1;
	}
    Pixel RGB {r, g, b};
	auto start = std::make_pair(start_x,start_y);//pair of uchar
	try{
		Image input {input_filename};
	}catch(std::runtime_error& e){
		std::cout << "Error: Unable to open input image";
		return 1;
	}
	Image input {input_filename};//to avoid an annoying scope, I just put this here. Makes the try-catch block easier to look at.
	if ( start_x < 0 || start_y < 0 || start_x > input.get_width()-1 || start_y > input.get_height()-1){
		//Note: get_w and get_h have the -1 because I have assumed they count from 1 and not 0 (ie a 1x1 image is just one pixel at index 0,0)
		std::cout << "Error: Invalid starting pixel";
		return 1;
	}
	
	//Excecute algorithm
	bucket_fill (input, RGB, start);
	
	//Save image
	try{
		input.save(output_filename);
	}catch(std::runtime_error& e){
		std::cout << "Error: Unable to write output image";
		return 1;
	}

    return 0;
}

void bucket_fill(Image& I, const Pixel& RGB, pair<uchar,uchar> start_coord){
	/* 	Note: Original algorithm by B. Bird (and/or UVic CSC dep.), modified by B. Lyne
		1. Create a new queue data structure to contain (x, y) coordinate pairs.
		2. Add the pair (xstart, ystart) to the queue.
		3. Set the colour of pixel (xstart, ystart) to the new colour C.
		4. While Q is non-empty:
			(a) Remove the first coordinate pair from the queue. Let (x, y) be the coordinates that were removed.
				Then, set the pixel at those coordinates to the new colour, C
			(b) For each of the four cardinal neighbour pixels of (x, y) (up, down, left, right):
				• If the colour of the neighbouring pixel is the old colour, add the coordinates of the neighbouring pixel to the queue.
	*/
	auto dim = std::make_pair(I.get_width(),I.get_height());
	//Step 1:
	std::list<pair<uchar,uchar>> queue;
	//Step 2:
	queue.push_front(start_coord);
	//Step 3: Done in step 4a by my modified algorithm
	
	//Step 4:
	Pixel oRGB {0,0,0};
	{
		auto& [x, y] = start_coord;
		set_equal(oRGB, I.at(x,y));//save the original RGB values
	}
	do{
		//Step a:
		auto& coord = *(queue.begin());//sets coord to the first pair in the queue
		auto& [x,y] = coord;//Unpack coord
		
		set_equal(I.at(x,y), RGB);//set the pixel at coord to the desired colour
		queue.erase(queue.begin());//erases the first element of the queue
		//Step b:
		check_cardinals(I, queue, coord, oRGB, RGB, dim);//Adds any adjacent pixels that are coloured oRGB to the list
	}while (!queue.empty());
	
}

void check_cardinals(Image& I, std::list<pair<uchar,uchar>>& queue,const pair<uchar,uchar>& coord, const Pixel& oRGB, const Pixel& RGB, const std::pair<uint,uint>& dim){
	//Step 4b:
	auto& [w,h] = dim;
	auto& [x,y] = coord;
	//Again, note that w and h need a -1 so that they are the endpoints of the pixel array (ie, the width array is {0, ..., w-1} )
	if(y != 0) if(I.at(x,y-1) == oRGB) queue.push_back(std::make_pair(x,y-1));//up
	if(y != h-1) if(I.at(x,y+1) == oRGB) queue.push_back(std::make_pair(x,y+1));//down
	if(x != 0) if(I.at(x-1,y) == oRGB) queue.push_back(std::make_pair(x-1,y));//left
	if(x != w-1) if(I.at(x+1,y) == oRGB) queue.push_back(std::make_pair(x+1,y));//right
	
	//Bug: For whatever reason, code doesn't check below the pixel at times?
	//std::cout << coord.first << " " << coord.second << std::endl;//let's check every coordinate, since we know which are being missed.
}
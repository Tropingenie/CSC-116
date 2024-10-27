/* fill.cpp
   CSC 116 - Fall 2019
   
   Write your implementation below.

   Benjamin Lyne
   V00914888
   2019-11-06
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <list>
#include <functional>//for static cast
#include <algorithm>//for std::find
#include "image.hpp"

using Pixel = Image::Pixel;

void bucket_fill (Image& I, const unsigned& start_x, const unsigned& start_y, const unsigned char & r, const unsigned char & g, const unsigned char & b);
void check_cardinals(Image& I, std::list<std::pair<unsigned, unsigned>>& Q, const unsigned& x, const unsigned& y, const Pixel& original);

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
	
	/*Check error conditions:*/{
		if ( r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255){
			std::cout << "Error: Invalid RGB fill colour";
			return 1;
		}
		try{
			Image I {input_filename};
			if ( start_x < 0 || start_y < 0 || start_x > I.get_width()-1 || start_y > I.get_height()-1){
				//Note: get_w and get_h have the -1 because I have assumed they count from 1 and not 0 (ie a 1x1 image is just one pixel at index 0,0)
				std::cout << "Error: Invalid starting pixel";
				return 1;
			}
		}catch(std::runtime_error& e){
			std::cout << "Error: Unable to open input image";
			return 1;
		}
	}
	
	//Initialise Image
    Image I {input_filename};
	
	//Run algorithm
	try{
		bucket_fill(I, start_x, start_y, r, g, b);
	}catch(std::runtime_error& e){
		std::cout << "Caught error: (" << e.what() << ")" << std::endl;
	}
	//Save image
	try{ I.save(output_filename); }catch(std::runtime_error& e){
		std::cout << "Error: Unable to write output image";
		return 1;
	}

    return 0;
}

//void print_list(std::list<std::pair<unsigned, unsigned>>& L){
//	for(auto& [e,l]: L) std::cout << "(" << e << "," << l << "), ";
//	std::cout << std::endl;
//}

void bucket_fill (Image& I, const unsigned& start_x, const unsigned& start_y, const unsigned char & r, const unsigned char & g, const unsigned char & b){
	/*
		Algorithm:
			Make a queue. Push the pixel in .at(x,y) into it
			While the queue has stuff in it
				-Set the current pixel to the desired colour
				-Add adjacent pixels or the original colour to the queue
	*/
	std::list<std::pair<unsigned, unsigned>> Q;//Q is a list of coordinates to the pixels of the image
	Pixel original {I.at(start_x,start_y).r, I.at(start_x,start_y).g, I.at(start_x,start_y).b};//saves the original RGB values
	Pixel desired {r, g, b};//saves the desired RGB values for comparison later
	Q.push_front(std::make_pair(start_x,start_y));//pushes the initial coordinates into the list
	do{
		//std::cout << "Loop. Q has this many elements: " << Q.size() << std::endl;
		//std::cout << "Desired RGB:" << std::endl;
		//std::cout << static_cast<int>(r) << " " << static_cast<int>(g) << " " << static_cast<int>(b) << std::endl;
		//std::cout << "Original RGB:" << std::endl;
		//std::cout << static_cast<int>(original.r) << " " << static_cast<int>(original.g) << " " << static_cast<int>(original.b) << std::endl;
		auto& [x, y] = *(Q.begin());//reads the first pair stored in Q
		//std::cout << "Current RGB:" << std::endl;
		//std::cout << static_cast<int>(I.at(x,y).r) << " " << static_cast<int>(I.at(x,y).g) << " " << static_cast<int>(I.at(x,y).b) << std::endl;
		if (I.at(x,y) != desired)//checks that the pixel isn't already the desired colour
			{I.at(x,y).r = r; I.at(x,y).g = g; I.at(x,y).b = b;}//sets the RGB values of the pixel
		check_cardinals(I, Q, x, y, original);//check the cardinal pixels
		Q.erase(Q.begin());//erase the first element in Q
		//std::cout << "Changed RGB:" << std::endl;
		//std::cout << static_cast<int>(I.at(x,y).r) << " " << static_cast<int>(I.at(x,y).g) << " " << static_cast<int>(I.at(x,y).b) << std::endl;
		//std::cout << "Queue is: " << std::endl;
		//print_list(Q);
		if (Q.size() > I.get_width()*I.get_height() ) throw std::runtime_error ("Queue has exceeded size of image");
	}while(!Q.empty());
	
}

void check_cardinals(Image& I, std::list<std::pair<unsigned, unsigned>>& Q, const unsigned& x, const unsigned& y, const Pixel& original){
	auto w = I.get_width(); auto h = I.get_height();
	
	/*
	All of these have basically the same three conditions:
		1st if: checks if the current coordinates are at the edge of the image
		2nd if: checks that the adjacent pixel is the same colour as the originally selected pixel
		3rd if: checks that the coordinates of the adjacent pixel are already in the queue
		
	In order to push_back the coordinates onto the que, the coordinates must not be at the respective edge, must correspond
	to a pixel of the original colour, and must not already be in the list.
	*/
	
	//Up:
	if(y != 0){
		if(I.at(x,y-1) == original){
			auto P = std::make_pair(x,y-1);
			if(std::find(Q.begin(),Q.end(),P) == Q.end()){
				Q.push_back(P);
				//std::cout << "push_back" << std::endl;
			}
		}
	}
	//Down:
	if(y != h-1){
		if(I.at(x,y+1) == original){
			auto P = std::make_pair(x,y+1);
			if(std::find(Q.begin(),Q.end(),P) == Q.end()){
				Q.push_back(P);
				//std::cout << "push_back" << std::endl;
			}
		}
	}
	//Left:
	if(x != 0){
		if(I.at(x-1,y) == original){
			auto P = std::make_pair(x-1,y);
			if(std::find(Q.begin(),Q.end(),P) == Q.end()){
				Q.push_back(P);
				//std::cout << "push_back" << std::endl;
			}
		}
	}
	//Right:
	if(x != w-1){
		if(I.at(x+1,y) == original){
			auto P = std::make_pair(x+1,y);
			if(std::find(Q.begin(),Q.end(),P) == Q.end()){
				Q.push_back(P);
				//std::cout << "push_back" << std::endl;
			}
		}
	}
	
}
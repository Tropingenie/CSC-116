#include <iostream>
#include <vector>

using matrix_type = std::vector<std::vector<int>>;
using ull = unsigned long long;

// draws the spiral pattern inside the provided square matrix
void up(ull& i, ull& j){
	i++;
}
void down(ull& i, ull& j){
	i--;
}
void left(ull& i, ull& j){
	j--;
}
void right(ull& i, ull& j){
	j++;
}
ull sumn(unsigned int n){
	ull sumn = 0;
	for(;n>0;n--){
		sumn += n;
	}
	return sumn;
}
void draw_spiral(matrix_type& matrix) {
	// TODO: write the code to draw the spiral pattern in the matrix
	//Out for loop needs to run n+(n-1)+ ... + 2 + 1 times
	ull n_sum = sumn(matrix.size());

	enum direction {UP, DOWN, LEFT, RIGHT};
	direction dir = RIGHT;

	ull i = 0, j = 0, edge = matrix.size()-1, counter2 = 0, current_number = matrix.size();
	
	for(ull counter = 0; counter <= n_sum; counter++){
		if (edge == 0) break;
		else if (counter2 == current_number){
			current_number--;
			counter2 = 0;
		}
		switch(dir){
			case UP:
				if (i == edge){ 
					dir = RIGHT;
					edge--;
				}else{
					matrix.at(i).at(j) = current_number;
					 up(i,j);
				}
			case DOWN:
				if (i == edge){ 
					dir = LEFT;
					edge--;
				}else{
					matrix.at(i).at(j) = current_number;
					down(i,j);
				}
			case LEFT:
				if (i == edge){ 
					dir = UP;
					edge--;
				}else {
					matrix.at(i).at(j) = current_number;
					left(i,j);
				}
			case RIGHT:
				if (i == edge){ 
					dir = DOWN;
					edge--;
				}else {
					matrix.at(i).at(j) = current_number;
					right(i,j);
				}
		}
	}
	
}

// helper function which prints the provided matrix
void print(const matrix_type& matrix) {
	for (auto& row : matrix) {
		for (auto value : row) {
			std::cout << value << ' ';
		}
		std::cout << std::endl;
	}
}

int main(int argc, char** argv) {
	// check that the user provided a command line argument
	if (argc != 2) {
		std::cout << "One integer command line argument must be provided\n";
		return EXIT_FAILURE;
	}

	size_t dimension {0};

	// attempt to convert the command line argument into an integer
	try {
		int test {std::stoi(argv[1])};

		if (test < 0) {
			throw std::invalid_argument("Command line argument was negative");
		}
		dimension = static_cast<int>(test);
	} catch (std::invalid_argument& e) {
		std::cout << "The command line argument must be a positive integer\n";
		return EXIT_FAILURE;
	}

	// create an "empty" square matrix from the dimension
	matrix_type matrix {dimension, std::vector<int>(dimension, 0)};

	// student implements this function
	draw_spiral(matrix);

	print(matrix);

	return EXIT_SUCCESS;
}

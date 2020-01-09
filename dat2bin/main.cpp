#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

void printhelp(){
	std::cout << "Usage: convert2bin -in <path to input file> -out <path to output file>" << std::endl;
	std::cout << "Or: convert2bin -h" << std::endl;
	return;
}

int main(int argc,  char** argv){
	double test = 0.01;
	std::cout << "dSize is: " << sizeof(test) << std::endl;
	bool inSet = false;
	bool outSet = false;
	std::string inFile = "";
	std::string outFile = "";
	for(int i = 0; i < argc; i++){
		if(std::string(argv[i]).compare(std::string("-in")) == 0){
            		std::stringstream strStream(std::string(argv[i+1]));
            		strStream >> inFile;
			inSet = true;
        	}
        	else if(std::string(argv[i]).compare(std::string("-out")) == 0){
            		std::stringstream strStream(std::string(argv[i+1]));
            		strStream >> outFile;
			outSet = true;
        	}
		else if(std::string(argv[i]).compare(std::string("-h")) == 0){
            		printhelp();
			return 0;
        	}
    	}
	if(!inSet || !outSet){
		std::cout << "Error: Set input and output file" << std::endl;
		printhelp();
		return -1;
	}
	std::ofstream out;
        out.open (outFile.c_str(), std::ios::binary);
	
	
	std::ifstream in;
	in.open (inFile.c_str());
	std::string line;
	while(std::getline(in, line)) {
		std::stringstream stream;
		stream << line;
		//std::cout << stream.str() << std::endl;
		for(int i = 0; i < 4; i++){
			double intermediate = 0.0;
			stream >> intermediate;
			//std::cout << here << std::endl;
			out.write(reinterpret_cast<char*>(&intermediate),sizeof(intermediate));
		}
    	}
	in.close();
	out.close();
	
	return 0;
}

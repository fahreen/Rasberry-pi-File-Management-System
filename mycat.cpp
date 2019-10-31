/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * 
 * This class copies contents of the specified file 
 * to the terminal
 * */


#include <fstream>
#include "file_manager.h"

int mycat (const char* file);

int main(int argc, char *argv[]){
	const char *file;
	for (int i = 1; i < argc; ++i){
		file = argv[i];
		mycat(file);}
	return 0; }

// mycat will take a file name and display contents to terminal
int mycat (const char* file){
	File_manager m(file);	
	// use std output as a stream
	int e = m.Dump(&(std:: cout));
	if (e!= 0){
		std::cout<< "ERROR: " << strerror(e) << std:: endl;
		return -1;}
	return 0;
}

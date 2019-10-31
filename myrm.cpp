/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * 
 * This class removes the specified file from the system
 * 
 * */



#include <fstream>
#include <sys/types.h>
#include <iostream>
#include <errno.h> 
#include <stdio.h>
#include "file_manager.h"


int myrm (const char* file);

int main(int argc, char *argv[]){
	const char *file;
	for (int i =1; i< argc; ++i){
			file = argv[i];
			myrm(file);
			return 0; }}

// myrm will take a file name and remove it from the file system
int myrm (const char* file){
	File_manager m(file);
	int e = m.Remove();
	if (e != 0){
	std :: cout << "ERROR: " << strerror(e) << std :: endl;
	return -1;}	
	return 0;}

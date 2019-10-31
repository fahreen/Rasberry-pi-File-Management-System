/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * 
 * This class will list all the information stored in the filesysten 
 * of the given file
 * 
 * */

#include <fstream>
#include <sys/types.h>
#include <iostream>
#include <errno.h> 
#include <stdio.h>
#include <sys/stat.h>
#include <vector>
#include "file_manager.h"

int mystat (const char* file);
int main(int argc, char *argv[]){
	const char *file;
	file = argv[1];
	mystat(file);
	return 0; }


// mystat takes in a file name, and will list all the attributes of that file
int mystat (const char* file){
	File_manager m(file);
	std :: cout << "File Name: " << m.get_name() << std :: endl;
	std :: cout << "File Type: " << m.get_type() << std :: endl;
	std :: cout << "File Size: " << m.get_size() << std :: endl;
	std :: cout << "File Owner Name : " << m.get_owner_name() << std :: endl;
	std :: cout << "File Owner ID   : " << m.get_owner_id() << std :: endl;
	std :: cout << "File Group Name : " << m.get_owner_name() << std:: endl;
	std :: cout << "File Group ID   : " << m.get_owner_id() << std:: endl;
	std :: cout << "File Permission : " << m.get_permission() << std:: endl;
	std :: cout << "File Block Size: " << m.get_block_size() << std :: endl;
	
	if (!S_ISDIR(m.get_type())){
		std :: cout << "File Children: NULL (this is not a directory) " << std :: endl;}
	
	else {
		std :: cout << "File Children:  " << std:: endl ;
		m.Expand();
		std:: vector <File_manager> children = m.get_children();
		for (unsigned int i = 0; i< children.size() -1 ; i++){
			std :: string s =(children.at(i)).get_name();
				std:: cout << s << std:: endl;}
			std :: string s =(children.at(children.size() -1)).get_name();
		
		
		
		
	}
		std :: cout << "File error number: " << m.get_error_number() << std :: endl;
	return 0; 

	}
	
	
	
	
	
	
	
	
	


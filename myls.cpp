/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 *This class lists contents of the specified directory
 * if -l is used, lists similar to ls -l 
 * if file is given, ,simply prints file name
 * */
#include <fstream>
#include <sys/types.h>
#include <iostream>
#include <errno.h> 
#include <stdio.h>
#include <sys/stat.h>
#include "file_manager.h"

int myls(const char* file);
int mylsl(const char* file);

int main(int argc, char *argv[]){
	
	if (argc >1){ // to avoid null error
	
		if (strcmp (argv[1],  "-l" ) == 0){
			if (argc > 2){
				const char* f1;
				f1 = argv[2];
				mylsl(f1);}
		
		else{ 
			const char* f2;
			f2 = ".";
			mylsl(f2);}}
	else {
		if (argc > 1){
			const char* f3;
			f3 = argv[1];
			myls(f3);}}}
		else{
			const char* f4;
			f4 = ".";
			myls(f4);}
			}

// used for myls
int myls(const char* file){
		File_manager m(file);
		// if not directory, print name
		if (!S_ISDIR(m.get_type())){
			std:: cout << m.get_name()<<std :: endl;
			return 0;}
		m.Expand(); 
		std:: vector <File_manager> children = m.get_children();
		
		// iterate through directory vector  and print children 
		for (unsigned int i = 0; i< (children.size() -1) ; i++){
			std :: string s =(children.at(i)).get_name();
			std:: cout << s << std:: endl;}
			std :: string s =(children.at(children.size() -1)).get_name();
		return 0;
		}

// used for my ls -l
int mylsl(const char* file){
	File_manager m(file);
	
	// if not directory, print name
	if (!S_ISDIR(m.get_type())){
			std:: cout << m.get_name()<<std :: endl;
			return 0;}
	
	m.Expand(); 
	std:: vector <File_manager> children = m.get_children();
	
	// iterate through directory vector  and print children information
	for (unsigned int i = 0; i< children.size() -1 ; i++){
			
			File_manager child = children.at(i);
			std:: string d; 
			if (S_ISDIR(child.get_type()))
				d = "d";
			else 
				d= "-";
			std:: cout << d << "" << child.get_permission() << "  " <<  " " << child.get_owner_name() ;
			std :: cout << "  "<<  child.get_group_name() <<  "          " ;
			std :: cout << child.get_block_size() << "  " ;
			std :: cout << (child.get_modification_time()).tv_sec;
			std :: cout <<  "  "  << child.get_name() << std:: endl;
			}
			std :: string s =(children.at(children.size() -1)).get_name();

	return 0;
	}
	

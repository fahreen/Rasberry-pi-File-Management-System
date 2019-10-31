
/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * 
 * This class moves the file from arguement 1 to the destination 
 * specified in srguement 2
 * 
 * */


#include <fstream>
#include "file_manager.h"

int mymv(const char* source, const char* destination);


int main(int argc, char *argv[]){
	const char* s;
	const char* d;
	s = argv[1];
	d = argv[2];
	mymv(s, d);
}
		
// mymv will take two file names, and move source to destination
int mymv(const char* source, const char* destination){
		
		File_manager m(source);
		int e = m.Rename(destination);
		if (e == 0 ){
			return 0;}
		
		// if files are in different filesystems, copy into newfile
		//and delete old
		else if (e == EXDEV ){
			std:: fstream outstream;
			try{
				outstream.open(destination);
			}
			catch (std:: system_error &error){
				std :: cout << "ERROR RENAMING FILE : " << strerror((error.code()).value())<< std :: endl;
				return -1;}	
			int e1 = m.Dump(&outstream);
			
			if (e1!= 0){
				std :: cout << "ERROR RENAMING FILE : " << strerror(e1)<< std ::endl;
				return -1;}
			
			int e2 = m.Remove();
			if (e2!= 0){
				std :: cout << "ERROR RENAMING FILE : " << strerror(e2)<< std :: endl;
				return -1;}}
		 return 0;}

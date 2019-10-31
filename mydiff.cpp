/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * this class compares two files and notifies user whether they are the 
 * same or different
 * 
 * */

#include <fstream>
#include "file_manager.h"


int mydiff (const char* file1, const char* file2 );

int main(int argc, char *argv[]){
	const char * file1;
	const char *file2;
	file1 = argv[1];
	file2 = argv[2];
	mydiff(file1, file2);
	return 0; }

// my diff will take two file names, and print whether thay are same or different
int mydiff (const char* file1, const char* file2){
	File_manager m(file1);
	File_manager n(file2);
	int e = m.Compare(n);
	if (e == 1){
		std :: cout << "They are the same!" << std :: endl;}
 else if (e == 0){
		std :: cout << "They are different" << std :: endl;}
	else {
		std :: cout << "ERROR: " << strerror(e) << std :: endl;
		return -1;}	
		
	return 0;}

	

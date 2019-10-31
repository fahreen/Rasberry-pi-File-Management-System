/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * 
 * This class copies content from from file 1 (specified
 * in argument 1 ) to file 2 (arguement 2)
 * 
 * */


#include <fstream>
#include "file_manager.h"
int mycp (const char* source, const char* destination);

int main(int argc, char *argv[]){
	const char *s;
	const char *d;
	s = argv[1];
	d = argv [2];
	mycp(s, d);}

// my cp will take two file name, and copy source contents to destination
int mycp (const char* source, const char* destination){
	File_manager m(source);
	std:: fstream outstream;
	outstream.open(destination); // catch error	 
	int i = m.Dump(&outstream);
	if (i != 0){
		std :: cout << "ERROR: " << strerror(i) << std:: endl;
		return -1;
	}
	return 0;
	
	}

/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * 
 * File_manager class is a class which is a file management  
 * for the rasberry pi. This class encapsulates files in the 
 * file system, as well as the operations which can be performed
 * on them. Each instance of the class manages a single file.
 * 
 * */



#include <sys/stat.h>
#include <bitset>
#include <pwd.h>
#include <grp.h>
#include <errno.h> 
#include <fstream>
#include <stdio.h>
#include "file_manager.h"
#include <unistd.h>
#include <dirent.h>
#include <cstring>

// default constructor
File_manager:: File_manager (){
	// set invalid attributes
	this-> type = -1;
	this-> size = -1;
	this-> owner.id = -1;
	this -> owner.name = "";
	this -> group.id = -1;
	this -> group.name = "";
	this ->permissions = "";
	this-> access_time.tv_sec = -1;
	this-> access_time.tv_nsec = -1;
	this -> modification_time.tv_sec  =  -1;
	this -> modification_time.tv_nsec  =  -1;
	this ->  status_change_time.tv_sec=  -1;
	this ->  status_change_time.tv_nsec =  -1;
	this-> block_size = -1; 
	this-> children.clear();
	this -> error_number = -80;
	// notify user
	std:: cout << "File Name Required"  << std:: endl;
	
}


// main constructor
 File_manager:: File_manager (std:: string n){
	 this -> name = n;
	 struct stat info;
	 const char* n1;
	 n1 = n.c_str();
	 int e = stat(n1, &info);
	 if (e!= 0){
			std:: cout  << "Filename '" << n <<  "' does not exist in the system " << std:: endl;
			this -> name = "";
			this-> type = -1;
			this-> size = -1;
			this-> owner.id = -1;
			this -> owner.name = "";
			this -> group.id = -1;
			this -> group.name = "";
			this ->permissions = "";
			this-> access_time.tv_sec = -1;
			this-> access_time.tv_nsec = -1;
			this -> modification_time.tv_sec  =  -1;
			this -> modification_time.tv_nsec  =  -1;
			this ->  status_change_time.tv_sec=  -1;
			this ->  status_change_time.tv_nsec =  -1;
			this-> block_size = -1; 
			this-> children.clear();
			this-> error_number = -80;
			this-> num_children = -1;
		}
		else{
			this-> type = info.st_mode;
			this-> size = info.st_size;
			// owner
			this-> owner.id = info.st_uid;
			struct passwd *p = getpwuid(this-> owner.id);
			this -> owner.name = p -> pw_name;
			//group 
			this -> group.id = info.st_gid;
			struct group *q = getgrgid(this-> group.id);
			this -> group.name =  q -> gr_name;
			
			//permission
			
			// get last 9 binary digits of filetype
			std:: string binary = std :: bitset<9>(this-> type).to_string();
			std:: string z, z1,z2,z3,z4,z5,z6, z7,z8,z9, w; 
			std :: string q1, q2, q3, q4, q5, q6, q7, q8, q9;
			
			// extract substrings from binary permission number
			q1 = binary.substr(0, 1);
			q2 =binary.substr(1, 1);
			q3 =binary.substr(2, 1);
			q4 =binary.substr(3, 1);
			q5 =binary.substr(4, 1);
			q6 =binary.substr(5, 1);
			q7 =binary.substr(6, 1);
			q8 =binary.substr(7, 1);
			q9 =binary.substr(8, 1);
			
			// set strings for permission using binary number
			if ( q1.compare("1") == 0)
				z1 = "r";
			else 
				z1 = "-";
			if ( q2.compare("1") == 0)
				z2 = "w";
			else 
				z2 = "-";
				if ( q3.compare("1") == 0)
					z3 = "x";
				else 
					z3 = "-";
				if ( q4.compare("1") == 0)
					z4 = "r";
				else 
					z4 = "-";
				if ( q5.compare("1") == 0)
					z5 = "w";
				else 
					z5 = "-";
				if ( q6.compare("1") == 0)
					z6 = "x";
				else 
					z6 = "-";
				if ( q7.compare("1") == 0)
					z7 = "r";
				else 
					z7 = "-";
				if ( q8.compare("1") == 0)
					z8 = "w";
				else 
					z8 = "-";	
				if ( q9.compare("1") == 0)
					z9 = "x";
				else 
					z9 = "-";
				
				z = z1 + z2 + z3 + z4 + z5 + z6 + z7 + z8 + z9;
				this ->permissions = z;
				
				// accesstime, modtime, status change time
				this-> access_time =info.st_atim;
				this -> modification_time = info.st_mtim;
				this ->  status_change_time = info.st_ctim;
				this-> block_size = info.st_blksize;
				this-> num_children = 1;
				this ->  error_number = 0;
}}


	// destructor 
	File_manager:: ~File_manager(){
		//delete vector
		this-> children.clear();
	}
	

	// getters
	std:: string File_manager:: get_name(){ 
		return this->name ; }

	mode_t File_manager:: get_type() { 
		return this->type; }
	
	off_t File_manager:: get_size(){
		return this-> size;}
	
	std::string File_manager:: get_owner_name(){
		return this-> owner.name;}
	
	uid_t File_manager:: get_owner_id(){ 
		return this-> owner.id;}
	
	std:: string File_manager:: get_group_name(){
		return this -> group.name;}
	
	uid_t File_manager:: get_group_id(){
		return this-> group.id;}
	
	std:: string File_manager:: get_permission(){ 
		return this-> permissions;}
	
	struct timespec File_manager:: get_access_time(){ 
		return this-> access_time;}
	
	struct timespec File_manager:: get_modification_time(){ 
		return this-> modification_time;}
	
	struct timespec File_manager:: get_status_change_time(){
		return this-> status_change_time;}
	
	blksize_t File_manager:: get_block_size(){ 
		return this-> block_size;}
	
	std:: vector <File_manager> File_manager:: get_children(){
		return this->children;}

	int File_manager:: get_error_number(){ 
		return this-> error_number;}

/*
 * Function: Dump
 * -----------------------------------
 * This function takes a stream as a parameter and dumps the conttents of the
 * fileobject into that stream.  Block size reccomended by the stat() funcrion
 * is used to increase performance.  This function can only be used on regular files.
 * Attempting to do this on any other type of file results in error.
 * 
 * Parameters: std:: ostream * --> the stream where file content will be written
 * Returns: int --> error number
 * */

	int File_manager:: Dump(std:: ostream *outstream){
		// if file is not regular, retuen ENOTSUP error
		if (S_ISREG(this->type) != 1){ 
			this-> error_number = ENOTSUP;
			return error_number;} 
		
		//open stream, return error if unable to
		std:: fstream f;
		f.open(this->name);
		this -> error_number = errno; 
		if (!(f.is_open())){
			return this -> error_number;} 
		
		// get # of reads for the dump, and create buff
		double reads = (this-> size / this->  block_size) +1;
		char *buff = new char [this-> block_size];
	
		// write to buff
		for (int i = 0; i <reads; i++ ){
			f.read(buff, this-> block_size);
			outstream->write (buff, this-> block_size);}
		this-> error_number = errno;
		delete buff;
		return this-> error_number;
	}
	
	
	
	
	/*
 * Function: Rename
 * -----------------------------------
 * This Function changes the name of the file with the given paramete.
 * This is done on both the object and the disk.  The Rename() function is used 
 * 
 * Parameters: std :: string --> new name of file
 * Returns: int --> error number
 * */

	
	int File_manager:: Rename(std:: string new_file_name){
		const char* old_name;
		const char*new_name;
	
		old_name = (this-> name).c_str();
		new_name = (new_file_name).c_str();
	
		int e = rename(old_name, new_name);
		this-> error_number = errno;
		
		// if no error occured, return 0
		if (e == 0 ){
			this-> name = new_file_name;
			this-> error_number = 0;}
		
		// else return errno
		return this->error_number;
	}
	
	
	
	/*
 * Function: Remove
 * This Function removes a file from the system.  The file is deleted
 * from the disk, and the attributes are set to invalid values.
 * An error number returned if the file was not removed succesfully.
 * 
 * Parameters: void
 * Returns: int --> error number
 * -----------------------------------
 * */
	int File_manager ::  Remove(){
		// set invalid attributes for object
		this-> type = -1;
		this-> size = -1;
		this-> owner.id = -1;
		this -> owner.name = "";
		this -> group.id = -1;
		this -> group.name = "";
		this ->permissions = "";
		this-> access_time.tv_sec = -1;
		this-> access_time.tv_nsec = -1;
		this -> modification_time.tv_sec  =  -1;
		this -> modification_time.tv_nsec  =  -1;
		this ->  status_change_time.tv_sec=  -1;
		this ->  status_change_time.tv_nsec =  -1;
		this-> block_size = -1; 
		this-> children.clear();
		this -> error_number = -80;
	
		//attempt to call unlink function 
		try{
			const char* n1;
			n1 = (this-> name).c_str();
			unlink(n1);
			}
			
		//if unlink fails, return error number
		catch(std:: system_error &error){
			this-> error_number = (error.code()).value(); 
			return this-> error_number;}
		
		this-> error_number = 0;
		this -> name = "";
		return this-> error_number;}
	
	
	
/*
 * Function: Compare
 * This functiontakes another file object as a parameter, and 
 * compares the contents of this file with the one in the
 * parameter.  Block size from str() is used to determine amount of
 * data read and written in the stream.  
 * 
 * Parameters: File_manager --> another file
 * Returns: 0 if not the same, 1 if the same, error otherwise
 * -----------------------------------
 * */
	
	int File_manager::Compare(File_manager file_2){
		
		// if file sizes do not match, they are not the same
		if (this->size != file_2.get_size()){ 
			this ->error_number = 0;
			return this->error_number;}
			
		try{
			// open two streams
			std:: fstream my_stream, stream_2;
			my_stream.open(this->name);
			stream_2.open(file_2.get_name());
			
			// determine max amounts of reads required
			double read1 = (this-> size / this->  block_size) +1;
			double read2 = (file_2.get_size() / file_2.get_block_size()) +1;
			double reads = std::max(read1, read2);
			char *buff1 = new char [this-> block_size];
			char *buff2 = new char [this-> block_size];
			int same;
			
			// read from both streams and compare them
			for (int i = 0; i <reads; i++ ){
				my_stream.read(buff1, this-> block_size);
				stream_2.read(buff2, this-> block_size);
				same = memcmp(buff1, buff2, this->block_size);
				// if at any point streams are different, return 0
				if (same !=0){
					this->error_number = 0;
					return this-> error_number;}
		}
			// streams are the same, so return 1
			this->error_number = 0;
			return 1;
			}
		// catch any errors thrown during the reading
		catch(std:: system_error &error){
		this-> error_number = (error.code()).value(); 
		return this-> error_number;}}



/*
 * Function: Expand
 * This function operates only on directories.  It is ised to fill 
 * the children of the file it was invoked on.  The children are stored 
 * in a vector.
 * 
 * Parameters: void
 * returns: int --> error number
 * -----------------------------------
 * */
	int File_manager:: Expand(){
		
		// if not  a directory, return error(ENOTSUP)
		if (S_ISDIR (this->type) !=1 ){
			std:: cout << "This is not a directory " << std:: endl;
			this-> error_number = ENOTSUP;
			return this->error_number;}
		
		DIR * d_stream;
		try{
			const char* n1;
			n1 = (this-> name).c_str();
			d_stream = opendir(n1);  //create stream
			dirent *d_pointer = readdir(d_stream); // point at first item
			std :: string current_file ;
			std ::string my_name = this->name;
			
			// traverse through directory contents and add to children to vector (as file manager objects)
			while (d_pointer != NULL){
				std :: string child_name =d_pointer-> d_name; 
				current_file = my_name + "/" + child_name;
				File_manager child(current_file);
				(this->children).push_back(child);
				this -> num_children ++;
				d_pointer = readdir(d_stream);
		}
		closedir(d_stream);
	}
		// if error occurs during creating children, return errno
		catch(std:: system_error &error){
			std :: cout << "EXPAND ERROR : "<< (error.code()).value() << std:: endl;
			this-> error_number = (error.code()).value();
			return this-> error_number;
			}
			
		// return 0 if function was successful
		this-> error_number	= 0;
		return this-> error_number;			
		}


	

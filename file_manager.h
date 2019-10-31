
/* Author: Fahreen Bushra 
 * Date: October - 03- 2019
 * 
 * file_Manager.h file declares all attributes,  functions, and
 * structures for file_manager.cpp*/

#pragma once
#include <iostream>
#include <sys/types.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <errno.h> 
#include <stdio.h>



class File_manager{

protected: 
std :: string name;
mode_t type;
off_t size;
struct user {
	uid_t id;
	std:: string name;
	};
struct user owner, group; // structure used for user and group info; 
std :: string permissions;
struct timespec access_time, modification_time, status_change_time;
blksize_t block_size;
std:: vector <File_manager> children;
int num_children;
int error_number;


public:

File_manager ();
File_manager (std:: string n);
~File_manager();
int Dump(std:: ostream *f);
int Rename(std :: string new_file_name);
int Remove();
int Compare(File_manager file_2);
int Expand();


// getters 
std:: string get_name();
mode_t get_type();
off_t get_size();
std:: string get_owner_name();
uid_t get_owner_id();
std:: string get_group_name();
uid_t get_group_id();
std:: string get_permission();
struct timespec get_access_time();
struct timespec get_modification_time();
struct timespec get_status_change_time();
blksize_t get_block_size();
std:: vector <File_manager> get_children();
int get_error_number();
};

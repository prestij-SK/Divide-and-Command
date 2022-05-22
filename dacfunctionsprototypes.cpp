#include "dacfunctions.h"
#include "file_directory_struct.h"



// Main program, which is the File System Emulator (divide and command). 
void div_and_com();

// Shows the current path the User is in at the moment. The path always starts with "Root > ", after creating folders, the path changes at runtime.
void dac_show_current_path(const std::string);

// Asking the user to write command (operation) for the current folder. Returns the inserted string from User.
std::string dac_write_command();




/////////////////////////////// COMMAND LINE CHECK FUNCTIONS start ///////////////////////////////


// Checking the syntax of the command line, command line must start or be: ls  mkdir  cd  touch  rm  rmdir  cd..  cd(multi folders)  pwd  /exit /help.
bool dac_check_command_syntax(const std::string);

// Separate left side and right side of the line Example: cd alo -> left = cd and right = alo
void dac_seperate_left_right(const std::string , std::string &, std::string &);

// Returns true if name is probably file and false if name is folder
bool dac_check_name_is_file_or_folder(const std::string);

// Simple check of file name rules, must not start or end with '.'
bool dac_name_creating_rules(const std::string);

// Checks the rules of operations with: ls  mkdir  cd  touch  rm  rmdir  cd..  cd(multi folders)  pwd  /exit /help.
bool dac_command_rules(const std::string);

// Check the command line. Before doing the operation of the given comment, the line must pass the rules of the program !
bool dac_check_com_line(const std::string);


/////////////////////////////// COMMAND LINE CHECK FUNCTIONS end ///////////////////////////////




// Check if the File exists in given Directory
bool dac_file_exists(const Directory_content, const std::string);

// Check if the Folder exists in given Directory
bool dac_folder_exists(const Directory_content , const std::string);




/////////////////////////////// COMMAND LINE CREATING FUNCTIONS start ///////////////////////////////


// Creating and return File type data
File create_file(std::string name);

// Creating and return Folder type data
Folder create_folder(std::string name);

// Inserting created file to directory
void insert_file_to_directory(Directory_content &, const File );

// Inserting created folder to directory
void insert_folder_to_directory(Directory_content &, Folder );

// Swap two Directories (folders)
void directory_swap(Directory_content &, Directory_content &);

// Calling Touch command for the Command Line. Creates File with the name given by user and Inserts the created file to the current folder.
void dac_operation_touch(std::map <int, std::map < std::string, Directory_content>> &, Directory_content &, const std::string, const int);

// Calling Mkdir command for the Command Line. Creates Folder with the name given by user and Inserts the created folder to the current folder.
// Also creates new Directory_content type for the new folder and adds to the full_data
void dac_operation_mkdir(std::map <int, std::map < std::string, Directory_content>> &, Directory_content &, const std::string , const int);


/////////////////////////////// COMMAND LINE CREATING FUNCTIONS end ///////////////////////////////




/////////////////////////////// COMMAND LINE REMOVING FUNCTIONS start ///////////////////////////////


// Remove File from Directory_Content.files. Returns false if file was not found.
bool dac_remove_file_from_directory(std::vector<File> &, const std::string );

// Calling Rm command for the Command Line. Finds the file name given by user and removes the file from current folder.
// If no such file exists, returns false with message.
bool dac_operation_rm(std::map <int, std::map < std::string, Directory_content>> &, Directory_content &, const std::string , const int );

// Remove Folder from Directory_Content.folders. Returns false if folder was not found.
bool dac_remove_folder_from_directory(std::vector<Folder> &, const std::string);

// Calling Rmdir command for the Command Line. Finds the folder name given by user and removes the folder from current folder.
// If no such folder exists, returns false with message.
bool dac_operation_rmdir(std::map <int, std::map < std::string, Directory_content>> &, Directory_content &, const std::string , const int);


/////////////////////////////// COMMAND LINE CREATING FUNCTIONS end ///////////////////////////////




/////////////////////////////// COMMAND LINE MOVING THROW FOLDERS FUNCTIONS start ///////////////////////////////


// Move to the folder name given by the user, from current folder only one time.
bool dac_operation_cd(std::map <int, std::map < std::string, Directory_content>> , Directory_content &, Directory_content &, const std::string , int &, std::string &);

// Calling Cd command for the Command Line. Move to the folder name given by the user (can be chain of folder names), from current folder multiple times.
// Example: cd f1/f2/f3 or cd f1
void dac_operation_cd_multi(std::map <int, std::map < std::string, Directory_content>> , Directory_content &, Directory_content &, const std::string , int &, std::string &);

// Calling Cd.. command for the Command Line. Move to the prevoius folder only one time.
void dac_operation_cd_dot_dot(std::map <int, std::map < std::string, Directory_content>> , Directory_content &, Directory_content &, int &, std::string &);


/////////////////////////////// COMMAND LINE MOVING THROW FOLDERS FUNCTIONS end ///////////////////////////////




// Calling Ls command for the Command Line. Shows all content of the current Folder and the path to it.
void dac_operation_ls(const Directory_content &, std::string);

// Calling Pwd command for the Command Line. Shows the current place starting from Root.
void dac_operation_pwd(const std::string);

// Calling /help command for the Command Line. Shows the current place starting from Root.
void dac_operation_help();

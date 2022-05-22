#ifndef DACFANCTIONS_H
#define DACFANCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "file_directory_struct.h"

// Show the current path
void dac_show_current_path(const std::string line){

    std::cout << "\nGive_the_command_for_path:: " << line + " > ";

}

// Ask from user a command line
std::string dac_write_command(){
    
    std::string line = "";

    std::getline(std::cin, line);

    return line;
}

// Check Command Syntax                                                        ERROR________22
bool dac_check_command_syntax(const std::string line){

    std::string str = "";

    for(int i = 0; i < line.length(); ++i){

        if(line[i] == ' ' || i >= line.length() - 1){

            if(i >= line.length() - 1 ){
                str += line[i];
            }

            if(str.compare("ls") == 0 || str.compare("mkdir") == 0 || str.compare("cd") == 0 || str.compare("touch") == 0 || 
               str.compare("rm") == 0 || str.compare("rmdir") == 0 || str.compare("cd..") == 0 || str.compare("cd") == 0 || 
               str.compare("pwd") == 0 || str.compare("/exit") == 0 || str.compare("/help") == 0){
                
                return true;
            }
            else{

                return false;
            }
        }

        str += line[i];
    }

    return true;
}

// Separate left and right
void dac_seperate_left_right(const std::string line, std::string &left, std::string &right){

    bool add_to_right = false;

    for(int i = 0; i < line.length(); ++i){

        if(line[i] == ' ' && !(add_to_right)){
            add_to_right = true;
            continue;
        }

        if(add_to_right){
            right += line[i];
        }
        else{
            left += line[i];
        }
    }
}

// Check name is file or folder
bool dac_check_name_is_file_or_folder(const std::string name){
    
    for(int i = 0; i < name.length(); ++i){
        if(name[i] == '.'){
            return true; // file
        }
    }

    return false; // folder
}

// Check name creationg rules
bool dac_name_creating_rules(const std::string name){
    
    if(name[0] == '.' || name[name.length() - 1] == '.'){
        return false;
    }

    return true;
}

// Check if file exists
bool dac_file_exists(const Directory_content current_dir, const std::string name){

    for(auto i : current_dir.files){
        
        if(i.file_name.compare(name) == 0){
            return true;
        }
    }

    return false;
}

// Check if folder exists
bool dac_folder_exists(const Directory_content current_dir, const std::string name){

    for(auto i : current_dir.folders){
        
        if(i.folder_name.compare(name) == 0){
            return true;
        }
    }

    return false;
}

// Check Command Rules                                                         ERROR________33__35
bool dac_command_rules(const std::string line){

    std::string com = "";
    std::string name = "";

    dac_seperate_left_right(line, com, name);

    // Only one command
    if(com.compare("ls") == 0 || com.compare("cd..") == 0 || com.compare("pwd") == 0 || com.compare("/exit") == 0 || com.compare("/help") == 0){
        if(name.compare("") == 0){
            return true;
        }
        else{
            return false;
        }
    }

    if(dac_check_name_is_file_or_folder(name)){
        // Command for file
        if(dac_name_creating_rules(name)){
            if(com.compare("touch") == 0 || com.compare("rm") == 0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            std::cout << "\nerror35_Can't do an operation for file starting or ending with '.' !";
            return false;
        }
    }
    else{
        // Command for folder
        if(com.compare("mkdir") == 0 || com.compare("cd") == 0 || com.compare("rmdir") == 0){
            return true;
        }
        else{
            return false;
        }
    }

    return true;
}

// Check command line
bool dac_check_com_line(const std::string line){

    if(!(dac_check_command_syntax(line))){
        std::cout << "\nerror22_Wrong Command or Syntax, please try again. Write down /help if you need commands section.\n";
        return false;
    }

    if(!(dac_command_rules)(line)){
        std::cout << "\nerror33_Wrong Command use for file or folder, please try again. Write down /help if you need commands section.\n";
        return false;
    }

    return true;
}

// Create file and insert to the current folder
void dac_operation_touch(std::map <int, std::map < std::string, Directory_content>> &data, Directory_content &current_dir, const std::string name, const int current_folder_i){
    
    insert_file_to_directory(current_dir, create_file(name));
    data[current_folder_i][current_dir.dir_name] = current_dir;
}

// Remove file from directory/folder
bool dac_remove_file_from_directory(std::vector<File> &dir_files, const std::string name){

    for(int i = 0; i < dir_files.size(); ++i){

        if(dir_files[i].file_name.compare(name) == 0){

            dir_files.erase(dir_files.begin()+i);

            return true;
        }
    }

    return false;
}

// Remove file from the current folder
bool dac_operation_rm(std::map <int, std::map < std::string, Directory_content>> &data, Directory_content &current_dir, const std::string name, const int current_folder_i){

    for(auto i_it : data){
        if(i_it.first == current_folder_i){

            for(auto j_it : i_it.second){

                if(j_it.first.compare(current_dir.dir_name) == 0){

                    if(dac_remove_file_from_directory(j_it.second.files, name)){

                        data[current_folder_i][current_dir.dir_name] = j_it.second;
                        dac_remove_file_from_directory(current_dir.files, name);
                        
                        std::cout << "\nFile " << name << " is removed from " << j_it.second.dir_name << " Directory !\n";
                        return true;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }

   std::cout << "\nFile " << name << " is not found in " << current_dir.dir_name << " folder ! Please try again.\n";
   return false;
}

// Create folder and insert to the current folder
void dac_operation_mkdir(std::map <int, std::map < std::string, Directory_content>> &data, Directory_content &current_dir, const std::string name, const int current_folder_i){

    insert_folder_to_directory(current_dir, create_folder(name));
    data[current_folder_i][current_dir.dir_name] = current_dir; // navsyaki

    Directory_content new_dir;
    new_dir.dir_name = name;
    new_dir.dir_prev_name = current_dir.dir_name;

    data[current_folder_i + 1][new_dir.dir_name] = new_dir;
}

// Show files and folders for current folder
void dac_operation_ls(const Directory_content &current_dir, std::string path){
    
    std::cout << "\nCurrent " << current_dir.dir_name << " Folder's content list~-path: " << path;

    std::cout << "\nFiles:  ";
    for(auto i : current_dir.files){
            std::cout << i.file_name << "  ";
    }
    
    std::cout << "\nFolders:  ";
    for(auto i : current_dir.folders){
        std::cout << i.folder_name << "  ";
    }
}

// Go to given folder
bool dac_operation_cd(std::map <int, std::map < std::string, Directory_content>> data, Directory_content &current_dir, Directory_content &previous_dir, const std::string name, int &current_folder_i, std::string &path){
    
    if(dac_folder_exists(current_dir, name)){

        ++current_folder_i;

        previous_dir = current_dir;
        current_dir = data[current_folder_i][name];
        current_dir.dir_prev_name = previous_dir.dir_name;

        path += "/" + current_dir.dir_name;

        return true;
    }
    else{

        std::cout << "\nThe Folder " << name << " doesn't exist in the current " << current_dir.dir_name << " Folder ! Can't do the operation.\n";
        return false;
    }
}

// Go to given folder (multi)
void dac_operation_cd_multi(std::map <int, std::map < std::string, Directory_content>> data, Directory_content &current_dir, Directory_content &previous_dir, const std::string name, int &current_folder_i, std::string &path){
    
    std::string name_part = "";

    for(int i = 0; i < name.length(); ++i){
        
        if(name[i] == '/' || i >= name.length() - 1){

            if(i >= name.length() - 1){
                name_part += name[i];
            }

            if(dac_operation_cd(data, current_dir, previous_dir, name_part, current_folder_i, path)){
                name_part = "";
                continue;
            }
            else{
                return;
            }
        }

        name_part += name[i];
    }
}

// Go to previous folder
void dac_operation_cd_dot_dot(std::map <int, std::map < std::string, Directory_content>> data, Directory_content &current_dir, Directory_content &previous_dir, int &current_folder_i, std::string &path){
    
    if(current_folder_i <= 0){
        return;
    }

    --current_folder_i;

    current_dir = previous_dir;

    if(current_folder_i > 0){
        previous_dir = data[current_folder_i - 1][previous_dir.dir_prev_name];
    }
    else{
        previous_dir = data[current_folder_i][previous_dir.dir_prev_name];
    }

    int path_ind = 0;
    for(int i = path.length() - 1; i >= 0; --i){
        
        if(path[i] == '/'){
            path = path.erase(path.length() - path_ind - 1, path_ind + 1);
            return;
        }
        
        ++path_ind;
    }
}

// Remove Folder from directory
bool dac_remove_folder_from_directory(std::vector<Folder> &dir_folders, const std::string name){
    for(int i = 0; i < dir_folders.size(); ++i){

        if(dir_folders[i].folder_name.compare(name) == 0){

            dir_folders.erase(dir_folders.begin()+i);

            return true;
        }
    }

    return false;
}   

// Remove Folder
bool dac_operation_rmdir(std::map <int, std::map < std::string, Directory_content>> &data, Directory_content &current_dir, const std::string name, const int current_folder_i){
   for(auto i_it : data){
        if(i_it.first == current_folder_i){

            for(auto j_it : i_it.second){

                if(j_it.first.compare(current_dir.dir_name) == 0){

                    if(dac_remove_folder_from_directory(j_it.second.folders, name)){
                        
                        data[current_folder_i][current_dir.dir_name] = j_it.second;
                        dac_remove_folder_from_directory(current_dir.folders, name);
                        remove_directory_content(data[current_folder_i + 1][name]);
                        
                        std::cout << "\nFolder " << name << " is removed from " << j_it.second.dir_name << " Directory !\n";
                        return true;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }

   std::cout << "\nFile " << name << " is not found in " << current_dir.dir_name << " folder ! Please try again.\n";
   return false; 
}

// Show Current place (path)
void dac_operation_pwd(const std::string path){
    std::cout << "\n||  " << path << " <- You_are_here.\n";
}

// Show information
void dac_operation_help(){

    std::cout << "\n<<<-------------------------------------------------------------------------------------------->>>\n";
    std::cout << "\nls - Show all content of the current folder" 
              << "\nmkdir - Create a folder__ Like: mkdir folder_name" 
              << "\ncd - Open folder (can use multiple path)__ Like: cd f1_name   or    cd f1_name/f2_name/f3_name" 
              << "\ntouch - Create a file__ Like: touch file_name.txt"
              << "\nrm - Remove a file__ Like: rm file_name.txt"
              << "\nrmdir - Remove a folder__ Like: rmdir folder_name"
              << "\ncd.. - Go the the previous folder"
              << "\npwd - Show the current place"
              << "\n/exit - Exit the Program\n";
    std::cout << "\n<<<-------------------------------------------------------------------------------------------->>>\n";
}


void div_and_com(){

    std::cout << "\n________PROGRAM STARTED________\n" << std::endl;

    // Creating space for folders and files
    std::map <int, std::map < std::string, Directory_content>> full_data;
    int current_folder_index = 0;

    // Curent path
    std::string current_path = "";

    // Command Line
    std::string line = "";

    // Creating starting Directory point
    Directory_content current_directory;
    current_directory.dir_name = "Root";
    current_directory.dir_prev_name = "Root";
    current_path += current_directory.dir_name;
    full_data[current_folder_index][current_directory.dir_name] = current_directory;

    // Creating previous Directory point
    Directory_content previous_directory;
    previous_directory = current_directory;

    // Program is over
    bool program_exit = false;

    while(!program_exit){

        do{

        dac_show_current_path(current_path);
        line = dac_write_command();
        }while(!dac_check_com_line(line));

        std::string com = "";
        std::string name = "";

        dac_seperate_left_right(line, com, name);
        
        if(name.compare("Root") == 0){
            std::cout << "\n";
        }
        else if(com.compare("ls") == 0){
            // ls
            std::cout << "\n<<<-------------------------------------------------------------------------------------------->>>\n";
            dac_operation_ls(current_directory, current_path);
            std::cout << "\n\n<<<-------------------------------------------------------------------------------------------->>>\n";
        }
        else if(com.compare("mkdir") == 0){
            // mkdir
            if(!(dac_folder_exists(current_directory, name))){
                dac_operation_mkdir(full_data, current_directory, name, current_folder_index);
            }
            else{
                std::cout << "\nThe new_Folder " << name << " is already exists in " << current_directory.dir_name << " Folder ! Can't do the operation.\n";
            }
        }
        else if(com.compare("cd") == 0){
            // cd (multi folders)
            dac_operation_cd_multi(full_data, current_directory, previous_directory, name, current_folder_index, current_path);
        }
        else if(com.compare("touch") == 0){
            // touch
            if(!(dac_file_exists(current_directory, name))){
                dac_operation_touch(full_data, current_directory, name, current_folder_index);
            }
            else{
                std::cout << "\nThe File " << name << " is already exists in " << current_directory.dir_name << " Folder ! Can't do the operation.\n";
            }
        }
        else if(com.compare("rm") == 0){
            // rm
            if(dac_file_exists(current_directory, name)){
                dac_operation_rm(full_data, current_directory, name, current_folder_index);
            }
            else{
                std::cout << "\nThe File " << name << " doesn't exist in " << current_directory.dir_name << " Folder ! Can't do the operation.\n";
            }
        }
        else if(com.compare("rmdir") == 0){
            // rmdir
            if(dac_folder_exists(current_directory, name)){
                dac_operation_rmdir(full_data, current_directory, name, current_folder_index);
            }
            else{
                std::cout << "\nThe File " << name << " doesn't exist in " << current_directory.dir_name << " Folder ! Can't do the operation.\n";
            }
        }
        else if(com.compare("cd..") == 0){
            // cd..
            dac_operation_cd_dot_dot(full_data, current_directory, previous_directory, current_folder_index, current_path);
        }
        else if(com.compare("pwd") == 0){
            dac_operation_pwd(current_path);
        }
        else if(com.compare("/help") == 0){
            // /help
            dac_operation_help();
        }
        else if(com.compare("/exit") == 0){
            program_exit = true;
            std::cout << "\n\nThe Program is closed !\n";
        }


    }

}

#endif
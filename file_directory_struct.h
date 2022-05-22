#ifndef FILE_DIRECTORY_STRUCT_H
#define FILE_DIRECTORY_STRUCT_H

#include <string>
#include <map>
#include <vector>

struct File{
    std::string file_name = "";
};

struct Folder{
    std::string folder_name = "";
};

struct Directory_content{
    std::string dir_name = "";
    std::string dir_prev_name = "";
    std::vector <File> files;
    std::vector <Folder> folders;
};

File create_file(std::string name){
    File file;
    file.file_name = name;
    return file;
}

Folder create_folder(std::string name){
    Folder folder;
    folder.folder_name = name;
    return folder;
}

void insert_file_to_directory(Directory_content &dir_content, const File file){
    dir_content.files.push_back(file);
}

void insert_folder_to_directory(Directory_content &dir_content, const Folder folder){
    dir_content.folders.push_back(folder);
}

void directory_swap(Directory_content &dir1, Directory_content &dir2){
    
    Directory_content temp = dir1;
    dir1 = dir2;
    dir2 = temp;
}

void remove_directory_content(Directory_content &dir){
    dir.dir_name = "";
    dir.dir_prev_name = "";
    dir.files.clear();
    dir.folders.clear();
}

#endif

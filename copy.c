#include <errno.h>
#include <pwd.h>
#include "copy.h"

outcome copy(char* from, char* to, bool withDir)
{
    if (to == NULL) {
        char tto[FILENAME_MAX];
            const char *homedir;
            if ((homedir = getenv("HOME")) == NULL) {
                homedir = getpwuid(getuid())->pw_dir;
            }
            strcpy(tto, homedir);
            strcat(tto, "/saves/");
            if ("withDir") {
                strcat(tto, basename(from));
            }
        bool is_file = true;
        for (int i = 0; i < strlen(from); ++i) {
            if (from[i] == '/') {
                is_file = false;
                break;
            }
        }
        if (is_file)
            return copyFiles(from, to);
        return copyDir(from, tto, withDir);
    }
    bool from_file = true;
    for (int i = 0; i < strlen(from); ++i) {
        if (from[i] == '/') {
            from_file = false;
            break;
        }
    }
    bool to_file = true;
    for (int i = 0; i < strlen(to); ++i) {
        if (to[i] == '/') {
            to_file = false;
            break;
        }
    }
    if (from_file == false && to_file == true)
        return error("COPY DIR TO FILE", "", DIR_TO_FILE);
    
    if ((from_file == true && to_file == true) || (from_file == true && to_file == false))
        return copyFiles(from, to);
    char tto[FILENAME_MAX];
    strcpy(tto, to);
    strcat(tto, "/");
    if (withDir) {
        strcat(tto, basename(from));
    }
    return copyDir(from, tto, withDir);
}

outcome copyDir(char* from, char* to, bool withDir)
{
    DIR* dir_ptr = NULL;
    struct dirent *dirent_ptr;
    char tempTo[FILENAME_MAX];
    char tempFrom[FILENAME_MAX];
    if( (dir_ptr = opendir(from)) == NULL ) {
        fprintf(stderr, "CANNOT OPEN %s FOR COPYING\n", from);
        return DIR_UNAVAILABLE;
    }
    if (withDir) {
        if (mkdir(to, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
            printf("Error: %s\n", strerror(errno));
            return FAIL;
        }
    }
    
    struct stat fileinfo;
    while((dirent_ptr = readdir(dir_ptr))) {
        if (!strcmp(dirent_ptr->d_name, ".") || !strcmp(dirent_ptr->d_name, ".."))
            continue;
        outcome result = SUCCES;
        strcpy(tempTo, to);
        strcpy(tempFrom, from);
        strcat(tempTo, "/");
        strcat(tempFrom, "/");
        strcat(tempTo, dirent_ptr->d_name);
        strcat(tempFrom, dirent_ptr->d_name);
        if(stat(tempFrom, &fileinfo))
            return FAIL;
        if (S_ISREG(fileinfo.st_mode))
            result = copyFiles(tempFrom, tempTo);
        else if (S_ISDIR(fileinfo.st_mode))
            result = copyDir(tempFrom, tempTo, true);
        if (result != SUCCES)
            return result;
    }
    closedir(dir_ptr);
    return SUCCES;
}

outcome copyFiles(char* from, char* to)
{
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];
    //open file
    if ((in_fd=open(from, O_RDONLY)) == -1)
        return error("CANNOT OPEN", from, FILE_OPEN);
    if ((out_fd=creat(to, COPYMODE)) == -1)
        return error("CANNOT CREATE", to, FILE_CREATE);
    //copy
    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
        if (write(out_fd, buf, n_chars) != n_chars)
            return error("CANNOT WRITE TO", to, FILE_WRITE);
        if (n_chars == -1)
            return error("CANNOT READ FROM", from, FILE_READ);
    }
    if (close(in_fd) == -1 || close(out_fd) == -1)
        return error("ERROR CLOSING FILES", "", FILE_CLOSE);
    return SUCCES;
}

outcome error(char* text, char* file, int code)
{
    fprintf(stderr, "ERROR: %s %s\n", text, file);
    return code;
}

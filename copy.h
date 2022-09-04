#ifndef COPY_H
#define COPY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>

#define DEFAULT_LOCATION "~/saves"
#define BUFFERSIZE 1024
#define COPYMODE 0644
#define DIRMODE 0700
#define bool int
#define true 1
#define false 0
//RETURNS
#define outcome int
#define SUCCES 0
#define FAIL -1
#define DIR_TO_FILE 1
#define DIR_UNAVAILABLE 2
#define FILE_OPEN 3
#define FILE_CLOSE 4
#define FILE_READ 5
#define FILE_WRITE 6
#define FILE_CREATE 7
#define WRONG_SYNTAX 9
#define NOT_READY 10

outcome copy(char* from, char* to, bool withDir);
outcome copyDir(char* from, char* to, bool withDir);
outcome copyFiles(char* from, char* to);
outcome error(char* text, char* file, outcome code);

#endif

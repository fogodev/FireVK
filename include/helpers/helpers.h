/*************************************************************\
|-------------------------------------------------------------|
|         Created by Ericson "Fogo" Soares on 27/03/17        |
|-------------------------------------------------------------|
|                 https://github.com/fogodev                  |
|-------------------------------------------------------------|
\*************************************************************/

#ifndef FIREVK_HELPERS_H
#define FIREVK_HELPERS_H

#include <stdlib.h>
#include <stdio.h>

#define CHECK_PTR(PTR, MESSAGE) \
    if(!PTR) { \
        fprintf(stderr, "Unable to allocate memory for: %s\n", MESSAGE); \
        exit(1); \
    }

#define CHECK_FILE_PTR(FILEPTR, FILENAME) \
    if(!FILEPTR){ \
        fprintf(stderr, "Couldn't open %s file.\n", FILENAME); \
        exit(1); \
    }
#endif //FIREVK_HELPERS_H

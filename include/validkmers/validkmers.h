/*************************************************************\
|-------------------------------------------------------------|
|         Created by Ericson "Fogo" Soares on 27/03/17        |
|-------------------------------------------------------------|
|                 https://github.com/fogodev                  |
|-------------------------------------------------------------|
\*************************************************************/

#ifndef FIREVK_KMERVALIDATOR_H
#define FIREVK_KMERVALIDATOR_H

#include <stdlib.h>
#include <string.h>
#include "../helpers/helpers.h"

#define Kmer unsigned
#define LongKmer unsigned long long

typedef struct
{
    char* importFilename;
    char* exportFilename;
    size_t kmerSize;
    size_t kmersCount;
    Kmer* kmers;
    LongKmer* longKmers;
} ValidKmers;

ValidKmers* createValidKmers(char* importFilename);
void destroyValidKmers(ValidKmers* validKmers);

void readKmers(ValidKmers* validKmers);
void writeKmers(ValidKmers* validKmers);

#endif //FIREVK_KMERVALIDATOR_H

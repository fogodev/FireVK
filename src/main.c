/*************************************************************\
|-------------------------------------------------------------|
|         Created by Ericson "Fogo" Soares on 27/03/17        |
|-------------------------------------------------------------|
|                 https://github.com/fogodev                  |
|-------------------------------------------------------------|
\*************************************************************/

#include <stdio.h>
#include "../include/radixmp/radixmp.h"
#include "../include/validkmers/validkmers.h"

int main(int argc, char** argv)
{
    if(argc < 2){
        fprintf(stderr, "Usage %s filename.kmer\n", argv[0]);
        exit(1);
    }
    
    ValidKmers* validKmers = createValidKmers(argv[1]);
    
    readKmers(validKmers);
    
    if(!validKmers->kmers)
        ompLsdRadixSort64bits(validKmers->kmersCount, validKmers->longKmers, 4);
    else
        ompLsdRadixSort32bits(validKmers->kmersCount, validKmers->kmers, 4);
    
    writeKmers(validKmers);
    
    destroyValidKmers(validKmers);
    return 0;
}
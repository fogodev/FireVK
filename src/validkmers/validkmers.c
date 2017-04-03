/*************************************************************\
|-------------------------------------------------------------|
|         Created by Ericson "Fogo" Soares on 27/03/17        |
|-------------------------------------------------------------|
|                 https://github.com/fogodev                  |
|-------------------------------------------------------------|
\*************************************************************/

#include "../../include/validkmers/validkmers.h"

/********************
 * Bases encode:    *
 * A = 00;          *
 * C = 01;          *
 * G = 10;          *
 * T = 11           *
 ********************/
#define KMERS_ENCODE(KMERS, KMERS_SIZE, KMERS_COUNT, KMERS_FILEPTR)                                                     \
    char* currentTextKmer = malloc(KMERS_SIZE * sizeof(char));                                                          \
    CHECK_PTR(currentTextKmer, "Kmers read buffer");                                                                    \
    for(size_t kmerIndex = 0; kmerIndex != KMERS_COUNT; ++kmerIndex){                                                   \
        fgets(currentTextKmer, KMERS_SIZE + 1, KMERS_FILEPTR); /* Adding 1 because of terminating \0 */                 \
        fgetc(KMERS_FILEPTR); /* Getting rid of ending \n */                                                            \
        for(size_t base = 0; base != KMERS_SIZE; ++base){                                                               \
            KMERS[kmerIndex] <<= 2;                                                                                     \
            switch(currentTextKmer[base]){                                                                              \
                case 'A': case 'a':                                                                                     \
                    KMERS[kmerIndex] |= 0b00;                                                                           \
                    break;                                                                                              \
                case 'C': case 'c':                                                                                     \
                    KMERS[kmerIndex] |= 0b01;                                                                           \
                    break;                                                                                              \
                case 'G': case 'g':                                                                                     \
                    KMERS[kmerIndex] |= 0b10;                                                                           \
                    break;                                                                                              \
                case 'T': case 't':                                                                                     \
                    KMERS[kmerIndex] |= 0b11;                                                                           \
                    break;                                                                                              \
                default:                                                                                                \
                    fprintf(stderr, "Kmer file with invalid base %c on kmer #%lu\n", currentTextKmer[base], kmerIndex); \
                    exit(1);                                                                                            \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \
    free(currentTextKmer);

ValidKmers* createValidKmers(char* importFilename)
{
    ValidKmers* validKmers = malloc(sizeof(ValidKmers));
    CHECK_PTR(validKmers, "ValidKmers");
    
    size_t importFilenameSize = strlen(importFilename);
    
    // importFilename = "filename.kmer"
    validKmers->importFilename = malloc(sizeof(char) * importFilenameSize + 1); // Including terminating \0 by adding 1
    CHECK_PTR(validKmers->importFilename, "Import filename");
    
    strcpy(validKmers->importFilename, importFilename);
    
    // exportFilename = "filename.kbn"
    validKmers->exportFilename = malloc(sizeof(char) * importFilenameSize); // Export filename have 1 less char than import
    CHECK_PTR(validKmers->exportFilename, "Export filename");
    
    memcpy(validKmers->exportFilename, importFilename, importFilenameSize - 5);
    memcpy(validKmers->exportFilename + importFilenameSize - 5, ".kbn", 5);
    
    // Initializing other attributes
    validKmers->kmersCount = 0;
    validKmers->kmerSize = 0;
    validKmers->kmers = NULL;
    validKmers->longKmers = NULL;
    
    return validKmers;
}

void destroyValidKmers(ValidKmers* validKmers)
{
    free(validKmers->importFilename);
    free(validKmers->exportFilename);
    free(validKmers->kmers);
    free(validKmers->longKmers);
    free(validKmers);
}

void readKmers(ValidKmers* validKmers)
{
    FILE* kmersFile = fopen(validKmers->importFilename, "r");
    CHECK_FILE_PTR(kmersFile, validKmers->importFilename);
    
    /**********************************************************
     * KmerFile Example: First Line -> Kmer size, kmers count *
     * 14 5128172                                             *
     * CGAGCGTTCACGCG                                         *
     * ACATATCTGTGTCT                                         *
     * ACTGTCCGCATTTC                                         *
     * ACACTCTTAGCCAA                                         *
     * ...                                                    *
     **********************************************************/
    
    fscanf(kmersFile, "%lu %lu", &validKmers->kmerSize, &validKmers->kmersCount);
    fgetc(kmersFile); // Getting rid of ending \n on first line

    // Normal sized kmers, from 1 to 16
    if (validKmers->kmerSize <= 16) {
        validKmers->kmers = calloc(validKmers->kmersCount, sizeof(Kmer));
        CHECK_PTR(validKmers->kmers, "Kmers memory block");
        KMERS_ENCODE(validKmers->kmers, validKmers->kmerSize, validKmers->kmersCount, kmersFile);
    } else if (validKmers->kmerSize <= 32) { // Long sized kmers, from 17 to 32
        validKmers->longKmers = calloc(validKmers->kmersCount, sizeof(LongKmer));
        CHECK_PTR(validKmers->longKmers, "Long Kmers memory block");
        KMERS_ENCODE(validKmers->longKmers, validKmers->kmerSize, validKmers->kmersCount, kmersFile);
    } else { // Invalid size
        perror("Invalid Kmers Size, supported values from 0 to 32");
        exit(1);
    }
    fclose(kmersFile);
}

void writeKmers(ValidKmers* validKmers)
{
    FILE* kmerExportFile = fopen(validKmers->exportFilename, "w");
    CHECK_FILE_PTR(kmerExportFile, validKmers->exportFilename);
    
    fwrite(&validKmers->kmerSize, sizeof(size_t), 1, kmerExportFile);
    fwrite(&validKmers->kmersCount, sizeof(size_t), 1, kmerExportFile);
    
    if(!validKmers->kmers){
        fwrite(validKmers->longKmers, validKmers->kmersCount * sizeof(LongKmer), 1, kmerExportFile);
    } else {
        fwrite(validKmers->kmers, validKmers->kmersCount * sizeof(Kmer), 1, kmerExportFile);
    }
    
    fclose(kmerExportFile);
}





#include <iostream>
#include <ctype.h>
#include <fstream>
#include "dictionary.h"
#include <cstring>
#include <stdlib.h>

// default dictionary
#define DICTIONARY "./wordslist.txt"

using namespace std;

class FileLoader{
    fstream f,tobj;
    char filename[100];
    char replace[LENGTH+1];
    char filefolder[100];
    HashTable table;
  public:
    FileLoader();
    FileLoader(char * filepath,const char* dfname = DICTIONARY);
    void load();
    void write2new(const char *word);
    void writeChar(char c);
    int isCorrect(char *word);
    void save();
    const char * correct(char *word);
    ~FileLoader();
};

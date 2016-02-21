/****************************************************************************
 * Spellcheck.cpp
 *
 * Object Oriented Programming Course Project
 *
 * Implements a spell-checker.
 ***************************************************************************/

#include <iostream>
#include "fileloader.h"
#include <fstream>
using namespace std;


int main(int argc, char* argv[])
{
    FileLoader *f;

    if (argc != 2 && argc != 3)
    {
        cout<<"Usage: ./spellcheck [dictionary] text\n";
        return 1;
    }
    f = (argc==3)? new FileLoader(argv[2],argv[1]) : new FileLoader(argv[1]);
    f->load();
    f->save();
    return 0;
}

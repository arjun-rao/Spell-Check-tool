


#include <iostream>
#include <ctype.h>
#include <fstream>
#include <cstring>
#include <stdbool.h>


using namespace std;
#define HASH 8000
#define LENGTH 47
struct node
{
  char word[LENGTH+1];
  node* link;
};

class HashTable
{
    	public:


    	node* table[HASH];

    	unsigned long hash(char *str);



    bool check( char *word);


    /**
     * Loads dictionary into memory.  Returns true if successful else false.
     */
    bool load(const char* dictionary);

    /**
     * Unloads dictionary from memory.  Returns true if successful else false.
     */
    bool unload(void);

};

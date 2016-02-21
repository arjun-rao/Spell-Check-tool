#include "dictionary.h"

unsigned long HashTable::hash(char *str)
{
  unsigned long hash = 5381;
  int c;

 while ((c = *str++))
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}


bool HashTable::check( char *word)
{
   int found=0;
   node* tableword;
   char tempw[LENGTH+1];
   strcpy(tempw,word);
   for(int i=0;tempw[i]!='\0';i++) tempw[i] = tolower(tempw[i]);
   //cout<<"Checking word: "<<tempw<<endl;
   int hashval = hash(tempw)%8000;
   tableword=table[hashval];

   //cout<<"Checking hash key: "<<hashval<<" Word "<<table[hashval]->word<<endl;
   while(tableword!=NULL)
    {
      //cout<<"Checking with: "<<tableword->word<<endl;
        if(strcmp(tempw,tableword->word)==0)
        {
          found=1;
          break;
        }
        tableword=tableword->link;
    }
     if(found==1)
        return true;
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool HashTable::load(const char* dictionary)
{
  char readword[LENGTH + 1];
  int count=0;
  for(int i=0;i<8000;i++)
    table[i]=NULL;
  int key=0;
  fstream fp(dictionary,ios::in);
  if(!fp.good())
  {
    printf("cannot be loaded \n ");
    return false;
  }

  while(fp.getline(readword,LENGTH))
  {
    key=0;
    node* temp2 = new node;
    strcpy(temp2->word,readword);
    temp2->link=NULL;
    key=hash(temp2->word)%8000;
    //cout<<"\nRead Word: "<<temp2->word<<endl;
    if(table[key]==NULL)
    {
      table[key]=temp2;
      count++;
    }
    else
    {
      temp2->link=table[key];
      table[key]=temp2;
      count++;
    }
    //cout<<"Hashtable word: "<<table[key]->word<<" key: "<<key<<endl;
  }
  cout<<"Dictionary has: "<<count<<" Words!"<<endl;
  return true;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool HashTable::unload(void)
{
    node* prev=NULL,*cur=NULL;
    for(int i=0;i<HASH;i++)
    {
        prev=table[i];
        while(prev!=NULL)
        {
            cur=prev;
            prev=prev->link;
            delete cur;

        }
    }
return true ;
}

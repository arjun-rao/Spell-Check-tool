/****************************************************************************
 * Fileloader.cpp
 *
 * Object Oriented Programming Course Project
 *
 * Reads given file and loads words to spell check.
 ***************************************************************************/


#include "fileloader.h"

/**
 * Constructor to load given file into file object
 */
FileLoader::FileLoader(char *fname,const char *dfname)
{
    strcpy(filename,fname);
    f.open(filename,ios::out|ios::in);
    table.load(dfname);
    tobj.open("temp.txt",ios::out);
    tobj.close();
    cout<<"Checking spellings in "<<filename<<endl;
}

void FileLoader::save()
{
  char choice,tchar;

  cout<<"\nWould you like to replace "<<filename<<" with the changes made?(y/n): ";
  cin>>choice;
  choice= tolower(choice);
  if(choice == 'y')
  {
    f.close();
    tobj.open("temp.txt",ios::in);
    f.open(filename,ios::out);
    for(tobj.get(tchar);tobj.good();tobj.get(tchar))
    {
      f<<tchar;
    }
    f.close();
    tobj.close();
    cout<<"\nChanges successfully saved to: "<<filename<<endl;
  }
  else{
    char newfile[100];
    cout<<"\nEnter new file name to save changes to (0 to discard changes): ";
    cin>>newfile;
    if(strcmp(newfile,"0")!=0)
    {
      f.close();
      f.open(newfile,ios::out);
      tobj.open("temp.txt",ios::in);
      for(tobj.get(tchar);tobj.good();tobj.get(tchar))
      {
        f<<tchar;
      }
      f.close();
      tobj.close();
      cout<<"\nChanges successfully saved to: "<<newfile<<endl;
    }
    else{
      cout<<"\nChanges not saved!\n";
    }
  }
  remove("temp.txt");

}


void FileLoader::writeChar(char c)
{
  tobj.open("temp.txt",ios::out|ios::app);
  tobj<<c;
  tobj.close();
}


/**
 * Function to read words from the file and check for missellings
 */
void FileLoader::load()
{
  //cout<<"Reached!\n";
    if (!f.good())
    {
        cout<<"Could not open "<<filename;
        return;
    }



    // prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH +1];
    char c;
    // spell-check each word in text
    for (f.get(c);f.good();f.get(c))
    {

        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            word[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
              for(int i=0;i<index;i++)
              writeChar(word[i]);
                // consume remainder of alphabetical string
                while ((c = f.get())&& f.good() && isalpha(c))
                {

                  writeChar(c);
                }

                // prepare for new word
                index = 0;
            }
        }

        // ignore words with numbers
        else if (isdigit(c))
        {
            for(int i=0;i<index;i++)
            writeChar(word[i]);
            writeChar(c);
            // consume remainder of alphanumeric string
            while ((f.get(c)) && f.good() && isalnum(c))
            {
              writeChar(c);
            }

            // prepare for new word
            index = 0;
        }

        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';

            // update counter
            words++;

            // check word's spelling
            //cout<<word<<endl;
            //write2new(word);
            if(!isCorrect(word))
            {
              //cout<<"Incorrect!";
            	write2new(correct(word));
            }
            else
            {
              write2new(word);
            }

            // prepare for next word

            index = 0;
        }


        if(!isalpha(c))
        {
          writeChar(c);
          index = 0;

        }
    }

    // check whether there was an error
    if (!f.eof() && !f.fail())
    {
        f.close();
        printf("Error reading %s.\n", filename);
        return ;
    }
    cout<<"\nSpell check complete!\n";
}

/**
 *  @params - word -
 *  Writes given word to tempfile;
 *
 */

 void FileLoader::write2new(const char *word)
 {
    tobj.open("temp.txt",ios::out|ios::app);
    tobj<<word;
    tobj.close();
 }
/**
 *  @params - word - string to check if spelt incorrectly
 *  returns 1 if spelling is correct else returns 0
 *
 */
int FileLoader::isCorrect(char *word)
{
  if(table.check(word))
    return 1;
  else
	 return 0;
}

/**
 * @params word to use for lenghth to correct
 * Corrects incorrect word using seekg and fstream object f
 */
const char * FileLoader::correct(char *word)
{
    char ch;
  	//cout<<endl<<word;
  	cout<<"\nDo you want to replace \'"<<word<<"\' (Y): ";
  	cin>>ch;
  	if(ch=='Y'||ch=='y')
  	{
  		cout<<"\nEnter word: ";
  		cin>>replace;
  		return replace;
  	}
  	cout<<"\nWord not replaced.\n";
  	return word;
}




/**
 * Destructor to close the file at the end.
 */

FileLoader:: ~FileLoader()
{
    table.unload();
    tobj.close();
    f.close();

}

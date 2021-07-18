#include <stdio.h>
#include <string.h>

int sentence_count = 0;
int word_count = 0;
int avg_word_in_sentence = 0;

void tokenize_to_words (char * str ) //get all the words in a sentence with strtok
{
    char * pch;
    char temp_str[2000];  //create a string to hold a copy 
    strcpy(temp_str, str);//copy string
   
    pch = strtok (temp_str," ,:-;"); //tokenize the first word
    while (pch != NULL)//loop until a null pointer is hit
    {
        pch = strtok (NULL, " ,:-;");//tokenize the rest of the words
        word_count++;       //increase the word word count
    }
    return;
}

char * tokenize_to_sentence (char * str ) //tokenize into sentences
{
    char * pch;
    int i;
    char temp_str[10000], temp_sentence[1000][1000]; //create a string to hold a copy
  
    strcpy(temp_str, str);    //copy the string into temp_str
    pch = strtok (temp_str,".");  //tokenize the first sentence

    while (pch != NULL) //loop until a null pointer is hit
    {
        strcpy(&(temp_sentence[sentence_count][0]), pch); //copy otherwise the strings will be forgotten and null pointers wil be written over
        pch = strtok (NULL, ".");
        sentence_count++; //increase sentence count
    }

   for (i = 0; i < sentence_count; i++)//now call to tokenize sentences into words
   {
       tokenize_to_words(&(temp_sentence[i][0]));
   }

    return pch;
}

void getAverage( )//gets the average number of words in a sentence 
{
    avg_word_in_sentence = word_count/sentence_count;
    return;
}

int main ()
{
  char str[] ="We hold these truths to be self-evident, that all men are created equal, that they are endowed, by their Creator, with certain unalienable Rights, that among these are Life, Liberty, and the pursuit of Happiness. That to secure these rights, Governments are instituted among Men, deriving their just powers from the consent of the governed, That whenever any Form of Government becomes destructive of these ends, it is the Right of the People to alter or abolish it, and to institute new Government, laying its foundation on such principles, and organizing its powers in such form, as to them shall seem most likely to effect their Safety and Happiness. Prudence, indeed, will dictate that Governments long established should not be changed for light and transient causes; and accordingly all experience hath shewn, that mankind are more disposed to suffer, while evils are sufferable, than to right themselves by abolishing the forms to which they are accustomed. But when a long train of abuses and usurpations, pursuing invariably the same Object, evinces a design to reduce them under absolute Despotism, it is their right, it is their duty, to throw off such Government, and to provide new Guards for their future security.";
  char * pch;
  pch = tokenize_to_sentence(str);
  getAverage();
  printf ("\nAverage number of words per sentence is: %d\n",avg_word_in_sentence);
  printf ("\nThe sentence count %d\n",sentence_count);
  return 0;
}
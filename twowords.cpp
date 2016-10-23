// Author 1: Davy_Huang davyh@bu.edu


#include <fstream>  //Used for taking inputs and files
#include <string>   //used for strings
#include <vector>   //used for vectors and vectors of strings
#include <iostream> //general inputs
#include <stdlib.h> //string conversion to int
#include <algorithm>//sorting vectors
using namespace std;

void SubStrSorted(  string &lettercollection,   vector<string> &vectSortWord1,vector<string> &lettercollectionShort    ){
    string tempstr;                                     //  declares a temp. string to hold the complete lettercollection
    for(int i=0; i<vectSortWord1.size(); i++){          //  i is the string in the vector
    tempstr=lettercollection;                           //  reassigns the temp. string
        for(int j=0; j<vectSortWord1[i].size(); j++){   //  j is the location of the letter in the string in the vector
            for(int k=0; k<tempstr.size(); k++){        //  iterates through k the location of the tempstr
                if(vectSortWord1[i][j]==tempstr[k]){    //  if the letter matches then it is removed
                    tempstr.erase(k,1);
                    break;                              //  uses a BREAK to ensure only 1 letter was deleted
                }
            }
        }
    lettercollectionShort.push_back(tempstr);           //  Assigns the subtracted string to a vector
    }
}

void loadbylines(string &txtfile, vector<string> &vectWord1, vector<string> &vectWord2, int &word1Len, int &word2Len,vector<string> &vectSortWord1, vector<string> &vectSortWord2, string &lettercollection){
/*
*Take the input file name(including the .txt and assuming it is in the same directory), and the address of 4 vectors, and length
*Saves potential words and a sorted copy to each vector using pass by reference
*/
string linestring, lineSortstring;          //  declares strings for the loaded word and a sorted copy

ifstream thefile;                           //  declare variable for file

thefile.open(txtfile);                      //  opens the file

while(getline(thefile,linestring)){         //  loads the file by lines

    if( linestring.size()==word1Len   ){    //  only considers the words as potential word if it is the right length of word 1
        lineSortstring=linestring;
        sort(   lineSortstring.begin(),lineSortstring.end() );      //  makes a sorted copy
        if( includes(lettercollection.begin(),lettercollection.end(), lineSortstring.begin(),lineSortstring.end())  ){  //only considers the word as potential word if it could be made from the letter collection
            vectWord1.push_back(linestring);            //  assigns potential word
            vectSortWord1.push_back(lineSortstring);    //  assigns sorted potential word
        }   //  DONE IN 2 IF STATEMENTS TO AVOID CREATING A SORTED COPY IF THE WORD IS ALREADY RULED OUT BY THE LENGTH
    }       //  THIS SAVES A SIGNIFICANT AMOUNT OF TIME

    else if(    (linestring.size()==word2Len)   &&  (word1Len!=word2Len)    ){
        lineSortstring=linestring;
        sort(   lineSortstring.begin(),lineSortstring.end() );
        if(includes(lettercollection.begin(),lettercollection.end(), lineSortstring.begin(),lineSortstring.end())){
            vectWord2.push_back(linestring);
            vectSortWord2.push_back(lineSortstring);
        }   //  POTENTIAL WORD OF THE OTHER LENGHT SAVED IN THIS CONDITION
    }       //  EXCEPT IF THE WORDS ARE THE SAME LENGHT, IN THAT CASE ALL THE CONTENT NEEDED IS IN THE SECOND VECTOR

}

thefile.close();                    //  closes the file

}


int main(int argc, char** argv) {
                                        //  argc is the number of argument +1 passed to argv
                                        //  the file name saved for the [0] position so it will be 1 with no input
string wordfile,lettercollection;       //  declares strings for the .txt and letter collection
int word1Len, word2Len;                 //  declares integers for the length of words
if (argc==1){                           //  condition for no input. Set DEFAULTS.
    wordfile="wordlist.txt";
    lettercollection="aadekmmnortww";
    word1Len=7;
    word2Len=lettercollection.size()-word1Len;
    sort(lettercollection.begin(),lettercollection.end());
}
else if(argc==4){                       //  condition for 3 inputs

    wordfile=argv[1];                   //  no need to check, if the file does not exist, the program exits anyway

    int i=0;
    while (argv[2][i]){                 //  checks if the letter collection is all characters. Loops through each character
        if (!isalpha(argv[2][i])){
            return 0;                   //  exits if it is not
        }
    i++;
    }
    lettercollection=argv[2];           //  assigns it if it is
    sort(lettercollection.begin(),lettercollection.end());          //sorts the letters
    i=0;
    while (argv[3][i]){                 //  checks if the word length is a number. Loops through each 'character'
        if (!isdigit(argv[3][i])){
            return 0;
        }
        i++;
    }
    word1Len=atoi(argv[3]);                     //  assigns it if it is
    word2Len=lettercollection.size()-word1Len;                     //  assigns the length of the other word

}
else{                                   // ends the program if number of inputs is wrong
    return 0;
}

vector<string> vectWord1, vectWord2,vectSortWord1, vectSortWord2,lettercollectionShort,vectprint;               //  Declares vector of strings for the potential words and associated sorted version
                                                                                                                //  Also declares the letter collection subset and vector of strings to print
loadbylines(wordfile, vectWord1, vectWord2, word1Len, word2Len,vectSortWord1, vectSortWord2,lettercollection);          //  loads the words into the vectors
                                                                                                                        //  GOAL IS TO MINIMIZE POTENTIAL WORDS
SubStrSorted(lettercollection,vectSortWord1,lettercollectionShort);             //  creates a sub vector<string> of the non used letters correspond to a potential word
                                                                                //  lettercollectionShort=lettercollection-vectSortWord1

if (word1Len!=word2Len){                                                        //  condition for different length
    for(int i=0; i<vectSortWord1.size(); i++){
        for(int j=0; j<vectSortWord2.size(); j++){
            if( lettercollectionShort[i]==vectSortWord2[j]  ){                  //  if the sorted second words is the same as the remaining letters when subtracting the first word, then it can be made
                vectprint.push_back(    vectWord1[i] + " " + vectWord2[j]+ "\n" );      //assigns that string to a vector. BREAK is not needed so all anagrams can be included
            }
        }
    }
}

else{                                                                           //  condition for same length
    for(int i=0; i<vectSortWord1.size(); i++){
        for(int j=i; j<vectSortWord1.size(); j++){                              //  j=i is used to skip previous checked combinations
            if( lettercollectionShort[i]==vectSortWord1[j]  ){
                if( vectWord1[i]<vectWord1[j]){                                 //  checks for alphabetical order
                    vectprint.push_back(    vectWord1[i] + " " + vectWord1[j]+ "\n" );
                }
                else{
                    vectprint.push_back(    vectWord1[j] + " " + vectWord1[i]+ "\n" );
                }
            }
        }
    }
}

if(vectprint.empty()){                                                      //  double checks if combinations exist
    return 0;
}
sort(vectprint.begin(), vectprint.end());                                   //  sorts the vectors to be printed.
                                                                            //  sorting AFTER checking the potentials means the list is shorter
for (vector<string>::iterator it=vectprint.begin(); it!=vectprint.end(); ++it){
    cout << *it;                                                            //  Prints the answers using iterators
}
return 0;
}




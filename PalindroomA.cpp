#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

void reverse(string  & word){
    cout << word;
    unsigned int laatste_letter = word.size() - 1;
    for(unsigned i = 0; i < laatste_letter; i++){
        char temp_var = word[i];
        word[i] = word[laatste_letter];
        word[laatste_letter] = temp_var;
        laatste_letter -= 1;
    
    }
    cout << " is omgedraaid: " << word << '\n';
}
bool isPalindroom(const string& word){
  string orginalWord = word;
  reverse(orginalWord);
  for(unsigned int i=0; i<word.size(); i++){
    if(word[i] != orginalWord[i]){
      return false;
    }
  }
  return true;
}


int main(int argc, char **argv){
    vector<string> woordenlijst = {"stekkerdoos", "Halloween", "lepel", "flesje", "bommelding"};
    for(unsigned i = 0; i < woordenlijst.size(); i++){
        if(isPalindroom(woordenlijst[i])){
            cout << woordenlijst[i] << " is een palindroom. \n";
        }
        else{
            cout << woordenlijst[i] << " is geen palindroom. \n";
        }
        }
    }

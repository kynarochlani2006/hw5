#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  // Add your code here

  std::set<std::string> returnSet;

  // my base case
  if(in.find('-') == std::string::npos){
    bool usedFloating = true;
    for(size_t i = 0; i < floating.length(); i++){
      if(in.find(floating[i]) == std::string::npos){
        usedFloating = false;
        break;
      }
    }

    if(usedFloating == true && dict.find(in) != dict.end()){
      returnSet.insert(in);
    }

    return returnSet;
  }

  // recursive call to function

  int firstDash = in.find('-');


  for(int i = 0; i < 26; i++){
    char letter = 'a' + i;
    std::string newWord = in;
    newWord[firstDash] = letter;

    std::string newFloatingLetters = "";
    bool usedFloatingLetter = false;
    for(int j = 0; j < floating.length(); j++){
      if(floating[j] == letter && usedFloatingLetter == false){
        usedFloatingLetter = true;
      } else {
        newFloatingLetters += floating[j];
      }
    }

    int numDashesLeft = 0;
    for(size_t k = 0; k < newWord.length(); k++){
      if(newWord[k] == '-'){
        numDashesLeft++;
      }
    }

    if(newFloatingLetters.length() <= numDashesLeft){
      std::set<std::string> recursingWord = wordle(newWord, newFloatingLetters, dict);
      returnSet.insert(recursingWord.begin(), recursingWord.end());
    }

  }

  return returnSet;
}

// Define any helper functions here


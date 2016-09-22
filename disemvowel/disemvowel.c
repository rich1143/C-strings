#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "disemvowel.h"
#include <ctype.h>
#include <stdbool.h>

bool isvowel(char letter){
  if(tolower(letter) == 'a'){
    return true;
  } else if(tolower(letter) == 'e'){
    return true;
  } else if(tolower(letter) == 'i'){
    return true;
  } else if(tolower(letter) == 'o'){
    return true;
  } else if(tolower(letter) == 'u'){
    return true;
  } else{
    return false;
  } 
}


char* disemvowel(char* str) {

  unsigned int c;
  char* novowels;
  novowels = (char*) calloc(strlen(str)+1, sizeof(char));

  for (c = 0; c < strlen(str); ++c){

    if ( isalpha(str[c]) && !isvowel(str[c]) ){
      char cToStr[2];
      cToStr[0] = str[c];
      cToStr[1] = '\0';
      strcat( novowels, cToStr );
    }
  }
  return novowels;
}

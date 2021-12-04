#ifndef MISC_STRINGS_H
#define MISC_STRINGS_H

/*
* A string library I created for learning purposes.
* TODO: optimise this shit. Like, seriously.
*/

#include "mem.h"
#include <stdbool.h>

bool str_delim_check(char c, char* delims);

char* get_line(void) {
  /**
  * Gets a line of input from stdin and stores it in a string.
  * @return input the string that stores the line of input from stdin.
  */
  char* input = (char*)new_ptr(1,sizeof(char)); // initialize string
  char c = fgetc(stdin); // read first char
  int count = 0;
  while (c != '\n') {
    input = (char*)resize_ptr(input, (count+1)*sizeof(char)); // increase size by 1
    input[count] = c; // add char to string
    c = fgetc(stdin); // read next char
    count++;
  }
  input = (char*)resize_ptr(input, (count+1)*sizeof(char));
  input[count] = '\0';
  return input;
}

char* get_file_txt(FILE* fp, unsigned int* size) {
  /**
  * Gets all text data from a file and stores it in a string.
  * @param fp file pointer of file to be read (with read access).
  * @return output string that stores all data in file as text.
  */
  if (fp == NULL) { // file does not exist
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  // find number of chars in file
  unsigned int count = 0;
  while(fgetc(fp) != EOF) {
    count++;
  }
  count++;
  *size = count;
  fseek(fp, 0, SEEK_SET);
  char* text = (char*) new_ptr(count, sizeof(char));
  fgets(text,count,fp);
  text[count] = '\0';
  return text;
}

int get_int(void) {
  /**
  * Gets an integer value from stdin.
  * @return num an integer value parsed from stdin; equals zero if
  * the input cannot be parsed to an int.
  */
  char* input = get_line();
  printf("Input: %s\n", input);
  int num = strtol(input,NULL,10); // convert to decimal int
  free_ptr(input);
  return num;
}

double get_double(void) {
  /**
  * Gets a double value from stdin.
  * @return num an double value parsed from stdin; equals zero if
  * the input cannot be parsed to a double.
  */
  char* input = get_line();
  printf("Input: %s\n", input);
  double num = strtod(input,NULL); // convert to double
  free_ptr(input);
  return num;
}

char* str_new(char* str) {
  unsigned int size = strlen(str);
  char* output = (char*) new_ptr(1, size*sizeof(char));
  for (unsigned int i = 0; i <= size; i++) {
    output[i] = str[i];
  }
  return output;
}

void str_cpy(char* dest, char* source) {
  unsigned int src_size = strlen(source);
  if (src_size != strlen(dest)) { // sets size of destination string equal to source
    dest = (char*) resize_ptr(dest, src_size*sizeof(char));
  }
  for (unsigned int i = 0; i <= src_size; i++) {
    dest[i] = source[i];
  }
}

void str_null(char* str) {
  str = (char*) resize_ptr(str, sizeof(char));
  str[strlen(str)] = '\0';
}

char* str_cat_new(char* str_1, char* str_2) {
  unsigned int str_1_size = strlen(str_1);
  unsigned int str_2_size = strlen(str_2);
  char* holder = (char*) new_ptr(1, (str_1_size+str_2_size)*sizeof(char));
  unsigned int pos = 0;
  for (unsigned int i = 0; i < str_1_size; i++) {
    holder[pos] = str_1[i];
    pos++;
  }
  for (unsigned int i = 0; i <= str_2_size; i++) {
    holder[pos] = str_2[i];
    pos++;
  }
  return holder;
}

void str_cat(char* dest, char* source) {
  unsigned int size = strlen(dest);
  unsigned int src_size = strlen(source);
  dest = (char*) resize_ptr(dest, (size+src_size)*sizeof(char));
  for (unsigned int i = 0; i <= src_size; i++) {
    dest[i+size] = source[i];
  }
}

char* str_sub(char* str, unsigned int start, unsigned int end) {
  char* holder = str_new("");
  if (end > start) {
    holder = (char*) resize_ptr(holder, (end-start)*sizeof(char));
    for (unsigned int i = 0; i < (end-start); i++) {
      holder[i] = str[i+start];
    }
    holder[end-start] = '\0';
  }
  return holder;
}

char** str_split(char* str, char* del_string, unsigned int* size) {
  char* delims = str_new(del_string);
  char** pieces = (char**) new_ptr(1, sizeof(char*));
  unsigned int pieces_size = 0;
  unsigned int pos = 0;
  unsigned int start_char = 0;
  while (1) {
    if (str[pos] == '\0') {
      if (pieces_size == 0) {
        pieces[0] = str_new("");
      }
      else {
        pieces = (char**) resize_ptr(pieces, (pieces_size+1)*sizeof(char*));
        pieces[pieces_size] = str_sub(str, start_char, pos);
        pieces_size++;
        start_char = pos+1;
      }
      break;
    }
    if (str_delim_check(str[pos], delims)) {
      if (pieces_size == 0) {
        pieces[0] = str_sub(str, start_char, pos);
        pieces_size++;
        start_char = pos+1;
      }
      else {
        pieces = (char**) resize_ptr(pieces, (pieces_size+1)*sizeof(char*));
        pieces[pieces_size] = str_sub(str, start_char, pos);
        pieces_size++;
        start_char = pos+1;
      }
    }
    pos++;
  }
  free_ptr(delims);
  *size = pieces_size;
  return pieces;
}

char** str_split_alt(char* text, char* del_string, unsigned int* size) {
  char* str = str_new(text);
  char* delims = str_new(del_string);
  char** pieces = (char**) new_ptr(1, sizeof(char*));
  unsigned int pieces_size = 0;
  unsigned int pos = 0;
  unsigned int start_char = 0;
  while (1) {
    if (str[pos] == '\0') {
      if (pieces_size == 0) {
        pieces[0] = str_new("");
      }
      else {
        pieces = (char**) resize_ptr(pieces, (pieces_size+1)*sizeof(char*));
        pieces[pieces_size] = &str[start_char];
        pieces_size++;
        start_char = pos+1;
      }
      break;
    }
    if (str_delim_check(str[pos], delims)) {
      if (pieces_size == 0) {
        str[pos] = '\0';
        pieces[0] = &str[start_char];
        pieces_size++;
        start_char = pos+1;
      }
      else {
        pieces = (char**) resize_ptr(pieces, (pieces_size+1)*sizeof(char*));
        str[pos] = '\0';
        pieces[pieces_size] = &str[start_char];
        pieces_size++;
        start_char = pos+1;
      }
    }
    pos++;
  }
  free_ptr(delims);
  free_ptr(str);
  *size = pieces_size;
  return pieces;
}

bool str_delim_check(char c, char* delims) {
  unsigned int count = 0;
  while(delims[count] != '\0') {
    if (c == delims[count]) {
      return true;
    }
    count++;
  }
  return false;
}

#endif

// Luke Jiang
// CSE 374 HW 4
// April 24 2018

// This program implements a Unix utility program 'gasp'.
// Syntax:  ./gasp [options] STRING FILE...
// The program reads the listed FILEs and copy each line form the stdout
// if it contains STRING anywhere in the input line. The behavior of this
// program is undefined for any input line > 500 characters and STRING >
// 100 characters.
// Options:
// -n:  add to the front of the output the line number in the file where
//      STRING is found.
// -i:  ignore case when searching for STRING for each line.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The maximum length of input STRING and each input line
#define MAX_LINE_LENGTH 500
#define MAX_STRING_LENGTH 100

// Mark whether options are selected
int option_i = 0;
int option_n = 0;

void process_single_file(char *string, char *filename);
void strlwr(char *string);
void process_single_line(char *line, char *line_copy, int line_count,
    char *filename, char *string);

int main(int argc, char **argv) {
  // check if any options are selected
  int option_count = 1;
  for (int i = 1; i < 3; i++) {
    if (i < argc && !strcmp(argv[i], "-n")) {
      option_n = 1;
      option_count++;
    } else if (i < argc &&!strcmp(argv[i], "-i")) {
      option_i = 1;
      option_count++;
    }
  }
  // check if enough arguments are provided (at least 2 excluding options)
  // If not, print error message to stderr and exit with failure
  if (option_count + 2 > argc) {
    fprintf(stderr,
        "Not enough arguments: must provide at least a string and a file\n");
    exit(EXIT_FAILURE);
  }
  // copy at most 100 characters from input STRING to string_to_compare,
  // convert string_to_compare to lower case if option_i == 1
  char string_to_compare[MAX_STRING_LENGTH];
  int copy_length = strlen(argv[option_count]) + 1;
  strncpy(string_to_compare, argv[option_count], copy_length);
  if (option_i) {
    strlwr(string_to_compare);
  }
  // traverse the input files
  for (int i = option_count + 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") && strcmp(argv[i], "-i")) {
      process_single_file(string_to_compare, argv[i]);
    }
  }
  return EXIT_SUCCESS;
}

// Check if input string appears in file filename. If filename is
// not a legal file, print an error message to stdout and return.
// Else, process each line in the file and print the line if matches.
// (and a line count if option_n == 1)
void process_single_file(char *string, char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", filename);
  } else {
    // buffer for each line
    char line[MAX_LINE_LENGTH];
    // buffer for lower-cased line (if option_i == 1)
    char line_copy[MAX_LINE_LENGTH];
    int line_count = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
      line_count++;
      process_single_line(line, line_copy, line_count, filename, string);
    }
    fclose(file);
  }
}

// Check if input string appears in line. If so, print to stdout
// filename and line (and line_count if option_n == 1)
// Convert each line to lower case and store the converted string
// in line_copy if option_i == 1
void process_single_line(char *line, char *line_copy, int line_count,
    char *filename, char *string) {
  if (line[strlen(line) - 1] == '\n') {
    line[strlen(line) - 1] = '\0';
  }
  char *line_to_compare = line;
  if (option_i) {
    line_to_compare = line_copy;
    strncpy(line_to_compare, line, strlen(line) + 1);
    strlwr(line_to_compare);
  }
  if (strstr(line_to_compare, string) != NULL) {
    if (option_n) {
      printf("%d %s:%s\n", line_count, filename, line);
    } else {
      printf("%s:%s\n", filename, line);
    }
  }
}

// Convert input string to lower case
void strlwr(char *string) {
  for (int i = 0; i < strlen(string); i++) {
    string[i] = tolower(string[i]);
  }
}

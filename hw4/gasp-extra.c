// Luke Jiang
// CSE 374 HW 4 (Extra Credit)
// April 24 2018

// This program implements a Unix utility program 'gasp'.
// Syntax:  ./gasp [options] STRING FILE...
// The program reads the listed FILEs and copy each line form the stdout
// if it contains STRING anywhere in the input line. If an input line contains
// more than 500 characters, the extra content is ignored while searching.
// If no FILE input is not provided, the program should read from stdin.
// Options:
// -n:  add to the front of the output the line number in the file where
//      STRING is found.
// -i:  ignore case when searching for STRING for each line.
// -w:  search for words separated by whitespace. A line contains STRING if
//      the match is surrounded by whitespaces, or in the beginning or end of
//      line.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The maximum length of input STRING and each input line
#define MAX_LINE_LENGTH 500
#define MAX_STRING_LENGTH 100
// Number of possible options
#define PARAMETER_NUMBER 3

// Mark whether options are selected
int option_i = 0;
int option_n = 0;
int option_w = 0;

void process_stdin(char *string);
void process_single_file(char *string, char *filename);
void process_single_line(char *line, char *line_copy, int line_count,
    char *filename, char *string);
int match(char *line_to_compare, char *string);
int match_helper(char *line_to_compare, char *string, char *matchpoint);
void strlwr(char *string);

int main(int argc, char **argv) {
  // check if any options are selected
  int option_count = 1;
  for (int i = 1; i < PARAMETER_NUMBER + 1; i++) {
    if (i < argc && !strcmp(argv[i], "-n")) {
      option_n = 1;
      option_count++;
    } else if (i < argc && !strcmp(argv[i], "-i")) {
      option_i = 1;
      option_count++;
    } else if (i < argc && !strcmp(argv[i], "-w")) {
      option_w = 1;
      option_count++;
    }
  }
  // check if enough arguments are provided (at least 2 excluding options)
  // If not, print error message to stderr and exit with failure
  if (option_count + 1 > argc) {
    fprintf(stderr, "not enough arguments\n");
    exit(EXIT_FAILURE);
  }

  // copy at most 100 characters from input STRING to string_to_compare,
  // convert string_to_compare to lower case if option -i is selected
  char string_to_compare[MAX_STRING_LENGTH];
  int copy_length = strlen(argv[option_count]) + 1;
  strncpy(string_to_compare, argv[option_count], copy_length);
  if (option_i) {
    strlwr(string_to_compare);
  }

  // process input files or stdin
  if (option_count + 1 == argc) {
    process_stdin(string_to_compare);
  } else {
    for (int i = option_count + 1; i < argc; i++) {
      if (strcmp(argv[i], "-n") && strcmp(argv[i], "-i")) {
        process_single_file(string_to_compare, argv[i]);
      }
    }
  }

  return EXIT_SUCCESS;
}

// Read from stdin and find match
void process_stdin(char *string) {
  char line[MAX_LINE_LENGTH];
  char line_copy[MAX_STRING_LENGTH];
  fgets(line, MAX_LINE_LENGTH, stdin);
  process_single_line(line, line_copy, 1, "", string);
}

// Check if input string appears in file filename. If filename is
// not a legal file, print an error message to stdout and return
void process_single_file(char *string, char *filename) {
  // check valid file input
  FILE * file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", filename);
    return;
  }

  // buffers for each line
  char line[MAX_LINE_LENGTH];
  char line_copy[MAX_STRING_LENGTH];

  int line_count = 0;   // counter for line processed
  int line_break = 0;   // flag for determining if the segment is a new line

  // process each line, truncate if necessary, update line_count
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    if (line[strlen(line) - 1] == '\n') {
      if (line_break == 1) {
        line_break = 0;
      } else {
        line_count++;
        process_single_line(line, line_copy, line_count, filename, string);
      }
    } else if (line_break == 0) {
      line_break = 1;
      line_count++;
      process_single_line(line, line_copy, line_count, filename, string);
    }
  }

  // close file
  fclose(file);
}

// Check if input string appears in line. If so, print to stdout
// filename and line (and line_count if option -n is selected)
// Convert each line to lower case if option -i is selected
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
  if (match(line_to_compare, string)) {
    if (option_n) {
      printf("%d%s:%s\n", line_count, filename, line);
    } else {
      printf("%s:%s\n", filename, line);
    }
  }
}

// If option -w is not selected, check if string appears anywhere in
// line_to_compare. Else, check if string appears in the front or back
// of line_to_compare or surrounded by whitespace in the middle of
// line_to_compare. Return 1 is a match is found and 0 otherwise.
int match(char *line_to_compare, char *string) {
  char *matchpoint = strstr(line_to_compare, string);
  if (matchpoint == NULL) {
    return 0;
  } else if (matchpoint != NULL && !option_w) {
    return 1;
  } else {
    // matchpoint != NULL and option_w is selected
    while (matchpoint != NULL && strlen(matchpoint) >= 1) {
      if (match_helper(line_to_compare, string, matchpoint)) {
        return 1;
      }
      matchpoint = strstr(matchpoint + 1, string);
    }
    return 0;
  }
}

// Handle the case where -w is selected and string appears in line_to_compare
int match_helper(char *line_to_compare, char *string, char *matchpoint) {
  int size_line = strlen(line_to_compare);
  int size_str = strlen(string);
  if (size_line == size_str) {
    return 1;
  } else if (matchpoint == line_to_compare) {
    return isspace(line_to_compare[size_str]);
  } else if (matchpoint[size_str] == '\0') {
    return isspace(line_to_compare[size_line - size_str - 1]);
  } else {
    int size2 = strlen(matchpoint);
    return isspace(line_to_compare[size_line - size2 - 1])
      && isspace(matchpoint[size_str]);
  }
}

// Convert input string to lower case
void strlwr(char *string) {
  for (int i = 0; i < strlen(string); i++) {
    string[i] = tolower(string[i]);
  }
}

// Luke Jiang
// CSE 374 HW 5 (extra credit)
// May 8 2018

// This C program deals with reading from dictionary, generating trie, and
// interaction with users.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// interface for TrieNode data structure and useful functions
#include "trie.h"

#define T9_CHARS "23456789#"    // valid t9 characters
#define MAX_INPUT 100           // max length of user input
#define MAX_WORD 30             // length of the longest word in the dictionary
#define MAX_WORD_STR "30"       // MAX_WORD in string format
#define FORMAT "%" MAX_WORD_STR "d\t%" MAX_WORD_STR "s"   // input format

// takes an array of int as paramener, populate the array with t9 code sequence
// for the alphabet from 3 to 9.
void create_table(int *table);
// takes the trie root as parameter, repeatedly asks the user for a t9 code and
// searches user's input on the trie. If the input code does not represent a
// word in the dictionary or the user typed an illegal t9 code, print
// corresponding message and jump to the next query. Otherwise print out
// the word and jump to the next query until the user types 'exit', in which
// case the function returns.
void user_interface(TrieNode *root);
// takes word, code and the t9-code table as parameters, finds corresponding
// t9 code for the word and writes the result to code.
void get_T9_code(char *word, char *code, int *table);
// returns 1 if the code parameter represents a valid t9 code (non-empty string
// of lower case letters), Otherwise return 0.
int check_valid_code(char *code);

int main(int argc, char**argv) {
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "unable to open dictionary");
    exit(EXIT_FAILURE);
  }

  // table is an array that stores characters and correspoding t9 codes.
  int *table = (int *) malloc(26 * sizeof(int));
  check_malloc(table);
  create_table(table);

  // the root of the trie.
  TrieNode *root = make_node(-1, 0, "");

  // buffers for each word and its corresponding code
  char line[MAX_WORD];
  char code[MAX_WORD];
  char word[MAX_WORD];
  code[0] = '\0';
  word[0] = '\0';
  int freq;
  while (fgets(line, MAX_WORD, file)) {
    line[strlen(line) - 1] = '\0';
    sscanf(line, FORMAT, &freq, word);
    get_T9_code(word, code, table);
    if (!check_valid_code(code)) {
      continue;
    }
    add_word(root, code, word, freq);
  }
  user_interface(root);
  free(table);
  free_memory(root);
  fclose(file);
  return EXIT_SUCCESS;
}

void user_interface(TrieNode *root) {
  // current_word is a pointer to the TrieNode that stores the current
  // queried word.
  TrieNode *current_word = root;
  char *input = (char *) malloc(MAX_WORD * sizeof(char));
  check_malloc(input);
  printf("Enter \"exit\" to quit.\n");
  while (1) {
    printf("Enter Key Sequence (or \"#\" for next word):\n>");
    fgets(input, MAX_INPUT, stdin);
    input[strlen(input) - 1] = '\0';
    if (strstr(input, "exit")) {
      break;
    } else if (check_valid_code(input) == 0) {
      printf("Invalid T9 code\n");
      continue;
    }
    // pounds_count stores how many pounds the user has typed.
    int pounds_count = 0;
    char *pounds = strstr(input, "#");
    if (pounds) {
      pounds_count = strlen(pounds);
    }
    input[strlen(input) - pounds_count] = '\0';

    if (strlen(input) != 0) {
      current_word = get_word_node(root, input);
      if (current_word != NULL && strlen(current_word->word) == 0
        && pounds_count >= 1) {
        pounds_count--;
        while (current_word != NULL && strlen(current_word->word) == 0) {
          current_word = get_first_child(current_word);
        }
      } else if (current_word == NULL || strlen(current_word->word) == 0) {
        printf("Not found in current dictionary.\n");
        continue;
      }
    }
    // which_word is a copy current_word, pointing to the front of the current
    // T9onym list.
    TrieNode *which_word = current_word;
    // prev_word points to the node that is in front of current_word after the
    // while loop.
    TrieNode *prev_word = current_word;
    while (pounds_count > 0 && current_word != NULL) {
      current_word = current_word->children[10];
      if (pounds_count > 1) {
        prev_word = current_word;
      }
      pounds_count--;
    }

    if (current_word != NULL) {
      printf("%s\n", current_word->word);
    } else {
      printf("%s\n", "There are no more T9onyms");
    }

    if (which_word == current_word && current_word != NULL) {
      current_word->freq++;
    } else if (current_word != NULL) {
      prev_word->children[10] = current_word->children[10];
      TrieNode *new_curr = add_word_at(which_word,
        1 + current_word->freq, current_word->word);
      free(current_word->word);
      free(current_word);
      current_word = new_curr;
    }
  }
  free(input);
}

void create_table(int *table) {
  int i = 2;
  int k = 0;
  while (i < 8) {
    for (int j = 0; j < 3; j++) {
      table[k] = i;
      k++;
    }
    i++;
  }
  table[k] = i - 1;
  k++;
  while (i < 10) {
    for (int j = 0; j < 3; j++) {
      table[k] = i;
      k++;
    }
    i++;
  }
  table[k] = 9;
}

void get_T9_code(char *word, char *code, int *table) {
  int invalid = 0;
  for (int i = 0; i < strlen(word); i++) {
    int index = ((int) word[i]) - 97;
    if (index < 0 || index > 25) {
      invalid = 1;
      break;
    }
    int code_number = table[index];
    code[i] = code_number + '0';
  }
  if (invalid) {
    code[0] = '\0';
  } else {
    code[strlen(word)] = '\0';
  }
}

int check_valid_code(char *code) {
  if (code == NULL || strlen(code) == 0) {
    return 0;
  }
  for (int i = 0; i < strlen(code); i++) {
    if (strchr(T9_CHARS, code[i]) == NULL) {
      return 0;
    }
  }
  return 1;
}

// Luke Jiang
// CSE 374 HW 5 (extra credit)
// May 8 2018

// This C file implements functionalities defined in trie.h header file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

TrieNode *make_node(int number, int freq, char *word) {
  TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
  check_malloc(node);
  char *word_cpy = (char *) malloc(sizeof(char) * (strlen(word) + 1));
  check_malloc(word_cpy);
  strncpy(word_cpy, word, strlen(word) + 1);
  if (node) {
    node->number = number;
    node->freq = freq;
    node->word = word_cpy;
    for (int i = 0; i < 11; i++) {
      node->children[i] = NULL;
    }
  }
  return node;
}

void add_word(TrieNode *root, char *code, char *word, int freq) {
  TrieNode *curr = root;
  int i = 0;
  while (code[i] != '\0') {
    int number = code[i] - '0';
    TrieNode *next = curr->children[number];
    if (next == NULL) {
      curr->children[number] = make_node(number, 0, "");
    }
    curr = curr->children[number];
    i++;
  }
  add_word_at(curr, freq, word);
}

TrieNode *add_word_at(TrieNode *curr, int freq, char *word) {
  if (strlen(curr->word) == 0) {
    free(curr->word);
    char *word_cpy = (char *) malloc(sizeof(char) * (strlen(word) + 1));
    check_malloc(word_cpy);
    strncpy(word_cpy, word, strlen(word) + 1);
    curr->word = word_cpy;
    curr->freq = freq;
    return curr;
  } else if (curr->freq < freq) {
    TrieNode *next = curr->children[10];
    TrieNode *new_node = make_node(10, freq, word);
    curr->children[10] = new_node;
    new_node->children[10] = next;
    // curr fields
    int curr_freq = curr->freq;
    char *curr_word = curr->word;
    // new_node fields
    int new_freq = new_node->freq;
    char *new_word = new_node->word;
    // swapping
    new_node->freq = curr_freq;
    curr->freq = new_freq;
    new_node->word = curr_word;
    curr->word = new_word;
    return curr;
  } else {
    TrieNode *next = curr->children[10];
    while (next != NULL && next->freq > freq) {
      curr = next;
      next = next->children[10];
    }
    TrieNode *new_node = make_node(10, freq, word);
    curr->children[10] = new_node;
    new_node->children[10] = next;
    return new_node;
  }
}

TrieNode *get_word_node(TrieNode *root, char *code) {
  TrieNode *curr = root;
  int i = 0;
  while (code[i] != '\0') {
    int number = code[i] - '0';
    if (curr->children[number] == NULL) {
      return NULL;
    } else {
      curr = curr->children[number];
    }
    i++;
  }
  return curr;
}

void free_memory(TrieNode *root) {
  if (root != NULL) {
    free(root->word);
    for (int i = 0; i < 11; i++) {
      free_memory(root->children[i]);
    }
    free(root);
  }
}

void print_tree(TrieNode *root) {
  if (root != NULL) {
    int number = root->number;
    char *word = root->word;
    int freq = root->freq;
    printf("(%d, %s, %d) ", number, word, freq);
    for (int i = 0; i < 11; i++) {
      print_tree(root->children[i]);
    }
  }
}

TrieNode *get_first_child(TrieNode *node) {
  if (node == NULL) {
    return node;
  }
  for (int i = 0; i < 11; i++) {
    if (node->children[i] != NULL) {
      return node->children[i];
    }
  }
  return NULL;
}

void check_malloc(void *pointer) {
  if (!pointer) {
    fprintf(stderr, "Malloc failed, not enough space in heap\n");
    exit(EXIT_FAILURE);
  }
}

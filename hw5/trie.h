// Luke Jiang
// CSE 374 HW 5
// May 8 2018

// This is the C header file for data structure TrieNode and useful functions
// with it.

#ifndef _TRIE_H_
#define _TRIE_H_

typedef struct TrieNode {
  // number stores the t9 code of a TrieNode. Nodes that have a pound as
  // code are represented by int 10.
  int number;
  // word stores an empty string if the word it represents is not in the
  // dictionary, or a pointer to the word otherwise.
  char *word;
  // array of pointers to child TrieNodes
  struct TrieNode *children[11];
} TrieNode;

// Malloc a new node that has number and word as fields. Returns a pointer
// to the malloc'd node.
TrieNode *make_node(int number, char *word);

// Add a new word to the trie, with root being the root of trie, code being
// the t9 code of word.
void add_word(TrieNode *root, char *code, char *word);

// traverse the tree based on parameter code and return a pointer to the node
// that corresponds to the code. Returns NULL if a NULL node is traversed.
TrieNode *get_word_node(TrieNode *root, char *code);

// free all malloc'd strings and TrieNodes in the trie pointed by root.
void free_memory(TrieNode *root);

// helper function for printing the trie.
void print_tree(TrieNode *root);

// check if malloc was successful. If pointer is NULL, print error message
// to stderr and terminate.
void check_malloc(void *pointer);

#endif   // _TRIE_H_

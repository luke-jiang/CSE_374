// Luke Jiang
// CSE 374 HW 5 (extra credit)
// May 8 2018

// This is the C header file for data structure TrieNode and useful functions
// with it.

#ifndef _TRIENODE_H_
#define _TRIENODE_H_

typedef struct TrieNode {
  // number stores the t9 code of a TrieNode. Nodes that have a pound as
  // code are represented by int 10.
  int number;
  // freq stores the frequency of a word.
  int freq;
  // word stores an empty string if the word it represents is not in the
  // dictionary, or a pointer to the word otherwise.
  char *word;
  // array of pointers to child TrieNodes
  struct TrieNode *children[11];
} TrieNode;

// Malloc a new node that has number and word as fields. Returns a pointer
// to the malloc'd node.
TrieNode *make_node(int number, int freq, char *word);

// Add a new word to the trie, with root being the root of trie, code being
// the t9 code of word.
void add_word(TrieNode *root, char *code, char *word, int freq);

// traverse the tree based on parameter code and return a pointer to the node
// that corresponds to the code. Returns NULL if a NULL node is traversed.
TrieNode *get_word_node(TrieNode *root, char *code);

// free all malloc'd strings and TrieNodes in the trie pointed by root.
void free_memory(TrieNode *root);

// helper function for printing the trie.
void print_tree(TrieNode *root);

// return a pointer to the first non-NULL child of root.
TrieNode *get_first_child(TrieNode *node);

// curr points to the TrieNode which is followed by its T9onym nodes sorted
// by freq. This function inserts into the "LinkedList" of T9nonym nodes
// a new TrieNode with fields freq and word while keep the result list sorted.
TrieNode *add_word_at(TrieNode *curr, int freq, char *word);

// check if malloc was successful. If pointer is NULL, print error message
// to stderr and terminate.
void check_malloc(void *pointer);

#endif   // _TRIE_H_

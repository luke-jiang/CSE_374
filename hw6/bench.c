// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 23/05/2018

// This C file implements the bench test program.
// The output of print_heap is stored at result.txt
// Command-line syntax:
// ./bench --OPTION=VALUE   where OPTION can be
//    [ntrials] [pctget] [pctlarge] [small_limit]
//    [large_limit] [random_seed]
// If an option is not specified by the user, it would have default value.
// if the user passes a percentage smaller than 1 or larger than 0, or
// small_limit is larger than large_limit, or either small_limit or large_
// limit or both <= 0, the program quits with an error message.
#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include "mem.h"

// allocated space for type "t" in number of "l".
#define New(t, l) (t*) malloc(sizeof(t) * l)

// return the smaller one of a and b.
int min(int a, int b);
// randomly select an int within range(from, to) and return the int.
int get_rand_range(int from, int to, unsigned int *random_seed);
// if input is not a valid percentage (< 0 or > 100), print an error to stderr
// and exit; else, return the input.
int check_valid_pct(int pct);

int main(int argc, char **argv) {
  // process input
  int opt = 0;

  int ntrials = 10000;
  int pctget = 50;
  int pctlarge = 10;
  int small_limit = 200;
  int large_limit = 20000;
  unsigned int random_seed = (unsigned int) time(0);

  static struct option long_options[] = {
    {"ntrials",       optional_argument, 0,  'a' },
    {"pctget",        optional_argument, 0,  'b' },
    {"pctlarge",      optional_argument, 0,  'c' },
    {"small_limit",   optional_argument, 0,  'd' },
    {"large_limit",   optional_argument, 0,  'e' },
    {"random_seed",   optional_argument, 0,  'f' },
    {0,               0,                 0,   0  }
  };

  int long_index = 0;
  while ((opt = getopt_long(argc, argv, "abcdef",
          long_options, &long_index)) != -1) {
    switch (opt) {
    case 'a' : ntrials = atoi(optarg);  break;
    case 'b' : pctget = check_valid_pct(atoi(optarg));  break;
    case 'c' : pctlarge = check_valid_pct(atoi(optarg));  break;
    case 'd' : small_limit = atoi(optarg);  break;
    case 'e' : large_limit = atoi(optarg);  break;
    case 'f' : random_seed = atoi(optarg);  break;
    default  : exit(EXIT_FAILURE);
    }
  }

  if (small_limit > large_limit || small_limit <= 0 || large_limit <= 0) {
    fprintf(stderr, "Illegal limitation\n");
    exit(EXIT_FAILURE);
  }

  // array for pointers to requested blocks
  char **used_blocks = New(char*, ntrials);
  if (used_blocks == NULL) {
    fprintf(stderr, "No enough space!\n");
    exit(EXIT_FAILURE);
  }
  int used_blocks_size = 0;

  // print chart headers
  printf("time cost:\ttotal system call size:\t\ttotal free blocks number:\t");
  printf("average storage per block:\n");

  // statistics data
  clock_t start, end;
  double cpu_time_used;
  uintptr_t total_size_;
  uintptr_t num_free_blocks_;
  uintptr_t total_free_;
  int trail_counter = 0;

  // start trials
  start = clock();
  FILE *f = fopen("result.txt", "a");
  for (int i = 0; i < ntrials; i++) {
    int randNum = rand_r(&random_seed) % 100;
    if (randNum < pctget) {    // getmem
      char *get_mem_result;
      int request_size;
      if (rand_r(&random_seed) % 100 < pctlarge) {
        request_size = get_rand_range(small_limit, large_limit, &random_seed);
      } else {
        request_size = get_rand_range(1, small_limit, &random_seed);
      }
      // request to getmem
      get_mem_result = getmem(request_size);
      if (get_mem_result == NULL) {
        continue;
      }
      // add to the array of used_blocks
      used_blocks[used_blocks_size] = get_mem_result;
      used_blocks_size++;
      // write data to returned block
      int traverse_size = min(16, request_size);
      char *current = get_mem_result;
      for (int j = 0; j < traverse_size; j++) {
        *current = 0xFE;
        current++;
      }
    } else if (used_blocks_size > 0) {    // freemem
      int to_free = rand_r(&random_seed) % used_blocks_size;
      freemem(used_blocks[to_free]);
      used_blocks[to_free] = used_blocks[used_blocks_size - 1];
      used_blocks_size--;
    }
    // report statistics each 10%
    trail_counter++;
    if (trail_counter * 10 / ntrials >= 1) {
      end = clock();
      cpu_time_used = (double) (end - start) / CLOCKS_PER_SEC;
      get_mem_stats(&total_size_, &total_free_, &num_free_blocks_);
      double byte_per_block_ = (double) total_free_ / num_free_blocks_;
      printf("%f\t%lu\t\t\t\t%lu\t\t\t\t%f\n", cpu_time_used, total_size_,
              num_free_blocks_, byte_per_block_);
      trail_counter = 0;
    }
  }
  print_heap(f);

  // free remaining memory
  for (int i = 0; i < used_blocks_size; i++) {
    freemem(used_blocks[i]);
  }
  free(used_blocks);
}

int min(int a, int b) {
  return (a < b) ? a : b;
}

int get_rand_range(int from, int to, unsigned int* random_seed) {
  return rand_r(random_seed) % (to - from) + from;
}

int check_valid_pct(int pct) {
  if (pct < 0 || pct > 100) {
    fprintf(stderr, "Illegal percentage argument\n");
    exit(EXIT_FAILURE);
  }
  return pct;
}

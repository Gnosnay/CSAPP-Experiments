#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** global args & value */
int h_flag = false;           // help flag
int v_flag = false;           // verbose flag
int set_bits = -1;            // Number of set index bits.
int E_value = -1;             // Number of lines per set.
int offset_bits = -1;         // Number of block offset bits.
char *trace_file_path = NULL; // Trace file.

void printHelper() {
  printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
  printf("Options:\n");
  printf("  -h         Print this help message.\n");
  printf("  -v         Optional verbose flag.\n");
  printf("  -s <num>   Number of set index bits.\n");
  printf("  -E <num>   Number of lines per set.\n");
  printf("  -b <num>   Number of block offset bits.\n");
  printf("  -t <file>  Trace file.\n\n");
  printf("Examples:\n");
  printf("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
  printf("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

int main(int argc, char *argv[]) {
  while ((c = getopt(argc, argv, "hvs:E:b:t:")) != -1)
    switch (c) {
    case 'h':
      h_flag = true;
      break;
    case 'v':
      v_flag = true;
      break;
    case 's':
      set_bits = optarg;
      break;
    case '?':
      if (optopt == 'c')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
      return 1;
    default:
      abort();
    }

  printSummary(0, 0, 0);
  return 0;
}

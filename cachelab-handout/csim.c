#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cachelab.h"
#include "debug.h"

/** global args & value */
int v_flag = 0;               // verbose flag
int set_bits = -1;            // Number of set index bits.
int E_value = -1;             // Number of lines per set.
int offset_bits = -1;         // Number of block offset bits.
char *trace_file_path = NULL; // Trace file.

/**
 * print the help message
 */
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
  int c;
  while ((c = getopt(argc, argv, "hvs:E:b:t:")) != -1)
    switch (c) {
    case 'h':
      printHelper();
      return 0;
    case 'v':
      v_flag = 1;
      break;
    case 's':
      set_bits = atoi(optarg);
      break;
    case 'E':
      E_value = atoi(optarg);
      break;
    case 'b':
      offset_bits = atoi(optarg);
      break;
    case 't':
      trace_file_path = optarg;
      break;
    case '?':
      if (optopt == 's' || optopt == 'E' || optopt == 'b' || optopt == 't')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
      return 1;
    default:
      abort();
    }

  debug_print("v_flag: %d\n", v_flag);
  debug_print("set_bits: %d\n", set_bits);
  debug_print("E_value: %d\n", E_value);
  debug_print("offset_bits: %d\n", offset_bits);
  debug_print("*trace_file_path: %s\n", trace_file_path);
  // printSummary(0, 0, 0);
  return 0;
}

// set 1 for printing debug info
#define DEBUG 1
// do { ... } while (0) idiom ensures that the code acts like a statement
#define debug_print(fmt, ...)                                                  \
  do {                                                                         \
    if (DEBUG)                                                                 \
      fprintf(stderr, fmt, __VA_ARGS__);                                       \
  } while (0)
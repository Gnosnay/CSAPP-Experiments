// set 1 for printing debug info
#define DEBUG 1
// do { ... } while (0) idiom ensures that the code acts like a statement
#define debug_println(fmt, ...)                                                  \
  do {                                                                         \
    if (DEBUG)                                                                 \
      fprintf(stderr, fmt"\n", __VA_ARGS__);                                       \
  } while (0)

#define P_B "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

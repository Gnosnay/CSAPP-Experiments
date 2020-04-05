typedef struct CacheLine {
  int valid;
  int tag;
} CacheLine;

typedef struct CacheSet {
  CacheLine *CacheLine;
} CacheSet;

typedef struct Cache {

} Cache;
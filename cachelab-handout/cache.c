#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "cache.h"
#include "debug.h"
#define INVALID 0x20150912

int int_pow(int base, int exp) {
    int result = 1;
    while (exp) {
        if (exp % 2)
            result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}

void initCacheSet(CacheSet *set, int linePerSet) {
    debug_print("initCacheSet begins: linePerSet: [%d]\n", linePerSet);
    set->lines = malloc(linePerSet * sizeof(CacheLine));
    CacheLine *line = set->lines;
    for (int i = 0; i < linePerSet; ++i) {
        debug_print(" line[%d]: %p\n", i, line);
        line->tag = INVALID;
        line->valid = INVALID;
        line++;
    }
    set->capacity = linePerSet;
    debug_print(" inited set: %p\n", set);
}

void destroyCacheSet(CacheSet *cacheSet) {

}

Cache *createCache(int setBits, int linePerSet, int offsetBits, int verboseFlag) {
    debug_print("createCache begins: verboseFlag: %d\n", verboseFlag);
    int setsCount = int_pow(2, setBits);
    int tagBits = 64 - setBits - offsetBits;
    Cache *cache = malloc(sizeof(Cache));
    cache->misses = 0;
    cache->hits = 0;
    cache->evictions = 0;
    cache->verboseFlag = verboseFlag;
    cache->setSize = setsCount;
    cache->tagBits = tagBits;
    cache->cacheSets = malloc(setsCount * sizeof(CacheSet));
    CacheSet *set = cache->cacheSets;
    for (int i = 0; i < setsCount; ++i) {
        debug_print(" set[%d]: %p\n", i, set);
        initCacheSet(set, linePerSet);
        set++;
    }
    debug_print(" cache: %p\n", cache);
    return cache;
}

void destroyCache(Cache *cache) {

}

/**
 * 1. split instruction to [space]operation address,size
 * 2. I ignored, L S are same and M is L + S.
 *  2.1 case L:
 *  2.2 case S:
 *  2.3 case M:
 * 3. prints debug info
 * @param line one line from trace file
 */
void analyseOneLine(Cache *cache, char *line) {
//    char *op = malloc(sizeof(*op));
//    int *addr = malloc(sizeof(*addr));
//    splitOneInst(line, op, addr);
//    if (*op == 'I') return;
//    int res = accessMem(cache, addr);
//    // res is MISS -> line + ' miss'
//    // res is EVICTION -> line + ' miss eviction'
//    // res is HIT -> line + ' hit'
//    if (*op == 'M') {
//        // resLine + ' hit'
//    }
//    if (cache->verboseFlag) {
//        // TODO
//        printf();
//    }
}


/**
 *
 * @param line str from trace file
 * @param op operator of this trace line
 * @param addr hex format of addr of this trace line
 */
void splitOneInst(char *line, char *op, long *addr) {
    debug_print("splitOneInst begins: line: [%s]\n", line);
    if (line[0] == 'I') {
        *op = 'I';
        *addr = -1;
        debug_print(" is I instruction: %c\n", *line);
        return;
    }
    *op = *(line + 1);
    line += 3;
    char *cursor = line;
    int addrLength = 0;
    while (*cursor != ',') {
        debug_print(" move cursor: %c\n", *cursor);
        addrLength++;
        cursor++;
    }
    debug_print(" cursor: [%s]\n", line);
    char *hex = malloc(addrLength * sizeof(*hex));
    for (int i = 0; i < addrLength; ++i) {
        hex[i] = line[i];
    }
    debug_print(" hex: [%s]\n", hex);
    *addr = (long) strtol(hex, NULL, 16);
    debug_print(" addr: [%lx]\n", *addr);
    return;
}
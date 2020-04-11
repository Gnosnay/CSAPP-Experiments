#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "cache.h"
#include "debug.h"

#define INVALID 0x20150912
#define HIT 0x1221
#define EVICTION 0x1222
#define MISS 0x1223

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

unsigned long genMask(int bits) {
    return ((unsigned long) 1 << bits) - 1;
}

void initCacheSet(CacheSet *set, int linePerSet) {
    debug_println("initCacheSet begins: linePerSet: [%d]", linePerSet);
    set->lines = malloc(linePerSet * sizeof(CacheLine));
    CacheLine *line = set->lines;
    for (int i = 0; i < linePerSet; ++i) {
        debug_println(" line[%d]: %p", i, line);
        line->tag = INVALID;
        line->valid = INVALID;
        line++;
    }
    set->capacity = linePerSet;
    debug_println(" inited set: %p", set);
}

void destroyCacheSet(CacheSet *cacheSet) {

}

Cache *createCache(int setBits, int linePerSet, int offsetBits, int verboseFlag) {
    debug_println("createCache begins: verboseFlag: %d", verboseFlag);
    int setsCount = int_pow(2, setBits);
    int tagBits = 64 - setBits - offsetBits;
    Cache *cache = malloc(sizeof(Cache));
    cache->misses = 0;
    cache->hits = 0;
    cache->evictions = 0;
    cache->verboseFlag = verboseFlag;
    cache->setSize = setsCount;
    cache->tagBits = tagBits;
    cache->offsetBits = offsetBits;
    cache->setBits = setBits;
    cache->cacheSets = malloc(setsCount * sizeof(CacheSet));
    CacheSet *set = cache->cacheSets;
    for (int i = 0; i < setsCount; ++i) {
        debug_println(" set[%d]: %p", i, set);
        initCacheSet(set, linePerSet);
        set++;
    }
    debug_println(" cache: %p", cache);
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

void splitAddr(Cache *cache, long addr, int *setIndex, int *tagIndex) {
    long tagSetBits = addr >> cache->offsetBits;
    const long SET_MASK = genMask(cache->setBits);
    const long TAG_MASK = genMask(cache->tagBits);

    debug_println("original data: addr: %lx, offsetBits: %d, setBits: %d, tagBits: %d",
                  addr,
                  cache->offsetBits,
                  cache->setBits,
                  cache->tagBits
    );
    debug_println("[tag & set] bits: "
                          P_B, BYTE_TO_BINARY(tagSetBits));
    debug_println("SET_MASK: "
                          P_B, BYTE_TO_BINARY(SET_MASK));
    debug_println("TAG_MASK: "
                          P_B, BYTE_TO_BINARY(TAG_MASK));

    *setIndex = tagSetBits & SET_MASK;
    *tagIndex = tagSetBits >> cache->setBits;

    debug_println("setIndex: %d, binary: "
                          P_B, *setIndex, BYTE_TO_BINARY(*setIndex));
    debug_println("tagIndex: %d", *tagIndex);

}

int accessMem(Cache *cache, long addr) {
//    CacheSet *hitSet = (cache->cacheSets + setIndex);
    return 0;
}

/**
 *
 * @param line str from trace file
 * @param op operator of this trace line
 * @param addr hex format of addr of this trace line
 */
void splitOneInst(char *line, char *op, long *addr) {
    debug_println("splitOneInst begins: line: [%s]", line);
    if (line[0] == 'I') {
        *op = 'I';
        *addr = -1;
        debug_println(" is I instruction: %c", *line);
        return;
    }
    *op = *(line + 1);
    line += 3;
    char *cursor = line;
    int addrLength = 0;
    while (*cursor != ',') {
        debug_println(" move cursor: %c", *cursor);
        addrLength++;
        cursor++;
    }
    debug_println(" cursor: [%s]", line);
    char *hex = malloc(addrLength * sizeof(*hex));
    for (int i = 0; i < addrLength; ++i) {
        hex[i] = line[i];
    }
    debug_println(" hex: [%s]", hex);
    *addr = (long) strtol(hex, NULL, 16);
    debug_println(" addr: [%lx]", *addr);
    return;
}
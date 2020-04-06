#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "cache.h"
#include "debug.h"

CacheSet *createCacheSet(int linePerSet, int offsetBits) {
    return NULL;
}

void destroyCacheSet(CacheSet *cacheSet){

}

Cache *createCache(int setBits, int linePerSet, int offsetBits) {
    return NULL;
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
//    if (line == NULL) {
//        // is EOF
//    }
//    char *op = malloc(sizeof(*op));
//    int *addr = malloc(sizeof(*addr));
//    splitOneInst(line, op, addr);
//    switch (*op) {
//        case 'L':
//        case 'S':
//            break;
//        case 'M':
//            break;
//        default:
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
    if (line[0] == 'I'){
        *op = 'I';
        *addr = -1;
        debug_print(" is I instruction: %c\n", *line);
        return;
    }
    *op = *(line+1);
    line += 3;
    char* cursor = line;
    int addrLength = 0;
    while (*cursor != ','){
        debug_print(" move cursor: %c\n", *cursor);
        addrLength++;
        cursor++;
    }
    debug_print(" cursor: [%s]\n", line);
    char* hex = malloc(addrLength * sizeof(*hex));
    for (int i = 0; i < addrLength; ++i) {
        hex[i] = line[i];
    }
    debug_print(" hex: [%s]\n", hex);
    *addr = (long) strtol(hex, NULL, 16);
    debug_print(" addr: [%lx]\n", *addr);
    return;
}

void hitsPlusOne(Cache *cache) {

}

void missesPlusOne(Cache *cache) {

}

void evictionsPlusOne(Cache *cache) {

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cache.h"

#define ARRAY_SIZE(array) ( sizeof( array ) / sizeof( array[0] ) )

void splitOneInstTest() {
    char *op = malloc(sizeof(*op));
    long *addr = malloc(sizeof(*addr));
    splitOneInst(" S 00600aa0,1", op, addr);
    assert(*op = 'S');
    assert(*addr == 0x00600aa0);
    splitOneInst("I  004005b6,5", op, addr);
    assert(*op = 'I');
    assert(*addr == -1);
    splitOneInst("I  004005bb,5", op, addr);
    assert(*op = 'I');
    assert(*addr == -1);
    splitOneInst("I  004005c0,5", op, addr);
    assert(*op = 'I');
    assert(*addr == -1);
    splitOneInst(" S 7ff000398,8", op, addr);
    assert(*op = 'S');
    printf("0x7ff000398: %lx\n", 0x7ff000398);
    assert(*addr == 0x7ff000398);
    splitOneInst("I  0040051e,1", op, addr);
    assert(*op = 'I');
    assert(*addr == -1);
    splitOneInst(" S 7ff000390,8", op, addr);
    assert(*op = 'S');
    assert(*addr == 0x7ff000390);
    splitOneInst("I 0x123,2", op, addr);
    assert(*op == 'I');
    assert(*addr == -1);
    splitOneInst(" M 0x124,2", op, addr);
    assert(*op == 'M');
    assert(*addr == 0x124);
    splitOneInst(" S 123,2", op, addr);
    assert(*op == 'S');
    assert(*addr == 0x123);
    free(op);
    free(addr);
}

void structBuild() {
    Cache *cache = NULL;
    cache = createCache(2, 5, 3, 0);
    assert(cache != NULL);
    assert(cache->tagBits == 64 - 2 - 3);
    assert(cache->setSize == 4);
    assert(cache->verboseFlag == 0);
    assert(cache->cacheSets != NULL);
    assert(cache->cacheSets->lines != NULL);
    assert(cache->cacheSets->capacity == 5);
}

void splitAddrTest() {
    Cache *cache = NULL;
    cache = createCache(2, 5, 3, 0);
    int setIndex = 0;
    int tagIndex = 0;
    splitAddr(cache, 0x7, &setIndex, &tagIndex);
    assert(setIndex == 0);
    assert(tagIndex == 0);
    splitAddr(cache, 0xF, &setIndex, &tagIndex);
    assert(setIndex == 1);
    assert(tagIndex == 0);
    splitAddr(cache, 0x17, &setIndex, &tagIndex);
    assert(setIndex == 2);
    assert(tagIndex == 0);
    splitAddr(cache, 0x1F, &setIndex, &tagIndex);
    assert(setIndex == 3);
    assert(tagIndex == 0);

    // 01 00 111
    splitAddr(cache, 0x27, &setIndex, &tagIndex);
    assert(setIndex == 0);
    assert(tagIndex == 1);
    // 10 01 111
    splitAddr(cache, 0x4F, &setIndex, &tagIndex);
    assert(setIndex == 1);
    assert(tagIndex == 2);
    // 11 10 111
    splitAddr(cache, 0x77, &setIndex, &tagIndex);
    assert(setIndex == 2);
    assert(tagIndex == 3);
}

int main() {
    splitOneInstTest();
    structBuild();
    splitAddrTest();
}
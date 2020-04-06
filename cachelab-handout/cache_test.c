#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cache.h"

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

int main() {
    splitOneInstTest();
}
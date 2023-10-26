
#ifndef BIGINTEGER_H
#define BIGINTEGER_H


#include<stdio.h>
#include<stdlib.h>

struct BigInteger{
    char sign;
    int length;
    struct node * head;
};

struct node{
    int digit;
    struct node *next;
};

struct BigInteger initialize(char *);
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger ,struct BigInteger);
struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
struct BigInteger mod(struct BigInteger,struct BigInteger);

int  zero(struct BigInteger,struct node *);
void trav(struct node *);
void display(struct BigInteger);
void freell(struct node *);

#endif
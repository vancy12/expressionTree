#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node{
    struct node* left;
    struct node* right;
    char character;
}node;

typedef struct stackNode{
    node* store;
    struct stackNode* next;
}stackNode;

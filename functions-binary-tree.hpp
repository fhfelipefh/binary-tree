#ifndef _HPP_BINARY_TREE_
#define _HPP_BINARY_TREE_

typedef struct tree
{
    int info;
    tree *stl;
    tree *str;
} tree;

int empty(tree *t)
{
if(t == NULL)
return 1;
if(t->info == NULL)
return 1;
return 0;
}

void insert(tree **t, int num)
{
if(*t == NULL)
{
*t = new tree;
(*t)->stl = NULL;
(*t)->str = NULL;
(*t)->info = num;
}else
{
if(num < (*t)->info)
insert(&(*t)->stl, num);
else
insert(&(*t)->str, num);
}


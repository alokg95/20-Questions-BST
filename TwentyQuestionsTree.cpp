// Created by Alok Gupta and Vincent Gandolfo on 6/5/14
// Copyright (c) 2014 Alok Gupta. All rights reserved


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "TwentyQuestionsTree.h"

using namespace std;

TwentyQuestionsTree::TwentyQuestionsTree(FILE *fp)
{
    char b[256];
    
    const char *token;
    if(root==NULL)
    {
        const char *parent;
        
        const char *left;
        
        const char *right;
        
        int count = 0;
        
        fgets(b, 256, fp);
        
        while(1)
        {
            if(b[count] == '\n')
            {
                b[count] = '\0';
                break;
            }
            count ++;
        }
        
        token = strtok(b, ",\n");
        
        parent = strdup(token);
        
        BinaryNode *h = new BinaryNode(parent);
        
        root = h;
        token = strtok (NULL, ",");
        
        left = strdup(token);
        
        BinaryNode *b = new BinaryNode(left);
        
        root->left = b;
        
        token = strtok (NULL, ",");
        
        right = strdup(token);
        
        BinaryNode *z = new BinaryNode(right);
        root->right = z;
    }
    
    
    iterator = root;
    
    while(fgets(b,256,fp))
    {
        const char *parent;
        
        const char *left;
        const char *right;
        
        token = strtok(b, ",");
        
        parent = strdup(token);
        
        token = strtok(NULL, ",\n");
        
        left = strdup(token);
        token = strtok(NULL, ",\n");
        
        right = strdup(token);
        
        if(insert(iterator->left, parent, left, right)==false)
            
        {
            if(insert(iterator->right, parent, left, right)==false)
                
            {
                ;
            }
        }
    }
    
}

TwentyQuestionsTree::TwentyQuestionsTree()
{
    root = new BinaryNode("Is it a platypus?");
}


bool TwentyQuestionsTree::insert(BinaryNode *r, const char *parent,const char *left, const char *right)
{
    if(!r)
    {
        return false;
    }
    string p = parent;
    
    
    string questionString = r->question;
    
    if(questionString.compare(p)==0) {
        BinaryNode *rightOne = new BinaryNode(right);
        
        r->right = rightOne;
        
        
        
        BinaryNode *leftOne = new BinaryNode(left);
        
        
        r->left = leftOne;
        
        return true;
    } else {
        if(!insert(r->left, parent, left, right)) {
            return insert(r->right, parent, left, right);
        }
        return true;
    }
}

bool TwentyQuestionsTree::modifyAndInsert(BinaryNode *n, const char *parent,const char *left, const char *right)
{
    if(!n) {
        return false;
    }
    
    string l = left;
    
    string r = right;
    
    string q = n->question;
    if(q.compare(l)==0 || q.compare(r)==0) {
        n->question = strdup(parent);
        
        BinaryNode *var = new BinaryNode(left);
        
        n->left = var;
        
        
        BinaryNode *f = new BinaryNode(right);
        
        n->right = f;
        
        return true;
        
        
    } else {
        
        if(!modifyAndInsert(n->left, parent, left, right))
        {
            return modifyAndInsert(n->right, parent, left, right);
        }
        
        return true;
    }
}

void TwentyQuestionsTree::modifyAndInsert(const char *parent, const char *left,
                                          const char *right)
{
    reset();
    
    string l = left;
    
    string r = right;
    
    string question = iterator->question;
    
    if(!question.compare(l) || !question.compare(r))
    {
        iterator->question = strdup(parent);
        
        
        BinaryNode *digit = new BinaryNode(right);
        
        iterator->right = digit;
        
        
        BinaryNode *number = new BinaryNode(left);
        
        iterator->left = number;
        
        return;
        
    }
    else
        
    {
        if(modifyAndInsert(iterator, parent, left, right)==false)
        {
            ;
        }
    }
    return;
}


void TwentyQuestionsTree::reset()
{
    iterator = root;
}



const char *TwentyQuestionsTree::currentQuestion()
{
    if (iterator == NULL)
        return NULL;
    else
        return iterator->question;
}

void TwentyQuestionsTree::recordAnswer(int answer)
{
    if(answer == 1)
    {
        iterator = iterator->right;
    }
    
    if(answer == 0)
    {
        iterator = iterator->left;
    }
}


void TwentyQuestionsTree::storeTree(BinaryNode *n,FILE *fp)
{
    if (n && n->right && n->left) {
        fprintf(fp, "%s,", n->question);
        
        
        fprintf(fp, "%s,", n->left->question);
        
        
        fprintf(fp, "%s\n", n->right->question);

		storeTree(n->left,fp);
		
		storeTree(n->right,fp);
        
        return;
    }
    
    else {
        
        return;
    }
}
void TwentyQuestionsTree::storeTree(FILE *fp)
{
    if (root == NULL) {
        return;
    }
    
    storeTree(root, fp);
}

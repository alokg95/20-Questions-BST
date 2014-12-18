// Created by Alok Gupta on 6/5/14
// Copyright (c) 2014 Alok Gupta. All rights reserved

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include "TwentyQuestionsTree.h"
using namespace std;

int main(int argc, char *argv[])
{
    TwentyQuestionsTree *tree;
    FILE *fp;
    FILE *f;
    if (argc > 1)
    {
        fp = fopen(argv[1],"r");
        tree = new TwentyQuestionsTree(fp);
        fclose(fp);
    }
    else
        tree = new TwentyQuestionsTree();
    int play;
    do
    {
        char buf[256];
        tree->reset();
        const char *question = tree->currentQuestion();
        const char *lastquestion;
        int answer = 0;
        
        while(question != NULL)
        {
            
            printf("%s (yes=1, no=0): ", question);
            
            fgets(buf, 256, stdin);
            answer = atoi(buf);
            if (answer == 0)
                printf("No\n");
            else
                printf("Yes\n");
            tree->recordAnswer(answer);
            lastquestion = strdup(question);
            question = tree->currentQuestion();
        }
        
        if (answer == 1)
            printf("Yippee!  I got it right!\n");
        else
        {
            
            printf("What should I have guessed?\n");
            printf("(i.e. Is it a platypus?)?  ");
            char *o;
            char realanswer[256], otherquestion[256];
            fgets(realanswer, 256, stdin);
            strtok(realanswer, "\n");
            printf("Real answer: %s\n", realanswer);
            
            printf("What question would have distinguished this from %s\n",
                   lastquestion);
            fgets(otherquestion, 256, stdin);
            strtok(otherquestion, "\n");
            printf("Other question: %s\n", otherquestion);
            do{
                printf("Would the answer to that question have been yes or no (yes=1,no=0)? ");
                o = fgets(buf, 256, stdin);
                answer = atoi(o);
            } while(!isdigit(*o));
            if (answer == 0)
            {
                tree->modifyAndInsert(strdup(otherquestion), strdup(realanswer), strdup(lastquestion));
            }
            else
            {
                tree->modifyAndInsert(strdup(otherquestion), strdup(lastquestion), strdup(realanswer));
            }
        }
        printf("Would you like to play again (yes=1,no=0)?");
        fgets(buf, 256, stdin);
        play = atoi(buf);
    } while(play == 1);
    if(argc > 1)
    {
        f = fopen(argv[1],"w");
        tree->storeTree(f);
        fclose(f);
    }
    return 0;
}


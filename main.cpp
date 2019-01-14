#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Dictionary{
    char Word[69], Meaning[200];
};

struct TNode{
    Dictionary key;
    TNode *Left, *Right;
};
typedef TNode *BSTree;

int compare(Dictionary s1, Dictionary s2){
    return strcmp(s1.Word, s2.Word);
}

int InsertTNode(BSTree &root, Dictionary Word){
    if(!root){
        root = new TNode;
        if(!root) return 0;
        root->key= Word;
        root->Left= root->Right=NULL;
        return 1;
    }

    if(compare(root->key,Word)==0) return -1;
    else {
        if(compare(root->key,Word)>0)
            return InsertTNode(root->Left,Word);
        return InsertTNode(root->Right,Word);
    }
}

Dictionary Input(){
    Dictionary word;
    cout <<"Input Words...(Press[0] to Quit)\n";
    gets(word.Word);
    if(strcmp(word.Word,"0")==0) return word;
    cout<<"Input Meaning of the Word:\n";
    gets(word.Meaning);
    return word;
}

void Output(Dictionary word){
    cout<<"<Information>\n-Word: "<<word.Word<<"\n-Meaning: "<<word.Meaning<<endl;
}

void CreateBSTree(BSTree &root){
    Dictionary word;
    while(1){
        word = Input();
        if( strcmp(word.Word,"0")==0) break;
        int check= InsertTNode(root,word);
        if(check==-1) break;
    }
}

void NLR(BSTree &root){
    if(root!=NULL){
        Output(root->key);
        NLR(root->Left);
        NLR(root->Right);
    }
}

void searchin(BSTree &tree, char *in){
   int flag=0, res=0; BSTree parent = NULL;
   if(!tree){
        cout<<"Out of memory!\n";
        return;
   } parent=tree;
   while(parent){
        if((res=strcmp(parent->key.Word,in))==0){
            cout<<"Found!\n-Word: "<<in<<"\n-Meaning: "<<parent->key.Meaning<<endl;
            flag=1; break;
        }
        parent =(res>0)?parent->Left:parent->Right;
   }
    if(!flag)
        cout <<"This word doesn't existence in Dictionary!\n";
    return;
}

void deleteNode(BSTree &root, char *str) {
        BSTree parent = NULL;
        BSTree current = NULL;
        BSTree temp = NULL;
        int flag = 0, res = 0;
        if (!root) {
            cout<<"Out of memory!\n";
            return;
        }
        current = root;
        while (1) {
                res = strcmp(current->key.Word, str);
                if (res == 0)
                        break;
                flag = res;
                parent = current;
                current = (res > 0) ? current->Left : current->Right;
                if (current== NULL)
                        return;
        }
        /* deleting leaf node */
        if (current->Right == NULL) {
                if (current == root && current->Left == NULL) {
                        free(current);
                        root = NULL;
                        return;
                } else if (current== root) {
                        root = current->Left;
                        free (current);
                        return;
                }

                flag > 0 ? (parent->Left = current->Left) :
                                (parent->Right = current->Left);
        } else {
                /* delete node with single child */
                temp = current->Right;
                if (!temp->Left) {
                        temp->Left = current->Left;
                        if (current == root) {
                                root = temp;
                                free(current);
                                return;
                        }
                        flag > 0 ? (parent->Left = temp) :
                                        (parent->Right = temp);
                } else {
                        /* delete node with two children */
                        BSTree successor = NULL;
                        while (1) {
                                successor = temp->Left;
                                if (!successor->Left)
                                        break;
                                temp = successor;
                        }
                        temp->Left = successor->Right;
                        successor->Left = current->Left;
                        successor->Right = current->Right;
                        if (current == root) {
                                root = successor;
                                free(current);
                                return;
                        }
                        (flag > 0) ? (parent->Left = successor) :
                            (parent->Right = successor);
                }
        }
        free (current);
        return;
  }

int main(){
    BSTree root=NULL;
    int choice;
    char in[100];
    while(1){
        cout<<"[1]- Input\n[2]- Search\n[3]- Clear\n[4]- Output\n[5]- Exit\n";
        cin>>choice;
        switch(choice){
            case 1:
                getchar();
                CreateBSTree(root);
                break;
            case 2:
                cout <<"Input for searching...\n";
                getchar();
                gets(in);
                cout <<"Searching...\n";
                searchin(root,in);
                cout<<"After searching pls input again!\n";
                break;
            case 3:
                cout <<"Input for removing...\n";
                getchar();
                gets(in);
                deleteNode(root,in);
                break;
            case 4:
                NLR(root);
                break;
            case 5:
                exit(0);
            default:
                cout<<"You have entered wrong option!\n";
                return 0;
                break;
        }
    } return 0;
}

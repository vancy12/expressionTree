#include "tree.c"

int main(){
    node* root;
    char infix[] = "(a+b)*c/d";
    initTree(&root);
    infixToTree(infix, &root);
    inorder(root);
    return 0;
}
#include "header.h"
void initStackNode(stackNode** head){
    *head = NULL;
    return;
}

void initTree(node** root){
    *root = NULL;
    return;
}

void inorder(node* root){
    inorder(root->left);
    printf("%d ", root->character);
    inorder(root->right);
}

void push(stackNode** stack, node* input){
    stackNode* nn = (stackNode*)malloc(sizeof(stackNode));
    
    nn->store = input;
    nn->next = NULL;

    stackNode* p = *stack;
    *stack = nn;
    nn->next = p;
    return;
}

node* pop(stackNode** stack){
    if(*stack == NULL)
        return NULL;
    
    stackNode* p = *stack;
    (*stack)->next = p->next;
    return(p->store);
}

node* peek(stackNode* stack){
    return stack->store;
}

node* createtreeNode(char operand){
    node* nn = (node*)malloc(sizeof(node));
    nn->character = operand;
    nn->left = NULL;
    nn->right = NULL;

    return nn;
}
void infixToTree(char* string, node* root){
    stackNode* operator;
    stackNode* operand;
    initStackNode(&operator);
    initStackNode(&operand);
    node *stringRoot, *operand1, *operand2;

    for(int i = 0; string[i] != '\0'; i++){
        if(isalpha(string[i])){
            node* p = createtreeNode(string[i]);

            push(&operand, p);
        }

        else if(string[i] == '('){
            node* p =  createtreeNode(string[i]);
            push(&operator, p);
        }
        else if(string[i] == '+' || string[i] == '-'){
            node* p = createtreeNode(string[i]);

            if(peek(operator)->character != '('){
                // pop element and create tree
                
                stringRoot = pop(&operator);
                operand2 = pop(&operand);
                operand1 = pop(&operand);

                stringRoot->right = operand2;
                stringRoot->left = operand1;
                
                push(&operand, stringRoot);
                // push it back to operand stack
                
            }
        
            // if it is -> (
            push(&operator, p);
        }
        else if(string[i] == '*' || string[i] == '/'){
            node* p = createtreeNode(string[i]);
            push(&operator, p);
        }
        else if(string[i] == ')'){
            // pop everything and create tree
            stringRoot = pop(&operator);
            operand1 = pop(&operand);
            operand2 = pop(&operand);

            stringRoot->right = operand2;
            stringRoot->left = operand1;


            // pop remaining ( bracket
            pop(&operator);
            push(&operand, stringRoot);        
        }
    }

    root = pop(&operand);

}
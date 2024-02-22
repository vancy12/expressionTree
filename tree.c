#include "header.h"
void initStackNode(stackNode **head)
{
    *head = NULL;
    return;
}

void initTree(node **root)
{
    *root = NULL;
    return;
}

void inorder(node *root)
{
    inorder(root->left);
    printf("%d ", root->character);
    inorder(root->right);
}

void push(stackNode **stack, node *input)
{
    stackNode *nn = (stackNode *)malloc(sizeof(stackNode));

    nn->store = input;
    nn->next = NULL;

    stackNode *p = *stack;
    *stack = nn;
    nn->next = p;
    return;
}

node *pop(stackNode **stack)
{
    if (*stack == NULL)
        return NULL;

    stackNode *p = *stack;
    *stack = p->next;
    node *poppedNode = p->store;
    free(p);
    return (poppedNode);
}

int isEmpty(stackNode* stack){
    return(stack == NULL);
}

node* peek(stackNode *stack)
{
    if (isEmpty(stack))
        return NULL;

    return stack->store;
}

node *createtreeNode(char operand)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->character = operand;
    nn->left = NULL;
    nn->right = NULL;

    return nn;
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0; // Assuming all other characters have lower precedence
    }
}

void infixToTree(char *string, node *root)
{
    stackNode *operator;
    stackNode *operand;
    initStackNode(&operator);
    initStackNode(&operand);
    node *stringRoot, *operand1, *operand2;

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (isalpha(string[i]))
        {
            node *p = createtreeNode(string[i]);
            push(&operand, p);
        }

        else if (string[i] == '(')
        {
            node *p = createtreeNode(string[i]);
            push(&operator, p);
        }

        else if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/')
        {
            node *p = createtreeNode(string[i]);

            while (precedence(peek(operator)->character) <= string[i] && operator!= NULL)
            {
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

        else if (string[i] == ')')
        {
            // pop everything and create tree
            while (operator!= NULL)
            {

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
        // Build the remaining tree
        while (operator!= NULL)
        {
            stringRoot = pop(&operator);
            operand2 = pop(&operand);
            operand1 = pop(&operand);

            stringRoot->right = operand2;
            stringRoot->left = operand1;

            push(&operand, stringRoot);
        }

        root = pop(&operand);
    }

}   
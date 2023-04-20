#include <iostream>

//These includes are for random number generation
#include <cstdlib>
#include <time.h>

using namespace std;

//AVL node
struct AVLnode{
    int data;
    int height;
    AVLnode* left;
    AVLnode* right;
};

//determines the height of a node from the head.
int heigh(AVLnode* node){
    if(node == nullptr){
        return -1;
    }

    return node->height;
}

//updates the height after an AVL rotation
void updateHeight(AVLnode* node){
    node->height = max(heigh(node->left),heigh(node->right) ) + 1;
}

//Determines if a rotation is needed or not
int balance(AVLnode*& node){
    return heigh(node->left) - heigh(node->right);
}

void leftRotate(AVLnode*& A){ //A( () B( () () )) -> B( A( () () ) ())
    AVLnode* B = A->right;
    AVLnode* b = B->left;
    A->right = b;
    B->left = A;

    updateHeight(A);
    updateHeight(B);

    A = B;
    cout << "L: ";
}

void rightRotate(AVLnode*& A){ // B( A( () () ) ()) -> A( () B( () () ))
    AVLnode* B = A->left;
    AVLnode* b = B->right;
    A->left = b;
    B->right = A;

    updateHeight(A);
    updateHeight(B);

    A = B;
    cout << "R: ";
}



void insertNode(AVLnode*& node, int data){
    if(node == nullptr){
       AVLnode *newNode = new AVLnode;
       newNode->data = data;
       newNode->left = nullptr;
       newNode->right = nullptr;
       newNode->height = 0;

       node = newNode;
       return; 
    }

    if(data < node->data){
        insertNode(node->left, data);
    }else{
        insertNode(node->right, data);
    }

    updateHeight(node);

    //AVL stuff
    int bf = balance(node);
    if(bf >= 2){
        if(balance(node->left) > 0){
            //right right?
            rightRotate(node);
        }else{
            //left right?
            leftRotate(node->left);
            rightRotate(node);
        }
    }
    if(bf <= -2){
        if(balance(node->right) < 0){
            //left left?
            leftRotate(node);
        }else{
            //right left?
            rightRotate(node->right);
            leftRotate(node);
        }
    }
}

void printNode(AVLnode *node){
    if(node == nullptr){
        cout << "()";
        return;
    }
    cout << node->data << "( ";

    printNode(node->left);
    cout << ", ";
    printNode(node->right);
    cout << ")";
}

int main(){

    AVLnode *tree = nullptr;

    srand(time(0));

    for(int i = 0 ; i < 20; i++){
        insertNode(tree, rand() % 100 + 1);
        printNode(tree);
        cout << endl;
    }

    return 0;
}
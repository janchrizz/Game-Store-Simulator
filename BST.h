/*
Calvin Fernando Tjoeng
Team #8
Topic: FPS Games
BST.h
ADDED A FUNCTION CALLED searchAndGrab(bstdata value)
*/

#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <assert.h>
#include <iostream>

using namespace std;

template<typename bstdata>
class BST {
private:
    struct Node {
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata): data(newdata), left(NULL), right(NULL){}
    };

    typedef struct Node* NodePtr;

    NodePtr root;

    /**Private helper functions*/
    void insertDataPrimary(NodePtr root, bstdata value);
    //private helper function for insert
    //recursively inserts a value into the BST

    void insertDataSecondary(NodePtr root, bstdata value);
    //private helper function for insert
    //recursively inserts a value into the BST

    void inOrderPrint(ostream& out, NodePtr root);
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void printInfo(NodePtr root);
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void preOrderPrint(ostream& out, NodePtr root);
    //private helper function for preOrderPrint
    //recursively prints tree values in pre order

    void postOrderPrint(ostream& out, NodePtr root);
    //private helper function for postOrderPrint
    //recursively prints tree values in post order

    void makeCopy(NodePtr copy);
    //recursive helper function to the copy constructor

    void freeNode(NodePtr root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool search(NodePtr root, bstdata value);
    //recursive helper function to search
    //returns whether the value is found in the tree

    bool searchPrimary(NodePtr root, bstdata value);
    bool searchSecondary(NodePtr root, bstdata value);

    bstdata searchAndGrab(NodePtr root, bstdata value);
    //recursive helper function to search and grab the value of the searched node
    //returns the value of the searched node

    bstdata searchAndGrabPrimary(NodePtr root, bstdata value);

    bstdata searchAndGrabSecondary(NodePtr root, bstdata value);

    bstdata minimum(NodePtr root);
    //recursive helper function to minimum
    //returns the minimum value in the tree

    bstdata maximum(NodePtr root);
    //recursive helper function to maximum
    //returns the maximum value in the tree

    NodePtr deleteData(NodePtr root, bstdata value);
    //recursive helper function to deleteData
    //removes value from the tree

    void size(NodePtr root, int& size);
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int height(NodePtr root);
    //recursive helper function to the height function
    //returns the height of the tree

public:

    /**constructors and destructor*/

    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory

    /**access functions*/

    bstdata minimum();
    //returns the minimum value in the BST
    //pre: !empty()

    bstdata maximum();
    //returns the maximum value in the BST and returns it
    //pre: !empty()

    bool empty();
    //determines whether the BST is empty

    int size();
    //returns the size of the tree

    bstdata getRoot();
    //returns the value stored at the root of the BST
    //pre: !empty()

    int height();
    //returns the height of the tree

    bool search(bstdata value);
    //returns whether the value is found in the tree
    //pre: !empty()

    bool searchPrimary(bstdata value);
    bool searchSecondary(bstdata value);

    bstdata searchAndGrab(bstdata value);
    //returns the value of the searched node
    //pre: !empty()
    //pre: value is located in the tree

    bstdata searchAndGrabPrimary(bstdata value);

    bstdata searchAndGrabSecondary(bstdata value);

    /**manipulation procedures*/

    void insertDataPrimary(bstdata value);
    //inserts a new value into the BST

    void insertDataSecondary(bstdata value);
    //inserts a new value into the BST

    void removeData(bstdata value);
    //removes the specified value from the tree
    //pre: value is located in the tree

    /**additional functions*/

    void inOrderPrint(ostream& out);
    //calls the inOrderPrint function to print out the values
    //stored in the BST

    void printInfo();
    //calls the inOrderPrint function to print out the values
    //stored in the BST

    void preOrderPrint(ostream& out);
    //calls the reOrderPrint function to print out the values
    //stored in the BST

    void postOrderPrint(ostream& out);
    //calls the postOrderPrint function to print out the values
    //stored in the BST
};

#endif /* BST_H_ */

template<typename bstdata>
BST<bstdata>::BST(){
    root = NULL;
}


template<typename bstdata>
void BST<bstdata>::makeCopy(NodePtr copy){
    if (copy == NULL) {
        return;
    }
    else {
        NodePtr temp = root; //creates a temporary pointer to point at the root

        if (root == NULL){
            root = new Node(copy->data);
        }
        else {
            while (copy->data != root->data){
                if (copy->data < root->data){
                    if (root->left == NULL){
                        root->left = new Node(copy->data);
                    }
                    root = root->left;
                }
                else {
                    if (root->right == NULL){
                        root->right = new Node(copy->data);
                    }
                    root = root->right;
                }
            }
        }

        if (temp != NULL){
            root = temp; //returns the root pointer to the real root
        }

        makeCopy(copy->left);
        makeCopy(copy->right);
    }
}


template<typename bstdata>
BST<bstdata>::BST(const BST &bst){
    makeCopy(bst.root);
}

template<typename bstdata>
void BST<bstdata>::freeNode(NodePtr root){
    if (root == NULL){
        return;
    }
    else {
        freeNode(root->left);
        freeNode(root->right);
        delete root;
    }
}

template<typename bstdata>
BST<bstdata>::~BST(){
    freeNode(root);
}

template<typename bstdata>
bstdata BST<bstdata>::minimum(NodePtr root){
    if (root->left == NULL){
        return root->data;
    }
    else {
        return minimum(root->left);
    }
}

template<typename bstdata>
bstdata BST<bstdata>::minimum(){
    assert(!empty());
    return minimum(root);
}

template<typename bstdata>
bstdata BST<bstdata>::maximum(NodePtr root){
    if (root->right == NULL){
        return root->data;
    }
    else {
        return maximum(root->right);
    }
}

template<typename bstdata>
bstdata BST<bstdata>::maximum(){
    assert(!empty());
    return maximum(root);
}

template<typename bstdata>
bool BST<bstdata>::empty(){
    return (root == NULL);
}

template<typename bstdata>
void BST<bstdata>::size(NodePtr root, int& count){
    if (root == NULL) {
        return;
    }
    else {
        count++;
        size(root->left, count);
        size(root->right, count);
    }
}

template<typename bstdata>
int BST<bstdata>::size(){
    int count = 0;
    size(root, count);
    return count;
}

template<typename bstdata>
bstdata BST<bstdata>::getRoot(){
    assert(!empty());
    return (root->data);
}

template<typename bstdata>
int BST<bstdata>::height(NodePtr root){
    if (root == NULL){
        return -1;
    }
    else {
        return (max(height(root->left), height(root->right)) + 1);
    }
}

template<typename bstdata>
int BST<bstdata>::height(){
    return height(root);
}

template<typename bstdata>
bool BST<bstdata>::search(NodePtr root, bstdata value){
    if (root->data == value){
        return true;
    }
    else if (value < root->data){
        if (root->left == NULL){
            return false;
        }
        else {
            return search(root->left, value);
        }
    }
    else {
        if (root->right == NULL){
            return false;
        }
        else {
            return search(root->right, value);
        }
    }

    return false;
}

template<typename bstdata>
bool BST<bstdata>::search(bstdata value){
    assert(!empty());
    return search(root, value);
}

template<typename bstdata>
bool BST<bstdata>::searchPrimary(NodePtr root, bstdata value){
    if (root->data <= value){
        return true;
    }
    else if (value < root->data){
        if (root->left == NULL){
            return false;
        }
        else {
            return searchPrimary(root->left, value);
        }
    }
    else {
        if (root->right == NULL){
            return false;
        }
        else {
            return searchPrimary(root->right, value);
        }
    }

    return false;
}

template<typename bstdata>
bool BST<bstdata>::searchPrimary(bstdata value){
    assert(!empty());
    return searchPrimary(root, value);
}

template<typename bstdata>
bool BST<bstdata>::searchSecondary(NodePtr root, bstdata value){
    if (root->data >= value){
        return true;
    }
    else if (value > root->data){
        if (root->right == NULL){
            return false;
        }
        else {
            return searchSecondary(root->right, value);
        }
    }
    else {
        if (root->left == NULL){
            return false;
        }
        else {
            return searchSecondary(root->left, value);
        }
    }

    return false;
}

template<typename bstdata>
bool BST<bstdata>::searchSecondary(bstdata value){
    assert(!empty());
    return searchSecondary(root, value);
}

template<typename bstdata>
bstdata BST<bstdata>::searchAndGrab(NodePtr root, bstdata value){
    if (root->data == value){
        return root->data;
    }
    else if (value < root->data){
        return searchAndGrab(root->left, value);
    }
    else {
        return searchAndGrab(root->right, value);
    }
}

template<typename bstdata>
bstdata BST<bstdata>::searchAndGrabPrimary(NodePtr root, bstdata value){
    if (root->data <= value){
        return root->data;
    }
    else if (value < root->data){
        return searchAndGrabPrimary(root->left, value);
    }
    else {
        return searchAndGrabPrimary(root->right, value);
    }
}

template<typename bstdata>
bstdata BST<bstdata>::searchAndGrabSecondary(NodePtr root, bstdata value){
    if (root->data >= value){
        return root->data;
    }
    else if (value > root->data){
        return searchAndGrabSecondary(root->right, value);
    }
    else {
        return searchAndGrabSecondary(root->left, value);
    }
}

template<typename bstdata>
bstdata BST<bstdata>::searchAndGrab(bstdata value){
    assert(!empty());
    assert(search(value));
    return searchAndGrab(root, value);
}

template<typename bstdata>
bstdata BST<bstdata>::searchAndGrabPrimary(bstdata value){
    assert(!empty());
    assert(searchPrimary(value));
    return searchAndGrabPrimary(root, value);
}

template<typename bstdata>
bstdata BST<bstdata>::searchAndGrabSecondary(bstdata value){
    assert(!empty());
    assert(searchSecondary(value));
    return searchAndGrabSecondary(root, value);
}

template<typename bstdata>
void BST<bstdata>::insertDataPrimary(NodePtr root, bstdata value){
    if (value == root->data){
        return;
    }
    else if(value < root->data){
        if (root->left == NULL){
            NodePtr N = new Node(value);
            root->left = N;
        }
        else {
            insertDataPrimary(root->left, value);
        }
    }
    else {
        if (root->right == NULL){
            NodePtr N = new Node(value);
            root->right = N;
        }
        else {
            insertDataPrimary(root->right, value);
        }
    }
}

template<typename bstdata>
void BST<bstdata>::insertDataPrimary(bstdata value){
    if (root == NULL){
        root = new Node(value);
    }
    else {
        insertDataPrimary(root, value);
    }
}

template<typename bstdata>
void BST<bstdata>::insertDataSecondary(NodePtr root, bstdata value){
    if (value == root->data){
        return;
    }
    else if(value > root->data){
        if (root->right == NULL){
            NodePtr N = new Node(value);
            root->right = N;
        }
        else {
            insertDataSecondary(root->right, value);
        }
    }
    else {
        if (root->left == NULL){
            NodePtr N = new Node(value);
            root->left = N;
        }
        else {
            insertDataSecondary(root->left, value);
        }
    }
}

template<typename bstdata>
void BST<bstdata>::insertDataSecondary(bstdata value){
    if (root == NULL){
        root = new Node(value);
    }
    else {
        insertDataSecondary(root, value);
    }
}

template<typename bstdata>
typename BST<bstdata>::NodePtr BST<bstdata>::deleteData(NodePtr root, bstdata value){
    if (root == NULL){
        return root;
    }
    else if (value < root->data){
        root->left = deleteData(root->left, value);
    }
    else if (value > root->data){
        root->right = deleteData(root->right, value);
    }
    else {
        if (root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        }
        else if (root->right == NULL){
            NodePtr temp = root;
            root = root->left;
            delete temp;
        }
        else if (root->left == NULL){
            NodePtr temp = root;
            root = root->right;
            delete temp;
        }
        else {
            root->data = minimum(root->right);
            root->right = deleteData(root->right, minimum(root->right)); 
        }
    }

    return root;
}

template<typename bstdata>
void BST<bstdata>::removeData(bstdata value){
    assert(!empty());
    assert(search(value));
    root = deleteData(root, value);
}

template<typename bstdata>
void BST<bstdata>::inOrderPrint(ostream& out){
    inOrderPrint(out, root);
}

template<typename bstdata>
void BST<bstdata>::inOrderPrint(ostream& out, NodePtr root){
    if (root == NULL){
        return;
    }
    else {
        inOrderPrint(out, root->left);
        out << root->data;
        string maxTitle = maximum().getTitle();
        if (root->data.getTitle() != maxTitle){
            out << endl;
        }
        inOrderPrint(out, root->right);
    }
}

template<typename bstdata>
void BST<bstdata>::printInfo(){
    printInfo(root);
}

template<typename bstdata>
void BST<bstdata>::printInfo(NodePtr root){
    if (root == NULL){
        return;
    }
    else {
        printInfo(root->left);
        root->data.printGameInfo();
        printInfo(root->right);
    }
}

template<typename bstdata>
void BST<bstdata>::preOrderPrint(ostream& out, NodePtr root){
    if (root == NULL){
        return;
    }
    else {
        out << root->data;
        preOrderPrint(out, root->left);
        preOrderPrint(out, root->right);
    }
}

template<typename bstdata>
void BST<bstdata>::preOrderPrint(ostream& out){
    preOrderPrint(out, root);
}

template<typename bstdata>
void BST<bstdata>::postOrderPrint(ostream& out, NodePtr root){
    if (root == NULL){
        return;
    }
    else {
        postOrderPrint(out, root->left);
        postOrderPrint(out, root->right);
        out << root->data;
    }
}

template<typename bstdata>
void BST<bstdata>::postOrderPrint(ostream& out){
    postOrderPrint(out, root);
}

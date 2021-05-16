/* Insertion, searching,deleting, minimum and maximum and height of Binary search tree, Level order traversal(BFS),
                                                            Inorder, Preorder, Postorder Traversal(DFS)
                                                            
               In this example the tree looks like:
                                10
                              8    15
                            5   9     17 
                                    16   18                                              

This function also checks if this tree is a binary search tree or not. i.e all elements in left are lesser than root 
and all elements in right are greater than root. 
                                                            */
#include<iostream>
#include<queue> // For level order traversal
using namespace std;
struct BSTNode{
    int data;
    BSTNode* left;
    BSTNode* right;
};
BSTNode* getNode(BSTNode* root,int data){
    BSTNode* Node = new BSTNode();
    Node->data = data;
    Node->left = Node->right = NULL;
    return Node;
}
BSTNode* Insert(BSTNode* root,int data){
    if(root == NULL){
        root = getNode(root,data);
        return root;
    }
    else if(data <= root->data){  //Send to left side
        root->left = Insert(root->left,data);
        return root;
    }
    else{  //Send to right side
        root->right = Insert(root->right,data);
        return root;
    }
}
void levelorder(BSTNode* root){ // Breadth First Search Traversal
    BSTNode* current = root;
    queue<BSTNode*> q; // Creating a queue to store all the addresses one by one
    q.push(current); //starting with root
    while(!q.empty()){
        current = q.front();
        cout<<current->data<<" ";
        if(current->left != NULL) q.push(current->left);
        if(current->right != NULL) q.push(current->right);
        q.pop();
    }

}
void inorder(BSTNode* root){  // Depth First Search LDR; Fact: Inorder traversal prints elements in sorted order!
    if(root == NULL) return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
void preorder(BSTNode* root){ // Depth First Search DLR
    if(root == NULL) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(BSTNode* root){ // Depth First Search LRD
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
int max(BSTNode* root){
    if(root == NULL) return -1; //Empty Tree
    else{
        while(root->right!=NULL){
            root = root->right; //Keep going to the right bottom to reach the max element
        }
        return root->data;
    }
}
int min(BSTNode* root){
    if(root == NULL) return -1; //Empty Tree
    else{
        while(root->left!=NULL){
            root = root->left; //Keep going to the left bottom to reach the min element
        }
        return root->data;
    }
}
BSTNode* Findmin(BSTNode* root){ // Same as above but this returns root itself
    if(root == NULL) return NULL; //Empty Tree
    else{
        while(root->left!=NULL){
            root = root->left; //Keep going to the left bottom to reach the min element
        }
        return root;
    }
}
int height(BSTNode* root){
    if(root == NULL) return -1; //Height of empty tree
    else{
        int leftheight,rightheight;
        leftheight = height(root->left);
        rightheight = height(root->right);
        return max(leftheight,rightheight)+1;
    }
}
bool Search(BSTNode* root,int data){
    if(root == NULL) return false;
    else if(root->data == data) return true;
    else if(data <= root->data) return Search(root->left,data); //Search is left
    else return Search(root->right,data); //Search is right
}
bool checkBSTutil(BSTNode* root, int minVal, int maxVal){
    if (root == NULL) return true;
    if (root->data > minVal && root->data < maxVal && checkBSTutil(root->left,minVal,root->data) && checkBSTutil(root->right,root->data,maxVal))
    {
        return true;
    }
    else return false;
}
bool checkBST(BSTNode* root){
    return checkBSTutil(root,INT8_MIN,INT8_MAX);
}
BSTNode* Delete(BSTNode* root, int d){
    /* There can be three cases in deleting a node
        Case 0: Delete leaf node
        Case 1: Delete a node with one child
        Case 2: Delete a node with two children */
        if(root == NULL) return NULL;
        else if(d < root->data) root->left = Delete(root->left,d);
        else if(d > root->data) root->right = Delete(root->right,d);
        else{ // This block enters if th element has been found.
            if(root->left == NULL && root->right == NULL){ //Case 0
                delete root;
                root = NULL; 
            }
            else if(root->left == NULL){ // Case 1
                BSTNode* temp = root;
                root = root->right;
                delete temp;   
            }
            else if(root->right == NULL){ // Case 1
                BSTNode* temp = root;
                root = root->left;
                delete temp;
            }
            else{ // Case 2 - Go right and find the min element present in the right
                BSTNode *temp = Findmin(root->right);
			    root->data = temp->data;
			    root->right = Delete(root->right,temp->data);  
            }
        }
        return root;
        
    }
int main(){
    BSTNode* root = NULL; //Declare locally instead of global. This is nothing but head
    int x,maxele,minele,h,d;
    root = Insert(root,10);
    root = Insert(root,8);
    root = Insert(root,9);
    root = Insert(root,15);
    root = Insert(root,17);
    root = Insert(root,5);
    root = Insert(root,16);
    root = Insert(root,18);
    cout<<"\n All nodes were inserted successfully! ";
    if(checkBST(root)) cout<<"\n This is a BST! ";
    else cout<<"\n This is not a BST!";
    h = height(root);
    cout<<"\n The height of the tree is: "<<h;
    maxele = max(root);
    cout<<"\n Max element in the BST is: "<<maxele;
    minele = min(root);
    cout<<"\n Min element in the BST is: "<<minele;
    cout<<"\n Level order traversal (Breadth First Search Traversal): ";
    levelorder(root);
    cout<<"\n Inorder traversal (Depth First Search Traversal) - LDR: ";
    inorder(root);
    cout<<"\n Preorder traversal (Depth First Search Traversal) - DLR: ";
    preorder(root);
    cout<<"\n Postorder traversal (Depth First Search Traversal) - LRD: ";
    postorder(root);
    cout<<"\n Enter element to search in the BST: ";
    cin>>x;
    if(Search(root,x)){
        cout<<"\n Element is there in this BST!";
    }
    else{
        cout<<"\n This element is not present in the BST!";
    }
    cout<<"\n Enter element to delete from this tree: ";
    cin>>d;
    root = Delete(root,d);
    cout <<"\n After deleting (Levelorder): ";
    levelorder(root);
}
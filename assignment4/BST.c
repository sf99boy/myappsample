//Chris Cai
//cjcai
//11/26/18
//CMPS-12B
//BST.c
//Contains Binary Search Tree manipulation routines

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "BST.h"

BSTObj* findParent(char* search_key, BSTObj* T);
BSTObj* findLeftMost(BSTObj* T);

// Constructor for tree objects
BSTObj* newBSTObj(char *new_data){
	//Allocate memory to the new node of size BSTObj
	BSTObj* newNode;
	newNode = (BSTObj *)malloc( sizeof(BSTObj) );
	//Initialize data of the new node
	char* data = (char *)malloc( strlen(new_data) + 1);
	strcpy(data, new_data);
	newNode->term = data;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	return newNode;
}

// add a new node to the BST with the new_data values, space must be allocated in the BST node
void insert(char *new_data,  BSTObj **pBST){
	//Check if new_data inserted is NULL
	if(new_data == NULL){
		fprintf(stderr, "Error: new_data is NULL.\n");
		return;
	}
	//Check if pBST is NULL, return if it is
	if(pBST == NULL){
		fprintf(stderr, "Error: pBST is NULL.\n");
		return;
	}
	//BSTObj* newNode = newBSTObj(new_data);
	//Check if *pBST is NULL, if it is set *pBST to the new node, return
	if(*pBST == NULL){
		*pBST = newBSTObj(new_data);
		return;
	}
	//Find place to insert the node in the tree
	//Go to the left if it is smaller
	if( strcmp( new_data, (*pBST)->term) < 0 ){
		insert( new_data, &( (*pBST)->leftChild) );
	}

	//Otherwise enter it to the righti
	else{
		insert( new_data, &( (*pBST)->rightChild) );
	}
	
}

// print to OUT the inorder traversal
// left print right
void inorderTraverse(FILE *out, BSTObj *T){
	if(T == NULL){
		return;
	}
	if(out == NULL){
		fprintf(stderr, "out file is NULL.\n");
		return;
	}
	//BSTObj should not be NULL
	if(T != NULL){
		inorderTraverse(out, T->leftChild);
		fprintf(out, "%s ", T->term);
		inorderTraverse(out, T->rightChild);
	}
}

// print to OUT the preorder traversal
// print left right
void preorderTraverse(FILE *out, BSTObj *T){
	if(T == NULL){
		return;
	}
	if(out == NULL){
		fprintf(stderr, "out file is NULL.\n");
		return;
	}
	if(T != NULL){
		fprintf(out, "%s ", T->term);
		preorderTraverse(out, T->leftChild);
		preorderTraverse(out, T->rightChild);
	}
}

// print to OUT the postorder traversal
// left right print
void postorderTraverse(FILE *out, BSTObj *T){
	if(T == NULL){
		return;
	}
	if(out == NULL){
		fprintf(stderr, "out file is NULL.\n");
		return;
	}
	if(T != NULL){
		postorderTraverse(out, T->leftChild);
		postorderTraverse(out, T->rightChild);
		fprintf(out, "%s ", T->term);
	}
}

// print the leaves of the tree in inorder to OUT
// left print right
// leaves have no children leftChild = NULL rightChild = NULL
void inorderLeaves(FILE *out, BSTObj *T){
	if(T == NULL){
		return;
	}
	if(out == NULL){
		fprintf(stderr, "out file is NULL.\n");
		return;
	}
	if(T != NULL){
		inorderLeaves(out, T->leftChild);
		//Check if nodes have any children
		if(T->leftChild == NULL && T->rightChild == NULL){
			fprintf(out, "%s ", T->term);
		}
		inorderLeaves(out, T->rightChild);
	}
}


// return TRUE if the item_to_find matches a string stored in the tree
int find(char *term_to_find, BSTObj *T){
	if(term_to_find == NULL){
		fprintf(stderr, "term_to_find should not be NULL.\n");
		return FALSE;
	}
	//return FALSE if BSTObj is NULL
	if(T == NULL){
		fprintf(stderr, "Can not find node.\n");
		return FALSE;
	}
	//return TRUE if searchkey is equal to the node's data
	else if( strcmp(term_to_find, T->term) == 0){
		return TRUE;
	}
	//If the searchkey is less than or equal to the node's data go left
	//Otherwise go right
	if( strcmp(term_to_find, T->term) < 0){
		return find(term_to_find, T->leftChild);
	}
	else{
		return find(term_to_find, T->rightChild);
	}
	return FALSE;
}
  
// compute the height of the tree
// call with height = 0 and root of tree
// root starts at 1, height is number of nodes in the tallest subtree
int treeHeight(BSTObj *T, int height){
	//Tree is empty, height is 0
	if(T == NULL){
		return 0;
	}
	//Call height recursively
	//Set heights of left and right subtrees
	//int left subtree and int right subtree
	int lSub = treeHeight(T->leftChild, height);
	int rSub = treeHeight(T->rightChild, height);
	//Find which subtree has greater height, add one each time
	if(lSub >= rSub){
		return treeHeight(T->leftChild, height) + 1;
	}
	else{
		return treeHeight(T->rightChild, height) + 1;
	}
    
}

// create and return a complete memory independent copy of the tree 
BSTObj * copyTree(BSTObj *T){
	if(T == NULL){
		return T;
	}
	//Create a new Tree and allocate memory to it
	BSTObj* cTree = newBSTObj(T->term);
	//Copy data of tree into copy of tree
	//cTree->term = T->term;
	//Set its data and left and right child to ones of the passed Tree object
	cTree->leftChild = copyTree(T->leftChild);
	cTree->rightChild = copyTree(T->rightChild);
	return cTree;
}

// remove all the nodes from the tree, deallocate space and reset Tree pointer
// post order traverse, starts at bottom then go up along the tree starting with the leaves
// free memory
void makeEmpty(BSTObj **pT){
	if(pT == NULL){
		fprintf(stderr, "Can not empty an already empty Tree.\n");
		return;
	}
	//Go left if not NULL
	if((*pT)->leftChild != NULL){
		makeEmpty(&((*pT)->leftChild));
	}
	//Go right if not NULL
	if((*pT)->rightChild != NULL){
		makeEmpty(&((*pT)->rightChild));
	}
	//Free the data and node
	free((*pT)->term);
	free(*pT);
	*pT = NULL;
}

// delete a node within the tree, deallocate space and reset tree pointer
// 3 cases: leaf node, node with one child, node with two children
int deleteItem(char *term_to_delete, BSTObj **pT){
	//Check if term_to_delete is NULL
	if(term_to_delete == NULL){
		fprintf(stderr, "term_to_delete should not be NULL.\n");
		return FALSE;
	}
	//Check if pT is NULL
	if(pT == NULL){
		fprintf(stderr, "pT should not be NULL.\n");
		return FALSE;
	}
	//Check if Tree is empty
	if(*pT == NULL){
		fprintf(stderr, "Can not delete from an empty tree or node does not exist.\n");
		return FALSE;
	}
	//Delete a node with two children
	else if ( strcmp(term_to_delete, (*pT)->term) == 0 && (*pT)->leftChild != NULL && (*pT)->rightChild != NULL){
		//Find left most node in right subtree
		BSTObj* temp = findLeftMost((*pT)->rightChild);
		//Copy its term to the node to be deleted
		char* temp_data = (char *)malloc(strlen(temp->term)+1);
		strcpy(temp_data, temp->term);
		//Free old pointer to old term
		free((*pT)->term);
		(*pT)->term = temp_data;
		
		//Delete leftmost node

		//left most node has no children
		if(temp->leftChild == NULL && temp->rightChild == NULL){
			//Set the pointer to the left most node NULL
			if(temp == findParent(temp->term, *pT)->rightChild){
				findParent(temp->term, *pT)->rightChild = NULL;
			}
			else{
				findParent(temp->term, *pT)->leftChild = NULL;
			}
			free(temp->term);
			free(temp);
			temp = NULL;
			return TRUE;
		}
		//left most node has one child
		//left most node has a right child
		if(temp->rightChild != NULL){
			//If temp (leftMost node) is the left child of its parent
			if(findParent(temp->term, *pT)->leftChild == temp){
				//the parent's leftChild (leftMost node)  equals the temp's rightChild (leftMost node rightChild)
				findParent(temp->term, *pT)->leftChild = findParent(temp->term, *pT)->leftChild->rightChild;
			}
			//If temp (leftMost node) is the right child of its parent
			else if(findParent(temp->term, *pT)->rightChild == temp){
				//the parent's rightChiild (leftMost node) equals the temp's rightChild (leftMOst node rightChild)
				findParent(temp->term, *pT)->rightChild = findParent(temp->term, *pT)->rightChild->rightChild;
			}
			free(temp->term);
			free(temp);
			temp = NULL;
			return TRUE;
		}
	}
	//Delete a leaf node
	//Node's right and left child are both null
	else if( strcmp(term_to_delete, (*pT)->term) == 0 && (*pT)->leftChild == NULL && (*pT)->rightChild == NULL){
		free((*pT)->term);
		free(*pT);
		*pT = NULL;
		return TRUE;
	}
	//Delete a node with one child
	//Either the node's left or right child is null
	else if( strcmp(term_to_delete, (*pT)->term) == 0 && ((*pT)->leftChild != NULL || (*pT)->rightChild != NULL)){
		//The node to be deleted has only a left child
		if((*pT)->leftChild != NULL && (*pT)->rightChild == NULL){
			//Set temp node to be deleted node
			BSTObj* temp = *pT;
			//set node to its left child
			*pT = (*pT)->leftChild;
			//delete temp node
			free(temp->term);
			free(temp);
			temp = NULL;
			return TRUE;
		}
		//The node to be deleted has only a right child
		else if((*pT)->rightChild != NULL && (*pT)->leftChild == NULL){
			//Set temp node to be deleted node
			BSTObj* temp = *pT;
			//Set node to its right child
			*pT = (*pT)->rightChild;
			//delete temp node
			free(temp->term);
			free(temp);
			temp = NULL;
			return TRUE;
		}

	}
	//Go left if strcmp of term_to_delete and (*pT)->term is less than 0, right otherwise
	if( strcmp(term_to_delete, (*pT)->term) < 0){
		return deleteItem(term_to_delete, &((*pT)->leftChild));
	}
	else{
		return deleteItem(term_to_delete, &((*pT)->rightChild));
	}
	return FALSE;
}

// Helper Functions:
// retrieveNode
// Traverses the tree and finds the node to delete and the parent of the node

//findLeftMost
//find the leftmost element in a tree
BSTObj* findLeftMost(BSTObj *T){
	if(T == NULL){
		return NULL;
	}
	//Go left while the left childs of the tree are not NULL
	while(T->leftChild != NULL){
		//Set node to the left child
		T = T->leftChild;
	}
	//Return left most node
	return T;
}

//Find parent of a node
BSTObj* findParent(char* search_key, BSTObj* T){
	//If T is NULL return NULL
	if(T == NULL){
		return NULL;
	}
	//If the search_key passed is NULL return NULL
	if(search_key == NULL){
		return NULL;
	}
	//Return NULL if both childs are NULL
	if(T->leftChild == NULL && T->rightChild == NULL){
		return NULL;
	}
	//If left child is not NULL and the term matches the left child's term or the right child is not NULL and the term matches the right child's term return the parent node
	else if((T->leftChild != NULL && strcmp(T->leftChild->term, search_key) == 0) || (T->rightChild != NULL && strcmp(T->rightChild->term, search_key) == 0)){
		//fprintf(stdout, "%s\n", T->term);
		return T;
	}
	//Go left if srtcmp is less than 0 and right otherwize
	if(strcmp(search_key, T->term) < 0){
		return findParent(search_key, T->leftChild);
	}
	else{
		return findParent(search_key, T->rightChild);
	}
	return T;
}



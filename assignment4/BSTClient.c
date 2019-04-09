//Chris Cai
//cjcai
//11/26/18
//CMPS-12B
//BSTClient.c
//Test client for Binary Search Tree ADT
//This is just an example, you will be doing a lot more tests!

#include "stdio.h"
#include <string.h>
#include "BST.h"

BSTObj* findParent(char* key, BSTObj* T);
BSTObj* findLeftMost(BSTObj* T);

int main(int argc, char* argv[]){

	BSTObj  *T;
	//BSTObj *cT;
    
	T = NULL;
	//cT = NULL;

	printf("\n");

	//Lexicographic Order string comparison, dictionary order, strcmp()
	printf("inserting a lot of nodes to build a tree \n");
	insert("cat", &T); //312
	insert("rat", &T); //327
	insert("bat", &T); //311
	insert("crow", &T); //443
	insert("dog", &T); //314
	insert("dan", &T); //307
	insert("dtsh", &T); //435 
	insert("fox", &T); //333
	insert("aaz", &T); //316
	insert("zoo", &T); //344
	//insert("fpx", &T);
	//insert("fzz", &T);
	insert("bed", &T);
	//insert("zzo", &T);
	//insert("zxo", &T);
	//insert("fwo", &T);
	//insert("agc", &T);
	//insert("aec", &T);
	//insert("adc", &T);
	//insert("acc", &T);
	//insert("ahc", &T);
	//insert(NULL, &T);
	//insert("cheat", NULL);
	//insert(NULL, NULL);

	printf("\n");
	//cT = copyTree(T);
	//makeEmpty(&cT);
	//makeEmpty(&T);
	printf("inorder traverse == \n");
	inorderTraverse(stdout, T);
	printf("\n== after traverse ==\n");
	printf("\n");

	printf("preorder traverse == \n");
	preorderTraverse(stdout, T);
	printf("\n== after traverse ==\n");
	printf("\n");

	printf("postorder traverse == \n");
	postorderTraverse(stdout, T);
	printf("\n== after traverse ==\n");
	printf("\n");

	printf("inorderLeaves traverse == \n");
	inorderLeaves(stdout, T);
	printf("\n== after traverse ==\n");
	printf("\n");
	
	printf("Find (0)No Match (1)Match :");
	printf("%d\n", find("aaz", T));
	printf("Find:%d\n", find("dish", T));
	printf("\n");

	printf("treeHeight:%d\n", treeHeight(T, 0));
	printf("\n");
	
	/*printf("Tree:%p\n", T);
	printf("& of Tree:%p\n", &T);
	//printf("Copy of Tree:%p\n", copyTree(T));
	cT = copyTree(T);
	//insert("fpx", &cT);
	printf("Copy of Tree:%p\n", cT);
	printf("Copy of & of Tree:%p\n", &cT);
	inorderTraverse(stdout, cT);
	printf("\n");
	preorderTraverse(stdout, cT);
	printf("\n");
	postorderTraverse(stdout, cT);
	printf("\n");
	inorderLeaves(stdout, cT);
	printf("\n");
	printf("Find:%d\n", find("dans", cT));
	printf("Find:%d\n", find("bat", cT));
	printf("Height:%d\n", treeHeight(cT, 0));
	makeEmpty(&cT);
	printf("\n");*/

	//printf("\nEmptying Tree\n");
	//makeEmpty(&T);
	//printf("\n");
	
	//printf("About to delete a leaf node in BST.\n");
	//printf("%d\n", deleteItem("zoo", &T));
	inorderTraverse(stdout, T);
	printf("\n");
	printf("\n");

	printf("About to delete a node with one child in BST.\n");
	printf("%d\n", deleteItem("cat", &T));//2 (children)
	printf("%d\n", deleteItem("rat", &T));//2
	printf("%d\n", deleteItem("dog", &T));//2
	printf("%d\n", deleteItem("crow", &T));//1
	printf("%d\n", deleteItem("bat", &T));//2
	printf("%d\n", deleteItem("dtsh", &T));//1
	printf("%d\n", deleteItem("dan", &T));//0
	printf("%d\n", deleteItem("fox", &T));//0
	printf("%d\n", deleteItem("aaz", &T));//0
	printf("%d\n", deleteItem("zoo", &T));//0
	printf("%d\n", deleteItem("bed", &T));//0 
	//insert("aaz", &T);
	//BSTClient 2> errors.txt
	inorderTraverse(stderr, T);
	printf("\n");
	postorderTraverse(stderr, T);
	printf("\n");
	preorderTraverse(stderr, T);
	printf("\n");
	inorderLeaves(stdout, T);
	//cT = copyTree(T);
	//makeEmpty(&cT);
	//makeEmpty(&T);
	printf("\n");
	printf("\n");

	printf("Find Parent Node.\n");
	//printf("%s\n", findParent("cat", T)->term);
	//printf("%p\n", T->leftChild);
	//printf("%s\n", T->leftChild->term);
	
	printf("\n");

	printf("Find left most node in the tree.\n");
	//printf("%d\n", treeHeight(T, 0));
	//printf("%d\n", find("fox", T));
	//printf("%p\n", findLeftMost(T));
	//printf("%s\n", findLeftMost(T)->term);
	//printf("%s\n", T->rightChild->leftChild->rightChild->term);
	printf("\n");

	//Can not use strcmp for string digits
	/*char* c = "cat";
	char* d = "rat";
	printf("strcmp(c, d):%d\n", strcmp(c, d));
	printf("\n");*/
   
	return 0;
}

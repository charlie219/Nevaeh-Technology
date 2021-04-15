#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;
struct Tree{
	int data;
	int priority;
	Tree* right;
	Tree* left;	
};

Tree* root = NULL;

Tree* rotate_Right(Tree* node){
	Tree *node_left = node->left , *node_right = node_left->right;
	
	node_left->right = node;
	node -> left = node_right;

	return node_left;
}

Tree* rotate_Left(Tree* node){
        Tree *node_right = node->right, *node_left = node_right->left;

        node_right->left = node;
        node -> right = node_left;

        return node_right;
}

Tree* create( int val, int prior){
	Tree* new_node = new Tree;
        new_node->data = val;
        new_node->priority = prior;
        new_node->left=NULL;
        new_node->right = NULL;

	return new_node;	

}

Tree* insert(int val, int prior, Tree* node){
	if(node == NULL)
		return create( val , prior);
		

	if(node->data < val){
		node -> right = insert(val , prior, node-> right);
		
		if(node->priority < node->right->priority )
			node = rotate_Left(node);
	}
	else{
		node ->left = insert(val , prior, node-> left);
                
                if(node->priority < node->left->priority )
                        node = rotate_Right(node);
	}
	
	return node;
}
Tree* delete_node(Tree* node, int val){
	if(node == NULL)
		return node;

	if (val < node->data)
        	node->left = delete_node(node->left, val);
    	else if (val > node->data)
        	node->right = delete_node(node->right, val);

	else if (node->left == NULL)
		node = node->right;
	else if (node->right == NULL)
		node = node->left;

	else if (node->left->priority < node->right->priority)
    	{
        	node = rotate_Left(node);
        	node->left = delete_node(node->left, val);
    	}
    	else
    	{
        	node = rotate_Right(node);
        	node->right = delete_node(node->right, val);
    	}
			
	return node;
}
bool search(Tree* node, int val){
        if(node == NULL)
                return false;
        if(node->data == val)
                return true;

        return search(node->right , val) || search(node->left , val);
}

int display_Pre(Tree* root){
	
	if(!root)
		return 1;
	cout << "(" << root->data << "," << root->priority << ") ";
	display_Pre(root->left);
	//cout << "(" << root->data << "," << root->priority << ") ";
	display_Pre(root->right);
	
	return 0;
}
int display_In(Tree* root){

        if(!root)
                return 1;
//      cout << "(" << root->data << "," << root->priority << ") ";
        display_In(root->left);
        cout << "(" << root->data << "," << root->priority << ") ";
	display_In(root->right);

        return 0;
}
int main(int arg_len, char* args[]){
	int ch, num, prior;
	string ans = "Yes";
	do{
		cout << "\n1 ... Insert \n2 ... Delete \n3 ... Search \n4 ... Exit";
		cout << "\nEnter Your Choice:- ";
		cin >> ch;
		
		if(ch < 1 || ch >4){
			cout << "\n\nWrong Option try again\n\n";
			continue;
		}
		switch(ch){
			case 1:	cout << "\nEnter the number to be inserted and its priority \n";
				cin >> num >> prior;
				root = insert(num, prior, root);
				break;
			case 2: cout << "\nEnter the number to be deleted \n";
                                cin >> num;
                       		root = delete_node(root, num);
                                break;
			case 3: cout <<"\nEnter the number to be searched \n";
				cin >> num;
				ans = search(root, num) ? "YES" : "NO";
				cout << ans << endl ;
				break;
			case 4 : cout << "\n\n\t\tThanks ...\n\n";
				 cout << "Tree Status :- ";
				 if(root == NULL)
					cout << "Empty Treap";
				 else{
					cout << "\nPreorder - ";
				 	display_Pre( root );
					cout << "\nInorder - ";
					display_In(root);
				 }
                		 cout << endl << endl ;
				exit(0);
			//default: cout << "Wrong Option try again";

		};
		cout << "\n\nTask Completedn\n\n";
		cout << "Tree Status :- ";
		if(root == NULL)
                	cout << "Empty Treap";
                else{
                        cout << "\nPreorder - ";
                        display_Pre( root );
                        cout << "\nInorder - ";
                        display_In(root);
               }
		cout << endl << endl ;
	}while(true);
}

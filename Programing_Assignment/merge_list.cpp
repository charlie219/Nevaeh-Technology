#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

class Node{
	public:
		int data;
		Node* next;
};

void append(Node** head_ref, int new_data)
{
	Node* new_node = new Node();

	Node *last = *head_ref; 
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return;
}

void print(Node *node)
{
	while (node != NULL)
	{
		cout<<" "<<node->data;
		node = node->next;
	}
	cout << endl;
}

int main(int arg_len, char* args[]){

	Node* a, *ans= NULL, *p;
	priority_queue < pair< int, int> > h;
	pair <int , int> temp;

	int he, n = atoi(args[1]), len[n], l[n];
	//cout << n;
	Node* s[n];
	
	for(int i = 0 ; i < n ; i ++){
		cout << i+1 << "th list length followed by its content\n";
		cin >> l[i];
		s[i] = NULL;
        	for(int ii= 0 ; ii< l[i] ; ii++){
                	cin >> he;
                	append(&s[i] , he);
        	}
	}
	
	for(int ii= 0 ; ii< n ; ii++){
                len[ii]=0;
                temp.first = -s[ii]->data, temp.second = ii;
		h.push(temp);
		//cout << -temp.first << " " << temp.second << endl;

        }

	while ( !h.empty() ){
		
		temp = h.top();
		append(&ans,-temp.first);
		//cout << -temp.first << " " << temp.second << endl;
		he = temp.second;
		s[he] = s[he]->next;
		h.pop();
		if(s[he] == NULL )
			continue;
		temp.first = -s[he]->data,temp.second = he;
		
		h.push(temp);
		print(ans);
		//cout << endl;
	}
	
	print(ans);

}

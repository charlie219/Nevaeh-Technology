#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

unordered_map<int , vector<int> > graph;
vector<bool> visited;
int n,m;
bool dfs(int node, int val){
	int next;
	//cout << node << " " << val << " " << visited[1]<< endl;
	
	if(graph.find(node) == graph.end())
		return false;
	for(int i = 0 ; i <graph[node].size() ; i++){
		next = graph[node][i];
		//cout << "*" << next << endl;
		if(visited[next])
			continue;
		visited[next] = true;
		if(next == val || dfs(next , val))
			return true;
        }
	return false;
}
bool chk(int node){
	return dfs(node , node);
}
int main(int arg_len, char* args[]){

	//unordered_map<int , vector<int>> graph;
	n = atoi(args[1]), m=atoi(args[2]);
	int  a, b ; 
	cout << "Enter the edges: \n";
	for(int i= 0 ; i<m ; i++){
		cin >> a >> b;
		graph[a].push_back(b);
	}
	for(int i=0 ; i <= n ;i++)
		visited.push_back(false);

	for(int i=1 ; i<=n ; i++){
		visited.clear();
		for(int j=0 ; j <= n ; j++)
                	visited.push_back(false);
		if(chk(i)){
			cout << "The Graph has a SCC\n";
			return 0;
		}
	}
	cout << "The Graph do not have a SCC\n";
}

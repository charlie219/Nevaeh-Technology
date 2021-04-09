#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;
vector<int> cal_range(priority_queue < pair< int, int> > n){
	int maxi = -99999 , mini = 100000;
	vector<int> a;
	pair <int , int> temp;
	while(n.empty() == false){
		temp = n.top();
		maxi = maxi < -temp.first ?  -temp.first : maxi;
		mini = mini > -temp.first ?  -temp.first : mini;
		n.pop();
	}
	
	a.push_back(maxi);
	a.push_back(mini);
	a.push_back(maxi - mini);
	//cout << mini << " " << maxi <<endl;
	return a;
}
void print(vector<int> a){
	
	for(int i=0 ; i< a.size() ; i++)
		cout << a[i] << " ";
	cout << endl ;
}
int main(int arg_len, char* args[]){

	vector<int> a, ans;
	priority_queue < pair< int, int> > h;
	pair <int , int> temp;
	vector < vector<int> > s;
	
	int he, n = atoi(args[1]), len[n], l[n];
	//cout << n;

	for(int i = 0 ; i < n ; i ++){
		cout << i+1 << "th array length followed by its content\n";
		cin >> l[i];
		cout << "End";
        	for(int ii= 0 ; ii< l[i] ; ii++){
                	cin >> he;
                	a.push_back(he);
        	}
        	s.push_back(a);
        	a.clear();
	}
	
	cout << "End";
	for(int ii= 0 ; ii< n ; ii++){
                len[ii]=0;
                temp.first = -s[ii][0], temp.second = ii;
		h.push(temp);
		cout << -temp.first << " " << temp.second << endl;

        }

	while (h.empty() == false){
		
		temp = h.top();
		ans.push_back(-temp.first);
		//cout << -temp.first << " " << temp.second << endl;
		he = temp.second;
		len[he]++;
		h.pop();
		if(len[he] >= l[he])
			continue;
		temp.first = -s[he][len[he]],temp.second = he;
		
		h.push(temp);
		print(ans);
		//cout << endl;
	}
	
	print(ans);

	cout << ans.size() << endl;
	
}

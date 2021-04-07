#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;

void print(vector<int> s){
	for(int i=0; i<s.size(); i++)
		cout << s[i] << " ";
	cout << endl;
}
vector<int> LIS(vector<int> arr){
	vector<int> lis;
	int n= arr.size(), max= 0;	
	for(int i=0 ; i<n; i++){
		lis.push_back(1);
		for(int j= 0; j < i ;  j++)
			if(arr[j]< arr[i] && lis[i]< lis[j]+1)
				lis[i] = lis[j]+1;
	}
	return lis;
}

vector<int> find_seq(vector<int> lis, vector<int> arr, int pos){
	vector<int> res;
	int val= lis[pos] - 1;
	
	for(int i = pos-1 ; i >= 0; i--){
		if(lis[i] == val){
			res.push_back(arr[i]);
			val--;
		}
	}
	return res;
}

int solve(vector<int> inp){
	vector<int>  lis1, lis2,dupli, sum;
	int n = inp.size();
	dupli = inp;

        lis1= LIS(inp);
	//print(lis1);	
        reverse(dupli.begin(), dupli.end());
        lis2 = LIS(dupli);
        reverse(lis2.begin(), lis2.end());
	//print(lis2);
	
	pair<int,int> max_pos;
	for(int i=0; i<n; i++){
		if(max_pos.first < lis1[i] + lis2[i]){
			max_pos.second = i;
			max_pos.first = lis1[i] + lis2[i];
		}
	}
	//cout << max_pos.first << " " << max_pos.second << endl;

	vector<int> ans,temp;
	ans = find_seq(lis1, inp, max_pos.second); 
	reverse(ans.begin(), ans.end());

	ans.push_back(inp[max_pos.second]);
	reverse(lis2.begin(), lis2.end());
	temp = find_seq(lis2, dupli, n-1-max_pos.second);
	
	for(int i=0 ; i< temp.size(); i++)
		ans.push_back(temp[i]);
	
	cout << "\n\n\nLongest Bitonic sequence : ";
	print(ans);

	return ans.size();
}
int main(int arg_len, char* args[]){
	vector<int> inp, lis1, lis2,dupli;
	int len= atoi(args[1]), ans_len;
	for(int i=0; i<len; i++)
		inp.push_back(atoi(args[i+2]));
	
	auto start = high_resolution_clock::now();
	solve(inp);
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Execution Time:- " << duration.count() << " ms\n\n" << endl;
}

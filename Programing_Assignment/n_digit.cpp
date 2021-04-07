#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <vector>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
#define M 64

bool check(bitset<M> bin, int n){
	for(int i = 1 ; i < n-1 ; i++)
		if( bin[i] == 1 && (bin[i-1] == 1 || bin[i+1] == 1))
			return false;
	
	return true;
}

void print(bitset<M> bin, int n){
	for(int i = n-1 ; i >= 0 ; i--)
		cout << bin[i];
	
	cout << endl;
}

void solve(int n){
	uint64_t m = pow(2 , n), count = 0;

	for(int i=0 ; i < m ; i++){
		bitset<M> bin(i);

		if( check( bin , n)){
			print(bin, n );
			count++;
		}
	}
	cout << "\n\nNumber of n–digit binary strings without any consecutive 1's := " << count << endl; 
}

int main(int arg_len, char* args[]){
	int n = atoi(args[1]);
	auto start = high_resolution_clock::now();
	solve(n);
	cout << "Execution time:- " << duration_cast<microseconds>(high_resolution_clock::now() - start ).count() << " ms\n\n" << endl;
}

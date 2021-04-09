#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;
//int mat[][] =  {{0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {1, 1, 0, 1, 1}, {1, 1, 1, 1, 1}};
void print(vector< vector <int> > mat , int n , int m){
	
	for(int i = 0; i < n ; i++){
		for(int j = 0 ; j < m ; j++ )
			cout << mat[i][j];

		cout << endl;
	} 
}
int main(){
	vector< vector <int> > mat;
	int x[][4] =   {{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 1, 0, 1},
			{1, 1, 1, 1}};
	int n = 4 , m = 4 , area=1 , count = 0 , min =890212;
	vector<int> a;
	for(int i = 1; i < n ; i++)
                for(int j = 0 ; j < m ; j++ )
                       x[i][j] += x[i-1][j];
	
	
	for(int i = 0; i < m ; i++){
		a.clear();
                for(int j = 0 ; j < n ; j++ )
                        a.push_back(x[j][i]);
		reverse(a.begin(), a.end());
                mat.push_back(a);
        }
	
	sort(mat.begin(), mat.end());
	print(mat , m , n);
	for(int i = 0; i < m  ; i++){
		count = mat[i][0]*(m-i-1);
		area = area < count ? count : area;
	}

	cout << "Largest Area = " << area<<endl;
}

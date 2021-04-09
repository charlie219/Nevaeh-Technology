#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int move_x[][2] = {{0,1},{0,-1}};
int move_y[] = {1, 0};
int mat[][5] =  {{1,1,-1,1,1},
		 {1,0,0,-1,1},
		 {1,1,1,1,-1},
		 {-1,-1,1,1,1},
		 {1,1,-1,-1,1}};
vector< vector <int> > visited;
int n = 5 ;
int move(int x, int y){
	//cout << x << " " << y << endl;
	int max_point = 0, odd= x%2, te=0;
	int r , c;	
	for(int i=0 ; i < 2 ; i++){
		r = x + move_y[i];
		c = y + move_x[odd][i];
		//cout << "*" << r << " " << c << endl;	
		if((0 <= r && r < n) and (0 <= c && c < n) and visited[r][c] != 1 and mat[r][c] != -1){
			visited[r][c] = 1;
			max_point = max(max_point , move( r, c));
			visited[r][c] = 0;
		}
	}
	return max_point + mat[x][y];
}
int main(){
	vector <int> temp;
	for(int i=0 ; i < 5 ; i++){
		temp.clear();
		for(int j = 0 ; j < 5 ; j++)
			temp.push_back(0);
		visited.push_back(temp);
	}
	
	cout << "Maximum Points = " << move(0,0) << endl;
	
}

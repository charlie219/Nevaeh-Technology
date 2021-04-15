#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int movex[] = { 1, 2, 2, 1, -1, -2, -2, -1};
int movey[] = { 2, 1, -1, -2, -2, -1, 1, 2};
int n = 8;
bool visited[8][8];
int des_x, des_y, short_path[8][8];
int place_knight(int x , int y, int k){
	
	int r,c, mini = 99999 , temp = 0;
	//cout << x << " " << y << endl ;
	if(x == des_x && y == des_y){
		//cout << k << endl;
		return k;
	}
	for(int i=0 ; i< 8 ;i++){
		r = x + movex[i];
		c = y + movey[i];
		if((0<=r && r<n) && (0<=c && c<n) && ! visited[r][c]){
			visited[r][c] = true;
			if( short_path[r][c] == -1)
				short_path[r][c] = place_knight(r,c,0);
			mini = min(mini, short_path[r][c]);	
			visited[r][c] = false;
		}
	}
	return mini + k + 1;
}
int main(int arg_len, char* args[])
{

	int src_x = atoi(args[1]), src_y =  atoi(args[2]);
	des_x =  atoi(args[3]), des_y = atoi(args[4]);
	for(int i = 0; i <8 ; i++){
		for(int j= 0 ; j<8 ; j++){
			visited[i][j] = false;
			short_path[i][j] = -1;
		}
	}
			
	visited[src_x][src_y] = 0;
	int ans = place_knight(src_x ,src_y, 0);
	cout << "Answer= " << ans << endl;
	
}

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
int movex[] = { 1, 2, 2, 1, -1, -2, -2, -1};
int movey[] = { 2, 1, -1, -2, -2, -1, 1, 2};
int board[8][8];
int print(){
	for(int i=0; i<8 ; i++){
		for(int j=0; j<8 ; j++)
			cout << setw(3) << board[i][j] << " ";
	
		cout << endl;
	}
}

bool move_knight(int x ,int y , int k){
	if( k == 65)
		return true;
	
	for(int i = 0; i <8 ; i++ ){
		int r = x + movex[i];
		int c = y + movey[i];
		if((0 <= r and r <8) and (0 <= c and c < 8) and board[r][c] == -1){
			board[r][c] = k;
			if(move_knight( r, c, k+1))
				return true;
			board[r][c] = -1;	
		}
	}
	return false;
}
int main(){

	//int a[] = { 2,1 ,-1,-2, -2, -1, 1,2};
	//int b[] = { 1,2,2,1,-1,-2,-2,-1 };
	
	//int a[] = { 1, 1, 2, 2, -1, -1, -2, -2};
	//int b[] = { 2 ,-2, 1, -1, 2, -2, 1, -1};
	for(int i = 0; i < 8 ; i++)
		for(int j = 0; j<8 ; j++)
			board[i][j] = -1;
	
	board[0][0] = 1;	
	move_knight(0, 0 , 2);
	print();
	
	
}

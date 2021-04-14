#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <vector>
//using namespace std;

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int n=5 ,m=6 ;
int  top[] = {1, 2, -1, 2, 1, -1} , bottom[] = {2, -1, -1, 2, -1, 3};
int left[] = {2, 3, -1, -1, -1} , right[] = {-1, -1, -1, 1, -1};
char rule[][6] = {{'L', 'R', 'L', 'R', 'T', 'T'},
		 {'L', 'R', 'L', 'R', 'B', 'B'},
		 {'T', 'T', 'T', 'T', 'L', 'R'},
		 {'B', 'B', 'B', 'B', 'T', 'T'},
		 {'L', 'R', 'L', 'R', 'B', 'B'}};
vector< vector<int> > head;
int move[][2] = {{ 1, 0}, {-1, 0} , {0, 1}, {0, -1}};
bool visited[5][6];
int ans[5][6];
int count=0;

void display(int mat[][6]){
	for(int i=0 ;i<n ;i++){
		for(int j=0 ; j<m ; j++){
			int k = mat[i][j];
			if(k == 1)	cout << "+ ";
			else if(k == 0)	cout << "- ";
			else		cout << "X ";
		}
		cout << endl ;
	}
}

bool chk(){
	int a[6], b[6];
	for(int i=0 ; i<m ; i++)
		a[i] = 0, b[i] = 0;

	for(int i=0 ;i< 5 ;i++){
		int p=0,q=0;
                for(int j=0 ; j<m ; j++){
			if(ans[i][j] == 1)
				p += 1, a[j] += 1;
			if(ans[i][j] == 0)
				q += 1, b[j] += 1;
		}
		if((p != left[i] && left[i] != -1) || (q != right[i] && right[i] != -1))
			return false;
        }
	for(int i=0 ; i<m ; i++)
		if((a[i] != top[i] && top[i] != -1) || (b[i] != bottom[i] &&  bottom[i] != -1))
			return false;

	return true;
}
bool place_magnet(int x, int y, int tt){

	//if(tt == 10)
	//	exit(0);
	if(tt == count)
                return chk();

	int tempo[2] = {0 , 0}, temp, ii,jj,r,c;
	int choice[]= {1, 0, -1};
	//display(ans);
	//cout << tt <<endl;
	int xx = head[tt][0], yy = head[tt][1];


	for(int xyz=0 ; xyz< 3 ; xyz++){
		temp = choice[xyz];
		bool boo = false;
	//	cout << x << " " << y << endl ;
		for(int i=0 ; i<4 ; i++){
                	r = x + move[i][0];
                	c = y + move[i][1];
			//cout <<"**"<< r << " " << c << endl ;
			
			if(rule[r][c] == 'T')
                       		ii = r+1 , jj = c;
                	else if(rule[r][c] == 'L')
                                ii = r , jj = c+1;
			if(temp == -1)
				continue;
                	if((0<=r && r<n) && (0<=c && c<m) ){
                        	if((temp == ans[r][c]))
					boo = true;
	//				cout <<"____________"<< r << " " << c << " " << temp  << ans[r][c] << visited[r][c] << boo <<endl;
					//boo = true;
					
				for(int k=0 ; k<4 ; k++){
					int rr = ii + move[k][0];
                        		int cc = jj + move[k][1];
					if(visited)
						continue;
					if((0<=rr && rr<n) && (0<=cc && cc<m)){
						if((temp == ans[rr][cc]) && visited[rr][cc]){
							boo = true;
						//	cout <<"____________"<< rr << " " << cc << " " << temp  << ans[rr][cc]  << boo <<endl;
                                        
						}
					}
				}
                	}
        	}
//		if(x == 2 && y == 1)
		
		if(boo  && temp != -1)
			continue;
	//	display(ans);
           //     cout << x << " " << y << " " << temp  << ans[x-1][y] << visited[x-1][y] << boo <<endl;
          //      cout << x << " " << y << " " << temp  << ans[x-1][y] << visited[x-1][y] << boo <<endl;
        	ans[x][y] = temp;
        	visited[x][y] = true;
        	if(rule[x][y] == 'T'){
			ans[x+1][y] = temp != -1 ? temp^1 : -1;
                	visited[x+1][y] = true;
                	ii = x+1 , jj = y;
        	}
        	else if(rule[x][y] == 'L'){
     			ans[x][y+1] = temp != -1 ? temp^1 : -1;
                	visited[x][y+1] = true;
                	ii = x , jj = y+1;
       		}
	//	cout << r << " " << c << " " << ii << " " << jj <<endl;
		if(ii == x && jj == y)
			continue;
		//cout << r << " " << c << " " << ii << " " << jj <<endl; 
        	if( place_magnet(xx ,yy , 1+tt) )
        		return true;

       		ans[x][y] = -1;
        	visited[x][y] = false;

        	ans[ii][jj] = -1;
        	visited[ii][jj] = false;
	}
	return false;
}

int main(){
	vector<int> h;
	for(int i=0 ; i<n ; i++){
		for(int j = 0; j<m ;j++){			
			if(rule[i][j] == 'T' || rule[i][j] == 'L'){
				h.clear();
				h.push_back(i);
				h.push_back(j);
				head.push_back(h);
				count++;
			}
						
			visited[i][j] = false;
			ans[i][j] = -1;
		}
	}
	place_magnet(0,0,1);
	display(ans);
}

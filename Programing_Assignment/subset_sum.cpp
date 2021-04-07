#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

int sum,n;
int s[1000];

//bool fill(int a[] , int k);
bool _fill(int a[] , int k, int cal){	
	if (cal == sum || k == 0)
		return true;
	for(int i =0 ; i < n ; i++){
		//cout <<"      ---" <<k << " " << a[i] << "*** " <<cal << endl;
		if(s[i] == -1 && cal + a[i] <=sum){
			cal += a[i];
			s[i] = k;
			//cout << k << " " << a[i] << "*** " <<cal << endl;
			if(_fill(a, k ,cal)){
				k -= 1; 
				if(_fill(a, k ,0))
                                	return true;
				k += 1;
			}
                        s[i] = -1;
                        cal -= a[i];
                        //cout <<k << " "  <<a[i] << "* " <<cal << endl;
			
 
		}
	}
	for(int i=0; i<n ; i++)
		if(s[i] == -1)
			return false;
	return true;
}
void print(int a[]){
	vector < vector<int> > ans;
	vector <int> temp;
	for(int i = 0 ;i < 3 ; i++)
		ans.push_back(temp);
	for(int i = 0 ;i < n ; i++)
                ans[s[i]-1].push_back(a[i]);

	for(int i=0 ; i < ans.size() ; i++){
		cout << "Set " << i+1 << " : ";  
		for( int j = 0 ; j < ans[i].size() ; j++ )
			cout << ans[i][j] << " ";
		cout << endl;
	}
}
int main(int arg_len, char* args[]){
	n = atoi(args[1]);
	int a[n], target_sum = 0;
	for(int i = 0 ; i < n ; i++){
		s[i] = -1;
		a[i] = atoi(args[i+2]);
		target_sum += a[i];
	}
	if(target_sum % 3 != 0){
		cout << "Can't divide it into 3 equal sum subset. :( \n";
		return 0;
	}
	target_sum /= 3;
	sum = target_sum;
	_fill(a, 3 ,0);
	for(int i =0 ; i < n ; i++)
		cout << s[i] << " ";
	cout << endl << "\nAnswer: \n";
	print(a);
	

}

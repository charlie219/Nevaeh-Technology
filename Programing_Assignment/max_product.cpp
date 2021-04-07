#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main(int arg_len, char* args[]){

	int n = atoi(args[1]),max = -999999999, x=1;
	vector<int> arr, ans,temp;
	for(int i=0 ; i < n ; i++)
		arr.push_back(atoi(args[i+2]));

	auto start = high_resolution_clock::now();
	for(int i =0 ; i < n ; i++){
		temp.clear();
		x = 1;
		for(int j = i ; j < n ; j++){
			temp.push_back(arr[j]);
			x*=arr[j];
			//cout << i << " " << x << " " << max << endl;
			if(max < x){
				ans=temp;
				max=x;
			}
		}
	}
	cout << "Answer:- ";
	for(int i=0 ; i < ans.size() ; i++)
                cout << ans[i] << " ";
	cout << "\nProduct:= " << max;
	cout << "\nExecution time:- " << duration_cast<microseconds>(high_resolution_clock::now() - start ).count() << " ms\n\n" << endl;
	
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
vector<pair <int,int> > ans;

//int merge(vector<int> a , int temp[] , int st , int mid, int end );
int merge_sort(int a[] , int temp[] , int st ,int end );
int inversion(int a[], int st , int mid, int val){
	pair<int,int> temp;
	temp.first = val;
	//if(val == 0)
	//	return 0;
	for(int i= st; i< mid ; i++){
		temp.second = a[i];
		ans.push_back(temp);
	}
}

int print_inv(){
	for(int i = 0 ; i< ans.size(); i++)
		cout << "( " << ans[i].first << ", " << ans[i].second << " )\n";
}

int merge(int a[] , int temp[] , int st , int mid, int end ){
	
	int i=st, j= mid, k=st;
	int count = 0;
	while( i <= mid-1 && j <= end){
		
		if(a[i] <= a[j])
			temp[k++] = a[i++];
		else{
			inversion(a, i , mid, a[j]);
			temp[k++] = a[j++];
			count += (mid - i);
		}
	}

	while( i <= mid-1)
		temp[k++] = a[i++];
	
	while(j <= end )
		temp[k++] = a[j++];

	for(int ind = st ; ind <= end ; ind++)
		a[ind] = temp[ind];

	return count;
}

int merge_sort(int a[] , int temp[] , int st ,int end ){
        int mid, inv =0;
        if( st < end){

                mid =(st + end)/2;
                inv += merge_sort( a, temp , st, mid);
                inv += merge_sort( a, temp , mid+1 , end);

                inv += merge(a, temp, st, mid+1 , end);
        }
        return inv;

}

int main(int arg_len, char* args[]){
	int n = atoi(args[1]), c=0;
	int a[n];
	for(int i=0 ; i < n ; i++)
		a[i]=(atoi(args[i+2]));
	int temp[n];
	c = merge_sort(a, temp, 0, n-1 );
	
	cout << c << endl;
	for(int i = 0; i < n ; i++ )
		cout << a[i] << " ";

	cout << endl ;
	print_inv();
}

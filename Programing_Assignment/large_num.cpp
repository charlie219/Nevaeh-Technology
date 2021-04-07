#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <list>

using namespace std;
string st1,st2;
int len1,len2;
vector<int> ans;

vector<int> conv(string s){
	vector<int> n;
	for(int i = 0; i< s.length() ; i++)
		n.push_back((int)s[i] - 48);

	return n;
}

int print(vector<int> ans){
	int len = ans.size();
	for(int i=0; i <len ;i++){
	//cout << "**" << ans[i] << endl;
                if(ans[0]==0)
                        ans.pop_back();
                else
                        break;
        }
        if(ans.size()==0){
		cout << "0\n";
                return 0;
	}
	len= ans.size();
	bool boo=false;
	for(int i = len-1; i >= 0; i--){
		if(ans[i]!=0)
			boo=true;
		if(boo)
			cout << ans[i];
	}
	cout << endl;
}

vector<int> add(vector<int> s1, vector<int> s2){
	ans.clear();

	int len1 =s1.size(),len2=s2.size();
        vector <int> st1 = len1 <= len2 ?  s2 : s1, st2=  len1 > len2 ?  s2 : s1 ;
        len1 = st1.size(), len2 =st2.size();
	int carry=0, temp;
	//print(st1);
	//print(st2);
	for(int i = 0; i < len2 ; i++){
		temp =  st1[i] + st2[i] + carry;
		ans.push_back((temp % 10));
		carry = temp / 10;
	}
	
	for(int i = len2 ; i < len1  ; i++){
		temp = st1[i] + carry;
		ans.push_back(temp % 10);
		carry = temp / 10;
	}
	
	if(carry !=0)
		ans.push_back(carry);
	//cout << ans.size() << endl ;
	return ans;
}

void subtract(){
	ans.clear();
        int carry=0, temp;
//	cout << st1[] << " *" << st2 << endl;
        for(int i = 0 ; i< len2 ; i++){
                temp =  int(st1[i]) - (int)st2[i]  - carry;
		if(temp < 0){
			temp+=10;
			carry = 1;
		}
		else
			carry =0;
		ans.push_back((temp % 10));
        }
        for(int i = len2 ; i < len1 ; i++){
                temp = (int)st1[i] - int('0') - carry;
		if(temp < 0){
                        temp+=10;
                        carry = 1;
                }
                else
                        carry =0;

		//cout << temp << " " << temp %10 << " "<< int(temp /10) << endl;
                ans.push_back((temp % 10));
        }
	
	if(ans[-1]==0)
		ans.pop_back();
	cout << "Subtraction result:- ";
	print(ans);
        //cout << ans.size() << endl ;
        
}

void multiply(vector<int> st1, vector<int> st2){
	vector<int> temp, mul;
	vector<vector<int>> res;
	int carry=0,temp2;
	for(int i=0; i< len2 ; i++){
		carry=0;
		temp.clear();
		for(int j=0 ; j<i ;j++)
                        temp.push_back(0);
		for(int j=0; j< len1; j++){
			temp2 = st2[i] * st1[j] + carry;	
			temp.push_back(temp2 % 10);
			carry = temp2 /10;
		}
		if(carry>0)
			temp.push_back(carry);
		//print(temp);
		res.push_back(temp);
		//res = add(res, temp);
	}
	mul = res[0];
	for(int i=1 ; i< res.size(); i++){
		mul = add(mul, res[i]);
	}
	cout << "Ans : " ;
	print(mul);
	cout << "\n\n";
	
}
void division(vector<int> s1, vector<int> s2){
	reverse(s2.begin(), s2.end());
	reverse(s1.begin(), s1.end());
	uint64_t divs=0 ,div=0;
	for(int i=0; i< len2; i++)
		divs = divs*10 + s2[i];

	int pos=0,temp=0;
	vector<int> res;
	while(pos != len1){
		div= div*10 + s1[pos];
		if(div > divs){
			temp=div / divs;
			div %= divs;
			res.push_back(temp);
		}
		pos++;
	}
	reverse(res.begin(), res.end());
	cout << "Qutoient :- ";
	print(res);
	cout << "Remiander :- " << div;
}

int main(int arg_len, char* args[]){
	vector<int> ans;
	string s1,s2;
	st1 = args[1], st2 = args[2];
	len1 =st1.length(),len2=st2.length();
	//st1 = len1 <= len2 ?  s2 : s1, st2=  len1 > len2 ?  s2 : s1 ;
	//len1 = st1.length(), len2 = st2.length();
	
	cout << "Numbers of digits in the numbers :- ";
	cout << len1 << " " << len2 << endl ;
	reverse(st1.begin(), st1.end());
    	reverse(st2.begin(), st2.end());
	vector<int> a,b;
	a= conv(st1), b= conv(st2);
	
	//ans = add(a,b);
	//cout << "Addition = ";
	//print(ans);
	//subtract();
	
	//multiply(a , b);
	
	division(a , b);
}

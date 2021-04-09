#include <iostream>
using namespace std;

int index;
int request[1000];

bool my_dropped_func(int val){
    request[index] = val;
    int count = 0;
    for(int i = index ; i >= 0; i--){
        if(request[i] == val)
            count++;
        else
            break;
    }
    
    if(count > 3)
        return true;
    
    count = 0;
    for(int i=index ; request[i]>=val-10+1 && i>=0 ; i--){
        count += 1;
    }
    if(count > 20)
        return true;
    
    count=0;
    for(int i = index; request[i] >= val-60+1 && i>=0; i--)
        count += 1;

    if(count > 60)
        return true;
    
    return false;
}

int main()
{
    cout << "Throttling Gateway" << endl;
    int n = 27;
    int requestTime[27]={1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,11,11,11,11};
        
    int drop = 0;
    for(int i = 0; i < 27; i++){
        index=i;
        bool isDropped = my_dropped_func(requestTime[i]);
        if(isDropped){
            cout << "Request " << i+1 << " is Dropped \n";
            drop += 1;
        }
        else
            cout << "Request " << i+1 << " is not Dropped\n";
        
        
    }
    
    
    cout << "Number of Drops = " << drop << endl;
    return 0;
}

#include <iostream>

using namespace std;

class Solution {
public:
    void bobble_sort(int arr[],int len) {
        for(int i=0;i<len;i++){
            for(int j=0;j<len-i-1;j++){
                if(arr[j]>arr[j+1]){
                    int tmp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=tmp;
                }
            }
        }
    }
};

int main(){
    int a[6]={1,3,5,2,5,7};
    
    Solution solution=Solution();
    solution.bobble_sort(a,6);

    for(int num: a){
        cout<<num<<' ';
    }
    cout<<endl;
}
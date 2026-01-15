#include<iostream>
using namespace std;

bool search(int arr[],int n){
      for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i]==arr[j]){
                return true;
            }
        }
    }
    return false;
}

int main(){
    int arr[5] = {1,2,3,4,5};
    int n = sizeof(arr) / sizeof(int) ;
    if(search(arr,n)){
        cout << "Duplicate found" << endl;
    } else {
        cout << "No duplicates" << endl;
    }
  
}
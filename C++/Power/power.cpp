#include <iostream>
using namespace std;

float power(float x,int y){
    if(y==0)
        return 1;
    float temp=power(x,y/2);
    if(y%2==0){
        return temp*temp;
    }else{
        if(y>0){
            return temp*temp*x;
        }else{
            return (temp*temp)/x;
        }
    }
}

int main(){
    cout<<power(2,-3)<<endl;
    return 0;
}
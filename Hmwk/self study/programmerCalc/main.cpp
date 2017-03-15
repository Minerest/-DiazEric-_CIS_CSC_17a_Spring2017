using namespace std;

#include <iostream>

int expo(int,int);
char Ltr(int);

int main() {
    
    //initialize variables... arrays are for base16, base8, and base2
    char arr[100] = {0};
    int num, exp = 0, base, limit=0, i = 0, div;
    
    //get inputs
    cout<<"Enter a number to convert into the base"<<endl;
    cin>>num;
    cout<<"Enter the base of that number"<<endl;
    cin>>base;
    
    //Figure out the upper limit e.g. 2,4,8,16,32 etc
    while (limit <= num){
        limit = (expo(base, exp));
        exp++;
    }
    div = num;//just a copy to keep the original intact
    while (limit != 1){ //it will reach 1 because the limit derives from the base.
        limit /= base;
        if (div>=limit){
            arr[i] = div/limit >= 10 ? Ltr(div/limit) : div/limit+48;   //Did you mention 1 Liners?
            div = div % limit;
            cout<<"div = "<<div<<endl;
        }
        else{
            arr[i] = '0';
        }
        i++;
    }
    //This loop prints out the number
    for (int j = 0; j < i; j++) cout<<arr[j];
  return 0;
}

char Ltr(int num){
    char c;
    switch (num){
        case 10: c = 'A';
        break;
        case 11: c = 'B';
        break;
        case 12: c = 'C';
        break;
        case 13: c = 'D';
        break;
        case 14: c = 'E';
        break;
        case 15: c = 'F';
        break;
        default:
            cout<<"Something went wrong at switch num="<<num<<" c = err"<<endl;
            break;
    }
    return c;
}

int expo(int num, int exp){
    int n = num;
    for (int i = 1; i < exp; i++){
        n *= num;
    }
    if(exp == 0){
        return 1;
    }
    else{
        return n;
    }
}


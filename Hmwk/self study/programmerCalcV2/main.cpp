// V2
using namespace std;

#include <iostream>
#include <cmath>
#include <string>

int expo(int,int);
char Ltr(int);
int decTot(string, int);
string cnv2Base(int,int);
int main() {  
    //initialize variables... arrays are for base16, base8, and base2
    int num, num1, exp = 0, base, limit=0, i = 0, div;
    string arr;
    //get inputs
    cout<<"Enter a number to convert into the base"<<endl;
    cin>>num;
    do{
        cout<<"Enter the base of that number"<<endl;
        cin>>base;
    }while (base <=0);
    //Figure out the upper limit e.g. 2,4,8,16,32 etc
    cout<<"number In base "<<base<<endl;
    arr = cnv2Base(num, base); 
    num1 = decTot(arr, base);
    cout<<"total after conv"<<num1<<endl;
    //This loop prints out the number
    for (int j = 0; j < i; j++) cout<<arr[j];
    num++;
    
  return 0;
}
int decTot(string nonBin, int base){
    int exp = 1, len = 0, decVal = 0, j=0,z=0, ascii=0, arr[100] = {0};
    for (int i = 0; nonBin[i+1] != 'z'; i++){
        len++;//Find the length of the array'
    }
    cout<<endl<<"Number reversed: ";
    j = len-1;      
    while (j >= 0){ //-57 && 4
        ascii = nonBin[j] <= 57 ? static_cast<int>(nonBin[j]) - 48 : static_cast<int>(nonBin[j]) - 55;
        arr[z] = ascii;cout<<Ltr(arr[z]);
        j--;z++;
    }
    cout<<endl;
    for (int i = 0; i < len; i++){
        
        decVal += arr[i]*pow(base, i);
        exp*=base;//2,4,8,16,32,64,128 etc...
    }
    return decVal;
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
            if (num < 10 && num >= 0){ c=num+48;}
            else{
            cout<<"Something went wrong at switch num="<<num<<" c = err"<<endl;
            }
            break;
    }
    return c;
}

int expo(int num, int exp){
    int n = num;
    if (exp == 0) return 1;
    for (int i = 1; i < exp; i++){
        n *= num;
    }
    return n;
}   
string cnv2Base(int num, int base){
    int i=0,limit=0,exp=0,div;
    string arr;
    while(limit <= num){
        limit = (expo(base, exp));
        exp++;
    }
    div = num;//just a copy to keep the original intact
    cout<<"cnv2Base"<<endl;
    while (limit != 1){ //it will reach 1 because the limit derives from the base.
        limit /= base;
        if (div>=limit){
            arr[i] = div/limit >= 10 ? (Ltr(div/limit)) : (div/limit+48);   //Did you mention 1 Liners?
            div = div % limit;
        }
        else{
            arr[i] = '0';
        }
        cout<<arr[i];
        i++;
    }
    cout<<endl;
    i++;
    arr[i] = 'z';//end flag... like null terminator
    return arr;
}
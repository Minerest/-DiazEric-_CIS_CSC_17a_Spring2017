//V3
using namespace std;
#include <iostream>
#include <cmath>
#include <string>
int expo(int,int);          //pretty much same as the pow function for ints
char Ltr(int);              // converts 10-16 into hexadec
int decTot(string, int);    //calculates BaseN numbers into base 10
string cnv2Base(int,int);   //converts base10 numbers into baseN
int cnvStr(string, int);    //
string rvsStr(string, int &);
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

int main() {  
    //initialize variables... arrays are for base16, base8, and base2
    int num, num1, exp = 0, base, limit=0, i = 0, div, len=0;
    string arr, str="123A";
    //get inputs
    //str = rvsStr(str,len);cout<<str<<" "<<len;return 0;
    //num1 = cnvStr(str,10);cout<<num1;
    //return 0;
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
int cnvStr(string str,int base, int len){
    int num, j=0, exp=1;
//    string rvs = rvsStr(str);//reverse the string
//    for (int)
    
    return num;
}
int decTot(string nonBin, int base){
    string rvs;
    int exp = 1, len = 0, decVal = 0, j=0,z=0, ascii=0, arr[100] = {0};
    cout<<"Dec total "<<"nonBin="<<nonBin<<endl;
    cout<<endl<<"Number reversed: ";
    rvs = rvsStr(nonBin, len);
    cout<<rvs<<" len = "<<len<<endl;
    for (int i = 0; i < len; i++){      
        decVal += arr[i]*pow(base, i);
        exp*=base;//2,4,8,16,32,64,128 etc...
    }
    return decVal;
}
char Ltr(int num){
    char c;
    static int tst = 0;
    tst++;
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
            cout<<"Something went wrong at switch num="<<num<<" tst = "<<tst<<endl;
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
    cout<<"cnv2Base num="<<num<<"base="<<base<<endl;
    int i=0,limit=0,exp=0,div;
    string arr,str;
    while(limit <= num){
        limit = (expo(base, exp));
        exp++;
    }
    div = num;//just a copy to keep the original intact
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
    arr[i] = 'z';//end flag... like null terminator
    for(int i =0;arr[i]!='z';i++)str+=arr[i];
    cout<<"str from cnv2Base = "<<str<<endl;
    return str;
}
string rvsStr(string str, int &len){
    int j, z=0, ascii;
    string arr;
    //str+='z';
    for (int i = 0; str[i] != 'z'; i++){
        len++;//Find the length of the array'
    }
    cout<<endl<<"Number reversed: ";
    j = len-1;      
    while (j >= 0){ //-57 && 4
        ascii = str[j] <= 57 ? static_cast<int>(str[j])-48 : static_cast<int>(str[j])-55;
        arr[z] = ascii;cout<<Ltr(arr[z]);
        j--;z++;
    }
    cout<<arr;
    return arr;
}
/* 
 * File:   main.cpp
 * Author: ericd
 *
 * Created on February 21, 2017, 6:29 AM
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

/*
 * 
 */

void p9_2();
void p9_6();
void p9_7();

void c9_1();
int *dynArr(int sz);

void c9_2();
int *sort(int *tstScrs, int sz);
int avg(int *tstScrs, int sz);

int main(int argc, char** argv) {
    srand(time(0));
    //p9_2();//done?
    //p9_6();//done?
    //p9_7();//done?
    //c9_1();//done
    
    return 0;
}
/*1.    Array Allocator 
 Write a function that dynamically allocates an array of integers. 
 * The function should accept an integer argument indicating the number of 
 * elements to allocate. The function should return a pointer to the array.
 */
void c9_1(){
    int size;
    int *ptr = 0;
    cout<<"Hi, I'm going to allocate an array with a size of your choosing"<<endl;
    cout<<"How big do you want the array to be? Size = ";
    cin>>size;cout<<endl;
    ptr = dynArr(size);
    for (int i = 0; i < size; i++){
        ptr[i] = rand()%25;
        cout<<ptr[i]<<", ";
    }
    delete [] ptr;
}
int *dynArr(int sz){
    int *dynPtr = 0;
    dynPtr = new int [sz];
    return dynPtr;
}
/*
 Write a program that dynamically allocates an array large enough to hold a userdefined
 *  number of test scores. Once all the scores are entered, the array should be 
 * passed to a function that sorts them in ascending order. Another function 
 * should be called that calculates the average score. The program should 
 * display the sorted list of scores and averages with appropriate headings. 
 * Use pointer notation rather than array notation whenever possible.
 */
void c9_2(){
    int amtStu, *tstScrs = 0;
    
    do{
        cout<<"Hey, how many students are in your class?[num>0]"<<endl;
        cin>>amtStu;
    }while(amtStu<=0);
    cout<<"Awesome, let me pull up the test scores for the "<<amtStu<<" students"<<endl;
    tstScrs = new int [amtStu];
    for(int i = 0; i < amtStu; i++){
        tstScrs[i] = rand()%60+40;
        cout<<tstScrs[i]<<", ";
    }
    cout<<endl<<"Hmm, it seems that the scores are out of order, let me sort that for you"<<endl;
    tstScrs = sort(tstScrs, amtStu);
    cout<<"Here you go!"<<endl;
    for(int i = 0; i < amtStu; i++){
        cout<<tstScrs[i]<<", ";
    }
    
    
    delete [] tstScrs;
}

int *sort(int *tstScrs, int sz){
    int i1 = 0, i2 = 0,k=0, mid = sz/2, temp, oper = 0, oper1 = 0;;    //testing out how many operations each sorting function does
    for (int i = 0; i < mid; i++){                              //My theory is that cutting up the array into 2 pieces will be faster
        for (int j = i+1; j < mid; j++){
            oper++;//if statement compare
            if (tstScrs[j] < tstScrs[i]){
                temp = tstScrs[i];
                tstScrs[i] = tstScrs[j];
                tstScrs[j] = temp;
                oper+=3;//swap
            }finish making the sorting algorithim. create 2 new half arrays
            oper++; //j++
            oper++;//j < mid
        }
        oper++;//i++;
        oper++;//i < mid

    }
    for (int i = mid+1; i < sz; i++){
        for (int j = i+1; j < sz; j++){
            oper++;
            if (tstScrs[j] < tstScrs[i]){
                temp = tstScrs[i];
                tstScrs[i] = tstScrs[j];
                tstScrs[j] = temp;
                oper+=3;
            } 
        }
        oper++;//i++
        oper++;//i<sz
    }
}
int avg(int *tstScrs, int sz){
    
}

// Write the definition statement for a variable  fltPtr . The variable should be a pointer to a  float .
void p9_2(){
    float a = 1.1;
    float *ptr = &a;
    cout<<"The ptr is pointing to the address of 'a' which is "<<ptr<<" 'a' has a value of "<<*ptr<<endl;
}
//    Assume  ptr  is a pointer to an  int  and holds the address 12000.
//      On a system with 4-byte integers, what address will be in  ptr  after the following statement? 
//      ptr+=10
void p9_6(){
    cout<<"Assume  ptr  is a pointer to an  int  and holds the address 12000."<<endl;
    cout<<"On a system with 4-byte integers, what address will be in  ptr  after the following statement: ptr+=10"<<endl;
    cout<<"Answer: The adress would be equal to 12000+(4)(10) which is 12,040"<<endl;
}
void p9_7(){
    cout<<"Assume  pint  is a pointer variable. Is each of the following statements valid or invalid? If any is invalid, why"<<endl;
    cout<<"A) pint++ -------------- Valid"<<endl;
    cout<<"B) --pint -------------- Valid"<<endl;
    cout<<"C) pint/=2 -------------- INVALID, can only add or subtract spaces"<<endl;
    cout<<"D) pint*=2 --------------- INVALID, cannot multiply pointers"<<endl;
    cout<<"E) pint+=x where x is an int. Valid... I think..."<<endl;
}
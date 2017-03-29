//Chapter 11, do 8 problems from Chapter 11 and flowchart 2

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

#include "MovieData.h"
#include "company.h"
#include "weather.h"
#include "soccer.h"
#include "acc.h"
#include "budget.h"

/*
 * p 682
 */

void ch11P1();
void ch11P2();
void ch11P3();
void ch11P4();
void ch11P5();
void ch11P6();
void ch11P7();
void ch11P11();
//===============================================================================
budget amtSpent();
custAct makeCust();
player makeP();
Weather makeTmp();
Company mkeCmpny(string name);
void prntMov(MovieData &);//print movie data,h structures
void prntMv(MovieData &p);
int main(int argc, char** argv) {
    srand(time(0));
    bool b = true;
    int c;
    do{
        cout<<"=========================================================="<<endl;
        cout<<"=====================Welcome=============================="<<endl;
        cout<<"Movie data - Press 1"<<endl;
        cout<<"Movie Profit - Press 2"<<endl;
        cout<<"Corporate sales - press 3"<<endl;
        cout<<"Weather statistics - press 4"<<endl;
        cout<<"Weather modification - press 5"<<endl;
        cout<<"Soccer scores - press 6"<<endl;
        cout<<"Customer accounts - press 7"<<endl;
        cout<<"Monthly budgets - press 8"<<endl;
        cout<<"To quit - press any other key"<<endl;
        cin>>c;
        switch(c){
            case 1:ch11P1();break;// done
            case 2:ch11P2();break;//done
            case 3:ch11P3();break;//done
            case 4:ch11P4();break;//done
            case 5:ch11P5();break;//done
            case 6:ch11P6();break;//done
            case 7:ch11P7();break;//done
            case 8:ch11P11();break;
            default: b = false;
        }

    }while(b);
    return 0;
}

void ch11P11(){
    budget me;
    int hous = 500, util = 150, hExp = 65, tran = 50,
        food = 250, med = 30, insur = 100, ent = 150, clothing = 75, misc = 50;
    int mnthlyB = 0;
    me = amtSpent();//generate how much you spent to compare it to the budgets above.
    mnthlyB += clothing - me.clothing;
    clothing -= me.clothing; //Save memory by reusing variables?
    mnthlyB += misc - me.misc;
    misc -= me.misc;
    mnthlyB += ent  - me.entertainment;
    ent -= me.entertainment;
    mnthlyB += insur - me.insurance;
    insur -= me.insurance;
    mnthlyB += med  - me.medical;
    med -= me.medical;
    mnthlyB += food - me.food;
    food -= me.food;
    mnthlyB += tran - me.transportation;
    tran -= me.transportation;
    mnthlyB += hExp - me.houseExpenses;
    hExp -= me.houseExpenses;
    mnthlyB += util - me.utilities;
    util -= me.utilities;
    mnthlyB += hous - me.housing;
    hous -= me.housing;
    cout<<"Format: Negative numbers means you're over budget. Positive numbers means you're doing great!"<<endl;
    cout<<"Clothing: "<<clothing<<endl;
    cout<<"Misc: "<<misc<<endl;
    cout<<"Entertainment: "<<ent<<endl;
    cout<<"Insurance: "<<insur<<endl;
    cout<<"Medical: "<<med<<endl;
    cout<<"Food: "<<food<<endl;
    cout<<"Transportation"<<tran<<endl;
    cout<<"Housing expenses:"<<hExp<<endl;
    cout<<"Utilities: "<<util<<endl;
    cout<<"Rent: "<<hous<<endl;
    cout<<"Total budget: "<<mnthlyB<<endl;
    mnthlyB>=0 ? cout<<"GoodJob!"<<endl : cout<<"You can do better"<<endl;
    
}

budget amtSpent(){
    budget b;
    b.housing = 500;
    b.utilities = 150;
    b.insurance = 100;
    b.houseExpenses = rand()%70+20;
    b.transportation = rand()%50+20;
    b.food = rand()%250+50;
    b.medical = 30;
    b.entertainment = rand()%100+66;
    b.clothing = rand()%60+30;
    b.misc = rand()%40+15;
    return b;
}

void ch11P7(){
    custAct a[10];
    int ioman = 15;
    for (int i = 0; i < 10; i++){
      a[i] = makeCust();  
      cout<<setw(ioman)<<left<<"Cust name: "<<a[i].name<<endl;
      cout<<setw(ioman)<<left<<"Cust phone: "<<"951-"<<a[i].teleNum<<endl;
      cout<<setw(ioman)<<left<<"Cust zip:  "<<a[i].zipcode<<endl;
      cout<<setw(ioman)<<left<<"Cust last paid: "<<a[i].dateLastPaid<<endl;
    }
    
}
custAct makeCust() {
    custAct act;
    char ltr;
    for (int i = 0; i < 5; i++) {
        ltr = rand() % 26 + 65;
        act.name += ltr;
    }
    act.city = "Riverside";
    act.state = "Ca";
    act.address = "Bell Ruso";
    act.teleNum = rand()%8999;   
    act.accBal = rand()%12943;
    act.zipcode = 10000 + rand()%89999;
    act.dateLastPaid = round(rand()%10)+48;
    act.dateLastPaid+= "/";
    act.dateLastPaid+= round(rand()%3)+48;
    act.dateLastPaid+= round(rand()%10)+48;
    act.dateLastPaid += "/200";
    act.dateLastPaid += round(rand()%10)+48;
    return act;
}

void ch11P6(){
    player pArr[12];
    cout<<"Name   Number  Points"<<endl;
    for (int i = 0; i < 12; i++){
        pArr[i] = makeP();
        cout<<pArr[i].name<<"   "<<pArr[i].num<<"      "<<pArr[i].points<<endl;
    }
}

player makeP(){
    player P;
    char ltr;
    for (int i = 0; i < 5; i++){
        ltr = rand()%26+65;
        P.name += ltr;
    }
    P.num = rand()%100;
    P.points = rand()%12;
    return P;
}

void ch11P5(){
    enum Month {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
    Month mnth;
    Weather ar[12];
    int high, low, highI,lowI;
    float rainAv=0, rainTot=0, tempAv=0;
    for (mnth = Jan; mnth <= Dec; mnth = static_cast<Month>(mnth + 1)){
        ar[mnth] = makeTmp();
        if (ar[mnth].highT > high) high = ar[mnth].highT, highI = static_cast<int>(mnth); //not sure why I have to static cast this
        if (ar[mnth].lowT < low)    low = ar[mnth].lowT,   lowI = mnth;                   //vs not static casting lowI = mnth. c++ sucks
        rainAv += ar[mnth].rainFal;
        rainTot += ar[mnth].rainFal;
        tempAv += ar[mnth].highT + ar[mnth].lowT;
    }
    rainAv/=12;
    tempAv/=24;
    cout<<"Highest temperature happened at month "<<highI+1<<" reaching "<<high<<" temps"<<endl;
    cout<<"Lowest temperature happened at month "<<lowI+1<<" reaching "<<low<<" temps"<<endl;
    cout<<"Total rainfall: "<<rainTot<<endl;
    cout<<"Average rainfall: "<<rainAv<<endl;
    cout<<"Average temp: "<<tempAv<<endl;
}

void ch11P4(){
    Weather ar[12];
    int high = 0, low = 160, highI, lowI;
    float rainAv=0, tempAv = 0, rainTot=0;
    for (int i = 0; i < 12; i++){
        ar[i] = makeTmp();
        if (ar[i].highT > high) high = ar[i].highT, highI = i;
        if (ar[i].lowT < low) low = ar[i].lowT, lowI = i;
        rainAv += ar[i].rainFal;
        rainTot += ar[i].rainFal;
        tempAv += ar[i].highT + ar[i].lowT;
    }
    rainAv/=12;
    tempAv/=24;
    cout<<"Highest temperature happened at month "<<highI+1<<" reaching "<<high<<" temps"<<endl;
    cout<<"Lowest temperature happened at month "<<lowI+1<<" reaching "<<low<<" temps"<<endl;
    cout<<"Total rainfall: "<<rainTot<<endl;
    cout<<"Average rainfall: "<<rainAv<<endl;
    cout<<"Average temp: "<<tempAv<<endl;
    
    
}
Weather makeTmp(){
    Weather month;
    month.highT = rand()%60+25;
    month.lowT = rand()%70 -25;
    month.rainFal = rand()%15;
    return month;
}

void ch11P3(){
    Company North, West, East, South;
    North = mkeCmpny("North");
    West = mkeCmpny("West");
    East = mkeCmpny("East");
    South = mkeCmpny("South");
    Company a[4] = {North, West, East, South};

    for (int i = 0; i < 4; i++){
        cout<<a[i].divisionName<<endl;
        a[i].avgQSales = (a[i].Q1Sales+a[i].Q2Sales+a[i].Q3Sales+a[i].Q4Sales)/4;
        a[i].totAnual = a[i].Q1Sales+a[i].Q2Sales+a[i].Q3Sales+a[i].Q4Sales;
        cout<<"Total Sales = "<<a[i].totAnual<<endl;
        cout<<"Average Quarter = "<<a[i].avgQSales<<endl;
    }
    
}

Company mkeCmpny(string name){
    Company c;
    c.divisionName = name + " Wing";
    c.Q1Sales = rand()%100000;
    c.Q2Sales = rand()%100000;
    c.Q3Sales = rand()%100000;
    c.Q4Sales = rand()%100000;
    return c;
}



void ch11P2(){
    float profit;
    string s = "";
    MovieData Rambo = {"Rambo", "Director Rambo", 1989, 240, rand()%100000, rand()%956000};
    profit = Rambo.fstYrRev - Rambo.prodCst;
    
    if (profit < 0) s = "not";
    cout<<"Movie: "<<Rambo.title<<endl;
    cout<<"Director: "<<Rambo.director<<endl;
    cout<<"Year released"<<Rambo.yrRlsd<<endl;
    cout<<"First year revenue:"<<Rambo.fstYrRev<<endl;
    cout<<"Production cost: "<<Rambo.prodCst<<endl;
    cout<<"profit: "<<Rambo.fstYrRev - Rambo.prodCst<<endl;
    cout<<"First year was "<<s<<" profitable"<<endl;
}

void ch11P1(void){
    MovieData Dyno = {"Dyno Title", "Director Dyno", 1926, 220};
    MovieData Empr = {"Empr Title", "Director Empr", 1999, 260};
    prntMov(Dyno);
    prntMov(Empr);
}

void prntMov(MovieData &p){
    cout<<setw(15)<<left<<"Director:"<<p.director<<endl;
    cout<<setw(15)<<left<<"runningTime:"<<p.rngTime<<endl;
    cout<<setw(15)<<left<<"Movie title:"<<p.title<<endl;
    cout<<setw(15)<<left<<"year released:"<<p.yrRlsd<<endl;
}
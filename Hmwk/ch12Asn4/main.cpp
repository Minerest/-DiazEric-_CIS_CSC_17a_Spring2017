#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "inventory.h"
//In the order I did the problems
void p3Ch12();
void p6Ch12();
char toLower(char &);
void p7Ch12();
void p9Ch12();
void p10Ch12();
void p13Ch12();
void p8Ch12();
void fToArr(int *, int);
void arrToF(int *, int);
void mkArr(int *, int);
void p1Ch12();	//<- I ran out of problems I wanted to do here
void p2Ch12();
void p5Ch12();
int main(int argc, char** argv) {
	srand(time(0));
    int usrIn;
	bool boo = true;
	do{
		cout<<"Chapter 12 HW"<<endl;
		cout<<"Pick your problems"<<endl;
		cout<<"0. Problem 3 chapter 12"<<endl;
		cout<<"1. Problem 6"<<endl;
		cout<<"2. problem 7"<<endl;
		cout<<"3. Problem 9"<<endl;
		cout<<"4. Problem 10"<<endl;
		cout<<"5. Problem 13 \n";
		cout<<"6. Problem 8\n";
		cout<<"7. Problem 1\n";
		cout<<"8. Problem 2\n";
		cout<<"9. Problem 5\n";
		cout<<"Any other, QUIT\n";
		cin>>usrIn;
		switch(usrIn){
			case 0: p3Ch12(); break;   //done
			case 1: p6Ch12(); break;    //done
			case 2: p7Ch12(); break;    //done
			case 3: p9Ch12(); break;     //done
			case 4: p10Ch12(); break;    //done	
			case 5: p13Ch12(); break; //done
			case 6: p8Ch12(); break;	  //done
			case 7: p1Ch12(); break;	  //done
			case 8: p2Ch12(); break;	  //done	  	
			case 9: p5Ch12(); break;	  //done
			default: boo = false; cin.clear(); cin.ignore(); break;
		}
	}while(boo);
    return 0;
}
//==============================================================================
void p5Ch12(){
	ifstream p5;
	string t;
	char a;
	int cnt = 1;
	p5.open("p5.txt");
	while (!p5.eof()){
		if (cnt % 25 == 0){
			cout<<"Continue?[Y/N]"<<endl;
			cin>>a;
			toLower(a);
			if (a != 'y') {
				break;
			}
		} 
		getline(p5, t);
		cout<<cnt<<" "<< t << endl;
		cnt++;
	}
}

//==============================================================================
void p2Ch12(){
	ifstream p2;
	string t;
	char a;
	int cnt=0;
	p2.open("p2.dat");
	while (!p2.eof()){
		if (cnt==24) {
			cout << "Continue?[Y/N]" << endl;
			cin>>a;
			if (a == 'y' || a == 'Y') {
				cnt = 0;
			}
			else{
				break;
			}
		}
		getline(p2, t);
		cout << t << endl;
		cnt++;
	}
}

//==============================================================================

void p1Ch12(){
	ifstream p1;
	int counter = 0, lim = 10;
	string t;
	char a;
	p1.open("p1.txt");
	while (!p1.eof()){
		if (counter != lim){
			getline(p1, t);
			cout<<t<<endl;
		}
		else{
			cout<<"Continue? [Y/N]"<<endl;
			cin>>a;
			if (a == 'y' || a == 'Y'){
				lim+=10;
			}
			else{
				break;
			}
		}
		counter++;
		if (p1.eof()){
			cout<<"End of file!"<<endl;
		}
	}
	p1.close();p1.clear();
	
}



//==============================================================================


void p8Ch12(){
	int size = 50, arr[size], arrF[size];
	string t;
	cout<<"Lets make a binary file!"<<endl;
	cout<<"Starting off with making an array."<<endl;
	mkArr(arr, size);
	for (int i = 0; i < size; i++){
		if (i % 10 == 0) cout<<endl;
		cout << arr[i] << " ";
	}
	cout<<endl;
	cout<<"Writing the array to the file written in binary"<<endl;
	arrToF(arr, size);
	cout<<"Reading the file back into the array"<<endl;
	fToArr(arrF, size);
	cout<<"Printing the array"<<endl;
	for (int i = 0; i < size; i++){
		if (i % 10 == 0) cout<<endl;
		cout << arrF[i] << " ";
	}
	
}
void fToArr(int *arr, int sz){
	fstream file;
	file.open("p8.dat", ios::in | ios::binary );	//The books example on page 684 does not work,
	file.read(reinterpret_cast<char *>(arr), sizeof(arr)*sz);// I had to find this out on my own.
	file.clear();file.close();
}
void arrToF(int *arr, int sz){
	fstream file;
	file.open("p8.dat", ios::out | ios::binary);
	file.write(reinterpret_cast<char *>(arr), sizeof(arr)*sz);
	file.clear();file.close();
}

void mkArr(int *arr, int sz){
	for (int i = 0; i < sz; i++){
		arr[i] = rand()%100;
	}
}

//==============================================================================
void p13Ch12(){
	int usrIn, recIn, nSz, dtSz, i;
	inventory item, newItem;
	fstream inv;
	ifstream in;
	ofstream out;
	inv.open("inv.dat", ios::in | ios::out | ios::binary);
	string t;
	char chA [20];
	bool rFound = false;
	do{
	cout<<"Hey! Enter an option\n";
	cout<<"1. Input an item into the inv.dat file"<<endl;
	cout<<"2. Display all items from the inv.dat file."<<endl;
	cout<<"3. Change your records"<<endl;
	inv.clear();
	cin>>usrIn;
		switch(usrIn){
			case 1: 
				cout<<"You're going to add a new record.\n";
				do{
					cout<<"Item name?[Enter a string]\n";
					cin.ignore();
					cin>>t;
					nSz = t.length();
					for (int z = 0; z < nSz; z++){
						item.name[z] = t[z];
					}
					item.name[nSz] = '\0';
					cin.ignore();
				}while(item.name == "" && nSz >= 20);
				do{
					cout<<"Quantity on hand?[Enter a number]";
					cin>>item.Q;
					cin.ignore();

				}while(item.Q <= 0);
				do{
					cout<<"Whole sale cost?[Enter a number]\n";
					cin>>item.wCost;
					cin.ignore();

				}while(item.wCost <=0);
				do{
					cout<<"Retail cost?[Enter a number]\n";
					cin>>item.rCost;
					cin.ignore();

				}
				while(item.rCost <= 0);
				do{
					cout<<"Date added?\n"; 
					cin>>item.dtAdded;
					cin.ignore();
				}while(item.dtAdded == "");
				in.open("num.dat");
				in >> i;
				in.clear();in.close();
				item.record = i;
				out.open("num.dat");
				i++;
				out << i;
				out.clear();out.close();
				inv.seekg(0L, ios::end);
				inv.write(reinterpret_cast<char *>(&item), sizeof(item));
				cout<<"Your inventory item has been successfully added"<<endl;
				break;
			case 2:
				inv.seekg(0L, ios::beg);
				inv.read(reinterpret_cast<char *>(&item), sizeof(item));
				cout<<"Getting data..."<<endl;
				do{
					cout<<"Item name: "<<item.name<<endl;
					cout<<"Item Quantity: "<<item.Q<<endl;
					cout<<"Item wholesale cost: "<<item.wCost<<endl;
					cout<<"Item retail cost: "<<item.rCost<<endl;
					cout<<"Date added: "<<item.dtAdded<<endl;	
					cout<<"File index: "<<item.record<<endl<<endl;
					inv.read(reinterpret_cast<char *> (&item), sizeof (item));
				}while(!inv.eof());
				break;
			case 3:
				do{
					cout<<"Which record do you want to change?"<<endl;
					cin>>recIn;
				}while(recIn < 0);
				cout<<"Searching for an item with that file index";
				inv.seekg(0, ios::beg);
				while(!inv.eof()) {
					inv.read(reinterpret_cast<char *> (&item), sizeof (item));
					if(item.record == recIn){
						rFound = true;
						break;
					}
				}
				if (rFound){
					cout<<"The record was found."<<endl;
					cout << "Item name: " << item.name << endl;
					cout << "Item Quantity: " << item.Q << endl;
					cout << "Item wholesale cost: " << item.wCost << endl;
					cout << "Item retail cost: " << item.rCost << endl;
					cout << "Date added" << item.dtAdded << endl;
					cout << "File index" << item.record << endl << endl;
					cout<<"Let's change the item"<<endl;
					cout<<"Item name: "; cin>>newItem.name;
					cout<<"\nItem Quantity: "; cin>>newItem.Q;
					cout<<"\nItem Whole Sale Cost: "; cin>>newItem.wCost;
					cout<<"\nItem Retail Cost: "; cin>>newItem.rCost;
					cout<<"\nDate added: "; cin>>newItem.dtAdded;
					newItem.record = recIn;
					inv.seekp(sizeof(newItem)*recIn, ios::beg);//some hacker wizardry right there.
					inv.write(reinterpret_cast<char *>(&newItem), sizeof(newItem));
				}
				else{
					cout<<"Sorry, nothing was found within our records"<<endl;
				}
				rFound = false;
				break;
			default:
				usrIn = 0;
				break;
		}
	}while(usrIn != 0);
	inv.close();inv.clear();
}


//==============================================================================
void p10Ch12(){
    ifstream crypt;
    ofstream decrypt;
    crypt.open("encrypted.txt");
    decrypt.open("decrypted.txt");
    char ch='A';
    int i = 0;
    string temp;
    while (!crypt.eof()){
        getline(crypt, temp);
        do{
            temp[i] = temp[i]^ch;
            i++;ch++;
            if (ch == 'Z') ch = 'A';
            
        }while(i < temp.length());
        decrypt<<temp<<'\n';
        i = 0;
        ch = 'A';
    }
	cout<<"\n\nCheck out 'encrypted.txt' and 'decrypted.txt' for the results!\n\n";
    decrypt.close();crypt.close();
}
//==============================================================================
//==============================================================================
void p9Ch12(){
    ifstream toEnc;
    ofstream crypt;
    toEnc.open("toEncrypt.txt");
    crypt.open("encrypted.txt"); 
    char ch='A';
    int i = 0;
    string temp;
    while(!toEnc.eof()){
        getline(toEnc, temp);
        do{
            temp[i] = temp[i]^ch;
            i++;ch++;
            if(ch == 'Z') ch = 'A';
        }while(i < temp.length());
        crypt<<temp<<'\n';
        i = 0;
        ch = 'A';
    }
	cout<<endl<<endl<<"Check out the files 'toEncrypt.txt' and 'encrypted.txt' for the results!"<<endl;
	
    toEnc.close();crypt.close();
}
//==============================================================================
//==============================================================================
void p7Ch12(){          
    ofstream out;       
    ifstream in;        
    string t;
    int i = 0;
    bool flag = true;
    in.open("filterOg.txt");
    out.open("augmented.txt");
    while (!in.eof()){
        getline(in,t);
        cout<<t;
        do{ //bounds check for letter uppercase conversion.
            if ((t[i-1]< 'A' || (t[i-1] > 'Z')) && t[i-1] < 'a'){
                if (t[i+1] >= 'a' && t[i+1] <= 'z'){
                    t[i+1]-=32;
                    toLower(t[i]);
                }
            }
            i++;
        }while(i < t.length());
        out<<t<<'\n';
        i=0;
    }
	cout<<endl<<"Check the file 'augmented.txt' for the changed version of what's printed above\n";
    in.close();out.close();
}
//==============================================================================
//==============================================================================
void p6Ch12(){
    string usrSrch;
    ifstream txt;
    string c, a="";
    int count = 0, i = 0, len, j = 0;
    txt.open("search.txt");
    cout<<"What's the word or phrase you'd want to search for?\n";
	cin.ignore();
    getline(cin, usrSrch);      
    len = usrSrch.length();
        //Loop until you hit the end of the file
    while (!txt.eof()){
        j=0;i=0;    //counters for the string indexes
        getline(txt, c);    //read file line by line
        cout<<c<<endl;     
        do{
            while(toLower(c[j]) == toLower(usrSrch[i])){//condition to increment
                a += c[j];                              //both indexes
                j++;i++;
            }
            if (a == usrSrch){  //If the temp string matches what you're searching for
                count++;        //Increment the count
            }
            a = "";//reset temp string and temp string counter
            i = 0;
            j++;  //while moving through the file. This happens many times before another getline
        }while(j < c.length());   //Break out when you hit line length
    }//break out when you hit end of file
    if (count == 0)cout<<"No matches found\n";
    
    else{
        cout<<endl<< count <<" matches found for "<< usrSrch <<" search"<<endl;
    }
    txt.close();
}

char toLower(char &ltr){
    if (ltr >= 65 && ltr <= 90){    //check if it's in ASCII range of UPPERCASE char
        ltr+= 32;
    }
    return ltr;
}
//==============================================================================
//==============================================================================
void p3Ch12(){
    ifstream joke, punch;
    int lim = 50, i=0;
    char a[lim], ch;                //Store the files in arrays And temporarily, in characters
    joke.open("joke.txt");
    punch.open("punchline.txt");
    do{
        joke.get(a[i]);
        cout<<a[i];
        i++;
    }while(!joke.eof());
    cout<<endl;
    punch.seekg(0,ios::end); //Set the read bit at the end of the file.
    while (ch!= '\n'){
        punch.seekg(-2, ios::cur);  //for some reason, swapping the position 
        punch.get(ch);              // of these 2 lines messes everything up
    }                               //Also, seekg HAS to be -2, probably because
    //punch.seekg(-1, ios::cur);    //punch.get(ch) moves the readbit over by 1
    while (!punch.eof()){
        cout<<ch;
        punch.get(ch);
    }
    punch.close();
    joke.close();
	cout<<endl;
}

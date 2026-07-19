#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <limits>
#include <climits>
#define BASELINE 1000000
#define MAXLOAN  1000000
#define XOR 23
using namespace std;

unsigned long long int balance;

struct Loan{
    unsigned short int id;
    char* cnic;
    unsigned int loanAmount;
    char* name;
};

void showMenu(){
    cout<<endl<<'\t'<<'\t'<<"Available Operations"<<endl<<endl;
    cout<<"addRecord         ->\tAdd a loan record in file"<<endl;
    cout<<"addBalance        ->\tAdd balance in the system"<<endl;
    cout<<"showLoans         ->\tDisplay records"<<endl;
    cout<<"showById          ->\tDisplay record of a specific ID"<<endl;
    cout<<"showByCnic        ->\tDisplay record of a specific CNIC"<<endl;
    cout<<"removeById        ->\tRemove record of a specific ID"<<endl;
    cout<<"removeByCnic      ->\tRemove record of a specific CNIC"<<endl;
    cout<<"returnInstallment ->\tTo return the installement"<<endl;
    cout<<"changePassword    ->\tTo change Password"<<endl;
    cout<<"showSummary       ->\tShow Summary, Lists overview of the system"<<endl;
    cout<<"restoreBackup     ->\tReplace current content with Backup"<<endl;
    cout<<"showBackup        ->\tDisplay Backup Content"<<endl;
    cout<<"showHistory       ->\tDisplay History Operations"<<endl;
    cout<<"logout            ->\tExit program"<<endl;
    //      At the end of the list;
    cout<<"showMenu          ->\tDisplays Menu"<<endl;
    cout<<endl<<"!!! Function Names are Case-Sensitive !!!"<<endl;
}

void  encDecPassword(char * pass){             //to encrypt & decrypt password
    for(int i=0;pass[i]!=0;i++){
        pass[i]=pass[i]^XOR;
    }
}

int length(char * str){                    //to calculate length of char*
     int i;
    for( i=0;str[i]!=0;i++);
    return ++i;
}

bool compare(char *first,char *sec){    //returns true if 2 strings are equal
    if(length(first)!=length(sec))return false;
    for(int i=0;first[i]!=0 && sec[i]!=0;i++)
        if(sec[i]!=first[i])
            return false;
     return true ;
}

char * input(){                         //to take input in a char* arr
    char *temp=new char[50];
    cin.getline(temp, 50);
    unsigned short int len=length(temp), i;
    char *p;
    p=new char[len];
    for(i=0; i<len; i++)
        p[i]=temp[i];
    p[i]='\0';
    delete[] temp;
    return p;
}
bool checkPassword(){  // Check if correct previous password is entered by the user
    ifstream file("loans.txt");
    string str;
    cin.ignore();
    getline(file,str);
    char *temp=new char[strlen(str.c_str())+1];
    int i;
    for( i=0;str[i]!=0;i++)
      temp[i]=str[i];
      temp[i]='\0' ;
    encDecPassword(temp);
    cout<<"Enter your old password "<<endl;
    char *pass=input();
    bool cmp=compare(pass,temp);
    delete []pass;
    delete []temp;
    file.close();
    return cmp;
}
bool strength(char *pass){      // To check the new password's strength
     bool flag1=0,flag2=0,flag3=0,flag4=0;
     int i; 
  for(i=0;pass[i]!=0;i++){
    if(pass[i]>='a' && pass[i]<='z')
    flag1=true;
    else if(pass[i]>='A' && pass[i]<='Z')
    flag2=true;
    else if( pass[i]>='0' && pass[i]<='9') 
    flag3=true;
    else  if(pass[i]=='#' || pass[i]=='@' ||pass[i]=='$'||pass[i]=='&'|| pass[i]=='*' )flag4=true;

  }
  if(i<8)return false;
  if(!(flag1 ) || !(flag2 ) ||  !(flag3 ) || !(flag4 )){
    return false;
  }
  return true;
 }
void changePassword(){      // To change the password by asking previous password, if correct then ask new password and check if it fulfills our strenght's criteria then finally change the password and updated in the file.
    ifstream file("loans.txt");
    string tempPassword,tempName;
    char tempCnic[14];
    int tempLoan,tempBalance,tempId,ws;
    getline(file,tempPassword);
    file>>tempBalance;
    file.ignore();
    cout<<'\t'<<"!!!Instructions!!!"<<endl;
    cout<<"Password must be strong.\nThere must be atleast one small, CAPITAL, Number and Special Character like: #,$,@,&,* "<<endl;
    bool  check =checkPassword();
    if(!check){cout<<"Your old passord does not match with currnet password "<<endl; file.close();return ;}
    else {
        cout<<"Enter New password  "<<endl;
        char * New=input();
        bool checkStrength=strength(New);
        if(!checkStrength){
            cout<<"Password is weak "<<endl;
            delete []New;
            file.close();
            return ;
        }
        cout<<"Confirm New password  "<<endl;
        char * confirm=input();
        bool passwordCheck=compare(New,confirm);
        if(!passwordCheck){
            cout<<"password does not match "<<endl;
            delete []New;
            delete []confirm;
            file.close();
             return;
         }
        else {
            encDecPassword(New);
            ofstream out("temp.txt");   
            out<<New<<endl;
            out<<tempBalance<<endl;
            string temp;
            while(getline(file,temp)){
                out<<temp<<endl;
            }
            out.close();
        }
    }
    file.close();
    if(remove("loans.txt")==0){
        cout<<"File  (loans.txt) is removed "<<endl;
    }
    else {
        cout<<"Error in removing file (loans.txt)  "<<endl;
    }
    if(rename("temp.txt","loans.txt")==0){
        cout<<"temp file is succesfully renamed "<<endl;
    }
    else {
        cout<<"Error in renaming file "<<endl;
    }
    cout<<"Password is updated succesfully"<<endl;
}

void returnInstallment(){       // To return the installement By CNIC and ID while handling different input cases. Then updating the file.
        ifstream file("loans.txt");
        if(!file){
            cout<<"Error in opening file loans.txt "<<endl;
            return;
        }
        int id,installment;
        char cnic[14];
        cout<<"Enter id  "<<endl;
        cin>>id;
        cin.ignore();
        cout<<"Enter CNIC  "<<endl;
        cin.getline(cnic,14);
        int tempId,tempLoan;
        bool flag=0,exceed=0;
        char  *tempCnic=new char [14];
        string password,name;
        getline(file,password);
        file>>balance;
        while(file>>tempId >>tempCnic >>tempLoan)
        {

            getline(file,name);

            if(tempId==id  && compare(tempCnic,cnic))
            {
                cout<<"Enter  installment: "<<endl;
                cin>>installment;
                cin.ignore();
                if(tempLoan-installment<=0)
                {
                    exceed=true;
                    if(tempLoan-installment<0){
                        int back=installment-tempLoan;
                   cout<<"Extra Amount: "<<back<<endl;
                    }
                }
                flag=true;
                break;
            }
         }
        if(!flag){
            file.close();
            cout<<"Id and CNIC are wrong "<<endl; 
            delete []tempCnic;
            return ;
        }
            ofstream outhis("history.txt",ios::app);
            outhis<<"Return Installment "<<installment<<"BY: ";
            outhis<<tempId<<" "<<tempCnic<<" "<<tempLoan<<" "<<name<<endl;
            outhis.close();

        file.close();

        ifstream in("loans.txt");
        if(!in){cout<<"Error in opening file loans.txt ";return ;}

        ofstream out("temp.txt");
        if(!out){cout<<"Error in opening file temp.txt "; in.close();return ;}

        in>>password;
        out<<password<<endl;

        in>>balance;

        if(exceed)
        out<<balance+tempLoan<<endl;
        else 
        out<<balance+installment<<endl;

        while(in>> tempId >>tempCnic >>tempLoan){
              getline(in,name);
            if(tempId==id && compare(tempCnic,cnic)){
                if(!exceed){
                    out<<id<<' '<<cnic<<' '<<tempLoan-installment;
                    out<<name<<endl;
                }
            }
            else {
                out<<tempId<<' '<<tempCnic<<' '<<tempLoan;
                out<<name<<endl;
            }
        }
        in.close();
        out.close();
        remove("loans.txt");
        rename("temp.txt","loans.txt");
        cout<<"Record is updated successfully "<<endl;
         delete []tempCnic;
    }

void showSummary(){         //Show overview of the loans system (important details).
    ifstream file("loans.txt");
    int tempId,tempLoan,count=0;
    char  *tempCnic=new char [14];
    string tempname,password;
    unsigned long long  int max=0,min=INT_MAX,total=0,currBalance=0;
    getline(file,password);
    file>>currBalance;
     while(file>>tempId >>tempCnic >>tempLoan){
        if(max<tempLoan) max=tempLoan;
        if(min>tempLoan) min=tempLoan;
             count++;
           total+=tempLoan;
        getline(file,tempname);
    }
    cout<<"Current Balance \t:"<<currBalance<<endl;
    cout<<"Total Number of Loans \t:"<<count<<endl;
    cout<<"Total Lend money\t:"<<total<<endl;
    cout<<"MIN loan amount\t\t:"<<min<<endl;
    cout<<"MAX loan amount\t\t:"<<max<<endl;
    delete []tempCnic;
    file.close();
}
void initializeSystem(){                        //if file doesn't exist, the make the file
    fstream file("loans.txt", ios::in | ios::out);
    char* password= new char[30];

    if(!(file)){
        ofstream fout("loans.txt", ios::out);
        cout<<"Set Password for file (include no spaces and no more than 29 characters): ";
        cout<<"Password must be strong.\nThere must be atleast one small, CAPITAL, Number and Special Character like: #,$,@,&,* "<<endl;
        cin>>password;
        while(!(strength(password))){
            cout<<"Password is Weak"<<endl;
            cout<<"Enter again: ";
            cin>>password;
        }
            encDecPassword(password);
            fout<<password<<endl;
            cout<<"Enter Balance: ";
            cin>>balance;
            fout<<balance<<endl;
            fout.close();
    }
    else{
        file>>password;
        file>>balance;
        file.close();
    }
    delete[] password;
}

bool login(){                       //returns 1 if login failed
    ifstream fin("loans.txt", ios::in); 
    char* password= new char[30];
    char* userPassword= new char[30];
    
    fin>>password;
    fin.close();

    short int i=0;
    cout<<"Be careful you have only 3 attempts "<<endl;
    while(i<3){
        cout<<"Enter Password: ";
        cin>>userPassword;
        encDecPassword(userPassword);
        i++;
        if(compare(password, userPassword))
            break; 
        else{
            cout<<"Wrong Password  \nattempts  left "<<3-i<<endl;
            
            if(i==3){
                delete[] password;
                delete[] userPassword;
                return 1;
            }
        }
    }
    delete[] password;
    delete[] userPassword;
    return 0;
}

void addRecord(){                           //to add a record
    Loan l;
    l.id=0;
    l.cnic= new char[14];   //one location for \0
    l.loanAmount;
    l.name= new char[50];
    char* password= new char[30];
    unsigned int newLoanAmount;
    bool personExists= false;
    bool giveLoan=true;

    cout<<"Enter Loan Amount (Max loan allowed is "<<MAXLOAN<<") : ";
    cin>>newLoanAmount;

    if(newLoanAmount>balance || balance<=BASELINE){
        cout<<"Not enough Balance"<<endl;
        giveLoan=false;
    }

    else if(newLoanAmount>MAXLOAN){
        cout<<"Loan higher than "<<MAXLOAN<<" is not allowed"<<endl;
        giveLoan=false;
    }
    if(giveLoan==false){
        delete[] password;
        delete[] l.cnic;
        delete[] l.name;
        return;
    }

    char* newCnic= new char[14];

    cout<<"Enter CNIC (wihtout -) : ";
    cin.ignore();
    cin.getline(newCnic, 14);
    if (cin.fail()) {   //clearing buffer if input fails
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input too long. Truncated to fit in"<<endl;;
    }
    
    ifstream fin("loans.txt");
    fin>>password;
    fin>>balance;
    
    while(fin>>l.id){
        fin>>l.cnic;
        fin>>l.loanAmount;
        fin.getline(l.name, 50);
        if(compare(l.cnic, newCnic)) {
            cout<<"Person already exists"<<endl;
            personExists= true;
            break;
        }     
    }
    if(personExists){
        if(l.loanAmount+newLoanAmount>MAXLOAN){
            cout<<"Person cannot take a new loan because his total loan exceeds "<<MAXLOAN<<endl;
            fin.close();
            delete[] password;
            delete[] l.cnic;
            delete[] l.name;
            return;
        }
        cout<<"Person can take a new loan because his total loan is within limit"<<endl;

        fin.close();
        ifstream fin("loans.txt");
        ofstream fout("temp.txt");

        fin>>password;
        fin>>balance;
        balance-=newLoanAmount;
        fin.clear();
        fout<<password<<endl;
        fout<<balance<<endl;

        while(fin>>l.id){
            fin>>l.cnic;
            fin>>l.loanAmount;
            fin >> std::ws; 
            fin.getline(l.name, 50);
            if(compare(l.cnic, newCnic)){
            l.loanAmount+=newLoanAmount;
            ofstream outhis("history.txt",ios::app);
            outhis<<"Increased Loan by "<<newLoanAmount<<" for: ";
            outhis<<l.id<<" "<<l.cnic<<" "<<l.loanAmount<<" "<<l.name<<endl;
            outhis.close();
            }
            fin.clear();
            fout<<l.id<<" "<<l.cnic<<" "<<l.loanAmount<<" "<<l.name<<endl;
            
            }
            fout.close();
            fin.close();
    }
    else{
        fin.close();
        ifstream fin("loans.txt");
        ofstream fout("temp.txt");

        fin>>password;
        fin>>balance;
        balance-=newLoanAmount;
        fin.clear();
        fout<<password<<endl;
        fout<<balance<<endl;

        while(fin>>l.id){
            fin>>l.cnic;
            fin>>l.loanAmount;
            fin >> std::ws; 
            fin.getline(l.name, 50);
            fin.clear();
            fout<<l.id<<" "<<l.cnic<<" "<<l.loanAmount<<" "<<l.name<<endl;
        }
        
        cout<<"ID is "<<++l.id<<endl;
        cout<<"Enter Name: ";
        cin.getline(l.name, 50);
        fout<<l.id<<" "<<newCnic<<" "<<newLoanAmount<<" "<<l.name<<endl;
        fout.close();
        fin.close();
        ofstream outhis("history.txt",ios::app);
            outhis<<"New Record: ";
            outhis<<l.id<<" "<<newCnic<<" "<<newLoanAmount<<" "<<l.name<<endl;
            outhis.close();
    }
    cout<<"Record Added"<<endl;
    remove("loans.txt");
    rename("temp.txt","loans.txt");
    delete[] password;
    delete[] l.cnic;
    delete[] l.name;
    delete[] newCnic;
}

void takeBackup(){      //Stores backup when user logout
    Loan l;
    l.name= new char[50];
    l.cnic= new char[14];
    char* password= new char[30];
    
    ifstream fin("loans.txt");
    ofstream fout("loansBackup.bin", ios::binary);

    fin>>password;
    fin>>balance;
    fout.write(password, 30);
    fout.write((char*) &balance, sizeof(balance));

    while(fin>>l.id){
        fin>>l.cnic;
        fin>>l.loanAmount;
        fin >> std::ws;
        fin.getline(l.name, 50);
        fout.write((char*) &l.id, sizeof(l.id));
        fout.write(l.cnic, 14);
        fout.write((char*) &l.loanAmount, sizeof(l.loanAmount));
        fout.write(l.name, 50);
    }
    fout.close();
    fin.close();
    delete[] l.name;
    delete[] l.cnic;
    delete[] password;
}

void restoreBackup(){       //Replace the file's current data with backfile file's data.
    Loan l;
    l.name= new char[50];
    l.cnic= new char[14];
    char* password= new char[30];

    ofstream fout("loans.txt");
    ifstream fin("loansBackup.bin", ios::binary);

    fin.read(password, 30);
    fin.read((char*) &balance, sizeof(balance));
    fout<<password<<endl;
    fout<<balance<<endl;

    while(fin.read((char*) &l.id, sizeof(l.id))){
        fin.read(l.cnic, 14);
        fin.read((char*) &l.loanAmount, sizeof(l.loanAmount));
        fin.read(l.name, 50);
        fout<<l.id<<" "<<l.cnic<<" "<<l.loanAmount<<" "<<l.name<<endl;
    }
    fout.close();
    fin.close();
    delete[] l.name;
    delete[] l.cnic;
    delete[] password;
    ofstream outhis("history.txt",ios::app);
            outhis<<"!!!Backup Restored!!!"<<endl;
            outhis.close();
}
void printCnic(const char* cnic);

void showBackup(){     // Displays the content inside backup file.
    Loan l;
    l.name= new char[50];
    l.cnic= new char[14];
    char* password= new char[30];
    unsigned long long int tempBalance;

    ifstream fin("loansBackup.bin", ios::binary);

    fin.read(password, 30);
    fin.read((char*) &tempBalance, sizeof(balance));
    cout<<"ID\tCNIC\t  Loan\t\tName "<<endl<<endl;
    while(fin.read((char*) &l.id, sizeof(l.id))){
         memset(l.cnic, 0, 14);     
         memset(l.name, 0, 50); 
        fin.read(l.cnic, 14);
        fin.read((char*) &l.loanAmount, sizeof(l.loanAmount));
        fin.read(l.name, 50);
        cout<<l.id<<" ";
        printCnic(l.cnic);
        cout<<' '<<l.loanAmount<<" "<<l.name<<endl;
    }
    fin.close();
    delete[] l.name;
    delete[] l.cnic;
}

void printCnic(const char* cnic) {  //To display CNIC with a ( - ).
    for(int i=0; i<13; i++){
        if(i==5 || i==12) 
        cout<<"-";
        cout<<cnic[i];
    }
}

char* copyingString(const string& s) { //returns a character pointer by taking a string.
    char* temparr=new char[s.length()+1];
    for (int i=0;i<s.length();i++) 
    temparr[i] = s[i];
    temparr[s.length()]='\0';
    return temparr;
}

void showLoans(){                           //Display all records
    Loan l;
    ifstream in("loans.txt");
    if (!in)
    {
        cout << "Error opening loans.txt\n";
        return;
    }
    string password;
    in>>password;
    in>>balance;
    cout<<"ID\tCNIC\t  Loan\t\tName "<<endl<<endl;
    while (in>>l.id)
    {   
        cout<<l.id<<" ";

        string ctemp;
        in>>ctemp;
        l.cnic=copyingString(ctemp);
        printCnic(l.cnic);
        delete[] l.cnic;
        cout<<" ";

        in>>l.loanAmount;
        cout<<l.loanAmount<<' ';
        in>>ws;
        string ntemp;
        getline(in,ntemp);
        l.name=copyingString(ntemp);
        cout<<l.name;
        cout<<'\n';
        delete[] l.name;
    }
    in.close();
}

void addBalance() {                     //add balance to system
    Loan l;
    ifstream in("loans.txt");
    if (!in)
    {
        cout << "Error opening loans.txt\n";
        return;
    }

    ofstream out("temp.txt");
    if (!out) {
        cout << "Error opening temp.txt\n";
        return;
    }

    cout<<endl<<"Enter Amount to be added in the Balance: ";
    int add;
    cin>>add;

    string password;
    in>>password;
    out<<password<<'\n';

    in>>balance;
    balance+=add;
    out<< balance <<'\n';

   while (in>> l.id)
    {   
        out<<l.id<<" ";

        string ctemp;
        in>>ctemp;
        l.cnic=copyingString(ctemp);
        out<<l.cnic<<" ";
        delete[] l.cnic;

        in>>l.loanAmount;
        out<<l.loanAmount<<'\t';

        in>>ws;
        string ntemp;
        getline(in,ntemp);
        l.name=copyingString(ntemp);
        out<<l.name<<'\n';
        delete[] l.name;
    }

    in.close();
    out.close();

    remove("loans.txt");
    rename("temp.txt","loans.txt");
    ofstream outhis("history.txt",ios::app);
            outhis<<"Added Balance: ";
            outhis<<add<<endl;
            outhis.close();
}

void showBalance() {                //show balance in system
    ifstream in("loans.txt");
    if (!in) {
        cout << "Error opening loans.txt\n";
        return;
    }

    string password;
    in>>password;

    in>>balance;
    cout<<"Balance: "<<balance<<'\n';
    in.close();
    }

void showById() {                   //show record by id
    ifstream in("loans.txt");
    if (!in) {
    cout << "Error opening loans.txt\n";
    return;
    }
    cout<<"Enter ID: ";
    unsigned short int i;
    cin>>i;

    Loan l;

    string password;
    in>>password;

    in>>balance;
    
    while (in>> l.id)
    {   
        if(i==l.id){
            cout<<"ID\tCNIC\t  Loan\t\tName "<<endl;
            cout<<l.id<<" ";
            string ctemp;
            in>>ctemp;
            l.cnic=copyingString(ctemp);
            printCnic(l.cnic);
            delete[] l.cnic;
            cout<<" ";

            in>>l.loanAmount;
            cout<<l.loanAmount<<' ';
            in>>ws;
            string ntemp;
            getline(in,ntemp);
            l.name=copyingString(ntemp);
            cout<<l.name;
            cout<<'\n';
            delete[] l.name;
            in.close();
            return;
        }

        else {
            string waste;
            getline(in,waste);
        }
    }

    cout<<"ID does not Exists!"<<endl;
    in.close();
}

void showByCnic() {     //Show record by CNIC
    cin.ignore();
        cout<<endl<<"Enter CNIC(without - ) : ";
        char *c;
        c=new char[14];
        cin.get(c, 14);
        for(int i=0;i<13;i++) 
        {
            if(c[i]<'0' || c[i]>'9')
            {
                cout<<"Invalid Cnic!"<<endl;
                delete []c;
                return;
            }
        }

        Loan l;

        ifstream in("loans.txt");
        if(!in){
        cout<<"Error opening file!"<<endl;
        delete[] c;
        return;
        }

        string password;
        in>>password;

        in>>balance;

        string ctemp;
        
        while (in>> l.id)
        {   
        in>>ctemp;
        l.cnic=copyingString(ctemp); 

        if(compare(c,l.cnic))
        {
            cout<<"ID\tCNIC\t  Loan\t\tName "<<endl;
        cout<<l.id<<" ";

        printCnic(l.cnic);
        delete[] l.cnic;
        delete[] c;
        cout<<" ";

        in>>l.loanAmount;
        cout<<l.loanAmount<<'\t';

        in>>ws;
        string ntemp;
        getline(in,ntemp);
        l.name=copyingString(ntemp);
        cout<<l.name<<endl;

        delete[] l.name;
        in.close();
        return;
        }

        else {
            string waste;
            getline(in,waste);
        }
        delete[] l.cnic;
    }
    
    delete[] c;
    cout<<"This CNIC does not Exists!"<<endl;
    in.close();
    }

void removeById(){    //Remove record by ID
    Loan l;

    ifstream in("loans.txt");
    if (!in) {
        cout << "Error opening loans.txt\n";
        return;
    }

    cout<<"Enter ID: ";
    unsigned short int ti;
    cin>>ti;

    bool flag=false;
    string a;

    string password;
    in>>password;

    in>>balance;

    while (in>> l.id)
    {   
        if(ti==l.id)
        {
            flag=true;
            break;
        }
        in.ignore();
        getline(in,a);
    }
        
    if(!flag){
        cout<<"ID Already does not Exists!";
            return;
    }

    in.clear();
    in.seekg(0, ios::beg);

    ofstream out("temp.txt");
    if (!out) {
    cout << "Error opening temp.txt\n";
    return;
    }
        
    in>>password;
    out<<password<<'\n';

    in>>balance;
    out<<balance<<'\n';
        string ctemp;
        string ntemp;
    while (in>> l.id)
    {   
        if(ti==l.id){
           cout<<"Removed ID: "<<l.id<<" ";
            
            in>>ctemp;
            cout<<ctemp<<" ";

            in>>l.loanAmount;
            cout<<l.loanAmount<<" ";

            in>>ws;
            string ntemp;
            getline(in,ntemp);
            cout<<ntemp<<'\n';
            
            ofstream outhis("history.txt",ios::app);
            outhis<<"Removed ID: ";
            outhis<<l.id<<" "<<ctemp<<" "<<l.loanAmount<<" "<<ntemp<<endl;
            outhis.close();
        }
        else {
            out<<l.id<<" ";

            in>>ctemp;
            out<<ctemp<<" ";

            in>>l.loanAmount;
            out<<l.loanAmount<<" ";

            in>>ws;
            
            getline(in,ntemp);
            out<<ntemp<<'\n';
        }
    }

    in.close();
    out.close();

    remove("loans.txt");
    rename("temp.txt","loans.txt");
}

void removeByCnic(){ //Remove record by CNIC
    cin.ignore();
        cout<<"Enter CNIC(without - ) : ";
        char *c;
        c=new char[14];
        cin.get(c, 14);

        for(int i=0;i<13;i++){
            if(c[i]<'0' || c[i]>'9'){
                cout<<"Invalid Cnic!"<<endl;
                delete []c;
                return;
            }
        }

        Loan l;

        ifstream in("loans.txt");
        if(!in) {
        cout<<"Error opening file!"<<endl;
        delete[] c;
        return;
        }

        string ctemp;
        bool flag=false;
        string w;

        string password;
        in>>password;
        in>>balance;

    while (in>> l.id)
        {
            in>>ctemp;
            l.cnic=copyingString(ctemp); 
        if(compare(c,l.cnic))  
            {
            flag=true;
            delete[] l.cnic;
            break;
            }
        delete[] l.cnic;
        in.ignore();
        getline(in,w);
        }
        
        if(!flag)
        {
            cout<<"This CNIC Already does not Exists!"<<endl;
            delete[] c;
            return;
        }

        in.clear();
        in.seekg(0, ios::beg);

        ofstream out("temp.txt");
        if (!out) {
        cout << "Error opening temp.txt\n";
        return;
        }

        in>>password;
        out<<password<<'\n';

        in>>balance;
        out<<balance<<'\n';

        string ntemp;

    while (in>> l.id)
    {   
        in>>ctemp;
        l.cnic=copyingString(ctemp); 

        if(compare(c,l.cnic))
        {
        cout<<endl<<"Removed Cnic: "<<l.id<<" ";

            cout<<ctemp<<" ";
            delete[] l.cnic;

            in>>l.loanAmount;
            cout<<l.loanAmount<<" ";

            in>>ws;
            getline(in,ntemp);
            cout<<ntemp<<'\n';
            
            ofstream outhis("history.txt",ios::app);
            outhis<<"Removed Cnic: ";
            outhis<<l.id<<" "<<ctemp<<" "<<l.loanAmount<<" "<<ntemp<<endl;
            outhis.close();

        }

        else 
        {
            out<<l.id<<" ";

            out<<ctemp<<" ";
            delete[] l.cnic;

            in>>l.loanAmount;
            out<<l.loanAmount<<" ";

            in>>ws;
            getline(in,ntemp);
            out<<ntemp<<'\n';
        }  
    }
    delete[] c;

    in.close();
    out.close();

    remove("loans.txt");
    rename("temp.txt","loans.txt");
    }

    void showHistory(){
        ifstream in("history.txt");
        if(!in) {
            cout<<"Error opening History file!"<<endl;
            return;
            }
            string operations;
        while(getline(in,operations))
        cout<<operations<<endl;
    }

 int main() {
	initializeSystem();
    if(login()) return 0;
    showMenu();
    string funcName;
    while(true){
        cout<<endl<<"Function please :-) ";
        cin>>funcName;
        if(funcName=="logout") {
           takeBackup();
            return 0;
        }
        else if(funcName=="addRecord") addRecord();
        else if(funcName=="showLoans") showLoans();
        else if(funcName=="showBalance") showBalance();
        else if(funcName=="addBalance") addBalance();
        else if(funcName=="showById") showById();
        else if(funcName=="showMenu") showMenu();
        else if(funcName=="showByCnic") showByCnic();
        else if(funcName=="removeById") removeById();
        else if(funcName=="removeByCnic") removeByCnic();
        else if(funcName=="showSummary") showSummary();
        else if(funcName=="returnInstallment") returnInstallment();
        else if(funcName=="changePassword") changePassword();
        else if(funcName=="restoreBackup") restoreBackup();
        else if(funcName=="showBackup") showBackup();
        else if(funcName=="showHistory") showHistory();
        else
        cout<<"Invalid Function Name: ";
    }
}

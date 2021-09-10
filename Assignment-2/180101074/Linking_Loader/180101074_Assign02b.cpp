/*
Assignment-2 Two Pass Linking Loader
CS348

Environment:        LINUX g++

Compile and Run:    g++ 180101074_Assign02b.cpp
                    ./a.out

Name:       SHIVAM KUMAR AGRAWAL
Roll no.    180101074
*/


#include<bits/stdc++.h>
using namespace std;

struct estab //Data for external symbol table
{
    string csname;
    string extsym;
    string address;
    string length;
}ESTAB[2000];

struct exttable  
{
  string cextsym, extsym;
  string address,length;
}myexttab[2000];

struct objectcode   //Object Code and its address
{
 string code;
 string add;
}myobjectcode[50000];

//Integer to Hexadecimal
string itoh(int d) {
	string hs;
    stringstream ss;
    ss << hex << d;
    ss >> hs;
	transform(hs.begin(), hs.end(), hs.begin(), ::toupper);
	return hs;
}

// hexadecimal to integer
int htoi(string hs) {
    int d;
    stringstream ss;
    ss << hs;
    ss >> hex >> d;
    return d;
}

//To extend size
string extendTo(int dig,string a)
{
    string temp="";
    for(int i=0;i<dig-a.length();++i)
        temp+='0';
    return temp+a;
}

void PASS1(string input_file,string prog_addr) //Pass 1 of linking-loader (Assign address to all external Symbols)
{
    string input,name,symbol;
    char file_char;
    int count=0;

    //CSADDR contains the starting address assigned to the  current control section.
    //PROGADDR is the beginning address in memory where the linked program is to be loaded

    string progaddr,csaddr,add,len,sym; 
    ifstream ip(input_file);
    ofstream op("estab.txt");
    progaddr=prog_addr; //prog_addr is taken as 4000  (Can be changed at Main function)
    csaddr=progaddr;
    ip>>input;      //First read from input file
    while(input!="END")
    {
        if(input=="H") //If Header Record
        {
            ip>>name;
            ip>>add;
            ip>>len;
            ESTAB[count].csname=name;
            ESTAB[count].extsym=" ";
            ESTAB[count].address=itoh(htoi(add)+htoi(csaddr));
            ESTAB[count].length=len;
            op<<ESTAB[count].csname<<" ** "<<ESTAB[count].address<<" "<<ESTAB[count].length<<endl;
            count++;
            
        }
        else if(input=="D") //If Define Record
        {
            ip>>input;
            while(input!="R")// If Refer Record then stop
            {
                ip>>add;
                ESTAB[count].csname=" ";
                ESTAB[count].extsym=input;
                ESTAB[count].address=itoh(htoi(add)+htoi(csaddr));
                ESTAB[count].length="0";
                op<<"** "<<ESTAB[count].extsym<<" "<<ESTAB[count].address<<" "<<ESTAB[count].length<<endl;
                count++;
                ip>>input;
            }
            csaddr=itoh(htoi(csaddr)+htoi(len));
        }
        else if(input=="T")// If Text Record then read without storing until end record (Will be used in Pass 2)
        {
            while(input!="E")
            {
                ip>>input;
            }
            
        }
        ip>>input;
    }
    ip.close();
    op.close();
    ip.open("estab.txt");
    cout<<"\n\t***** PASS ONE OF A LINKING LOADER *****\n";
    cout<<"\nThe contents of the ESTAB file :";
    cout<<"\n---------------------------------------------------------------\n";
    ip.get(file_char);
    while(!ip.eof())    //Print Contents of ESTAB file
    {
        cout<<file_char;
        ip.get(file_char);
    }
    ip.close();
    cout<<"---------------------------------------------------------------\n";


}

// Pass 2 of linking-loader (Responsible for the actual loading, 
// along with the tasks involved in relocating and linking the different object codes.)
void PASS2(string input_file) 
{
    string temp;
    ifstream ip1,ip2;
    ofstream op;
    long long int i,j,x,y;
    string prog_start,exeloc,start,text_loc,loc,text_len,st,s;
    long long int n=0,num=0,inc=0,count=0,record=0;
    long long int length,curr_loc;
    string mloc[30],mlen[30];
    string newadd;
    char operation,file_char,*add1;
    string lbl,input,labels[50],address;
    ip1.open(input_file);
    ip2.open("estab.txt");
    op.open("output.txt");
    while(!ip2.eof())// Read Input from ESTAB file
    {
        string csym,extsym,addr,len;
        ip2>>csym>>extsym>>addr>>len;
        myexttab[num].cextsym=csym;
        myexttab[num].extsym=extsym;
        myexttab[num].address=addr;
        myexttab[num].length=len;
        num++;

    }
    exeloc=myexttab[0].address;
    loc=exeloc;
    start=loc; // Assign start address
    st=start;
    while(!ip1.eof()) //Read Input from Object Program
    {
        ip1>>input;
        if(input=="H") //Handle the case of header record
        {
            ip1>>input;
            for(i=0;i<num;i++)
            {
                if(input==myexttab[i].cextsym)
                {
                    prog_start=myexttab[i].address;
			        break;

                }
            }
            while(input!="T") // Till text Record
            {
                ip1>>input;
            }
        }
        do
        {
            if(input=="T") //Handle the case of Text record
            {
                ip1>>text_loc;
                text_loc=itoh(htoi(text_loc)+htoi(prog_start));
                for(i=0;i<(htoi(text_loc)-htoi(loc));i++)
                {
                    myobjectcode[inc].code="..";
                    myobjectcode[inc++].add=start;
                    start=itoh(htoi(start)+1);

                }
                ip1>>text_len;
                loc=itoh(htoi(text_loc)+htoi(text_len));
            }
            else if(input=="M") //Handle the case of Modification record
            {
                string m_loc,m_len,m_label;
                ip1>>m_loc>>m_len>>m_label;
                mloc[record]=itoh(htoi(m_loc)+htoi(prog_start));
                mlen[record]=m_len;
                labels[record++]=m_label;



            }
            else // Handle the object codes of Text Records
            {
                length=input.length();
                x=0;
                for(i=0;i<length;i++)
                {
                    myobjectcode[inc].code+=input[i];
                    x++;
                    if(x>1)
				    {
					    myobjectcode[inc++].add=start;
                        start=itoh(htoi(start)+1);
					    x=0;
				    }
                }
            }
            ip1>>input;
        }
        while(input!="E"); // Till End Record

        if(input=="E")
        {
            ip1>>input;
        }
    }

    for(n=0;n<record;n++) //Generate Object Code and Program
    {
        operation=labels[n][0];
        length=(labels[n]).length();
        lbl="";
        for(i=1;i<length;i++)
        {
            lbl+=labels[n][i];
        }
        length=0;
        address="";
        curr_loc=htoi(mloc[n])-htoi(exeloc);
        loc=itoh(curr_loc);
        count=0;
        while(length<htoi(mlen[n]))
        {
            address+=myobjectcode[curr_loc++].code;
            count++;
            length+=2;
        }
        for(i=0;i<num;i++)
        {
            if(lbl==myexttab[i].cextsym)
            {
                break;
            }
            if(lbl==myexttab[i].extsym)
            {
                break;
            }
        }
        switch(operation)  
        {
            case '+':
                    newadd=itoh(htoi(address)+htoi(myexttab[i].address));
                    break;
            case '-':
                    newadd=itoh(htoi(address)-htoi(myexttab[i].address));
                    break;
        }
        address=newadd;
        x=0,y=0;
        while(count>0)
        {
            myobjectcode[htoi(loc)].code[x++]=address[y++];
            if(x>1)
            {
                    x=0;
                    string temp1=myobjectcode[htoi(loc)].code;
                    int t1=address.length();
                    if(t1==5&&y>4)
                    {
                        
                        myobjectcode[htoi(loc)].code[1]='.';
                    }
                    loc=itoh(htoi(loc)+1);
                    count--;
                    
            }
        }
    }
    count=0;
    n=0;
    s=itoh(htoi(st)-16);
    op<<s<<"\t";
    for(i=1;i<=16;i++)
    {
        op<<"xx";
        if(i==4||i==8||i==12)
        {
            op<<"\t";
        }
    }
    op<<"\n\n"<<myobjectcode[0].add<<"\t";
    for(i=0;i<inc;i++)
    {
        op<<myobjectcode[i].code;
        n++;
        if(n>3)
        {
            op<<"\t";
            n=0;
            count++;
        }
        if(count>3)
        {
            op<<"\n\n"<<myobjectcode[i+1].add<<"\t";
            count=0;
        }
    }
    ip1.close();
    ip2.close();
    op.close();
    cout<<"\n\t***** PASS TWO OF A LINKING LOADER *****\n";
    cout<<"\nThe contents of the output file :";
    cout<<"\n---------------------------------------------------------------";
    cout<<"\nAddress\t\t\t\tContents";
    cout<<"\n---------------------------------------------------------------\n";
    ip1.open("output.txt");
    ip1.get(file_char);
    while(!ip1.eof())
    {
        cout<<file_char;
        ip1.get(file_char);

    }
    ip1.close();
    cout<<"\n---------------------------------------------------------------\n";

}

int main()
{
    string input_file="input.txt";  //Put input obect file
    string prog_addr="2000";            //Put Address where program will be loaded
    PASS1(input_file,prog_addr);
    PASS2(input_file);
}
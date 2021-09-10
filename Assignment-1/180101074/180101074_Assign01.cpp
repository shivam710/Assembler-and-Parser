/*
Assignment-1
CS348

Environment:        LINUX g++

Compile and Run:    g++ 180101074_Assign01.cpp
                    ./a.out

Input file:         input.txt
Intermediate file:  inter.txt
Output file:        output.txt

Name:       SHIVAM KUMAR AGRAWAL
Roll no.    180101074
*/




#include <bits/stdc++.h>
using namespace std;
int symcount=0;
string len1;
string startaddr,locctr;
string label,opcode,operand;
string programname;

struct optab
{
    string code,objcode;

} myoptab[25] =
    {
        {"START", "*"},{"LDA", "00"},{"LDX", "04"},{"LDL", "08"},{"STA", "0C"},
        {"STX", "10"},{"STL", "14"},{"LDCH", "50"},{"STCH", "54"},{"ADD", "18"},
        {"SUB", "1C"},{"MUL", "20"},{"DIV", "24"},{"COMP", "28"},{"J", "3C"},
        {"JLT", "38"},{"JEQ", "30"},{"JGT", "34"},{"JSUB", "48"},{"RSUB", "4C"},
        {"TIX", "2C"},{"TD", "E0"},{"RD", "D8"},{"WD", "DC"},{"END","*"}
    };

// (SYMBOL , ADDRESS)
struct symtab
{
    string symbol;
    string addr;

} mysymtab[30];

// integer to hexadecimal
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
//function to process label (i.e SYMBOL)
void chk_label()
{
    int d=0;
    for(int i=0;i<symcount;i++)
    {
        if(label==mysymtab[i].symbol)
        {
            mysymtab[i].addr="-1";
            d=1;
            break;
        }
    }
    if(!d)
    {
        mysymtab[symcount].symbol=label;
        mysymtab[symcount++].addr = locctr;

    }
}

//function to process opcode
void chk_opcode()
{
    int found=0;
    for(int k=0;k<25;k++)
    {
        if(opcode==myoptab[k].code)
        {
            locctr=itoh(htoi(locctr)+3);
            found=1;
            break;
        }
    }
    if(!found)
    {
        if(opcode=="WORD")
        {
            locctr=itoh(htoi(locctr)+3);
        }
        else if(opcode=="RESW")
        {
            string nBytes=itoh((3*(stoi(operand))));
            locctr=itoh(htoi(locctr)+htoi(nBytes));
        }
        else if(opcode=="RESB")
        {
            string nBytes = itoh(stoi(operand));
            locctr=itoh(htoi(locctr)+htoi(nBytes));

        }
        else if(opcode=="BYTE")
        {
            int nBytes;
            char byteType=operand[0];
            if(byteType=='C')   //character byte
            {
                nBytes=operand.size()-3;
            }
            else    //hexadecimal numBytes
            {
                if((operand.size()-3)%2==0) 
                {
                    nBytes = (operand.size()-3)/2;
                }
				else 
                {
                    nBytes = ((operand.size()-3)/2)+1;
                }

            }
            locctr=itoh(htoi(locctr)+htoi(to_string(nBytes)));
        }
    }
}

//function to read process lines
void READ_LINE(string rline)
{
    int line_len=rline.length();
    int it=0;
    label="";
    opcode="";
    operand="";
    while(it<line_len)
    { 
        if(rline[it]!=' '&&rline[it]!='\t'&&rline[it]!='\n')
        {
            label+=rline[it];
            it++;
        }
        else break;
    }
    if(label=="")
    {
        label="**";
    }
    
    while(it<line_len)
    {
        if(rline[it]==' '||rline[it]=='\t'||rline[it]=='\n')
        {
            it++;
        }
        else break;
    }

    while(it<line_len)
    { 
        if(rline[it]!=' '&&rline[it]!='\t'&&rline[it]!='\n')
        {
            opcode+=rline[it];
            it++;
        }
        else break;
    }
    if(opcode=="")
    {
        opcode="**";
    }
    while(it<line_len)
    {
        if(rline[it]==' '||rline[it]=='\t'||rline[it]=='\n')
        {
            it++;
        }
        else break;
    }

    while(it<line_len)
    { 
        if(rline[it]!=' '&&rline[it]!='\t'&&rline[it]!='\n')
        {
            operand+=rline[it];
            it++;
        }
        else break;
    }
    if(operand=="")
    {
        operand="**";
    }
    while(it<line_len)
    {
        if(rline[it]==' '||rline[it]=='\t'||rline[it]=='\n')
        {
            it++;
        }
        else break;
    }

}




void PASS1()
{
    string rline;
    ifstream ip("input.txt");
    ofstream op("inter.txt");

    // reads first line
    getline(ip,rline);
    while(rline[0]=='.')
    {
        getline(ip,rline);
    }
    READ_LINE(rline);

    if(opcode=="START")
    {
        cout<<endl<<"--------------------INTERMEDIATE------------------------"<<endl;
        cout<<"ADDRESS"<<"\t"<<"LABEL"<<"\t"<<"OPCODE"<<"\t"<<"OPERAND"<<endl<<endl;
        startaddr= (operand);
        locctr=startaddr;
        programname=label;
        op<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
        cout<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
        getline(ip,rline);
        while(rline[0]=='.')
        {
            getline(ip,rline);
        }
        READ_LINE(rline);
    }
    else
    {
        programname="";
        startaddr="0";
        locctr="0";
    }

    // loop to read subsequent lines
    while(opcode!="END")
    {
        string orig_locctr=locctr;      //stores current location
        if(label!="**")
        {
            chk_label();    //check label
        }
        chk_opcode();      //check opcode
        op<<orig_locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
        cout<<orig_locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
        getline(ip,rline);
        while(rline[0]=='.')
        {
            getline(ip,rline);
        }
        READ_LINE(rline);


    }
    op<<locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
    cout<<locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
    len1=itoh(htoi(locctr)-htoi(startaddr));
    ip.close();
    op.close();
    cout<<"---------------------------------------------------------"<<endl<<endl;
    cout<<"Length of Object Program = "<<string(6-len1.size(),'0') <<len1<<endl;


}
void PASS2()
{
    string record,part,value;
    int currtxtlen = 0, foundopcode, foundoperand, chk, operandaddr;

    string recaddr;

    string address;
    ifstream ip("inter.txt");
    ofstream op("output.txt");

    //reads first line from intermediate file
    ip>>label>>opcode>>operand;

    if(opcode=="START")
    {
        cout<<"-----------------------OUTPUT----------------------------"<<endl;
        op<< "H^"<<programname<<string(6-programname.size(),' ') <<"^"<<string(6-startaddr.size(),'0') <<startaddr<<"^"<<string(6-len1.size(),'0') <<len1;
        cout<< "H^"<<programname<<string(6-programname.size(),' ') <<"^"<<string(6-startaddr.size(),'0') <<startaddr<<"^"<<string(6-len1.size(),'0') <<len1;
        recaddr = (startaddr);
        record="";

        //reads second line
        ip>>address>>label>>opcode>>operand;
    }

     // loop to read subsequent lines
    while(opcode!="END")
    {
        operandaddr = foundoperand = foundopcode = 0;
        value="";
        part="";

        //check for opcode
        for(chk=0;chk<25;chk++)
        {
            if(opcode==myoptab[chk].code)
            {
                foundopcode=1;
                part=myoptab[chk].objcode;
                if(operand!="**")
                {
                    string real_operand;
                    int spcl=0;

                    for(int j=0;j<operand.length();j++)
                    {
                        if(operand[j]==',') //check for index addressing
                        {
                            spcl=1;
                            break;
                        }
                        real_operand+=operand[j];
                    }
                    operand=real_operand; //remove ",X" ,if present

                    for(chk=0;chk<symcount;chk++)   //check for symbol
                    {
                        if(operand==mysymtab[chk].symbol)
                        {
                            value=(mysymtab[chk].addr);

                            //for index addressing
                            if(spcl)
                            {
                                value=itoh(htoi(value)+htoi("8000"));
                            }
                            for(int i=0;i<(4-value.length());i++)
                            {
                                part=part+"0";
                            }
                            part=part+value;
                            foundoperand=1;
                        }
                        
                    }
                    if(!foundoperand)   //operand not found in symbol table
                    {
                        part=part+"err";
                    }
                }
                else            //if there is no operand for opcode
                {
                    part=part+string(6-part.size(),'0');

                }
                break;
            }

        }
        if(!foundopcode)    //if opcode not found, checks for other cases
        {
            if(opcode=="BYTE")
            {
                if(operand[0]=='C')
                {
                    for(int i=2; i<operand.size()-1; i++) 
                    {
					    int ascii = operand[i];
					    part += (itoh(ascii));
                    }
                }
                else 
                {	
				    for(int i=2; i<operand.size()-1; i++) 
                    {
					    part += (operand[i]);
                    }
			    }

            }
            else if(opcode=="WORD")
            {
                string ad;
                ad=itoh(stoi(operand));
                int len=ad.length();
                for(int i=0;i<(6-len);i++)
                {
                    part=part+"0";
                }
                part=part+ad;

            }
        }
            
        if ((currtxtlen + part.length()) <= 36)
        {
            if(part!="")
            {
                record=record+"^";
                record=record+part;
                currtxtlen += part.length();
            }
        }
        else
        {
            string c_len=itoh(currtxtlen);
            op<<endl;
            cout<<endl;
            op<<"T^"<<string(6-recaddr.size(),'0')<<recaddr<<"^"<<string(2-c_len.size(),'0') <<c_len<<record;
            cout<<"T^"<<string(6-recaddr.size(),'0')<<recaddr<<"^"<<string(2-c_len.size(),'0') <<c_len<<record;
            currtxtlen=part.length();
            record="^"+part;
            recaddr=address;
            
        }
        ip>>address>>label>>opcode>>operand;
    }
    string c_len=itoh(currtxtlen);
    op<<endl;
    cout<<endl;
    op<<"T^"<<string(6-recaddr.size(),'0')<<recaddr<<"^"<<string(2-c_len.size(),'0') <<c_len<<record;
    cout<<"T^"<<string(6-recaddr.size(),'0')<<recaddr<<"^"<<string(2-c_len.size(),'0') <<c_len<<record;
    op<<endl;
    cout<<endl;
    op<<"E^"<<string(6-startaddr.size(),'0') <<startaddr<<endl;
    cout<<"E^"<<string(6-startaddr.size(),'0') <<startaddr<<endl;
    ip.close();
    op.close();
    cout<<"---------------------------------------------------------"<<endl;


}
int main()
{
    PASS1();
    cout<<endl<<"-----------------------SYMBOL TABLE--------------------"<<endl;
    cout<<"SYMBOL"<<"\t"<<"ADDRESS"<<endl<<endl;
    for(int i=0;i<symcount;i++)
    {
        cout<<mysymtab[i].symbol<<" "<<mysymtab[i].addr<<endl;
    }
    cout<<"---------------------------------------------------------"<<endl<<endl;
    PASS2();
}
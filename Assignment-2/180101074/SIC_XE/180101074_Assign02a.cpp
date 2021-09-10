/*
Assignment-2 SIC/XE Two Pass Assembler
CS348

Environment:        LINUX g++

Compile and Run:    g++ 180101074_Assign02a.cpp
                    ./a.out

Name:       SHIVAM KUMAR AGRAWAL
Roll no.    180101074
*/




#include <bits/stdc++.h>
using namespace std;
#include "TABLES.cpp"
int symcount=0;
string len1;
string startaddr,locctr;
string label,opcode,operand,prgm_ctr,address;
string programname;
bool imm,ind;
ofstream op,mod;
ifstream ip;
int next_control=0;
int finish=0;
int loop=0;
string extdef,extref,modify;


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

//To extend size
string setLength(int dig,string a)
{
    string temp="";
    for(int i=0;i<dig-a.length();++i)
        temp+='0';
    return temp+a;
}

//function to process label (i.e SYMBOL)
void chk_label()
{
    // bool present=false;
    if(SYMTAB.count(label)==0)
    {
        SYMTAB[label].address=locctr;

    } 
    else
    {
        cout<<"ERROR"<<endl;
    }
    if(opcode[0]=='=')
    {
        LITTAB[opcode].address=locctr;
        LITTAB[opcode].label=label;
    }
    
    
}
string cal_exp(string op)
{
    string curr="0000";
    string temp="";
    char operation;
    int i=0;
    while(i<op.length())
    {
        if(op[i]=='+'||op[i]=='-')
        {
            operation=op[i];
            curr=itoh(htoi(curr)+htoi(SYMTAB[temp].address));
            temp="";

        }
        else
        {
            temp+=op[i];
        }
        i++;
    }
    if(operation=='+')
    {
        curr=itoh(htoi(curr)+htoi(SYMTAB[temp].address));
    }
    if(operation=='-')
    {
        curr=itoh(htoi(curr)-htoi(SYMTAB[temp].address));
    }
    return curr;


}

//function to process opcode
void chk_opcode()
{
    int found=0;
    if(OPCODE_TABLE[opcode].exist=='y')
    {
        locctr=itoh(htoi(locctr)+OPCODE_TABLE[opcode].format);
        found=1;
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
        else if(opcode=="EQU")
        {
            if(operand=="*")return;
            locctr=cal_exp(operand);
        }
        else if(opcode[0]=='+')
        {
            locctr=itoh(htoi(locctr)+4);
        }
        else if(opcode[0]=='=') //Literals
        {
            int nBytes;
            char byteType=opcode[1];
            if(byteType=='C')   //character byte
            {
                nBytes=opcode.size()-4;
            }
            else    //hexadecimal numBytes
            {
                if((opcode.size()-4)%2==0) 
                {
                    nBytes = (opcode.size()-4)/2;
                }
				else 
                {
                    nBytes = ((opcode.size()-4)/2)+1;
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

string gen_code()
{
    string part1,part2,part3;
    string operand_addr;
    int format;
    if(opcode=="BYTE"||opcode[0]=='=')
    {
        string temp_op=operand;
        if(opcode[0]=='=')
        {
            temp_op=opcode.substr(1);

        }
        int i;
        part1="";
        if(temp_op[0]=='X')
            for(i=2;i<temp_op.length()-1;++i) part1+=temp_op[i];
        else //operand[0]=='C'
            for(i=2;i<temp_op.length()-1;++i)
                part1+=itoh((int)temp_op[i]);
        return part1;
    }
    else if(opcode=="WORD")
    {
        part1=itoh(atoi(operand.c_str()));
        if(label=="MAXLEN")
        {
            string loc_ctr=itoh(htoi(address));
            mod<<"M^"<<setLength(6,loc_ctr)<<"^06"<<"^+"<<"BUFEND"<<endl;
            modify+=("M^"+setLength(6,loc_ctr)+"^06"+"^+"+"BUFEND"+"\n");

            mod<<"M^"<<setLength(6,loc_ctr)<<"^06"<<"^-"<<"BUFFER"<<endl;
            modify+=("M^"+setLength(6,loc_ctr)+"^06"+"^-"+"BUFFER"+"\n");

        }
        return setLength(6,part1);
    }
    else if(opcode=="RSUB")
    {
        part1="4F0000";
        return part1;
    }
    else if(opcode=="+RSUB")
    {
        part1="4F000000";
        return part1;
    }
    if(opcode[0]=='+')
    {
        format=4;
        opcode=opcode.substr(1);
    }
    else
    {
        format=OPCODE_TABLE[opcode].format;
        
    }
    if(format==1)
    {
        part1=OPCODE_TABLE[opcode].opcode;
        return part1;
    }
    else if(format==2)
    {
        part1=OPCODE_TABLE[opcode].opcode;
        if(operand.length()==3)
        {
            part2=itoh(reg_num(operand[0]));
            if(isdigit(operand[2]))  part2=part2+itoh(operand[2]-1);
            else
            {
                part2=part2+itoh(reg_num(operand[2]));
            }
        }
        else  //operand.length==1
        {
            if(isdigit(operand[0]))
            {
                part2=itoh(atoi(operand.c_str()))+"0";
            }
            else
            {
                part2=itoh(reg_num(operand[0]))+"0";
            }
        }
        return (part1+setLength(2,part2));
    }
    else if(format==3)
    {
        part1=OPCODE_TABLE[opcode].opcode;
        if(operand[0]=='#')
        {
            imm=true;
            part1=itoh(htoi(part1)+1);
            operand=operand.substr(1);
            if(isdigit(operand[0]))
            {
                part2="0";
                part3=itoh(atoi(operand.c_str()));
                return setLength(2,part1)+part2+setLength(3,part3);
            }
        }
        else if(operand[0]=='@')
        {
            ind=true;
            part1=itoh(htoi(part1)+2);
            operand=operand.substr(1);
        }
        else if(operand[0]=='=')
        {
            operand=LITTAB[operand].label;
            part1=itoh(htoi(part1)+3);
        }
        else
            part1=itoh(htoi(part1)+3);
        part2="0";
        bool x=false;
        if(operand[operand.length()-2]==',')
        {
            x=true;
            part2=itoh(htoi(part2)+8);
            operand=operand.substr(0,operand.length()-2);
        }
        if(SYMTAB.count(operand)==0)
        {
            operand_addr="0";
        }
        else
        {
            operand_addr=itoh(htoi(SYMTAB[operand].address)+htoi(SYMTAB[operand].block));

        }
        if(x) operand+=",X";
        int disp=htoi(operand_addr)-htoi(prgm_ctr);
        if(disp>=-2048 && disp<2048)
        {
            part2=itoh(htoi(part2)+2);
            if(disp<0) disp+=4096;
            part3=itoh(disp);
            return setLength(2,part1)+setLength(1,part2)+setLength(3,part3);
        }
        disp=htoi(operand_addr);
        if(disp>=-2048 && disp<2048)
        {
            part2=itoh(htoi(part2)+4);
            if(disp<0) disp+=4096;
            part3=itoh(disp);
            return setLength(2,part1)+setLength(1,part2)+setLength(3,part3);
        }
        else return "ERROR";
    }
    else if(format==4)
    {
        part1=OPCODE_TABLE[opcode].opcode;
        if(operand[0]=='#')
        {
            imm=true;
            part1=itoh(htoi(part1)+1);
            operand=operand.substr(1);
            if(isdigit(operand[0]))
            {
                part2="0";
                part3=itoh(atoi(operand.c_str()));
                opcode="+"+opcode;
                return part1+part2+setLength(5,part3);
            }
        }
        else if(operand[0]=='@')
        {
            ind=true;
            part1=itoh(htoi(part1)+2);
            operand=operand.substr(1);
        }
        else
            part1=itoh(htoi(part1)+3);
        bool x=false;
        part2="1";
        if(operand[operand.length()-2]==',')
        {
            x=true;
            part2=itoh(htoi(part2)+8);
            operand=operand.substr(0,operand.length()-2);
        }
        if(SYMTAB.count(operand)==0)
        {
            operand_addr="0";
        }
        else
        {
            operand_addr=itoh(htoi(SYMTAB[operand].address)+htoi(SYMTAB[operand].block));

        }
        
        part3=operand_addr;
        opcode="+"+opcode;
        string loc_ctr=itoh(htoi(address)+1);
        mod<<"M^"<<setLength(6,loc_ctr)<<"^05"<<"^+"<<operand<<endl;
        modify+=("M^"+setLength(6,loc_ctr)+"^05"+"^+"+operand+"\n");
        if(x) operand+=",X";
        return setLength(2,part1)+setLength(1,part2)+setLength(5,part3);
    }
    else
    {
        return ("ERROR");
    }
}

void printDR()
{
    if(extdef!="")
    {
        op<<endl;
        op<<"D^";
        cout<<endl;
        cout<<"D^";
        string temp="";
        int i=0;
        for(int i=0;i<extdef.length();i++)
        {
            if(extdef[i]==',')
            {
                op<<temp<<"^"<<setLength(6,SYMTAB[temp].address)<<"^";
                cout<<temp<<"^"<<setLength(6,SYMTAB[temp].address)<<"^";
                temp="";

            }
            else
            {
                temp+=extdef[i];
            }
        }
        op<<temp<<"^"<<setLength(6,SYMTAB[temp].address);
        cout<<temp<<"^"<<setLength(6,SYMTAB[temp].address);
    }
    if(extref!="")
    {
        op<<endl;
        op<<"R^";
        cout<<endl;
        cout<<"R^";
        string temp="";
        int i=0;
        for(int i=0;i<extref.length();i++)
        {
            if(extref[i]==',')
            {
                op<<temp<<"^";
                cout<<temp<<"^";
                temp="";

            }
            else
            {
                temp+=extref[i];
            }
        }
        op<<temp;
        cout<<temp;
    }
}




void PASS1()
{
    string rline;
    create();
    
    string inter_file="inter"+ to_string(loop)+".txt";
    ofstream op1(inter_file);

    // reads first line
    if(opcode=="")
    {
        getline(ip,rline);
        while(rline[0]=='.')
        {
            getline(ip,rline);
        }
        READ_LINE(rline);
    }

    if(opcode=="START")
    {
        cout<<endl<<"--------------------INTERMEDIATE------------------------"<<endl;
        cout<<"ADDRESS"<<"\t"<<"LABEL"<<"\t"<<"OPCODE"<<"\t"<<"OPERAND"<<endl<<endl;
        startaddr= (operand);
        locctr=startaddr;
        programname=label;
        op1<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
        cout<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
        getline(ip,rline);
        while(rline[0]=='.')
        {
            getline(ip,rline);
        }
        READ_LINE(rline);
    }
    else if(opcode=="CSECT")
    {
        cout<<endl<<"--------------------INTERMEDIATE------------------------"<<endl;
        cout<<"ADDRESS"<<"\t"<<"LABEL"<<"\t"<<"OPCODE"<<"\t"<<"OPERAND"<<endl<<endl;
        startaddr= "0000";
        locctr=startaddr;
        programname=label;
        op1<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
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
        if(opcode=="EXTDEF")
        {
            extdef=operand;
            getline(ip,rline);
            READ_LINE(rline);
            continue;
        }
        if(opcode=="EXTREF")
        {
            extref=operand;
            getline(ip,rline);
            READ_LINE(rline);
            continue;
        }
        string orig_locctr=locctr;      //stores current location
        if(opcode=="CSECT")
        {
            len1=itoh(htoi(locctr)-htoi(startaddr));
            locctr=orig_locctr="0";
        }
        if(label!="**")
        {
            chk_label();    //check label
        }
        chk_opcode();      //check opcode
        if(opcode=="CSECT")
        {
          
            locctr=orig_locctr="0";
            
        }
        string temp_locctr=orig_locctr;
        if(opcode=="EQU")
        {
            orig_locctr=locctr;
            locctr=temp_locctr;
        }
        op1<<orig_locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<"\t"<<locctr<<endl;
        cout<<orig_locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<"\t"<<locctr<<endl;
        if(opcode=="CSECT")
        {
            
            op1.close();
            return;
        }

        getline(ip,rline);
        while(rline[0]=='.')
        {
            getline(ip,rline);
        }
        READ_LINE(rline);


    }
    op1<<locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<"\t"<<"***"<<endl;
    cout<<locctr<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<"\t"<<"***"<<endl;
    len1=itoh(htoi(locctr)-htoi(startaddr));
    finish=1;
    
    op1.close();
    cout<<"---------------------------------------------------------"<<endl<<endl;


}
void PASS2()
{
    string record,part,value;
    int currtxtlen = 0, foundopcode, foundoperand, chk, operandaddr;

    string recaddr;
    

    
    string inter_file="inter"+ to_string(loop)+".txt";
    

    ifstream ip1(inter_file);
    
    //reads first line from intermediate file
    ip1>>label>>opcode>>operand;

    if(opcode=="START")
    {
        cout<<"-----------------------OUTPUT----------------------------"<<endl;
        op<< "H^"<<programname<<string(6-programname.size(),' ') <<"^"<<string(6-startaddr.size(),'0') <<startaddr<<"^"<<string(6-len1.size(),'0') <<len1;
        cout<< "H^"<<programname<<string(6-programname.size(),' ') <<"^"<<string(6-startaddr.size(),'0') <<startaddr<<"^"<<string(6-len1.size(),'0') <<len1;
        printDR();
        recaddr = (startaddr);
        record="";

        //reads second line
        ip1>>address>>label>>opcode>>operand>>prgm_ctr;
    }
    if(opcode=="CSECT")
    {
        cout<<"-----------------------OUTPUT----------------------------"<<endl;
        op<< "H^"<<programname<<string(6-programname.size(),' ') <<"^"<<string(6-startaddr.size(),'0') <<startaddr<<"^"<<string(6-len1.size(),'0') <<len1;
        cout<< "H^"<<programname<<string(6-programname.size(),' ') <<"^"<<string(6-startaddr.size(),'0') <<startaddr<<"^"<<string(6-len1.size(),'0') <<len1;
        printDR();
        recaddr = (startaddr);
        record="";

        //reads second line
        ip1>>address>>label>>opcode>>operand>>prgm_ctr;
    }

     // loop to read subsequent lines
    while(opcode!="END"&&opcode!="CSECT")
    {
        if(opcode=="CSECT")
        {
            next_control=1;
        }
        operandaddr = foundoperand = foundopcode = 0;
        value="";
        part="";



        
        part=gen_code();
            
        if ((currtxtlen + part.length()) <= 36)
        {
            if(part!=""&&part!="ERROR")
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
        ip1>>address>>label>>opcode>>operand>>prgm_ctr;
    }
    string c_len=itoh(currtxtlen);
    op<<endl;
    cout<<endl;
    op<<"T^"<<string(6-recaddr.size(),'0')<<recaddr<<"^"<<string(2-c_len.size(),'0') <<c_len<<record;
    cout<<"T^"<<string(6-recaddr.size(),'0')<<recaddr<<"^"<<string(2-c_len.size(),'0') <<c_len<<record;
    op<<endl;
    cout<<endl;
    op<<modify;
    cout<<modify;
    if(loop==0)
    {
        op<<"E^"<<string(6-startaddr.size(),'0') <<startaddr<<endl;
        cout<<"E^"<<string(6-startaddr.size(),'0') <<startaddr<<endl;
    }
    else
    {
        op<<"E"<<endl;
        cout<<"E"<<endl;

    }
    ip1.close();
    cout<<"---------------------------------------------------------"<<endl;


}
int main()
{
    opcode="";
    ip.open("input.txt");
    op.open("output.txt");
    while(!finish)
    {
        cout<<"CONTROL SECTION - "<<loop<<endl;
        SYMTAB.clear();
        extdef="";
        extref="";
        modify="";
        PASS1();
        cout<<endl<<"-----------------------SYMBOL TABLE--------------------"<<endl;
        cout<<"SYMBOL"<<"\t"<<"ADDRESS"<<endl<<endl;
        for(auto i :SYMTAB)
        {
            cout<<i.first<<"\t"<<i.second.address<<endl;
        }
        cout<<"---------------------------------------------------------"<<endl<<endl;
        string mod_file="mod"+ to_string(loop)+".txt";
        mod.open(mod_file);
        PASS2();
        mod.close();
        loop++;
        op<<endl<<endl;
        cout<<endl<<endl<<endl;
    }
    ip.close();
    op.close();
}
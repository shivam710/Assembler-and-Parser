
#include<bits/stdc++.h>
using namespace std;


//stores info of ach mnemonic instruction


struct info_reg
{
    int num;
    char exist;
    info_reg()
    {
        exist='n';
    }
};

struct op_info
{
    string opcode;
    int format;
    char exist;
    op_info()
    {
        exist='n';
    }
};

struct label_info
{
     string address;
    //  string value;
     string block="0000";
    //  char exist;
     label_info()
     {
         //exist='n';
         address=="0000";
     }
};

struct literal_info
{
     string address;
    //  string value;
     string label;
    //  char exist;
     literal_info()
     {
         //exist='n';
         address=="0000";
     }
};

struct block_info
{
    string address,length;
    int num;
    char exist;
    block_info()
    {
        exist='n';
    }
};

typedef string mnemonic,label1;

typedef map<mnemonic,op_info>   MapType1;
typedef map<mnemonic,info_reg>  MapType2;
typedef map<label1,label_info>   MapType3;
typedef map<label1,block_info>   MapType4;
typedef map<label1,literal_info>   MapType5;
//USING MAPS ALLOWS SEARCHING FOR ANY ENTRY IN LOG(N) TIME

//This maps the instructions(mnemonic codes) with thier Opcode and their format
MapType1 OPCODE_TABLE;

//This maps the REG mnemonic with their number
MapType2 REG;

//This map forms the symbol table : Label and  Address
MapType3 SYMTAB;

//This maps the program block name with its info
MapType4 BLOCK;

//This maps the program block name with its info
MapType5 LITTAB;



// integer to hexadecimal




int reg_num(char a)
{
    if(a=='A') return 0;
    if(a=='X') return 1;
    if(a=='L') return 2;
    if(a=='B') return 3;
    if(a=='S') return 4;
    if(a=='T') return 5;
    if(a=='F') return 6;
    else return -1;
}


/*---------OPCODE_TABLELE-----------*/
void create()
{

OPCODE_TABLE["ADD"].opcode="18";
OPCODE_TABLE["ADD"].format=3;
OPCODE_TABLE["ADD"].exist='y';

OPCODE_TABLE["ADDF"].opcode="58";
OPCODE_TABLE["ADDF"].format=3;
OPCODE_TABLE["ADDF"].exist='y';

OPCODE_TABLE["ADDR"].opcode="90";
OPCODE_TABLE["ADDR"].format=2;
OPCODE_TABLE["ADDR"].exist='y';

OPCODE_TABLE["AND"].opcode="40";
OPCODE_TABLE["AND"].format=3;
OPCODE_TABLE["AND"].exist='y';

OPCODE_TABLE["CLEAR"].opcode="B4";
OPCODE_TABLE["CLEAR"].format=2;
OPCODE_TABLE["CLEAR"].exist='y';

OPCODE_TABLE["COMP"].opcode="28";
OPCODE_TABLE["COMP"].format=3;
OPCODE_TABLE["COMP"].exist='y';

OPCODE_TABLE["COMPF"].opcode="88";
OPCODE_TABLE["COMPF"].format=3;
OPCODE_TABLE["COMPF"].exist='y';

OPCODE_TABLE["COMPR"].opcode="A0";
OPCODE_TABLE["COMPR"].format=2;
OPCODE_TABLE["COMPR"].exist='y';

OPCODE_TABLE["DIV"].opcode="24";
OPCODE_TABLE["DIV"].format=3;
OPCODE_TABLE["DIV"].exist='y';

OPCODE_TABLE["DIVF"].opcode="64";
OPCODE_TABLE["DIVF"].format=3;
OPCODE_TABLE["DIVF"].exist='y';

OPCODE_TABLE["DIVR"].opcode="9C";
OPCODE_TABLE["DIVR"].format=2;
OPCODE_TABLE["DIVR"].exist='y';

OPCODE_TABLE["FIX"].opcode="C4";
OPCODE_TABLE["FIX"].format=1;
OPCODE_TABLE["FIX"].exist='y';

OPCODE_TABLE["FLOAT"].opcode="C0";
OPCODE_TABLE["FLOAT"].format=1;
OPCODE_TABLE["FLOAT"].exist='y';

OPCODE_TABLE["HIO"].opcode="F4";
OPCODE_TABLE["HIO"].format=1;
OPCODE_TABLE["HIO"].exist='y';

OPCODE_TABLE["J"].opcode="3C";
OPCODE_TABLE["J"].format=3;
OPCODE_TABLE["J"].exist='y';

OPCODE_TABLE["JEQ"].opcode="30";
OPCODE_TABLE["JEQ"].format=3;
OPCODE_TABLE["JEQ"].exist='y';

OPCODE_TABLE["JGT"].opcode="34";
OPCODE_TABLE["JGT"].format=3;
OPCODE_TABLE["JGT"].exist='y';

OPCODE_TABLE["JLT"].opcode="38";
OPCODE_TABLE["JLT"].format=3;
OPCODE_TABLE["JLT"].exist='y';

OPCODE_TABLE["JSUB"].opcode="48";
OPCODE_TABLE["JSUB"].format=3;
OPCODE_TABLE["JSUB"].exist='y';

OPCODE_TABLE["LDA"].opcode="00";
OPCODE_TABLE["LDA"].format=3;
OPCODE_TABLE["LDA"].exist='y';

OPCODE_TABLE["LDB"].opcode="68";
OPCODE_TABLE["LDB"].format=3;
OPCODE_TABLE["LDB"].exist='y';

OPCODE_TABLE["LDCH"].opcode="50";
OPCODE_TABLE["LDCH"].format=3;
OPCODE_TABLE["LDCH"].exist='y';

OPCODE_TABLE["LDF"].opcode="70";
OPCODE_TABLE["LDF"].format=3;
OPCODE_TABLE["LDF"].exist='y';

OPCODE_TABLE["LDL"].opcode="08";
OPCODE_TABLE["LDL"].format=3;
OPCODE_TABLE["LDL"].exist='y';

OPCODE_TABLE["LDS"].opcode="6C";
OPCODE_TABLE["LDS"].format=3;
OPCODE_TABLE["LDS"].exist='y';

OPCODE_TABLE["LDT"].opcode="74";
OPCODE_TABLE["LDT"].format=3;
OPCODE_TABLE["LDT"].exist='y';

OPCODE_TABLE["LDX"].opcode="04";
OPCODE_TABLE["LDX"].format=3;
OPCODE_TABLE["LDX"].exist='y';

OPCODE_TABLE["LPS"].opcode="D0";
OPCODE_TABLE["LPS"].format=3;
OPCODE_TABLE["LPS"].exist='y';

OPCODE_TABLE["MUL"].opcode="20";
OPCODE_TABLE["MUL"].format=3;
OPCODE_TABLE["MUL"].exist='y';

OPCODE_TABLE["MULF"].opcode="60";
OPCODE_TABLE["MULF"].format=3;
OPCODE_TABLE["MULF"].exist='y';

OPCODE_TABLE["MULR"].opcode="98";
OPCODE_TABLE["MULR"].format=2;
OPCODE_TABLE["MULR"].exist='y';

OPCODE_TABLE["NORM"].opcode="C8";
OPCODE_TABLE["NORM"].format=1;
OPCODE_TABLE["NORM"].exist='y';

OPCODE_TABLE["OR"].opcode="44";
OPCODE_TABLE["OR"].format=3;
OPCODE_TABLE["OR"].exist='y';

OPCODE_TABLE["RD"].opcode="D8";
OPCODE_TABLE["RD"].format=3;
OPCODE_TABLE["RD"].exist='y';

OPCODE_TABLE["RMO"].opcode="AC";
OPCODE_TABLE["RMO"].format=2;
OPCODE_TABLE["RMO"].exist='y';

OPCODE_TABLE["RSUB"].opcode="4C";
OPCODE_TABLE["RSUB"].format=3;
OPCODE_TABLE["RSUB"].exist='y';

OPCODE_TABLE["SHIFTL"].opcode="A4";
OPCODE_TABLE["SHIFTL"].format=2;
OPCODE_TABLE["SHIFTL"].exist='y';

OPCODE_TABLE["SHIFTR"].opcode="A8";
OPCODE_TABLE["SHIFTR"].format=2;
OPCODE_TABLE["SHIFTR"].exist='y';

OPCODE_TABLE["SIO"].opcode="F0";
OPCODE_TABLE["SIO"].format=1;
OPCODE_TABLE["SIO"].exist='y';

OPCODE_TABLE["SSK"].opcode="EC";
OPCODE_TABLE["SSK"].format=3;
OPCODE_TABLE["SSK"].exist='y';

OPCODE_TABLE["STA"].opcode="0C";
OPCODE_TABLE["STA"].format=3;
OPCODE_TABLE["STA"].exist='y';

OPCODE_TABLE["STB"].opcode="78";
OPCODE_TABLE["STB"].format=3;
OPCODE_TABLE["STB"].exist='y';

OPCODE_TABLE["STCH"].opcode="54";
OPCODE_TABLE["STCH"].format=3;
OPCODE_TABLE["STCH"].exist='y';

OPCODE_TABLE["STF"].opcode="80";
OPCODE_TABLE["STF"].format=3;
OPCODE_TABLE["STF"].exist='y';

OPCODE_TABLE["STI"].opcode="D4";
OPCODE_TABLE["STI"].format=3;
OPCODE_TABLE["STI"].exist='y';

OPCODE_TABLE["SUBR"].opcode="94";
OPCODE_TABLE["SUBR"].format=2;
OPCODE_TABLE["SUBR"].exist='y';

OPCODE_TABLE["SVC"].opcode="B0";
OPCODE_TABLE["SVC"].format=2;
OPCODE_TABLE["SVC"].exist='y';

OPCODE_TABLE["TD"].opcode="E0";
OPCODE_TABLE["TD"].format=3;
OPCODE_TABLE["TD"].exist='y';

OPCODE_TABLE["TIO"].opcode="F8";
OPCODE_TABLE["TIO"].format=1;
OPCODE_TABLE["TIO"].exist='y';

OPCODE_TABLE["TIX"].opcode="2C";
OPCODE_TABLE["TIX"].format=3;
OPCODE_TABLE["TIX"].exist='y';

OPCODE_TABLE["TIXR"].opcode="B8";
OPCODE_TABLE["TIXR"].format=2;
OPCODE_TABLE["TIXR"].exist='y';

OPCODE_TABLE["WD"].opcode="DC";
OPCODE_TABLE["WD"].format=3;
OPCODE_TABLE["WD"].exist='y';

OPCODE_TABLE["STL"].opcode="14";
OPCODE_TABLE["STL"].format=3;
OPCODE_TABLE["STL"].exist='y';

OPCODE_TABLE["STS"].opcode="7C";
OPCODE_TABLE["STS"].format=3;
OPCODE_TABLE["STS"].exist='y';

OPCODE_TABLE["STSW"].opcode="E8";
OPCODE_TABLE["STSW"].format=3;
OPCODE_TABLE["STSW"].exist='y';

OPCODE_TABLE["STT"].opcode="84";
OPCODE_TABLE["STT"].format=3;
OPCODE_TABLE["STT"].exist='y';

OPCODE_TABLE["STX"].opcode="10";
OPCODE_TABLE["STX"].format=3;
OPCODE_TABLE["STX"].exist='y';

OPCODE_TABLE["SUB"].opcode="1C";
OPCODE_TABLE["SUB"].format=3;
OPCODE_TABLE["SUB"].exist='y';

OPCODE_TABLE["SUBF"].opcode="5C";
OPCODE_TABLE["SUBF"].format=3;
OPCODE_TABLE["SUBF"].exist='y';

/*-------------------------*/



/*---REGS'-INFO-------*/

REG["A"].num=0;
REG["A"].exist='y';

REG["X"].num=1;
REG["X"].exist='y';

REG["L"].num=2;
REG["L"].exist='y';

REG["B"].num=3;
REG["B"].exist='y';

REG["S"].num=4;
REG["S"].exist='y';

REG["T"].num=5;
REG["T"].exist='y';

REG["F"].num=6;
REG["F"].exist='y';

REG["PC"].num=8;
REG["PC"].exist='y';

REG["SW"].num=9;
REG["SW"].exist='y';

/*--------------------------*/

}


string find_block(int num)
{
     for (MapType4::const_iterator it = BLOCK.begin();;++it)
         if(it->second.num==num)
            return it->first;
}


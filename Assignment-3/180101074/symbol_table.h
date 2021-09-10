#include <iostream>
using namespace std;
  
const int MAX = 100;
  
struct Node
{
  
    string value;
    string scope;
    string type;
    int lineNo;
    Node* next;
    
    Node()
    {
        next = NULL;
    }
  
    Node(string value, string scope_type, string type, int lineNo)
    {
        this->scope = scope_type;
        this->value = value;
        this->lineNo = lineNo;
        this->type = type;
        next = NULL;
    }
};

Node* head[MAX];

//Function to find hash value for ids
int hash_value(string id)
{
    int Sum;
    Sum=0;
    int len=id.length();
    for (int i = 0; i < len; i++) 
    {
        Sum = Sum + id[i];
    }
  
    return (Sum % 100);
}

//Function to print symbol Table
void print_symtab()
{
    cout<<"------------------------SYMBOL TABLE---------------------------"<<endl;
    cout<<"---------------------------------------------------------------"<<endl;
	cout<< "|    VALUE    | HASH VALUE |       TYPE       |  LINE No.  |"<<endl;
	cout<<"---------------------------------------------------------------"<<endl;
    
    for(int i=0;i<MAX;i++)
    {
        Node* start = head[i];
    
        if (start == NULL)
        {
            continue;
        }
    
        while (start != NULL)
        {
            cout << "| " << setw(11) << start->value<< " ";
			cout << "| " << setw(10) << i << " ";
			cout << "| " << setw(16)  << start->type<< " " ;
            cout << "| " << setw(10)  << start->lineNo<< " |" << endl;
            start = start->next;
        }
    }
    cout<<"---------------------------------------------------------------"<<endl;


}
  
// Function to insert an identifier
bool insert(string id, string scope,string Type, int lineno)
{
    int hash_index = hash_value(id);
    Node* newNode;
    newNode = new Node(id, scope, Type, lineno);
  
    if (head[hash_index] == NULL) 
    {
        head[hash_index] = newNode;
  
        return true;
    }
  
    else 
    {
        Node* start = head[hash_index];
        while (start->next != NULL)
        {
            start = start->next;
        }
  
        start->next = newNode;
  
        return true;
    }
  
    return false;
}
  

  

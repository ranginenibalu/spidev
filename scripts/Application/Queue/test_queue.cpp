#include<iostream>
#include<stdlib.h>

using namespace std;

class temp {

	public:
	float temp;
	char unit;
};

class humid {
	public:
	int density;
	char x;
};

union gen {
	public:
	temp t;
	humid h;
};


struct node {
	char type;
	union gen obj;
	struct node* rptr;
	struct node* lptr;
};

struct node *first, *last;


void insert(gen entry, char t){

	node* temp;
	temp = new node;
	temp->lptr = NULL;
	temp->rptr = NULL;
	
	temp->obj = entry;
	temp->type = t;
	if(first == NULL){
		first = temp;
		last = temp;
		return; }
			
	last->lptr = temp;
	temp->rptr = last;
	last = temp;	
}

void remove(){
	if(first == NULL){
		return; }
	
	first = first->lptr;
	first->rptr = NULL;
}

void display() {
	struct node * f;
	if(first == NULL) {
		return ; }
	f = first;
	while(first!=NULL) {	
			
		switch(first->type){
		
		case 't' : cout<<first->obj.t.temp<<first->obj.t.unit<<"  \n";break;
		case 'h' : cout<<first->obj.h.density<<first->obj.h.x<<"  \n";break;
		
		}
		
		first = first->lptr; }
	first = f;
}

int main()
{	int n;
	int val;
	char c,type;
	
	temp obt;
	humid obh;
	union gen g;
	
	first = NULL;
	last = NULL;
	while(1)
	{
		cout<<"\nEnter a choice (1-3). Exit = 999\n";
		cin>>n;	
		switch(n)
		{	
			case 1: cout<<"\nEnter a 't' or 'h' "; cin>>c;
			
				if( c == 't' ){
					cout<<"\nEnter temp & unit";
					cin>>obt.temp>>obt.unit; 
					g.t = obt; 
					type = 't';}
					
				else if( c == 'h' ) {
					cout<<"\nEnter density & x";
					cin>>obh.density>>obh.x;
					g.h = obh; 
					type = 'h'; }
					
				insert(g,type);break;
			case 2: remove(); break;
			case 3: display(); break;
			default: exit(0);
		}
	}
}
		
		

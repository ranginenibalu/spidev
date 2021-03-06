#include<iostream>
#include<stdlib.h>

using namespace std;

class sensor {

	public:
	int sid;
	float val[5];
	char unit[10][5];
	int count;
	int tid;
};
	
struct node {
	sensor obj;
	struct node* rptr;
	struct node* lptr;
};

struct node *first, *last;


void insert(sensor entry){

	node* temp;
	temp = new node;
	temp->lptr = NULL;
	temp->rptr = NULL;
	
	temp->obj = entry;
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
	int i;
	struct node * f;
	if(first == NULL) {
		return ; }
	f = first;
	while(first!=NULL) {	
			
		cout<<"\n\nSensor Id:"<<first->obj.sid<<"Coordinator Id:"<<first->obj.tid<d<"\n";
		for(i=0;i<first->obj.count;i++){
		
			cout<<first->obj.val[i]<<" "<<first->obj.unit[i]<<"\n";
		
		}
		
		first = first->lptr; 
	}
	first = f;
}

int main()
{	int n,i;
	sensor ob;
	
	first = NULL;
	last = NULL;
	while(1)
	{
		cout<<"\nEnter a choice (1-3). Exit = 999\n";
		cin>>n;	
		switch(n)
		{	
			case 1: cout<<"\nEnter number of values to be inserted, Sid, Tid\n"; 
				cin>>ob.count>>ob.sid>>ob.tid;
				for(i=0;i<ob.count;i++){
					cout<<"Enter value & Unit";
					cin>>ob.val[i]>>ob.unit[i];
				} 
				insert(ob);break;
			case 2: remove(); break;
			case 3: display(); break;
			default: exit(0);
		}
	}
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
typedef struct Node{
	int data;
	Node* link;

	Node(){
		data = 0;
		link = nullptr;
	}
	Node(int data,Node *link){
		this->data = data;
		this->link = link;
	}
}Node;

typedef struct Header{
	int size;
	Node* link;
	Node* last;

	Header(){
		size = 0;
		link = nullptr;
		last = nullptr;
	}

	Header(int size,Node* link,Node* last){
		this->size = size;
		this->link = link;
		this->last = last;
	}
	//== Operator (we need it so we can use std::find())
	bool operator==(const Header &cpyobj){
		if((size == cpyobj.size) && (link == cpyobj.link) && (last == cpyobj.last))
			return true;
		return false;
	}
}Header;

class DisjointSet{
private:
	std::vector<Header> Sets;
	std::unordered_map<int,Node *> RepresentativeTable;

public:

	void MakeSet(int data);
	Node* Find(int key);
	void ChangeRepresentatives(Header* head,Node* rep);
	void Union(int key1,int key2);
	void Display();
};

void DisjointSet::MakeSet(int data){
	Node *temp = new Node(data,nullptr);
	Sets.push_back(Header(1,temp,temp));
	RepresentativeTable[data] = temp;
}

inline Node* DisjointSet::Find(int key){
	return RepresentativeTable[key];//return a pointer to the respective representative of the given element
}

void DisjointSet::ChangeRepresentatives(Header* head,Node* rep){
	Node* ptr=head->link;
	while( ptr != nullptr){
		RepresentativeTable[ptr->data] = rep;
		ptr=ptr->link;
	}
}

void DisjointSet::Union(int key1,int key2){
	Header *A,*B;
	std::vector<Header>::iterator it_A,it_B;//I kinda messed up and got into iterator hell
	auto it = Sets.begin();			//if you dont understand whats happening , basically just using it to remember the current iterator so that i can use a range based for loop
	for(Header H: Sets){			//im doing this so that i can pass the iterator of B to std::erase without finding it (which caused some weird double free errors)
		if(H.link->data == RepresentativeTable[key1]->data){
			A = &H;
			it_A=it;
		}
		else if(H.link->data == RepresentativeTable[key2]->data){
			B = &H;
			it_B=it;
		}
		it++;
	}
/*	if(A->size >= B->size){
		std::swap(A,B);
		std::swap(it_A,it_B);
	}*/
	this->ChangeRepresentatives(B,A->link);
	A->last->link = B->link;
	A->last = B->last;
std::cout<<"-------------------------------------------------------------------->size : "<<A->size<<B->size<<std::endl;
	A->size += B->size;
	Sets.erase(it_B);
}

void DisjointSet::Display(){
	for(Header H : Sets){
		std::cout<<"---------------"<<std::endl;
		std::cout<<"Set size : "<<H.size<<std::endl;
		std::cout<<"Set Representative : "<<H.link->data<<std::endl;
		Node* temp = H.link;
		while(temp != nullptr){
			std::cout<<temp->data<<" ";
			temp=temp->link;
		}
		std::cout<<"\n---------------"<<std::endl;
	}
}

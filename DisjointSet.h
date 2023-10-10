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
}Header;

class DisjointSet{
private:
	std::vector<Header *> Sets;
	std::unordered_map<int,int> RepresentativeTable;

public:

	void MakeSet(int data);
	int Find(int key);
	void ChangeRepresentatives(Header* head,int rep);
	void Union(int key1,int key2);
	void Display();
};

void DisjointSet::MakeSet(int data){
	Node *temp = new Node(data,nullptr);
	Sets.push_back(new Header(1,temp,temp));
	RepresentativeTable[data] = data;
}

inline int DisjointSet::Find(int key){
	return RepresentativeTable[key];
}

void DisjointSet::ChangeRepresentatives(Header* head,int rep){
	Node* ptr=head->link;
	while( ptr != nullptr){
		RepresentativeTable[ptr->data] = rep;
		ptr=ptr->link;
	}
}

void DisjointSet::Union(int key1,int key2){
	int rep_A=Find(key1),rep_B=Find(key2);
	Header* A=nullptr;
	Header* B=nullptr;
	auto it_A=Sets.begin(),it_B=Sets.begin();
	for(auto it = Sets.begin() ; it != Sets.end() ; it++){
		if((*it)->link->data == rep_A){
			A=*it;
			it_A=it;
		}
		else if((*it)->link->data == rep_B){
			B=*it;
			it_B=it;
		}
	}
	if(A->size > B->size){
		std::swap(A,B);
		std::swap(it_A,it_B);
		std::swap(rep_A,rep_B);
	}
	ChangeRepresentatives(B,rep_A);
	A->last->link = B->link;
	A->last = B->last;
	A->size += B->size;
	Sets.erase(it_B);
	delete B;
}

void DisjointSet::Display(){
	for(Header* H : Sets){
		std::cout<<"---------------"<<std::endl;
		std::cout<<"Set size : "<<H->size<<std::endl;
		std::cout<<"Set Representative : "<<H->link->data<<std::endl;
		Node* temp = H->link;
		while(temp != nullptr){
			std::cout<<temp->data<<" ";
			temp=temp->link;
		}
		std::cout<<"\n---------------"<<std::endl;
	}
}

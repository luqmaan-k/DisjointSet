#include <vector>
#include <unordered_map>
typedef struct Node{
	int data;
	Node* link;

	Node(){
		data=0;
		link = nullptr;
	}
}Node;

typedef struct Header{
	int size;
	Node* link;
	Node* last;

	Header(){
		size=0;
		link = nullptr;
		last = nullptr;
	}
}Header;

class DisjointSet{
private:
	std::vector<Header> Sets;
	std::unordered_map<int,Node> RepresentativeTable;

public:

	void MakeSet(int data);
	Node* Find(int key);
	void Union(int key1,int key2);
};

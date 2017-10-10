// Jiayao Li
// username: jiayaoli
// UIN: 42302027
// CSCE-221-507
// jiayaoli@tamu.edu

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

class Node{
public:
	int id; // student's UIN
	int grade; // student's grade value
};

class HashTable{
public:
	vector<list<Node>> vec; 
	// constructor
	HashTable(){vec=vector<list<Node>>(100);} 
	// member functions
	int hash(const int key);
	void insert(const int key, int value);
	int search(const int key);
	void getStat();
}; 

int HashTable::hash(const int key){
	// hash function
	return key%vec.size(); // UIN mod student number
}

void HashTable::insert(const int key, int value){
	// insert function
	int index = hash(key);
	Node n;
	n.id = key;
	n.grade = value;	
	vec[index].push_back(n);
}

int HashTable::search(const int key){
	// search function
	int index = hash(key);
	for(list<Node>::iterator it=vec[index].begin(); it !=vec[index].end(); it++){ 
		if(key == it->id){
			return it->grade;
		}
	}
	return -1; //return -1 if not found
}

void HashTable::getStat(){
	// get statistics of hash table
	cout << "Statistics of Hash Table: " << endl;
	
	// get minimum length of linked lists
	int counter = 0;
	// initialize min
	for(list<Node>::iterator it=vec[0].begin(); it !=vec[0].end(); it++){ 
		counter++;
	}
	int min = counter;
	// go through the rest of the vector to find min
	for(int i=1; i<vec.size(); i++){
		counter = 0;
		for(list<Node>::iterator it=vec[i].begin(); it !=vec[i].end(); it++){ 
			counter++;
		}
		if(counter<min){
			min = counter;
		}
	}
	cout << "Minimum length of the linked lists in the hash table: " << min << endl;
	
	// get maximum length of linked lists
	counter = 0;
	// initialize min
	for(list<Node>::iterator it=vec[0].begin(); it !=vec[0].end(); it++){ 
		counter++;
	}
	int max = counter;
	// go through the rest of the vector to find min
	for(int i=1; i<vec.size(); i++){
		counter = 0;
		for(list<Node>::iterator it=vec[i].begin(); it !=vec[i].end(); it++){ 
			counter++;
		}
		if(counter>max){
			max = counter;
		}
	}
	cout << "Maximum length of the linked lists in the hash table: " << max << endl;
	
	// get average length of linked lists
	int s_ls = 0; // size of total linked lists in vector
	int s_vec = vec.size(); // size of the vector
	double avr = 0;

	// go through the rest of the vector to find avr
	for(int i=0; i<vec.size(); i++){
		counter = 0;
		for(list<Node>::iterator it=vec[i].begin(); it !=vec[i].end(); it++){ 
			counter++;
		}
		s_ls = s_ls + counter;
	}
	
	avr = (double)s_ls/s_vec;
	cout << "Average length of the linked lists in the hash table: " << avr << endl;
}

int main() {
	// read input file with grade values
	ifstream file("input.csv");
	string line;
	HashTable ht; // initialize hash table
	
	while(getline(file, line)){
		// parse data by columns
		regex pattern{R"(([\s\S]+),([\s\S]+),([\s\S]+),([\s\S]+))"}; 
		smatch matches;
		regex_search(line, matches, pattern);
		if(!matches.empty()){
			// insert UIN and grade values into hash table
			ht.insert(stoi(matches[3]),stoi(matches[4]));
		}
	}
	
	// read roster file 
	ifstream file2("roster.csv");
	string line2;
	ofstream ofile2("output.csv");
	int g = 0; // initialize flag 
	
	while(getline(file2, line2)){
		// parse data by columns
		regex pattern{R"(([\s\S]+),([\s\S]+),([\s\S]+),)"};
		smatch matches;
		regex_search(line2, matches, pattern);
		if(!matches.empty()){
			g = ht.search(stoi(matches[3]));
		}
		if (g==-1){
			// no match copy original role
			for(int i=1; i<4; i++){
				ofile2 << matches[i] << ',';
			}
			ofile2 << endl;
		}
		else{
			for(int i=1; i<4; i++){
				ofile2 << matches[i] << ',';
			}
			ofile2 << g;
			ofile2 << endl;
		}
	}
	
	// output statistics of hash table
	ht.getStat();
	
	return 0;
}

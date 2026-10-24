#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <float.h>
#include <fstream>
#include <chrono>
#include <queue>
#include <unordered_map>

using namespace std;
using namespace chrono;

//find function of Union-Find
//find node that is parent of itself (root)
int find(vector<int>& parent, int i){
	if(parent.at(i) == i){
		return i;
	}
	else{
		return find(parent, parent.at(i));
	} 
}

//union function of Union-Find
//union by rank unites trees by height
bool unionByRank(int u, int v, vector<int>& parent, vector<int>& rank){
	int uRoot = find(parent, u);
	int vRoot = find(parent, v);
	int uRank = rank.at(uRoot); 
	int vRank = rank.at(vRoot); 

	if(uRoot != vRoot){ //makes sure not the same photo
		if(uRank > vRank){
			parent.at(vRoot) = uRoot;
			return true;
		}
		else if(uRank < vRank){
			parent.at(uRoot) = vRoot;
			return true;
		}
		else{
			parent.at(vRoot) = uRoot;
			rank.at(uRoot)++;
			return true;
		}
	}

	return false;
}

int main(){
/*
	//inputFile and outputFile handling
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	*/
	
	
	
	vector<tuple<string, string, int>> edges = {
		{"p1", "p2", 80}, {"p5", "p9", 73}, {"p9", "p13", 69}, {"p2", "p3", 10}, {"p5", "p7", 20}, {"p5", "p2", 74}, {"p9", "p18", 15}, {"p13", "p14", 21}, {"p9", "p1", 92}, {"p13", "p2", 59}, {"p20", "p4", 6}, {"p18", "p17", 17}, {"p11", "p3", 74}, {"p7", "p18", 83}, {"p7", "p12", 27}, {"p1", "p10", 16}, {"p5", "p15", 47}, {"p20", "p14", 94}, {"p14", "p18", 77}, {"p2", "p4", 30}, {"p11", "p14", 62}, {"p3", "p20", 85}, {"p11", "p7", 62}, {"p6", "p10", 87}, {"p12", "p15", 81}, {"p3", "p19", 39}, {"p9", "p8", 45}, {"p19", "p4", 65}, {"p8", "p16", 70}, {"p15", "p17", 64}, {"p1", "p11", 32}, {"p11", "p6", 43}, {"p12", "p6", 87}, {"p12", "p19", 70}, {"p7", "p16", 39}, {"p13", "p6", 22}, {"p4", "p16", 68}, {"p17", "p10", 56}, {"p19", "p15", 71}
	}; //input {photo1, photo2, similarity}
	
	/*
	string photo1;
	string photo2;
	int similarity;
	
	vector<tuple<string, string, int>> edges;
	while(inputFile >> photo1 >> photo1 >> similarity){
		classPairs.push_back({photo1, photo2, similarity});
	}
	*/
	
	
	//photo names
	vector<string> photos = {
		"p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "p10", "p11", "p12", "p13", "p14", "p15", "p16", "p17", "p18", "p19", "p20"
	};
	
	auto start = steady_clock::now(); //starts the time
	
	
	//sort edges by similarity from greatest to smallest
	sort(edges.begin(), edges.end(), [](const auto& a, const auto& b){
		if(get<2>(a) > get<2>(b)){
			return true;
		}
		return false;
	});
	
	//have each photo be the parent of itself
	vector<int> parent(20);
	for(int i = 0; i < 20; i++){
		parent.at(i) = i;
	}
	vector<int> rank(20, 0); //each of the photos start with a rank of 0
	
	
	
	
	
	//make maximum spanning trees
	int currEdge = 0;
	int categories = 3;
	int groups = 20;   //have each photo be its own group
	while(currEdge < edges.size()){
		
		
		if(groups != categories){
			int similarity = get<2>(edges.at(currEdge)); //gets similarity of two photos
			int index1 = find(photos.begin(), photos.end(), get<0>(edges[currEdge])) - photos.begin();
			int index2 = find(photos.begin(), photos.end(), get<1>(edges[currEdge])) - photos.begin();
			if(unionByRank(index1, index2, parent, rank)){
				groups--;
			}
		}
		currEdge++;
	}
	
	//categorize each photo by roots
	vector<vector<string>> photoGroups(20);
	vector<vector<string>> finalGroups;
	int currPhotoGroup = 0;
	while(currPhotoGroup < photoGroups.size()){
		int root = find(parent, currPhotoGroup);
		photoGroups.at(root).push_back(photos.at(currPhotoGroup));
		currPhotoGroup++;
	}
	currPhotoGroup = 0; //reset
	//puts into one of three categories
	while(currPhotoGroup < photoGroups.size()){
		if(photoGroups.at(currPhotoGroup).size() > 0){
			finalGroups.push_back(photoGroups.at(currPhotoGroup));
		}
		currPhotoGroup++; 
	}
	
	for(int i = 0; i < finalGroups.size(); i++){
		cout << "Group " << i+1 << " = " << finalGroups.at(i).size() << "; ";
		cout << "photos: ";
		for(int j = 0; j < finalGroups.at(i).size(); j++){
			cout << finalGroups.at(i).at(j);
			if(j < finalGroups.at(i).size()-1){ //ensures there's no dangling ", "
				cout << ", ";
			}
		}
		cout << endl;
	}
	cout << endl;
	
	cout << "Running time: " << duration<double, milli>(steady_clock::now() - start).count() << " ms" << endl;
	//inputFile.close();
	//outputFile.close();
	return 0;
}

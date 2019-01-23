/**
 * @file BinarySearchTreeBenchmark.cpp
 * @author Giulia Franco
 * @date 19 January 2019
 * @brief Source file to perform Benchmark on the BinarySearchTree class.
 */

#include "BinarySearchTree.h"
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <map>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

int N_max=20000; 

// First benchmark: Define 2 BinarySearchTree of int,float. The function will measure time 
// for find() methods for different N size of the trees and print the result on file. 
// Input: string with "int"/"float" type of pair<type,type> (for semplicity we consider
// just one type for couple value-key),empty BinarySearchTree.
// Accessing element using operator[], so we expect an overestimation.

template<class myType>
void Timing(myType B,ofstream& myfile){
        myfile<<"N   total time    time per operation   Log(N)"<<endl;
        for(int j=0;j<N_max;j+=50){
        auto begin = chrono::high_resolution_clock::now();
                for(int i=0;i<j;++i){
                        B.find(i);
                }
        auto end = chrono::high_resolution_clock::now();
        auto total=chrono::duration_cast<chrono::microseconds>(end-begin).count();
        myfile<<j<<"        "<<total<<"         "<<total/double(j)<<"       "<<log2(total/double(j)) <<endl;
        }

};

void Benchmark_different_type(string type){
	ofstream myfile;
        myfile.open ("test/benchmark_results/benchmark_different_"+type+"1.txt");
	if(type=="int"){
		BinarySearchTree<int,int> b;
		for(int i=0;i<N_max;++i){
			std::pair<int, int> pair{i,i};
			b.insert(pair);
		}
		cout<<"Accessing Elements for int type."<<endl;
		myfile<<"Accessing Elements for int type."<<endl;
		Timing(b,myfile);
		myfile.close();
	}
	if(type=="double"){
                BinarySearchTree<double,double> b;
                vector<double> val;
                for(int i=0;i<N_max;++i){
			double x=((double)rand() / RAND_MAX) * (100. - 1.) + 1.;
			pair<double, double> pair{x,x};
                        b.insert(pair);
			val.push_back(x);
                }
                cout<<"Accessing Elements for double type."<<endl;
                myfile<<"Accessing Elements for double type."<<endl;
		myfile<<"N   total time    time per operation   Log(N)"<<endl;
                for(int j=0;j<N_max;j+=50){
                        auto begin = chrono::high_resolution_clock::now();
                        for(int i=0;i<j;++i){
				b.find(val[i]);
                        }
                        auto end = chrono::high_resolution_clock::now();
                        auto total=chrono::duration_cast<chrono::microseconds>(end-begin).count();
                        myfile<<j<<"        "<<total<<"         "<<total/double(j)<<"       "<<log2(total/double(j)) <<endl;
                }
		myfile.close();
        }

};

//Comparing unbalanced BinarySearchTree, balanced BinarySearchTree,map and unordered_map.
void Benchmark_Map(){
	ofstream myfile;
        myfile.open ("test/benchmark_results/benchmark_unbalanced.txt");
        BinarySearchTree<int,int> b;
        for(int i=0;i<N_max;++i){
        	pair<int, int> pair{i,i};
                b.insert(pair);
                }
	Timing(b,myfile);
     	myfile.close();
	ofstream myfile1;
	myfile1.open ("test/benchmark_results/benchmark_balanced.txt");
	b.balance();
	Timing(b,myfile1);
	myfile1.close();
	map<int,int> Bench;
	ofstream myfile2;
        myfile2.open ("test/benchmark_results/benchmark_map.txt");
	for(int i=0;i<N_max;++i){
                pair<int, int> pair{i,i};
                Bench.insert(pair);
                }
	Timing(Bench,myfile2);
        myfile2.close();
	unordered_map<int,int> UnBench;
        ofstream myfile3;
        myfile3.open ("test/benchmark_results/benchmark_unordered_map.txt");
        for(int i=0;i<N_max;++i){
                pair<int, int> pair{i,i};
                UnBench.insert(pair);
                }
	Timing(UnBench,myfile3);
        myfile3.close();
};

int main(){
	
	Benchmark_different_type("int");
	Benchmark_different_type("double");
	Benchmark_Map();
	return 0;
};

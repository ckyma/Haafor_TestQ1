/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yuchen
 *
 * Created on February 25, 2017, 8:12 PM
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

#define N 100000
#define RANGE 65536

/*
 * 
 */

class Numbers{

    uint16_t storage[N];
    multiset<uint16_t> sorted;
    map<uint16_t, long> freq;
    multimap<long, uint16_t> sizes;

public:
    
    Numbers(){
        for(int i = 0; i < N; ++i){
            storage[i] = rand() % RANGE;
        }
        sorted = multiset<uint16_t>(storage, storage + N);
    }
    
    void writeToBinFile(string fileName){
        ofstream myfile(fileName, ios::out | ios::binary);
        
        for(int i = 0; i < N; ++i){
            myfile.write((char*)&storage[i], sizeof(uint16_t));
        }
        myfile.close();
    }
    
    void readFromBinFile(string fileName){
        ifstream myfile(fileName, ios::in | ios::binary);
        
        for(int i = 0; i < N; ++i){
            myfile.read((char*)&storage[i], sizeof(uint16_t));
        }
        myfile.close();
        
        sorted = multiset<uint16_t>(storage, storage + N);
    }
    
    void writeSortedToBinFile(string fileName){
        ofstream myfile(fileName, ios::out | ios::binary);
        
        for(auto it = sorted.begin(); it != sorted.end(); ++it){
            uint16_t val = *it;
            myfile.write((char*)&val, sizeof(uint16_t));
        }
        myfile.close();
    }
    
    void writeSortedSizeToBinFile(string fileName){
        ofstream myfile(fileName, ios::out | ios::binary);
        
        for(auto it = sizes.rbegin(); it != sizes.rend(); ++it){
            uint16_t val = it->second;
            long n = it->first;
            for(int i = 0; i < n; ++i){
                myfile.write((char*)&val, sizeof(uint16_t));
            }
        }
        myfile.close();
    }
    
    void getFrequency(){
        freq.clear();
        for(auto it = sorted.begin(); it != sorted.end(); ++it){
            auto val = *it;
            auto it_map = freq.find(val);
            if( it_map != freq.end() ){
                ++(it_map->second);
            } else {
                freq.insert(pair<uint16_t, long>(val, 1));
            }
        }
    }
    
    void getSizesSorted(){
        sizes.clear();
        for(auto it = freq.rbegin(); it != freq.rend(); ++it){
            sizes.insert(pair<long, uint16_t>(it->second, it->first));
        }
    }
    
    void printSample(int n = 10){
        
        if(n > N){
            n = N;
        }
        
        cout << storage[0];
        for(int i = 1; i < n; ++i){
            cout << "," << storage[i];
        }
        
        cout << endl;
        
        set<uint16_t>::iterator it = sorted.begin();
        cout << *it;
        for(int i = 1; i < n; ++i){
            ++it;
            cout << "," << *it;
        }
        
        cout << endl;
    }
    
    void printFreqSample(int n = 10){
        auto it = freq.begin();
        cout << it->first << "," << it->second;
        for(int i = 1; i < n; ++i){
            ++it;
            cout << ";" << it->first << "," << it->second;
        }
        
        cout << endl;
    }
    
    void printSizeFreqSample(int n = 10){
        auto it = sizes.rbegin();
        cout << it->second << "," << it->first;
        for(int i = 1; i < n; ++i){
            ++it;
            cout << ";" << it->second << "," << it->first;
        }
        
        cout << endl;
    }
};

int main(int argc, char** argv) {

    Numbers numbers;
    numbers.printSample();
    numbers.writeToBinFile("hexDec.bin");
    
    Numbers n2;
    n2.printSample();
    
    n2.readFromBinFile("hexDec.bin");
    n2.printSample();
    
    numbers.writeSortedToBinFile("hexDecSort.bin");
    
    n2.readFromBinFile("hexDecSort.bin");
    n2.printSample();
    
    numbers.getFrequency();
    numbers.printFreqSample();
    
    numbers.getSizesSorted();
    numbers.printSizeFreqSample();
    numbers.writeSortedSizeToBinFile("hexDecSizeSort.bin");
    
    n2.readFromBinFile("hexDecSizeSort.bin");
    n2.printSample();
    
    return 0;
}


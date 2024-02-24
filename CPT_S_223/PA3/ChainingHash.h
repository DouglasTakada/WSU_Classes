/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

 // Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K, V> {
private:
    // Needs a table and a size.
    int num_elem = 0;
    // Table should be a vector of lists for lazy deletion
    vector<list<pair<K,V>>> hash_table;
public:
    ChainingHash(int n = 11) {
        list<pair<K, V>> temp_list;
        pair<K, V> temp_pair;
        temp_pair.first = -1;
        temp_pair.second = 0;
        temp_list.push_back(temp_pair);
        hash_table.resize(n, temp_list);
    }

    ~ChainingHash() {
        this->clear();
    }

    int size() {
        return num_elem;
    }

    V operator[](const K& key) {
        return hash_table.at(key).front().second;
    }

    bool insert(const std::pair<K, V>& pair) {
        float load = load_factor();
        if (load > .75) {
            int newsize = findNextPrime((this->hash_table.size() * 2) + 1);
            std::list<std::pair<K, V>> temp_list;
            std::pair<K, V> temp_pair;
            temp_pair.first = -1;
            temp_pair.second = 0;
            temp_list.push_back(temp_pair);
            hash_table.resize(newsize,temp_list);
        }
        int index = hash(pair.first);

        if (hash_table.at(index).size() == 1) {//if only one element in list 
            if (hash_table.at(index).front().first == -1) {// and key is -1 (initializer value)
                hash_table.at(index).front().first = pair.first;
                hash_table.at(index).front().second = pair.second;
            }
        
            else if (hash_table.at(index).front().first != pair.first) {// if keys are not the same 
                // then insertinsert
                hash_table.at(index).push_back(pair);
            }
            else if (hash_table.at(index).front().first == pair.first) {//if key the same as another key it's a duplicate
                return false;
            }
        }
        else if(hash_table.at(index).size() > 1) {//list of elements
            //we have to traverse through to check if there is another elemet with the same key

         //std::list<std::pair<K, V>>::iterator it;

            //for (it i = hash_table.at(index).begin(); i != hash_table.at(index).end(); i++) {
                //if (i->first == pair.first) {
                    // if same key is found don't insert and return
                    //return false;
                //}
            //}

            //otherwise push onto list
            hash_table.at(index).push_back(pair);
        }
        num_elem++;
        return true;
    }

    void erase(const K& key) {
        /*int index = hash(key);
        std::list<std::pair<K, V>> temp_list = this->hash_table.at(index);

        for (auto it = temp_list.begin; it != temp_list.end(); it++)
        {
            if (it->first == key) {
                it = temp_list.erase(it);
                num_elem--;

            }
        }*/
        hash_table.at(hash(key)).front().first = -1;//Lazy deletion
        num_elem--;
    }

    void clear() {
        hash_table.clear();//deletes entire table
    }

    int bucket_count() {
        return hash_table.size();
    }

    float load_factor() {
        return num_elem / (float)hash_table.size();
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return num_elem % hash_table.size();
    }

};

#endif //__CHAINING_HASH_H

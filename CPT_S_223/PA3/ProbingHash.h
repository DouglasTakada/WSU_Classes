#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K, V> { // derived from Hash
private:
    // Needs a table and a size.
    int num_elem = 0;
    // Table should be a vector of std::pairs for lazy deletion
    vector<pair<K, pair<V, EntryState>>> hash_table;

public:
    ProbingHash(int n = 11) {
        /*for (int i = 0; i < n; i++) {
            hash_table.push_back(std::make_pair(0, std::make_pair(0, EMPTY)));
        }*/
        num_elem = 0;
        pair<K, pair<V, EntryState>> p;
        p.second.second = EntryState::EMPTY;
        hash_table.resize(n, p);
    }

    ~ProbingHash() {
        this->clear();
    }

    int size() {
        return this->num_elem;
    }

    V operator[](const K& key) {
        int hash_key = hash(key);
        int initial = hash_key;
        while (hash_table[hash_key].first != key && hash_key != initial) {
            if (hash_key == hash_table.size() - 1) {
                hash_key = 0;
            }
            hash_key = hash(hash_key + 1);
        }
        if (hash_table[hash_key].first == key) {
            return hash_table[hash_key].second.first;
        }
        else {
            cout << "Key not in hash\n";
            return -1;
        }
    }

    bool insert(const std::pair<K, V>& pair) {
        float temp = load_factor();
        if (temp > .75) {
            int newsize = findNextPrime((this->hash_table.size() * 2) + 1);
            hash_table.resize(newsize);

            for (int i = 0, temp_key = 0; i < num_elem; i++) {// rehashes and reinserts the values
                temp_key = hash(i);
                    if (hash_table[temp_key].first == hash_table[i].first &&
                        hash_table[temp_key].second.first == hash_table[i].second.first) {//if either the key and value is not the same then change
                        hash_table[temp_key].second.first = hash_table[i].second.first;
                        break;
                    }
            }

            //int temp_key = 0;
            //for (int i = 0; i < temp_size; i++) {
            //    temp_key = hash(i);
            //    while (hash_table[temp_key].second.second == VALID) {
            //        if (hash_table[temp_key].first == hash_table[i].first) {
            //            hash_table[temp_key].second.first = hash_table[i].second.first;
            //            break;
            //        }
            //        temp_key = hash(temp_key + 1);
            //    }
            //    //if(hash_table[hash_key].first != pair.first) {
            //    //hash_table[hash_key].first = pair.first;
            //    //hash_table[hash_key].second.first = pair.second;
            //    //hash_table[hash_key].second.second = VALID;
            //}
            //int temp_size = hash_table.size();
            //int temp_key = 0;
            //for (int i = 0; i < temp_size; i++) {
            //    temp_key = hash(i);
            //    while (hash_table[temp_key].second.second == VALID) {
            //        if (hash_table[temp_key].first == pair.first) {
            //            hash_table[temp_key].second.first = pair.second;
            //            break;
            //        }
            //        temp_key = hash(temp_key + 1);
            //    }
            //    //if (hash_table[hash_key].first != pair.first) {
            //    hash_table[hash_key].first = pair.first;
            //    hash_table[hash_key].second.first = pair.second;
            //    hash_table[hash_key].second.second = VALID;
            //}
            //nums_elem = new_size;
        }

        int hash_key = hash(pair.first);
        while (hash_table[hash_key].second.second == VALID) {
            if (hash_table[hash_key].first == pair.first) {
                //hash_table[hash_key].second.first = pair.second;
                break;
            }
            hash_key = (hash_key) % hash_table.capacity();
        }
        //if (hash_table[hash_key].first != pair.first) {
        hash_table[hash_key].first = pair.first;
        hash_table[hash_key].second.first = pair.second;
        hash_table[hash_key].second.second = VALID;
        num_elem++;
        return true;
        //}
        //return false;
        /*int index = pair.first % this->size();
        int temp = index;
        while (this->hash_table[index].second.second == VALID) {
            if (hash_table.size - 1 = index) {
                index = -1;
            }
            index++;
        }
            hash_table.push_back(std::make_pair(pair.first, std::make_pair(pair.second, EMPTY)));*/

    }
    

    void erase(const K& key) {
        int hash_key = hash(key);
        int initial = hash_key;
        while (hash_table[hash_key].first != key && hash_key != initial) {
            if (hash_key == hash_table.size() - 1) {
                hash_key = 0;
            }
            hash_key = hash(hash_key + 1);
        }
        if (hash_table[hash_key].first == key) {
            hash_table[hash_key].second.second = EntryState::DELETED;//Don't need to actually clear the value//Lazy deletion
            this->num_elem--;
        }
    }

    void clear() {
        hash_table.clear();
        num_elem = 0;
        
    }

    int bucket_count() {
        return hash_table.size();
    }

    float load_factor() {
        return this->num_elem / (float)hash_table.size();
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
        return key % hash_table.size();
        //while (hash_table[hash].second.second == VALID) {//while a space is occupied
        //    if (hash == hash_table.size()-1) {//if you reach the end of the vector 
        //        hash = -1; //set value to -1 so after the has++ it will turn to 0 index
        //    }
        //    hash++;//increment to the next place
        //}
    }

};

#endif //__PROBING_HASH_H

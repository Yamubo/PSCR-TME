#include "HashMap.hpp"

using namespace pr ;

   bool put(const K&key , const V& value ){
         size_t h = std :: hash<K>()(key);
        size_t target = h%this.buckets.size();
        for(auto & ent : this.buckets[target]){
            if(ent.key == key){
                ent.value = value;
                return true;
            }
        }
        buckets[target].push.front(Entry(key,value));
        //buckets[target].emplace.front(Entry(key,value));
        return false;
    }
    V get(const K&key , const V& value ){
          size_t h = std :: hash<K>()(key);
        size_t target = h%buckets.size();
        for(auto & ent : buckets[target]){
            return &entry.value;
        }
       return nullptr;
    }
    void grow(){
        HashMap tmp = HashMap(2*&buckets.size());
        for(;auto&l = buckets;){
            for(;auto&e = l;){
                tmp.put(e.key , e.value);
            }
        }
        this.buckets = tmp.buckets;
    };


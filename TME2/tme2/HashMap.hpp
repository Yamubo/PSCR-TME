
#include <vector>
#include <cstddef>
#include <functional>


namespace pr{
template<typename K , typename V>

class HashMap{
    
    struct Entry {
    public: 
        const K key;
        V value;
        const Entry(K key , V value ){}
        ~Entry(){} 

    };

    typedef std::vector<forward_list <Entry>> buckets_t;
    buckets_t buckets ; 
    public: 
        HashMap(size_t alloc ){
            buckets = new std::vector<>(alloc);
        }

    bool get(const K&key , const V& value );
    V get(const K&key , const V& value );
    void grow();

    /*

    typename <forward_list <Entry>> :: iterator it ; 
    //buckets_t ::  iterator 

    */
};
}

Class iterator{
    size_t index ;
    forward_list<Entry>::iterator lit;
    buckets_t & buck;

    public:
    iterator (size_t index, forward_list<>::iterator lit , buckets_t & buck )
        ; index(index), lit(lit); buck(buck){}

    iterator & operator++(){
        ++lit;
        if(lit == buck[index].end()){
            ++index;
            for(;index<buck.size()&&buck[index].empty(); ++index){
                //nop
            }
            if(index < buck.size()) lit = buck[index].begin();
        }
        return * this;
    }

    bool operator!=(const iterator & o){
        return index != o.index ||
            lit != o.lit ||
            & buck != & o.buck;
    }

    Entry & operator*(){
        return * lit;
    }

    iterator begin(){
        for(int index = 0 ; index < buck.size() ; index ++){
            if(!buckets[index].empty()){
                return iterator(index,buckets[index].begin(), buckets);
            
            }
        }
        return end();
    }

    iterator end(){
        return iterator(buckets.size(),buckets[0].end(),buckets);

    }
    }
    /*
    void inserer ()
    void trouver ()
    empty()
    calculHash () -> fonction std::hash() 
    modif taille 

    */
    ;
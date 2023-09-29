template<typename K , typename V>

class HashMap{
    
    class bucket {
    public: 
        const K cle;
        V valeur;
        bucket * next;
        bucket(K cle , V valeur ){}
        ~bucket(){}

    };

    std::vector<bucket> buck ; 
    public: 
        HashMap(size_t taille )
    /*
    void inserer ()
    void trouver ()
    empty()
    calculHash () -> fonction std::hash() 
    modif taille 

    */
};
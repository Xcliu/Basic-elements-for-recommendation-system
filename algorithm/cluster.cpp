#include <iostream>
#include "cluster.h"

Cluster::ifv_t *malloc_ifv(){
    Cluster::ifv_t *result;
    try{
        result=new Cluster::ifv_t;
    }catch(const std::bad_alloc &ba){
        std::cout<<ba.what()<<std::endl;
        result=nullptr;
    }
    return result;
}

Cluster::itc_t *malloc_itc(){
    Cluster::itc_t *result;
    try{
        result=new Cluster::itc_t;
    }catch(const std::bad_alloc &ba){
        std::cout<<ba.what()<<std::endl;
        result=nullptr;
    }
    return result;
}


Cluster::Cluster(size_t c_num):cluster_num(c_num){
    item_feature_vector=malloc_ifv();
    item_to_category=malloc_itc();
    ref_count=new int(1);
}

Cluster::~Cluster(){
    if(*ref_count>1){
        --(*ref_count);
    }else{
        delete item_feature_vector;
        delete item_to_category;
        delete ref_count;
    }
}

Cluster::Cluster(const Cluster & cl):cluster_num(cl.cluster_num){
    ref_count=cl.ref_count;
    ++(*ref_count);
    feature_vector_size=cl.feature_vector_size;
    item_feature_vector=cl.item_feature_vector;
    item_to_category=cl.item_to_category;
}

Cluster::Cluster(Cluster && cl):cluster_num(cl.cluster_num){
    ref_count=cl.ref_count;
    cl.ref_count=nullptr;

    feature_vector_size=cl.feature_vector_size;
    
    item_feature_vector=cl.item_feature_vector;
    cl.item_feature_vector=nullptr;

    item_to_category=cl.item_to_category;
    cl.item_to_category=nullptr;
}

Cluster & Cluster::operator=(const Cluster & cl){
    if(this==&cl){
        return *this;
    }else{
        Cluster(cl);
        return *this;
    }
}

bool Cluster::add_item(std::string str,std::vector<double> v){
    if(item_feature_vector->empty()){
        feature_vector_size=v.size();
    }else if(v.size()!=feature_vector_size){
        return false;
    }
    auto temp=item_feature_vector->insert(ifv_t::value_type(str,v));
    return temp.second;
}


bool Cluster::delete_item(const std::string &name){
    if(item_feature_vector->count(name)){
        item_feature_vector->erase(name);
        return true;
    }
    return false;
}

bool Cluster::random_classify(){
    if(item_feature_vector->size()<cluster_num){
        return false;
    }else{
        int index=0;
        for(auto &item:*item_feature_vector){           
            item_to_category->insert(itc_t::value_type(item.first,index%cluster_num));
            ++index;
        }
    }
}






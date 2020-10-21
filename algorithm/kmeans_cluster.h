#pragma once
#include <map>
#include <string>
#include "cluster.h"

class Kmeans_cluster{
    private: 
        typedef std::vector<std::vector<double>> ifv_t;
        ifv_t *cluster_center;
        const size_t max_iterator_count;
        Cluster &c_set;
    public:
        explicit Kmeans_cluster(size_t num=10000);
        Kmeans_cluster(const Kmeans_cluster &kc)=delete;
        Kmeans_cluster(Kmeans_cluster &&kc)=delete;
        Kmeans_cluster& operator=(const Kmeans_cluster &kc)=delete;
        Kmeans_cluster operator=(Kmeans_cluster &&kc)=delete;

        void update_center();//update geometry center once
        bool classify(); //update geometry center to convergency
};
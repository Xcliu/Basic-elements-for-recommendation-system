#pragma once
#include <vector>
#include <map>
#include <string>

class Cluster{
    public:
        typedef std::map<std::string,std::vector<double>> ifv_t;
        typedef std::map<std::string,int> itc_t;
        explicit Cluster(size_t c_num=1);
        Cluster(const Cluster & cl);
        Cluster(Cluster && cl);
        Cluster& operator=(const Cluster & cl);
        Cluster& operator=(Cluster && cl);
        double reuclid_distance(const ifv_t & v1, const ifv_t &v2)const;
        bool add_item(std::string str,std::vector<double> v);
        bool add_item(std::string &&str,std::vector<double> &&v);
        bool delete_item(const std::string &name);
        bool random_classify();
        virtual ~Cluster();
    private:
        const size_t cluster_num;
        size_t feature_vector_size{0};
        int *ref_count;
        ifv_t *item_feature_vector{nullptr};
        itc_t *item_to_category{nullptr};

        ifv_t *malloc_ifv();
        itc_t *malloc_itc();
        
};
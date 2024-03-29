#include <iostream>
#include <vector>
#include <valarray>
#include <utility>
#include <cmath>

class k_means
{
private:
    int m_k;
    int m_features;
    std::valarray<std::vector<std::pair<double, double>>> m_data;
    std::valarray<std::pair<double, double>> m_means;

    bool computeMeans()
    {
        bool result = true;

        for (size_t i = 0; i < m_k; i++)
        {
            std::pair<double, double> mean(0, 0);
            int num_features_of_k = m_data[i].size();
            for (auto const &element : m_data[i])
            {
                mean.first += element.first;
                mean.second += element.second;
            }
            mean.first /= num_features_of_k;
            mean.second /= num_features_of_k;
            result = (m_means[i] == mean && result == true) ? true : false;
            m_means[i] = mean;
            std::cout << "/ Cluster Centroid: " << i << " x: " << mean.first << " y: " << mean.second;
        }
        std::cout << std::endl;
        return result;
    }

    void assignLabels()
    {
        std::valarray<std::vector<std::pair<double, double>>> new_data(m_k);
        for (auto const &clust : m_data)
        {
            for (auto const &feature : clust)
            {
                int closest_mean = computeClosestCentroid(feature);
                new_data[closest_mean].push_back(feature);
            }
        }
        m_data = new_data;
    }

    int computeClosestCentroid(const std::pair<double, double> &point)
    {
        std::valarray<double> distance(m_k);
        for (size_t i = 0; i < m_k; i++)
        {
            double del_x = point.first - m_means[i].first;
            double del_y = point.second - m_means[i].second;
            double dist = std::sqrt((del_x * del_x) + (del_y * del_y));
            distance[i] = dist;
        }
        auto closest_mean = std::distance(std::begin(distance), std::min_element(std::begin(distance), std::end(distance)));
        return closest_mean;
    }

public:
    k_means(int k, std::vector<std::pair<double, double>> &data) : m_k(k), m_means(k), m_data(k)
    {
        m_data[0] = data;
    }
    ~k_means() {}

    void clusterData(std::valarray<std::pair<double, double>> &init_means, int num_iters)
    {
        m_means = init_means;

        assignLabels();
        int i = 0;
        while (i < num_iters && !computeMeans())
        {
            std::cout << "Running iteration: " << i << std::endl;
            assignLabels();
            i++;
        }
    }

    void printCluster()
    {
        for (size_t i = 0; i < m_k; i++)
        {
            for (auto const &element : m_data[i])
            {
                std::cout << "[" << element.first << ", " << element.second << "]";
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    std::vector<std::pair<double, double>> data = {{1.1, 1}, {1.4, 2}, {3.8, 7}, {8, 6}, {5.0, 8}, {4.3, 6}, {8.0, 5}, {6, 8.5}, {3, 2.8}, {9, 6.0}, {9.1, 4}};

    { // 3 clusters
        k_means km(3, data);
        std::valarray<std::pair<double, double>> init_means = {{1, 1}, {3, 4}, {8, 8}};

        km.clusterData(init_means, 12);
        km.printCluster();
    }

    std::cout << std::endl;

    { // 2 clusters
        k_means km(2, data);
        std::valarray<std::pair<double, double>> init_means = {{1, 1}, {3, 4}};

        km.clusterData(init_means, 12);
        km.printCluster();
    }

    return 0;
}
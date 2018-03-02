#ifndef FATTREE_HPP_INCLUDED
#define FATTREE_HPP_INCLUDED

#include <vector>

#include "Pod.hpp"

/**
 * @brief The FatTree class generates a fat tree topology.
 */
class FatTree
{
    public:
        /**
         * @brief Constructor.
         * @param numberOfPods the number of pods of the fat tree
         */
        FatTree(unsigned int numberOfPods);

        /**
         * @brief Destructor
         */
        virtual ~FatTree();

        /**
         * @brief Serializes the fat tree topology to the given file.
         * @param filepath the file to serialize into
         */
         void serialize(const std::string& filepath);

    private:
        // The number of pods.
        unsigned int m_numberOfPods;

        // The list of the core nodes.
        std::vector<Node*> m_cores;

        // The list of the pods.
        std::vector<Pod*> m_pods;
};

#endif // FATTREE_HPP_INCLUDED

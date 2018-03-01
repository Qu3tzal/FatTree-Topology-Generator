#ifndef POD_HPP_INCLUDED
#define POD_HPP_INCLUDED

#include <vector>

#include "Node.hpp"

/**
 * @brief The Pod class represents a pod (a list of computers).
 */
class Pod
{
    public:
        /**
         * @brief Constructor.
         * @param id the ID of the pod
         */
        Pod(unsigned int id, unsigned int numberOfPods);

        /**
         * @brief Destructor.
         */
        virtual ~Pod();

        /**
         * @brief Connects the aggregation nodes of the pod to the given core nodes.
         * @param cores list of the core nodes to connect to
         */
         void connectToCores(std::vector<Node>& cores);

         /**
          * @brief Returns the aggregation nodes.
          */
          std::vector<Node> getAggregation() const {return m_aggregations;}

          /**
          * @brief Returns the edge nodes.
          */
          std::vector<Node> getEdge() const {return m_edges;}

          /**
          * @brief Returns the workstation nodes.
          */
          std::vector<Node> getWorkstation() const {return m_workstations;}

    private:
        unsigned int m_id;
        std::vector<Node> m_edges, m_aggregations, m_workstations;
};

#endif // POD_HPP_INCLUDED

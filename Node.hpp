#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <vector>
#include <string>

// Forward declaration of the class.
class Node;

/**
 * @brief NodeID holds the ID for a Node.
 */
struct NodeID
{
    unsigned int x, y, z;
};

/**
 * @brief The different types of hardware Nodes can have.
 */
enum class NodeHardware
{
    Hca,
    Switch
};

/**
 * @brief The different types of Nodes.
 */
enum class NodeType
{
    Core,
    Aggregation,
    Edge,
    Workstation
};

/**
 * @brief A node link is a connection between two nodes.
 */
struct NodeLink
{
    Node* node;
    unsigned int portNumber;
};

/**
 * @brief The Node class represents a simple node. A node has ports and can connect to other nodes' ports.
 */
class Node
{
    public:
        /**
         * @brief Constructor.
         * @param id the id of the node
         * @param hardwareType the hardware type of the node
         * @param logicalType the logical type of the node
         * @param numberOfPorts the number of ports the node has
         */
        Node(NodeID id, NodeHardware hardwareType, NodeType logicalType, unsigned int numberOfPorts);

        /**
         * @brief Destructor.
         */
        virtual ~Node();

        /**
         * @brief Connect to the given NodeID.
         * @param node the node to connect to
         * @param fromPort the port of our node
         * @param toPort the port of the other node to connect to
         */
        void connectTo(Node* node, unsigned int fromPort, unsigned int toPort);

        /**
         * @brief Returns the generated name of the node.
         */
        std::string getName() const {return m_name;}

        /**
         * @brief Returns the number of ports of the node.
         */
        unsigned int getNumberOfPorts() const {return m_links.size();}

        /**
         * @brief Returns the hardware type.
         */
        NodeHardware getHardware() const {return m_hardwareType;}

        /**
         * @brief Returns Links list.
         */
        std::vector<NodeLink>& getLinks() {return m_links;}

    private:
        NodeID m_id;
        NodeHardware m_hardwareType;
        NodeType m_logicalType;

        std::vector<NodeLink> m_links;
        std::string m_name;
};

#endif // NODE_HPP_INCLUDED

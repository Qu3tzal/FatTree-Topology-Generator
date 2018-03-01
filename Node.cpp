#include "Node.hpp"

#include <sstream>

Node::Node(NodeID id, NodeHardware hardwareType, NodeType logicalType, unsigned int numberOfPorts)
    : m_id(id)
    , m_hardwareType(hardwareType)
    , m_logicalType(logicalType)
{
    // Instanciates empty connections.
    for(unsigned int i(0) ; i < numberOfPorts ; ++i)
        m_links.push_back({nullptr, 0});

    // Generate the name.
    std::stringstream ss("");

    if(hardwareType == NodeHardware::Hca)
    {
        ss << "Workstation(" << id.x << ")";
    }
    else
    {
        if(logicalType == NodeType::Core)
            ss << "Core";
        else if(logicalType == NodeType::Aggregation)
            ss << "Aggr";
        else if(logicalType == NodeType::Edge)
            ss << "Edge";

        ss << "(" << id.x << " " << id.y << " " << id.z << ")";
    }

    m_name = ss.str();
}

Node::~Node()
{

}

void Node::connectTo(Node* node, unsigned int fromPort, unsigned int toPort)
{

}

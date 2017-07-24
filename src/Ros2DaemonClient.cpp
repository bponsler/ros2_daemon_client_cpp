#include <ros2_daemon_client_cpp/Ros2DaemonClient.hpp>

// standard headers
#include <iostream>

// xml rpc headers
#include <xmlrpcpp/XmlRpcValue.h>
#include <xmlrpcpp/XmlRpcException.h>


namespace ros2_daemon_client_cpp
{


Ros2DaemonClient::Ros2DaemonClient(
  const std::string& host,
  const int& port,
  const std::string& rmwImplId)
  :
  m_client(host.c_str(), port, std::string("/" + rmwImplId + "/").c_str())
{
}

Ros2DaemonClient::~Ros2DaemonClient()
{
  m_client.close();
}
  
StringVector
Ros2DaemonClient::getNodes()
{
  StringVector nodes;

  try {
    // Call the XML RPC method to get all the running nodes
    XmlRpc::XmlRpcValue params;
    XmlRpc::XmlRpcValue result;
    m_client.execute("get_node_names", params, result);

    for (int i = 0; i < result.size(); ++i) {
      XmlRpc::XmlRpcValue& item = result[i];

      // Each item must be a string
      if (item.getType() == XmlRpc::XmlRpcValue::TypeString) {
	std::string node = item;
      
	// Skip the ROS 2 daemon node
	if (node.compare("_ros2cli_node_daemon_0") == 0) continue;
	nodes.push_back(node);
      }
    }
  } catch (XmlRpc::XmlRpcException& exc) {
    std::cerr << "Failed to get nodes: " << exc.getMessage() << std::endl;
  }

  return nodes;
}
  
TopicDataVector
Ros2DaemonClient::getTopics()
{
  TopicDataVector topics;

  try {
    // Call the XML RPC method to get all the running nodes
    XmlRpc::XmlRpcValue params;
    XmlRpc::XmlRpcValue result;
    m_client.execute("get_topic_names_and_types", params, result);

    for (int i = 0; i < result.size(); ++i) {
      XmlRpc::XmlRpcValue& item = result[i];

      // Each item must be an array with two items (topic, type)
      if (item.getType() == XmlRpc::XmlRpcValue::TypeArray && item.size() == 2) {
	XmlRpc::XmlRpcValue& topicData = item[1];
     
	if (topicData.getType() == XmlRpc::XmlRpcValue::TypeArray && topicData.size() == 1) {
	  // Add the topic to the list
	  TopicData data;
	  data.topic = std::string(item[0]);
	  data.type = std::string(topicData[0]);
	  topics.push_back(data);
	}
      }
    }
  } catch (XmlRpc::XmlRpcException& exc) {
    std::cerr << "Failed to get topics: " << exc.getMessage() << std::endl;
  }

  return topics;
}

TopicDataVector
Ros2DaemonClient::getServices()
{
  TopicDataVector topics;

  try {
    // Call the XML RPC method to get all the running nodes
    XmlRpc::XmlRpcValue params;
    XmlRpc::XmlRpcValue result;
    m_client.execute("get_service_names_and_types", params, result);

    for (int i = 0; i < result.size(); ++i) {
      XmlRpc::XmlRpcValue& item = result[i];

      // Each item must be an array with two items (topic, type)
      if (item.getType() == XmlRpc::XmlRpcValue::TypeArray && item.size() == 2) {
	XmlRpc::XmlRpcValue& topicData = item[1];
     
	if (topicData.getType() == XmlRpc::XmlRpcValue::TypeArray && topicData.size() == 1) {
	  // Add the topic to the list
	  TopicData data;
	  data.topic = std::string(item[0]);
	  data.type = std::string(topicData[0]);
	  topics.push_back(data);
	}
      }
    }
  } catch (XmlRpc::XmlRpcException& exc) {
    std::cerr << "Failed to get services: " << exc.getMessage() << std::endl;
  }

  return topics;
}

  
}  // namespace ros2_daemon_client_cpp

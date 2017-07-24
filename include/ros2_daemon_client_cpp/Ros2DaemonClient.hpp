#ifndef ROS2_DAEMON_CLIENT_CPP__ROS2DAEMONCLIENT_HPP_
#define ROS2_DAEMON_CLIENT_CPP__ROS2DAEMONCLIENT_HPP_


// standard headers
#include <string>
#include <vector>

// xml rpc headers
#include <xmlrpcpp/XmlRpcClient.h>

// rclcpp headers
#include <rclcpp/node.hpp>



namespace ros2_daemon_client_cpp
{


/**
 * \brief The TopicData structure
 *
 * This struct contains data pertaining to a single ROS 2 topic.
 */
struct TopicData
{
  /** The topic. */
  std::string topic;

  /** The type of data published on this topic. */
  std::string type;
};

// various types
typedef std::vector<std::string> StringVector;
typedef std::vector<TopicData> TopicDataVector;


/**
 * \brief The Ros2DaemonClient class
 *
 * The Ros2DaemonClient class implements a basic XML-RPC client
 * for the ROS 2 daemon.
 */
class Ros2DaemonClient
{
public:
  /**
   * \brief Constructor
   *
   * Create a Ros2DaemonClient object.
   *
   * \param[in] host is the hostname for the ROS 2 daemon
   * \param[in] port is the port for the ROS 2 daemon
   * \param[in] rmwImplId is the RMW implementation identifier
   */
  Ros2DaemonClient(
    const std::string& host="localhost",
    const int& port=11511,
    const std::string& rmwImplId=rmw_get_implementation_identifier());

  /**
   * \brief Deconstructor
   *
   * Destroy the Ros2DaemonClient object.
   */
  virtual ~Ros2DaemonClient();

  /**
   * \brief Determine if the daemon client is connected
   *
   * Determine if the daemon client is connected.
   *
   * \return true if connected, false otherwise
   */
  bool isConnected() const;
  
  /**
   * \brief Get the list of running nodes
   *
   * Get the list of running nodes.
   *
   * \return the list of running nodes
   */
  StringVector getNodes();

  /**
   * \brief Get topic names and types
   *
   * Get ROS 2 topic names and types.
   *
   * \return the list of topic data
   */
  TopicDataVector getTopics();
  
  /**
   * \brief Get service names and types
   *
   * Get ROS 2 service names and types.
   *
   * \return the list of service data
   */
  TopicDataVector getServices();
  
protected:
  /** XML RPC client to the ROS 2 daemon. */
  XmlRpc::XmlRpcClient m_client;
};


}  // namespace ros2_daemon_client_cpp


#endif // ROS2_DAEMON_CLIENT_CPP__ROS2DAEMONCLIENT_HPP_

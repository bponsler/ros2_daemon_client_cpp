# ros2_daemon_client_cpp
A C++ client for the ROS 2 daemon

Examples:

    #include <ros2_daemon_client_cpp/Ros2DaemonClient.hpp>
    
    using namespace ros2_daemon_client_cpp;
    
    
    int main(int argc, char** argv)
    {
      Ros2DaemonClient client;
    
      // Get the list of nodes
      StringVector nodes = client.getNodes();
      std::cerr << "Found [" << nodes.size() << "] nodes:\n";
      for (int n = 0; n < nodes.size(); ++n) {
        std::cerr << "    [" << n << "]: " << nodes[n] << "\n";
      }
    
      // Get the list of topics
      TopicDataVector topics = client.getTopics();
      std::cerr << "Found [" << topics.size() << "] topics:\n";
      for (int t = 0; t < topics.size(); ++t) {
        std::cerr << "    [" << t << "]: " << topics[t].topic << " (" << topics[t].type << std::endl;
      }
    
      // Get the list of services
      TopicDataVector services = client.getServices();
      std::cerr << "Found [" << services.size() << "] services:\n";
      for (int t = 0; t < services.size(); ++t) {
        std::cerr << "    [" << t << "]: " << services[t].topic << " (" << services[t].type << std::endl;
      }
      
      return 0;
    }

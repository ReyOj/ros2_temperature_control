#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>

using namespace std::chrono_literals;

class Temperature : public rclcpp::Node
{
    std::string topic = this->get_parameter("topic_name").get_parameter_value().get<std::string>();
    std::string fileName = this->get_parameter("path").get_parameter_value().get<std::string>();
public:
  Temperature()
  : Node("temperature")
  {
    publisher_ = this->create_publisher<std_msgs::msg::Float32>(topic, 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Temperature::timer_callback, this));
  }

private:
    void timer_callback()
    {
      std::ifstream piCpuTempFile;
      float piCpuTemp = 0.0;
      std::stringstream buffer;
      piCpuTempFile.open(fileName);
      buffer << piCpuTempFile.rdbuf();
      piCpuTempFile.close();
      piCpuTemp = std::stof(buffer.str()); // convert string to float
      piCpuTemp = piCpuTemp / 1000; // convert float value to degree
      auto message = std_msgs::msg::Float32();
      message.data = piCpuTemp;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Temperature>());
  rclcpp::shutdown();
  return 0;
}

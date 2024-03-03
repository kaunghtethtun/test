#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8.hpp"

using namespace std::chrono_literals;

class Publisher : public rclcpp::Node
{
    public:
        Publisher(): Node("PubInteger")
        {
            pub_ = this->create_publisher<std_msgs::msg::UInt8>("int",10);
            timer_ = this->create_wall_timer(10ms,std::bind(&Publisher::callback,this));
        }
    private:
        void callback()
        {
            auto msg = std_msgs::msg::UInt8();
            msg.data = 8;
            RCLCPP_INFO(this->get_logger(),"%d",msg.data);
            pub_->publish(msg);
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr pub_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}

#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Publisher : public rclcpp::Node
{
    public:
        Publisher(): Node("mini_publish"), count_(0)
        {
            pub_ = this->create_publisher<std_msgs::msg::String>("mytopic",10);
            timer_ = this->create_wall_timer(10ms,std::bind(&Publisher::callback,this));
        }
    private:
        void callback()
        {
            auto msgs = std_msgs::msg::String();
            msgs.data = "Hello Testing" + std::to_string(count_++);
            //RCLCPP_INFO(this->get_logger(),"%s",msg.data.c_str());
            pub_->publish(msgs);
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
        size_t count_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}

#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class turtlecmd : public rclcpp::Node
{
    public:
        turtlecmd(): Node("forward")
        {
            pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
            timer_ = this->create_wall_timer(1000ms,std::bind(&turtlecmd::callback,this));
        }
    private:
        void callback()
        {
            auto msg = geometry_msgs::msg::Twist();
            msg.linear.x = 1.0;
            RCLCPP_INFO(this->get_logger(),"%2f",msg.linear.x);
            pub_->publish(msg);           
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<turtlecmd>());
    rclcpp::shutdown();
    return 0;
}

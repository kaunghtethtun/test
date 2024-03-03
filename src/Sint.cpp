#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8.hpp"

using std::placeholders :: _1;

class Subscriber : public rclcpp::Node
{
    public:
        Subscriber (): Node("SubInt")
        {
            sub_ = this->create_subscription<std_msgs::msg::UInt8>("int",10,std::bind(&Subscriber::callback,this,_1));
        }
    private:
        void callback(const std_msgs::msg::UInt8 & msg) const
        {
            RCLCPP_INFO(this->get_logger(),"%d",msg.data);
        }
        
        rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr sub_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Subscriber>());
    rclcpp::shutdown();
    return 0;
}

#include "autonomous_robot/ultrasonic_sensor.hpp"
#include "autonomous_robot/color_sensor.hpp"
#include "autonomous_robot/gripper_control.hpp"
#include "autonomous_robot/steering_control.hpp"
#include "rclcpp/rclcpp.hpp"

class AutonomousRobotNode : public rclcpp::Node {
public:
    AutonomousRobotNode() : Node("autonomous_robot_node") {
        // Initialize sensors and actuators
        ultrasonic_sensor_ = std::make_shared<UltrasonicSensor>();
        color_sensor_ = std::make_shared<ColorSensor>();
        gripper_control_ = std::make_shared<GripperControl>();
        steering_control_ = std::make_shared<SteeringControl>();

        // Create publishers and subscribers
        ultrasonic_publisher_ = this->create_publisher<std_msgs::msg::Float32>("ultrasonic_distance", 10);
        color_publisher_ = this->create_publisher<std_msgs::msg::String>("color_data", 10);
    }

private:
    std::shared_ptr<UltrasonicSensor> ultrasonic_sensor_;
    std::shared_ptr<ColorSensor> color_sensor_;
    std::shared_ptr<GripperControl> gripper_control_;
    std::shared_ptr<SteeringControl> steering_control_;

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr ultrasonic_publisher_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr color_publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AutonomousRobotNode>());
    rclcpp::shutdown();
    return 0;
}

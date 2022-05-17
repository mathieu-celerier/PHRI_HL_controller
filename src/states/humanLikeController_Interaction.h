#pragma once

#include <thread>
#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <mc_control/fsm/State.h>

struct humanLikeController_Interaction : mc_control::fsm::State
{
    void configure(const mc_rtc::Configuration & config) override;

    void start(mc_control::fsm::Controller & ctl) override;

    bool run(mc_control::fsm::Controller & ctl) override;

    void teardown(mc_control::fsm::Controller & ctl) override;
private:
    void updateVelTargetCallback(const std_msgs::Float32MultiArray::ConstPtr& joint_vel_msg);
    void get_ee_velocity_target(double dt);

    std::thread* thread;

    std::mutex target_mutex;
    Eigen::VectorXd joint_vel;
    bool runThread;
};
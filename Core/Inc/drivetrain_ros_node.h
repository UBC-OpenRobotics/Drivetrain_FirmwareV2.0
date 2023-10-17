#pragma once //should add this to ensure if this file is included in other files, the proceeding includes in this one will only
             //be added if theyre not already there -- Do
#ifndef DRIVETRAIN_ROS_NODE_H
#define DRIVETRAIN_ROS_NODE_H

//I AM TESTINGNGNGNGNGNGNGN

#include <math.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

//comms constants
#define CMD_VEL_TOPIC "/cmd_vel"
#define LOG_PUB_TOPIC "/stm32/log"
// #define STOP_TOPIC "/esp32/stop"

//robot kinematics constants
const float WHEEL_RADIUS = 0.075; //m
const float DRIVETRAIN_WIDTH = 0.55; //m
const float LIN_SPEED_LIMIT = 0.5; //m/s
const float ANG_SPEED_LIMIT = 1.0; //rad/s

//unit conversions
const float RADS_TO_RPM = 9.54929658551;

/** \brief Software interface for control over rosserial*/
class DriveTrainControlInterface
{
public:
    ros::Publisher logger; //field (variables), :: is an access operator
    ros::NodeHandle nh;
    ros::Subscriber<geometry_msgs::Twist, DriveTrainControlInterface> twistSubscriber;
    
    // function headers for the stuff i moved over/////////////////////////////////////////////////////
    void log(const char* msg); //method (function)
    void enforce_velocity_limits();
    static void calculateRobotKinematics(float velocityCmd[], u_int16_t rpmCmd[], bool dirCmd[]);
    bool isUpdated();
    void getMotorCmd(u_int16_t rpmCmd[], bool dirCmd[]);
    DriveTrainControlInterface();
    ////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    bool cmdUpdateFlag;
    float velocityCmd[2];
    u_int16_t _rpmCmd[2];
    bool _dirCmd[2];
    std_msgs::String string_msg;
    char msg_buff[100];
    
    //function i moved over:///////////////////////////
    void twistCmdCallback(const geometry_msgs::Twist &msg);
    ///////////////////////////////////////////////
};

#endif
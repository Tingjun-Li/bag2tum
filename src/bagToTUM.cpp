#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <iostream>
#include <chrono>
#include <string>
using namespace std;

// 设置一些保存路径
string Path = "/home/tingjunl/Downloads/data/fetch/conference_less_turn/";
string pathRGB = Path + "rgb.txt";
string pathDepth = Path + "depth.txt";
string dataRGB = Path + "rgb/";
string dataDepth = Path + "depth/";
// 设置图像topic名称
string depth_topic = "/head_camera/depth_registered/image_raw";
string rgb_topic = "/head_camera/rgb/image_raw";

// 保存图像路径至txt文件下
void savePath(string &path, string &type, double time)
{
    ofstream of;
    of.open(path, std::ios_base::app);
    if (of.fail())
    {
        ROS_INFO("Fail to opencv file!!");
    }
    else
    {
        of << endl;
        of << std::fixed << time << " " << type << time << ".png";
        of.close();
    }
}
// RGB图像回调函数
void GrabRGB(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        // 保存图像及路径
        cv_ptr = cv_bridge::toCvShare(msg);
        // 颜色通道转换
        cv::Mat bgrImage;
        cvtColor(cv_ptr->image, bgrImage, CV_BGR2RGB);
        // cv::imshow("RGB", bgrImage);

        double time = cv_ptr->header.stamp.toSec();
        string type = "rgb/";
        savePath(pathRGB, type, time);
        std::ostringstream osf;
        osf << dataRGB << std::fixed << time << ".png"; // 图像以时间戳命名
        cv::imwrite(osf.str(), bgrImage);
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    // cv::waitKey(2);
}

// 深度图像回调函数
void GrabDepth(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg);
        // imshow("Depth", cv_ptr->image);
        double time = cv_ptr->header.stamp.toSec();
        string type = "depth/";
        savePath(pathDepth, type, time);
        std::ostringstream osf;
        osf << dataDepth << std::fixed << time << ".png";
        cv::imwrite(osf.str(), cv_ptr->image);
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    // cv::waitKey(2);
}

// 节点主函数
int main(int argc, char **argv)
{
    ros::init(argc, argv, "bagToTUM");
    ros::start();
    ofstream of;
    of.open(pathRGB, std::ios_base::app);
    if (of.fail())
    {
        ROS_INFO("Fail to opencv file!!");
    }
    else
    {
        of << "#------------start a new dataset-----------------";
        of.close();
    }
    of.open(pathDepth, std::ios_base::app);
    if (of.fail())
    {
        ROS_INFO("Fail to opencv file!!");
    }
    else
    {
        of << "#------------start a new dataset-----------------";
        of.close();
    }

    // 订阅图像话题
    ROS_INFO("bagToTUM is ready.");
    ros::NodeHandle nodeHandler;
    ros::Subscriber subRGB = nodeHandler.subscribe(rgb_topic, 5, &GrabRGB);
    ros::Subscriber subDepth = nodeHandler.subscribe(depth_topic, 5, &GrabDepth);

    ros::spin();
    return 0;
}

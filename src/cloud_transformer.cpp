#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/transform_listener.h>

class CloudTransformer
{
public:
  explicit CloudTransformer(ros::NodeHandle nh)
    : nh_(nh)
  {
    // Define Publishers and Subscribers here
    pcl_sub_ = nh_.subscribe("/inputPC", 1, &CloudTransformer::pclCallback, this);
    pcl_pub_ = nh_.advertise<sensor_msgs::PointCloud2>("/outputPC", 1);

    buffer_.reset(new sensor_msgs::PointCloud2);
    buffer_->header.frame_id = "/marker";
  }

private:
  ros::NodeHandle nh_;
  ros::Subscriber pcl_sub_;
  ros::Publisher pcl_pub_;
  tf::TransformListener listener_;
  sensor_msgs::PointCloud2::Ptr buffer_;

  void pclCallback(const sensor_msgs::PointCloud2ConstPtr& pcl_msg)
  {
    listener_.waitForTransform("/marker", "/depth_camera_link", ros::Time::now(), ros::Duration(3.0));
    pcl_ros::transformPointCloud("/marker", *pcl_msg, *buffer_, listener_);
    pcl_pub_.publish(buffer_);
  }
}; 

int main(int argc, char **argv)
{
  ros::init(argc, argv, "point_cloud_tf");
  ros::NodeHandle nh;

  CloudTransformer tranform_cloud(nh);

  // ROS Loop
  while (ros::ok())
    ros::spin();

  return 0;
}

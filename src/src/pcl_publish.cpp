#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>


main(int argc, char **argv)
{
    ros::init (argc, argv, "pcl_publish");

    ros::NodeHandle nh;
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("/pcl_publish_output", 1);

    sensor_msgs::PointCloud2 publish_output;
    pcl::PointCloud<pcl::PointXYZ> cloud;

    pcl::io::loadPCDFile ("/home/janak/pcd_new_kitti/1317379226.699959039.pcd", cloud);

    pcl::toROSMsg(cloud, publish_output);
    publish_output.header.frame_id = "/camera_init"; 

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        pcl_pub.publish(publish_output);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}


# ROS-point-cloud-Transformer
## Simple ROS package for transforming point cloud using ROS TF tree

## Set Up
1. Clone this repo to your catlin workspace
2. Build Package
3. Launch point cloud transformer node (see example.launch)
```
<launch>
  <node name="cloud_tansformer"
        pkg="pointcloud_transformer" type="cloud_transformer" output="screen">
    <remap from="/inputPC" to="/croppedPointCloud" />
    <remap from="/outputPC" to="/croppedPointCloudWorld" />
    <param name="frameIn" type="str" value="rgb_camera_link" />
    <param name="frameOut" type="str" value="goal" />
  </node> 
</launch>
```
change input,output and frame in, frame out 

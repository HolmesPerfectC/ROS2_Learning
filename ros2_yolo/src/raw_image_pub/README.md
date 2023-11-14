该功能包主要实现原始图像读取及发布功能，主要包括以下几个功能：

- 图像读取功能：

  从图像文件读取图像（JPG、PNG、TGA、BMP、GIF、PSD、HDR、PIC、PNM）；

  从视频文件读取图像（MP4、MKV、AVI、FLV）;

  从各类型相机读取图像（MIPI CSI、V4L2、WebRTC、RTP、RTSP）；

- 图像格式转换

  应当支持像素格式和色彩空间转换（例如YUV、RGB、RGBA、GRAY、BAYER等）；

  支持将cv格式图像与sensor_msgs::Image类图像相互转换；

- 图像发布

  将图像以sensor_msgs::Image格式进行发布；

- 函数说明

  load_parameter:获取node parameter;

  ImagePub::image_timer_callback:图像发布回调函数;

  ImagePub::video_timer_callback:视频发布回调函数;
  
  video_capture:如果是获取视频数据，建立capture对象,获取总帧数;


- 参数说明

  use_image_flag:

  - 当值为1时，则使用图片，从image_path读取图片；
  - 当值为2时，则使用视频，从video_path读取视频；

  image_path:图像路径

  video_path:视频路径

  image_pub_topic_name:话题名称

  

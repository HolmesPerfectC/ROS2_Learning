# tensorrt_yolov5

该功能包主要实现yolov5的TensorRT构建及推理，主要包含以下功能：

## 数据部分

### 订阅图像数据：

从/raw_image_pub话题中订阅图像数据

### 图像预处理

将订阅的图像按照yolov5的inference所需格式进行预处理（格式转换、resize、归一化、通道转换）

### 图像后处理

将检测结果进行decode，得到最后的BoudingBOX及类别

### 检测结果发布

以坐标或者图像形式（若有可视化需求）进行发布

## 模型部分

### yolov5模型的TensorRT构建

从onnx文件构建yolov5网络并生成推理engine

### yolov5模型推理

将图像从CPU拷贝到GPU，并使用生成的engine进行推理

## 组件（Component）部分

### YOLOV5类

在YOLOV5的命名空间下实现YOLOV5类

实现构建、推理、前处理、后处理，读标签功能



### YOLOV5_COMPONENT类

该类对YOLOV5类进行Wrapper，用于注册ros2的component，并加载node parameter。

使用timer来调用connect函数，周期设为100ms。

Connect函数：用于判断识别结果是否有订阅者，若没有订阅者，则关闭yolov5的图像订阅image_sub_来节省资源，若有检测结果的订阅者，则创建原始图像的订阅者，来对原始图像进行识别。

### launch文件

使用launch文件加载componet，并实例化YOLOV5_COMPONENT类
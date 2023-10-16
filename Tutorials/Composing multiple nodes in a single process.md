# Composing multiple nodes in a single process

目标：在一个进程里面运行多个节点

## Background

可以参考这篇[components概念文章](https://docs.ros.org/en/humble/Concepts/Intermediate/About-Composition.html)。

## Run the demos

该例程使用rclcpp_components、ros2component和composition包里的可执行文件，并可以按照下面命令运行。

## Discover available components

查看工作空间里已注册和可用的components，在shell中执行以下命令：

```shell
ros2 component types
```

终端会返回可用的components列表:

```shell
(... components of other packages here)
composition
  composition::Talker
  composition::Listener
  composition::NodeLikeListener
  composition::Server
  composition::Client
(... components of other packages here)
```

## Run-time composition using ROS services with a publisher and subscriber

在第一终端shell里，开启component container(组件容器)：

```shell
ros2 run rclcpp_components component_container
```

打开第二个shell终端并且通过ros2 CLI tools验证正在运行的container:

```shell
ros2 component list
```

你应该会看到component的名字：

```shell
/ComponentManager
```

在第二个shell终端里加载talker component(源码在[这里](https://github.com/ros2/demos/blob/humble/composition/src/talker_component.cpp))

```shell
ros2 component load /ComponentManager composition composition::Talker
```

终端会返回一个已加载的component的unique ID和节点名字：

```shell
Loaded component 1 into '/ComponentManager' container node as '/talker'
```

现在第一个shell终端会显示component已加载并且会一直重复发布消息。

运行另外的命令来加载listener component（源码在[这里](https://github.com/ros2/demos/blob/humble/composition/src/listener_component.cpp)）

```shell
ros2 component load /ComponentManager composition composition::Listener
```

终端会返回

```shell
Loaded component 1 into '/ComponentManager' container node as '/talker'
```

ros2命令可以被用来检查container状态：

```shell
ros2 component list
```

会看到下面的结果：

```shell
/ComponentManager
   1  /talker
   2  /listener
```

现在第一个shell终端会显示接收到的每个消息及对应的输出。




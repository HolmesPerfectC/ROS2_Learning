# Composing multiple nodes in a single process

目标：在一个进程里面运行多个节点

## Background

可以参考这篇[components概念文章](https://docs.ros.org/en/humble/Concepts/Intermediate/About-Composition.html)。

## Run the demos

该例程使用rclcpp_components、ros2component和composition包里的可执行文件，并可以按照下面命令运行。

### Discover available components

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

### Run-time composition using ROS services with a publisher and subscriber

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

### Run-time composition using ROS services with a server and client

服务端和客户端的例子非常类似。

在第一个shell终端输入：

```shell
ros2 run rclcpp_components component_container
```

在第二个shell终端输入：([服务端](https://github.com/ros2/demos/blob/humble/composition/src/server_component.cpp)和[客户端](https://github.com/ros2/demos/blob/humble/composition/src/client_component.cpp)源码)

```shell
ros2 component load /ComponentManager composition composition::Server
ros2 component load /ComponentManager composition composition::Client
```

在这例子中，客户端给服务端发送请求，服务端处理请求并且返回处理结果，客户端打印出收到的结果。

### Compile-time composition using ROS services

这个demos展示一个能复用的共享库，该共享库能用来编译一个可以运行多个组件的可执行文件。可执行文件包含上述四种components: talker、listener 、server 、client。

在shell终端调用(源码在[这里](https://github.com/ros2/demos/blob/humble/composition/src/manual_composition.cpp))

```shell
ros2 run composition manual_composition
```

这将会显示the talker 和 the listener以及 the server 和 the client这两对组件成对的重复消息。

:pencil2::**Note**

```shell
上述方式手动编写的组件不会反映在ros2 component list命令工具的输出中
```

### Run-time composition using dlopen

这个demo展示了另一个运行组件的方法，通过创建一个通用的 container 进程，明确传递要加载的库，而不使用ROS接口。这个进程将会打开每个库并为库里的每个“rclcpp""Node”类创建一个实例。（[源代码](https://github.com/ros2/demos/blob/humble/composition/src/dlopen_composition.cpp)）

```shell
Linux
ros2 run composition dlopen_composition `ros2 pkg prefix composition`/lib/libtalker_component.so `ros2 pkg prefix composition`/lib/liblistener_component.so
```

现在shell终端会重复显示每个发送和接受信息的输出。

:pencil:**Note**

```shell
dlopen-composed 的components不会反映在ros2 component list命令工具的输出中
```

### composition using  launch actions

虽然CLI tools对于debugging和diagnosing component的配置很有用，但是同时启动一系列的components往往更加方便。为了实现这个自动化操作，我们可以使用launch文件:

```shell
ros2 launch composition composition_demo.launch.py
```

## Advanced Topics

现在我们已经了解了components的基础操作，我们可以讨论一点更加深入的话题了。

### Unloading components

在第一个shell终端，打开一个component container:

```shell
ros2 run rclcpp_components component_container
```

通过``ros2``验证正在运行的Container:

```shell
ros2 component list
```

你应该会看到这个名字的component:

```shell
/ComponentManager
```

像前面那样，在第二个shell终端加载the talker和the listener:

```shell
ros2 component load /ComponentManager composition composition::Talker
ros2 component load /ComponentManager composition composition::Listener
```

用唯一的ID来从Container里卸载 component:

```shell
ros2 component unload /ComponentManager 1 2
```

终端会返回:

```shell
Unloaded component 1 from '/ComponentManager' container
Unloaded component 2 from '/ComponentManager' container
```

在第一个shell终端验证来自talker和listener重复的消息是否停止。

### Remapping container name and namespace

组件管理器(component manager)名字和命名空间(namespace)可以通过命令行参数重新映射(remap)。

```shell
ros2 run rclcpp_components component_container --ros-args -r __node:=MyContainer -r __ns:=/ns
```

在第二个shell终端，组件(components)使用更新过名字的容器被加载。

```shell
ros2 component load /ns/MyContainer composition composition::Listener
```

:pencil:**Note**

```shell
容器命名空间(namespace)的重映射(remappings)不影响加载组件(components)。
```

### Remap component names and namespace

组件(component)名称和命名空间(namespace)可以通过加载命令的参数调整。

在地一个shell终端，开启组件容器(component container):

```shell
ros2 run rclcpp_components component_container
```

下面是一些如何重映射名字和命名空间(namespace)的例子:

1、重映射节点名字：

```shell
ros2 component load /ComponentManager composition composition::Talker --node-name talker2
```

2、重映射命名空间(namespace):

```shell
ros2 component load /ComponentManager composition composition::Talker --node-namespace /ns
```

3、两个都进行重映射:

```shell
ros2 component load /ComponentManager composition composition::Talker --node-name talker3 --node-namespace /ns2
```

现在我们用```ros2```命令工具：

```shell
ros2 component list
```

在控制台你将会看到相应的条目：

```shell
/ComponentManager
   1  /talker2
   2  /ns/talker
   3  /ns2/talker3
```

:pencil:**Note**

```shell
容器(Container)的命名空间(Namespace)的重映射不影响加载组件(Components)。
```

### Passing parameter values into components

``ros2 component load``命令支持在节点构建时传递任意参数。这项功能可以像下面这样使用:

```shell
ros2 component load /ComponentManager image_tools image_tools::Cam2Image -p burger_mode:=true
```

### Passing additional arguments into components

`ros2 component load`命令行支持向组件管理器传递特定选项，以便于在构建节点时使用。目前，唯一支持的命令行选项是使用进程内通信初始化节点。这个功能使用方法如下:

```shell
ros2 component load /ComponentManager composition composition::Talker -e use_intra_process_comms:=true
```

## Composable nodes as shared libraries

如果你想从一个软件包中导出一个可组合节点作为共享库，并在另一个可进行链接时组合的软件包中使用该节点，请在 CMake 文件中添加代码，导入下游软件包中的实际目标。

然后安装生成的文件并导出生成的文件。

在这里可以看到一个实际例子: [ROS Discourse - Ament best practice for sharing libraries](https://discourse.ros.org/t/ament-best-practice-for-sharing-libraries/3602)

## Composing Non-Node Derived Components

在 ROS 2 中，组件可以更有效地利用系统资源，并提供了一个强大的功能，使您可以创建不与特定节点绑定的可重用功能。

使用组件的一个好处是，可以将非节点衍生功能创建为独立的可执行文件或共享库，并根据需要加载到 ROS 系统中。

要创建一个非源于节点的组件，请遵循以下指导原则：

1. 实现一个以 const rclcpp::NodeOptions& 作为参数的构造函数。
2. 实现 get_node_base_interface() 方法，该方法应返回一个 NodeBaseInterface::SharedPtr。您可以使用在构造函数中创建的节点的 get_node_base_interface() 方法来提供此接口。

下面是一个非节点派生组件的例子，它监听一个 ROS 话题：[node_like_listener_component](https://github.com/ros2/demos/blob/humble/composition/src/node_like_listener_component.cpp)。

有关此主题的更多信息，请参阅[本讨论](https://github.com/ros2/rclcpp/issues/2110#issuecomment-1454228192)。

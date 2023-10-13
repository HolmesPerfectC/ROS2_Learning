# Composition

## Table of Contents

- ROS1 - Nodes vs. Nodelets
- ROS2 - Unified API
- Writing a Component
- Using Component
- Practical application

## ROS1 - Nodes vs. Nodelets

在 ROS 1 中，你可以将代码写成 ROS Node或 ROS nodelet。ROS 1 nodes被编译成可执行文件。而 ROS 1 nodelets则编译成共享库，然后由容器进程在运行时加载。

## ROS2 - Unified API

在 ROS 2 中，我们推荐的代码书写方式类似于节点（nodelet）--我们称之为组件（Component）。这使得在现有代码中添加通用概念（如生命周期）变得容易。在 ROS 1 中，不同的应用程序接口（API）是最大的缺点，而在 ROS 2 中，由于两种方法都使用相同的应用程序接口，因此避免了这一缺点。

```markdown
Note
使用类似节点的 "编写自己的主程序 "的方式也是可行的，但在一般情况下并不推荐使用。
```

将流程布局作为一个部署时间决策，用户可以在两者之间做出选择：

- 在独立进程中运行多个节点，具有进程/故障隔离以及更容易调试单个节点的优点，而且

- 在单个进程中运行多个节点，开销更低，通信效率更高（参见[进程内通信](https://docs.ros.org/en/humble/Tutorials/Demos/Intra-Process-Communication.html)）。

此外，还可以使用 ros2 launch 通过专门的启动操作自动执行这些操作。

## Writing a Component

由于组件仅内置在共享库中，因此没有主函数（参见 [Talker 源代码](https://github.com/ros2/demos/blob/humble/composition/src/talker_component.cpp)）。组件通常是 rclcpp::Node 的子类。由于它不控制线程，因此不应在构造函数中执行任何长时间运行或阻塞任务。相反，它可以使用定时器获取定期通知。此外，它还可以创建发布者、订阅、服务器和客户端。

让这样的类成为组件的一个重要方面是，该类使用 rclcpp_components 包中的宏来注册自己（参见源代码中的最后一行）。这样，在运行进程中加载组件库时，就可以发现该组件--它就像是一个入口点。

此外，一旦创建了一个组件，它就必须在索引中注册，才能被工具发现。

```cmake
add_library(talker_component SHARED src/talker_component.cpp)
rclcpp_components_register_nodes(talker_component "composition::Talker")
# To register multiple components in the same shared library, use multiple calls
# rclcpp_components_register_nodes(talker_component "composition::Talker2")
```

```markdown
Note
为了让 component_container 能够找到所需的组件，它必须从已获取相应工作区的 shell 中执行或启动。
```

## Using Components

组件包包含几种不同的组件使用方法。这里是composition的[demo](https://github.com/ros2/demos/tree/humble/composition)。

1. 启动一个（[通用容器进程](https://github.com/ros2/rclcpp/blob/humble/rclcpp_components/src/component_container.cpp)）并调用容器提供的 ROS 服务 [load_node](https://github.com/ros2/rcl_interfaces/blob/humble/composition_interfaces/srv/LoadNode.srv)。然后，ROS 服务就会加载由传递的软件包名称和库名称指定的组件，并在运行进程中开始执行。除了以编程方式调用 ROS 服务，你也可以使用命令行工具（[ros2 component CLI Tools](https://github.com/ros2/ros2cli/tree/humble/ros2component/ros2component)），通过传入的命令行参数调用 ROS 服务。
2. 创建一个自定义可执行文件(这里是[demo](https://github.com/ros2/demos/blob/humble/composition/src/manual_composition.cpp))，其中包含编译时已知的多个节点。这种方法要求每个组件都有一个头文件（严格来说，第一种情况并不需要）。
3. 创建一个启动文件，并使用 ros2 launch 创建一个已加载多个组件的容器进程。

## Practical application

Try the [Composition demos](https://docs.ros.org/en/humble/Tutorials/Intermediate/Composition.html).

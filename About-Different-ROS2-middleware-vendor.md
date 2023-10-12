# Different ROS2 middleware vendor

ROS 2 以 DDS/RTPS 作为中间件，提供发现、序列化和传输功能。[这篇文章](https://design.ros2.org/articles/ros_on_dds.html)详细解释使用 DDS 实现和/或 DDS 的 RTPS 线协议背后的动机。总之，DDS 是一个端到端中间件，提供与 ROS 系统相关的功能，如分布式发现（而非 ROS 1 中的集中式）和对不同传输 "服务质量 "选项的控制。

DDS 是一种行业标准，由一系列供应商实施，如 RTI 的 Connext DDS、eProsima 的 Fast DDS、Eclipse 的 Cyclone DDS 或 GurumNetworks 的 GurumDDS。RTPS（又称 DDSI-RTPS）是 DDS 用于网络通信的有线协议。

ROS 2 支持多种 DDS/RTPS 实现，因为在选择供应商/实现时，并不一定要 "一刀切"。在选择中间件实现时，您可能会考虑许多因素：如许可证等后勤因素，或平台可用性或计算占用等技术因素。供应商可能会针对不同需求提供多种 DDS 或 RTPS 实现。例如，RTI 的 Connext 实现就有多种不同的用途，如一种专门针对微控制器，另一种针对需要特殊安全认证的应用（目前我们只支持其标准桌面版本）。

为了在 ROS 2 中使用 DDS/RTPS 实现，需要创建一个 "ROS 中间件接口"（又名 rmw 接口或简称 rmw）包，使用 DDS 或 RTPS 实现的 API 和工具来实现抽象的 ROS 中间件接口。为支持 DDS 实现而实现和维护 RMW 包是一项繁重的工作，但至少支持几种实现对于确保 ROS 2 代码库不与任何一种特定实现绑定非常重要，因为用户可能希望根据自己项目的需要更换实现。

## Supported RMW implementations

| Product name             | License                     | RMW implementation | Status                                                       |
| ------------------------ | --------------------------- | ------------------ | ------------------------------------------------------------ |
| eProsima Fast DDS        | Apache 2                    | rmw_fastrtps_cpp   | Full support. Default RMW. Packaged with binary releases.    |
| Eclipse Cyclone DDS      | Eclipse Public License v2.0 | rmw_cyclonedds_cpp | Full support. Packaged with binary releases.                 |
| RTI *Connext DDS*        | commercial, research        | rmw_connextdds     | Full support. Support included in binaries, but Connext installed separately. |
| GurumNetworks *GurumDDS* | commercial                  | rmw_gurumdds_cpp   | Community support. Support included in binaries, but GurumDDS installed separately. |

有关使用多个 RMW 实现的实用信息，请参阅 "[使用多个 RMW 实现](https://docs.ros.org/en/humble/How-To-Guides/Working-with-multiple-RMW-implementations.html) "教程。

## Multiple RMW implementations

目前使用的发行版的 ROS 2 二进制版本已经内置了对几种 RMW 实现的开箱支持（Fast DDS、RTI Connext Pro、Eclipse Cyclone DDS、GurumNetworks GurumDDS）。默认的是 Fast DDS，它无需任何额外的安装步骤即可运行，因为我们随二进制软件包一起分发。

其他 RMW（如 Cyclone DDS、Connext 或 GurumDDS）可通过安装附加软件包启用，但无需重建任何东西或替换任何现有软件包。

从源代码构建的 ROS 2 工作区可以同时构建和安装多个 RMW 实现。在编译 ROS 2 核心代码的同时，如果相关的 DDS/RTPS 实现已正确安装并配置了相关的环境变量，那么找到的任何 RMW 实现都将被构建。例如，如果工作区中有用于 RTI Connext DDS 的 RMW 软件包的代码，那么如果还能找到 RTI Connext Pro 的安装，就会构建该软件包。

## Default RMW implementation

如果 ROS 2 工作区有多个 RMW 实现，则会选择可用的 Fast DDS 作为默认 RMW 实现。如果未安装 Fast DDS RMW 实现，则将使用按字母顺序排列的 RMW 实现标识符排在第一位的 RMW 实现。实现标识符是提供 RMW 实现的 ROS 软件包名称，例如 rmw_cyclonedds_cpp。例如，如果同时安装了 rmw_cyclonedds_cpp 和 rmw_connextdds ROS 软件包，则默认使用 rmw_connextdds。如果安装了 rmw_fastrtps_cpp，则默认为 rmw_fastrtps_cpp。

有关运行 ROS 2 示例时如何指定使用哪种 RMW 实现，请参阅[指南](https://docs.ros.org/en/humble/How-To-Guides/Working-with-multiple-RMW-implementations.html)。
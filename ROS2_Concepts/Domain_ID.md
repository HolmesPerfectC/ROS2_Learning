# The ROS_DOMAIN_ID

原文可参考ros2的[ROS DOMAIN ID文档](https://docs.ros.org/en/humble/Concepts/Intermediate/About-Domain-ID.html)。

## Overview

正如其他地方所解释的那样，ROS 2 默认使用的通信中间件是 DDS。在 DDS 中，不同logical network共享一个physical network的主要机制被称为Domain ID。同一域上的 ROS 2 节点可以自由地相互发现和发送信息，而不同域上的 ROS 2 节点则不能。所有 ROS 2 节点默认使用域 ID 0。为避免在同一网络上运行 ROS 2 的不同计算机组之间相互干扰，应为每个计算机组设置不同的域 ID。

## choosing a domain ID(short version)

下面的文字说明了 ROS 2 中应使用的域 ID 范围的推导过程。要跳过这些背景知识，直接选择一个安全的数字，只需在 0 到 101（含）之间选择一个域 ID。

## choosing a domain ID(long version)

DDS 使用域 ID 计算用于发现和通信的 UDP 端口。有关如何计算端口的详细信息，请参阅这个[文章](https://community.rti.com/content/forum-topic/statically-configure-firewall-let-omg-dds-traffic-through)。请记住，UDP 端口是一个无符号的 16 位整数([usigned 16-bit integer](https://en.wikipedia.org/wiki/User_Datagram_Protocol#Ports) )。因此，可分配的最高端口号是 65535。根据上述文章中的公式进行计算，这意味着可以分配的最高域 ID 是 232，而可以分配的最低域 ID 是 0。

### Platform-specific constraints

为实现最大兼容性，在选择域 ID 时还应遵循一些特定平台的限制条件。尤其是，最好避免在操作系统的临时端口([Ephemeral port](https://en.wikipedia.org/wiki/Ephemeral_port))范围内分配域 ID。这样可以避免 ROS 2 节点使用的端口与计算机上的其他网络服务发生冲突。

#### 这里以Linux系统为例：

默认情况下，Linux 内核使用 32768-60999 端口作为短暂端口。这意味着可以安全地使用域 ID 0-101 和 215-232，而不会与短暂端口发生冲突。在 Linux 中，可通过在 proc/sys/net/ipv4/ip_local_port_range 中设置自定义值来配置短暂端口范围。如果使用自定义的短暂端口范围，上述数字可能需要做相应调整。

### Participant constraints

计算机上每运行一个 ROS 2 进程，就会创建一个 DDS "参与者"。由于每个 DDS 参与者占用计算机上的两个端口，因此在一台计算机上运行超过 120 个 ROS 2 进程可能会溢出到其他域 ID 或短暂端口。

要了解原因，请看域 ID 1 和 2。

- 域 ID 1 使用端口 7650 和 7651 进行组播。

- 域 ID 2 使用端口 7900 和 7901 进行组播。

- 在域 ID 1 中创建第 1 个进程（第 0 个参与者）时，端口 7660 和 7661 用于单播。

- 在域 ID 1 中创建第 120 个进程（第 119 个参与者）时，端口 7898 和 7899 用于单播。

- 在域 ID 1 中创建第 121 个进程（第 120 个参与者）时，端口 7900 和 7901 用于单播并与域 ID 2 重叠。

如果知道计算机每次只在一个域 ID 上运行，而且域 ID 足够低，那么创建比这更多的 ROS 2 进程是安全的。

在选择接近平台特定域 ID 范围顶端的域 ID 时，还应考虑一个额外的限制因素。

例如，假设一台 Linux 计算机的域 ID 为 101：

- 计算机上的第 0 个 ROS 2 进程将连接到 32650、32651、32660 和 32661 端口。

- 计算机上的第一个 ROS 2 进程将连接到 32650、32651、32662 和 32663 端口。

- 计算机上的第 53 个 ROS 2 进程将连接到端口 32650、32651、32766 和 32767。

- 计算机上的第 54 个 ROS 2 进程将连接到 32650、32651、32768 和 32769 端口，进入短暂端口范围。

因此，在 Linux 上使用域 ID 101 时，应创建的最大进程数为 54。同样，在 Linux 上使用域 ID 232 时，应创建的最大进程数是 63，因为最大端口号是 65535。

macOS 和 Windows 上的情况类似，但数字有所不同。在 macOS 和 Windows 上，当选择的域 ID 为 166（范围的最高值）时，进入临时端口范围之前，在计算机上创建的 ROS 2 进程的最大数量为 120。
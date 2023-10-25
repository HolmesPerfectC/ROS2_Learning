# ament_cmake user documentation

`ament_cmake `是 ROS 2 中用于基于 CMake 的软件包的构建系统（特别是大多数 C/C++ 项目将使用它）。它是一组增强 CMake 并为软件包作者提供便捷功能的脚本集合。在使用 `ament_cmake `之前，了解 CMake 的基础知识非常有帮助。可以在这里找到[官方教程](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)。

[TOC]

## Basics

可以使用命令行上的 ``ros2 pkg create <package_name>``来生成基本的 CMake 大纲。然后，构建信息将被收集到两个文件中：`package.xml `和 `CMakeLists.txt`，这两个文件必须位于同一个目录中。`package.xml `必须包含所有依赖项以及一些元数据，以允许 colcon 找到正确的构建顺序，以在 CI 中安装所需的依赖项，并为使用 `bloom `进行发布提供信息。`CMakeLists.txt `包含用于构建和打包可执行文件和库的命令，将是本文档的主要关注点。

### Basic project outline

一个基础的ament package包的`CMakeLists.txt`大纲包含：

```cmake
cmake_minimum_required(VERSION 3.8)
project(my_project)

ament_package()
```

`project` 的参数将是软件包名称，必须与`package.xml `中的软件包名称完全相同。

项目的设置由 `ament_package()` 完成，每个软件包必须只调用一次 `ament_package()`。`ament_package()` 安装 package.xml，将软件包注册到 ament 索引，并安装配置文件（以及可能的目标文件）以便 CMake 可以被其他软件包通过 `find_package` 找到。由于 `ament_package()` 从 CMakeLists.txt 收集了许多信息，因此它应该是你的 CMakeLists.txt 中的最后一个调用。

`ament_package`能添加额外的参数：

- `CONFIG_EXTRAS`：这是一个包含CMake文件（.cmake或通过`configure_file()`扩展的.cmake.in模板）的列表，这些文件应该对软件包的客户端可用。关于何时使用这些参数的示例，请参见 ["Adding resources"]() 中的讨论。有关如何使用模板文件的更多信息，请参考[官方文档](https://cmake.org/cmake/help/v3.8/command/configure_file.html)。
- `CONFIG_EXTRAS_POST`:和`CONFIG_EXTRAS`一样，但是文件添加顺序不同。`CONFIG_EXTRAS` 中的文件在 `ament_export_*` 调用生成的文件之前包含，而 `CONFIG_EXTRAS_POST` 中的文件在之后包含。

除了添加到 `ament_package` 外，你还可以添加到变量 `${PROJECT_NAME}_CONFIG_EXTRAS` 和 `${PROJECT_NAME}_CONFIG_EXTRAS_POST`，其效果相同。和上面一样，唯一的区别是文件添加的顺序，总的顺序如下：

- 通过`CONFIG_EXTRAS`添加的文件
- 通过添加到`${PROJECT_NAME}_CONFIG_EXTRAS`加入的文件
- 通过添加到`${PROJECT_NAME}_CONFIG_EXTRAS_POST`加入的文件
- 通过`CONFIG_EXTRAS_POST`加入的文件

### Compiler and linker options

ROS 2 目标编译器符合 C++17 和 C99 标准。将来可能会瞄准更新的版本，这些版本在[这里](https://www.ros.org/reps/rep-2000.html)有引用。因此，通常会设置相应的 CMake 标志：

```cmake
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
```

为了保持代码的清晰性，编译器应该对可疑的代码引发警告，并应该修复这些警告。

建议至少涵盖以下警告级别：

- 对于Visual Studio，建议使用默认的`W1`警告级别。
- 对于GCC和Clang，强烈建议使用以下编译选项：`-Wall -Wextra -Wpedantic`，并建议使用`-Wshadow`。

目前建议使用`add_compile_options`来为所有目标添加这些选项。这样可以避免为所有可执行文件、库和测试添加基于目标的编译选项而使代码混乱不堪。

```cmake
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
```

### Finding dependencies

大多数 `ament_cmake`项目都会依赖其他软件包。在CMake中，可以通过调用 `find_package` 来实现这一点。例如，如果你的软件包依赖于` rclcpp`，那么 `CMakeLists.txt `文件应包含：

```cmake
find_package(rclcpp REQUIRED)
```

:pencil:**Note**

```
通常不需要使用`find_package`来查找一个非显式需要而是另一个显式需要的依赖的依赖项。如果出现这种情况，应该向相应的软件包提交错误报告（bug）。
```

### Adding targets

在CMake的术语中，"targets"（目标）是此项目将要创建的构件。可以创建库或可执行文件，并单个项目可以包含零个或多个库和可执行文件。



### Linking to dependencies

### Installing

## Linting and Testing

### Linting

### Testing

## Extending ament

### Adding a function/macro to ament

### Adding to extension points

### Adding extension points

## Adding resources

### The ament index explained

### Querying the ament index

### Adding to the ament index
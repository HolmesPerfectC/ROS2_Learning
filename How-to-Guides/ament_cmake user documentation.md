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

#### Libraries

这些是通过调用`add_library`来创建的，应该包含目标名字和编译时生成库的源文件。

因为在C/C++中将头文件和实习文件分离，因此没有必要将头文件作为`add_library`的参数。

下列是建议的最佳做法：

- 将应该可以被这个库使用的所有头文件放在一个名为包名称的`include`文件夹的子目录中，而所有其他文件（.c/.cpp和不应该被导出的头文件）放在src文件夹中。

- 在add_library的调用中只显式引用.c/.cpp文件。

- 通过以下方式找到你的库my_library的头文件：

  ```cmake
  target_include_directories(my_library
    PUBLIC
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
      "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>")
  ```

这将在构建时将位于`${CMAKE_CURRENT_SOURCE_DIR}/include`文件夹中的所有文件添加到公共接口，并在安装时将所有文件添加到`include`文件夹（相对于`${CMAKE_INSTALL_DIR}`）。

`ros2 pkg create`创建一个按照下面规则布局的功能包。

:pencil:**Note**

由于Windows是官方支持的平台之一，为了功能包能发挥最大作用，任何功能包也应该能够在Windows上构建。Windows库格式强制执行符号可见性；也就是说，每个应该被客户端使用的符号都必须由库显式导出（并且符号需要被隐式导入）。
由于通常情况下GCC和Clang构建不会自动执行这一点，建议使用[GCC wiki](https://gcc.gnu.org/wiki/Visibility)中的逻辑。要将其用于名为`my_library`的软件包：

- 将链接中的逻辑复制到名为visibility_control.hpp的头文件中。

- 将DLL替换为MY_LIBRARY（可以参考[rviz_rendering](https://github.com/ros2/rviz/blob/ros2/rviz_rendering/include/rviz_rendering/visibility_control.hpp)的可见性控制进行示例）。

- 对于需要导出的所有符号（例如类或函数），使用宏“MY_LIBRARY_PUBLIC”。

- 在项目的CMakeLists.txt文件中使用：

  ```cmake
  target_compile_definitions(my_library PRIVATE "MY_LIBRARY_BUILDING_LIBRARY")
  ```

更多的细节可以看[Windows Symbol Visibility in the Windows Tips and Tricks document](https://docs.ros.org/en/humble/The-ROS2-Project/Contributing/Windows-Tips-and-Tricks.html#windows-symbol-visibility)。

#### Executables

这些可执行文件应该通过调用`add_executable`来创建，该调用应包含目标的名称以及用来编译创建可执行文件的源文件。可执行文件可能还需要链接到该软件包中创建的任何库，可以使用`target_link_libraries`来实现这一点。

由于可执行文件通常不被客户端用作库，因此不需要将头文件放在`include`目录中。

在一个软件包中既有库又有可执行文件的情况下，确保结合上面“库”和“可执行文件”两个部分的建议。

### Linking to dependencies

有两种方法可以将目标与依赖链接起来。

第一种建议的方法是使用ament宏`ament_target_dependencies`。例如，假设我们想将`my_library`与线性代数库Eigen3链接起来。

```cmake
find_package(Eigen3 REQUIRED)
ament_target_dependencies(my_library PUBLIC Eigen3)
```

它会包括所需的头文件、库以及它们的依赖项，以便项目可以正确找到它们。

第二种方法使用`target_link_libraries`。

现代CMake更倾向于仅使用目标，导出和链接到它们。CMake目标可以进行命名空间管理，类似于C++。如果可用，建议使用命名空间目标。例如，Eigen3定义了Eigen3::Eigen目标。

以`Eigen3`为例，应该像下面这样调用：

```cmake
target_link_libraries(my_library PUBLIC Eigen3::Eigen)
```

这将包括必要的头文件、库以及它们的依赖项。请注意，这个依赖关系必须在之前通过调用`find_package`进行发现。

### Installing

#### Libraries

在构建可重用的库时，需要导出一些信息，以便下游软件包可以轻松地使用它。

首先，安装应该提供给客户端的头文件。`include`目录是自定义的，用于支持colcon中的叠加功能。请查看[相关文档](https://colcon.readthedocs.io/en/released/user/overriding-packages.html#install-headers-to-a-unique-include-directory)以了解更多信息。

```cmake
install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)
```

接下来，安装目标并创建导出目标（`export_${PROJECT_NAME}`），其他代码将使用它来找到这个软件包。请注意，你可以使用单个`install`调用来安装项目中的所有库。

```cmake
install(
  TARGETS my_library
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(some_dependency)
```

上述`Cmake`代码中的操作如下所示：

- `ament_export_targets`宏用于导出CMake的目标。这是为了允许库的客户端使用`target_link_libraries(client PRIVATE my_library::my_library)`语法。如果导出集包括一个库，可以使用`ament_export_targets`的`HAS_LIBRARY_TARGET`选项，将潜在的库添加到环境变量中。
- `ament_export_dependencies`用于将依赖项导出到下游软件包。这是必要的，以便库的使用者不必为这些依赖项调用`find_package`。

| :warning:Warning                                             |
| ------------------------------------------------------------ |
| 从CMake子目录中调用`ament_export_targets`、`ament_export_dependencies`或其他ament命令将不会按预期工作。这是因为CMake子目录无法在调用`ament_package`的父范围中设置必要的变量。 |

| :exclamation:Note                                            |
| ------------------------------------------------------------ |
| Windows DLL文件被视为运行时构件，会安装到RUNTIME DESTINATION文件夹中。因此，建议即使在Unix系统上开发库，也要保留RUNTIME安装设置，以确保在Windows平台上正常运行。 |

- `install`调用中的`EXPORT`标记需要额外的注意：它安装了`my_library`目标的CMake文件。它的名称必须与`ament_export_targets`的参数完全相同。为了确保它可以通过`ament_target_dependencies`使用，它不应该与库的名称完全相同，而应该具有一个前缀，比如"export_"（如上所示）。
- 所有安装路径都是相对于`CMAKE_INSTALL_PREFIX`的，而这个路径已经由colcon/ament正确设置。在ROS2的功能包里，这个`CMAKE_INSTALL_PREFIX`变量一般是工作空间下的`install/${package_name}`下。

还有两个额外的函数可供使用，但对于基于目标的安装来说是多余的：

```cmake
ament_export_include_directories("include/${PROJECT_NAME}")
ament_export_libraries(my_library)
```

第一个宏用于标记导出的包含目录的位置。第二个宏用于标记安装库的位置（这是通过调用`ament_export_targets`中的`HAS_LIBRARY_TARGET`参数完成的）。只有在下游项目不能或不希望使用基于CMake目标的依赖关系时，才应该使用它们。

一些宏可以接受不同类型的参数用于非目标导出，但由于现代Make的推荐方式是使用目标，因此我们不会在这里涵盖它们。这些选项的文档可以在源代码中找到。

#### Executables

在安装可执行文件时，必须严格遵循以下规则，以便ROS工具能够找到它：

```cmake
install(TARGETS my_exe
    DESTINATION lib/${PROJECT_NAME})
```

如果一个软件包既包含库又包含可执行文件，请确保结合上述“库”和“可执行文件”的建议。

## Linting and Testing

为了在colcon中将测试与库的构建分离，可以将所有对代码检查工具和测试的调用包装在条件语句中，例如：

```cmake
if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(<tests>)
endif()
```

### Linting

建议使用[ament_lint_auto](https://github.com/ament/ament_lint/blob/humble/ament_lint_auto/doc/index.rst#ament_lint_auto)提供的组合调用：

```
find_package(ament_lint_auto REQUIRED)
ament_lint_auto_find_test_dependencies()
```

这将按照`package.xml`中定义的方式运行代码检查工具。建议使用由ament_lint_common包定义的一组代码检查工具。包含在其中的各个代码检查工具以及它们的功能可以在[ament_lint_common文档](https://github.com/ament/ament_lint/blob/humble/ament_lint_common/doc/index.rst)中找到。

ament提供的代码检查工具也可以单独添加，而不是运行ament_lint_auto。如何这样做的示例可以在[ament_cmake_lint_cmake文档](https://github.com/ament/ament_lint/blob/humble/ament_cmake_lint_cmake/doc/index.rst)中找到。

### Testing

Ament包含了简化设置GTest的CMake宏。调用如下：

```cmake
find_package(ament_cmake_gtest)
ament_add_gtest(some_test <test_sources>)
```

使用上述命令添加一个GTest。然后它将成为一个常规目标，可以链接到其他库（比如项目库）。这些宏还有额外的参数：

- `APPEND_ENV`: 用于追加环境变量。例如，你可以通过以下方式将路径添加到ament前缀路径中：

  ```cmake
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(some_test <test_sources>
    APPEND_ENV PATH=some/addtional/path/for/testing/resources)
  ```

- `APPEND_LIBRARY_DIRS`: 用于追加库，以便链接器可以在运行时找到它们。这可以通过设置像Windows上的PATH和Linux上的LD_LIBRARY_PATH等环境变量来实现，但这会使调用特定于平台。

- `ENV`: 设置环境变量（与`APPEND_ENV`具有相同的语法）。

- `TIMEOUT`: 设置测试的超时时间（以秒为单位）。对于GTests，默认超时时间为60秒。例如：

  ```cmake
  ament_add_gtest(some_test <test_sources> TIMEOUT 120)
  ```

- SKIP_TEST: 跳过此测试（将在控制台输出中显示为“通过”）`：此命令表示跳过执行特定测试。当使用此命令时，测试将不会运行，但在测试结果中将被报告为“通过”，尽管实际上未执行该测试。这可用于暂时排除测试套件中的某个测试。
- SKIP_LINKING_MAIN_LIBRARIES: 不要链接到 GTest`：此命令表示不要将特定测试或组件链接到名为 GTest 的库。这可能用于排除特定库，可能是出于特定测试目的。GTest通常用作Google Test C++框架，用于编写和运行单元测试。
- `WORKING_DIRECTORY: 设置测试的工作目录`：此命令用于指定测试应在其中执行的工作目录。工作目录是测试进程运行的目录，可以影响测试执行过程中查找文件或资源的位置。明确设置工作目录可确保测试以一致的方式运行并按预期执行。

默认的工作目录是`CMAKE_CURRENT_BINARY_DIR`，这在CMake文档中有描述。

类似地，有一个用于设置GTest和GMock的CMake宏:

```cmake
find_package(ament_cmake_gmock REQUIRED)
ament_add_gmock(some_test <test_sources>)
```

它也有像`ament_add_gtest`一样的额外参数。

## Extending ament

可以使用 `ament_cmake` 注册额外的宏（macros）或函数，并以多种方式扩展它。

### Adding a function/macro to ament

扩展ament通常意味着您希望将某些函数提供给其他软件包。向客户端软件包提供宏的最佳方式是将其注册到ament中。

这可以通过将 `${PROJECT_NAME}_CONFIG_EXTRAS` 变量附加到 `ament_package()` 中来实现。

```cmake
list(APPEND ${PROJECT_NAME}_CONFIG_EXTRAS
  path/to/file.cmake"
  other/pathto/file.cmake"
)
```

另外，您也可以直接将这些文件添加到 `ament_package()` 调用中：

```cmake
ament_package(CONFIG_EXTRAS
  path/to/file.cmake
  other/pathto/file.cmake
)
```

### Adding to extension points

除了包含可以在其他软件包中使用的简单函数的文件外，您还可以向ament添加扩展。这些扩展是通过定义扩展点的函数执行的脚本。ament扩展的最常见用例可能是注册rosidl消息生成器：在编写生成器时，通常希望生成器生成所有消息和服务，而无需修改消息/服务定义软件包的代码。通过将生成器注册为rosidl_generate_interfaces的扩展，可以实现这一点。

有一个例子可供参考：

```cmake
ament_register_extension(
  "rosidl_generate_interfaces"
  "rosidl_generator_cpp"
  "rosidl_generator_cpp_generate_interfaces.cmake")
```

上面展示了如何将名为 `rosidl_generator_cpp_generate_interfaces.cmake` 的宏为 `rosidl_generator_cpp` 软件包注册到 `rosidl_generate_interfaces` 扩展点中。当扩展点被执行时，这将触发脚本 `rosidl_generator_cpp_generate_interfaces.cmake` 的执行。具体而言，这将在函数 `rosidl_generate_interfaces` 被执行时调用生成器。

除了 `rosidl_generate_interfaces` 之外，对于生成器来说，最重要的扩展点之一是 `ament_package`，它将在 `ament_package()` 调用时执行脚本。这个扩展点在注册资源时非常有用（请参见下文）。

`ament_register_extension` 是一个函数，它接受正好三个参数：

- `extension_point`：扩展点的名称（通常是 `ament_package` 或 `rosidl_generate_interfaces` 中的一个）。扩展点是一个用于执行自定义脚本或操作的位置，它通常与特定的构建或配置步骤相关联。
- `package_name`：包含CMake文件的软件包的名称（即，CMake文件所在的项目的项目名称）。这是指定包含扩展脚本的软件包的名称，以便确定在哪个软件包中注册了扩展。
- `cmake_filename`：当扩展点执行时要运行的CMake文件的名称。这是要执行的自定义脚本的文件名，它通常包含了具体的定制逻辑，以在特定情况下执行自定义操作。

| :exclamation:Note                                            |
| ------------------------------------------------------------ |
| 可以以类似的方式定义自定义扩展点，就像 `ament_package` 和 `rosidl_generate_interfaces` 一样，但这通常是不必要的。 |

### Adding extension points

很少情况下，可能有兴趣定义一个新的ament扩展点。

扩展点可以在宏中注册，以便在调用相应的宏时执行所有扩展。要实现这一点，可以采取以下步骤：

- 为你的扩展定义并命名一个名称（例如，`my_extension_point`），这个名称将在使用扩展点时传递给 `ament_register_extension` 宏。

- 在应该执行扩展的宏或函数中调用：

  ```cmake
  ament_execute_extensions(my_extension_point)
  ```

Ament扩展通过定义一个变量来工作，该变量包含扩展点的名称，并用要执行的宏填充它。在调用`ament_execute_extensions`时，变量中定义的脚本将依次执行。

## Adding resources

特别是在开发插件或允许插件的软件包时，通常需要从一个ROS软件包中向另一个软件包（例如插件）添加资源。示例可以是用于使用pluginlib的工具的插件。

这可以通过ament index(ament 索引)来实现(也称为资源索引“resource index”)。

### The ament index explained

对于设计的细节和目的，可以参考[这里](https://github.com/ament/ament_cmake/blob/humble/ament_cmake_core/doc/resource_index.md)。

原则上，Ament索引包含在您的软件包的install/share文件夹中的一个子文件夹中。它包含以不同类型的资源命名的浅层子文件夹。在子文件夹中，每个提供该资源的软件包都通过一个名为“标记文件”的名称进行引用。该文件可以包含获取资源所需的任何内容，例如资源的安装目录的相对路径，也可以为空文件。

举个例子，考虑为RViz提供显示插件：在名为`my_rviz_displays`的项目中提供RViz插件，这些插件将被`pluginlib`读取。您将提供一个名为`plugin_description.xml`的文件，该文件将被安装并由`pluginlib`用于加载插件。为实现这一点，`plugin_description.xml`会通过资源索引进行注册，如下所示：

```cmake
pluginlib_export_plugin_description_file(rviz_common plugins_description.xml)
```

当运行`colcon build`时，会将一个名为`my_rviz_displays`的文件安装到`resource_index`的`rviz_common__pluginlib__plugin`子文件夹中。`rviz_common`内部的`pluginlib`工厂会知道从所有名为`rviz_common__pluginlib__plugin`的文件夹中获取来自导出插件的软件包的信息。`pluginlib`工厂的标记文件包含了指向`plugins_description.xml`文件的相对安装路径（以及库的名称作为标记文件名称）。有了这些信息，`pluginlib`可以加载库，并从`plugins_description.xml`文件中知道要加载哪些插件。

作为第二个示例，考虑让您自己的RViz插件使用自定义的网格模型的可能性。网格模型在启动时被加载，这样插件所有者就不必自行处理加载，但这意味着RViz必须知道这些网格模型。为了实现这一点，RViz提供了一个函数：

```cmake
register_rviz_ogre_media_exports(DIRECTORIES <my_dirs>)
```

这将把这些目录注册为ament索引中的ogre_media资源。简而言之，它会安装一个以项目名称命名的文件，该文件调用函数并存储在名为rviz_ogre_media_exports的子文件夹中。该文件包含宏中列出的目录的安装文件夹相对路径。在启动时，RViz现在可以搜索所有名为rviz_ogre_media_exports的文件夹，并加载所有提供的文件夹中的资源。这些搜索是使用ament_index_cpp（或ament_index_py用于Python包）执行的。

在接下来的几节中，我们将探讨如何将您自己的资源添加到ament索引，并提供最佳实践方法以完成这一操作。

### Querying the ament index

如有必要，可以通过CMake查询ament索引中的资源。为此，有三个函数可供使用：

1、`ament_index_has_resource`：如果资源存在，获取资源的前缀路径，参数如下：

- `var`：这是一个输出参数，如果资源不存在，将其设置为FALSE，否则设置为资源的前缀路径。
- `resource_type`：资源的类型（例如`rviz_common__pluginlib__plugin`）。
- `resource_name`：资源的名称，通常等同于添加了资源的类型`resource_type`的软件包的名称（例如`rviz_default_plugins`）。

`ament_index_get_resource`函数用于获取特定资源的内容，即ament索引中标记文件的内容。这个函数的作用是检索资源文件中存储的信息。资源文件通常包含有关软件包或项目的信息，例如插件、可执行文件或其他数据文件的位置或标识。

2、`ament_index_get_resource`函数具有以下参数：

- `var`：这是一个输出参数，如果资源存在，将包含资源标记文件的内容。
- `resource_type`：资源的类型（例如`rviz_common__pluginlib__plugin`）。
- `resource_name`：资源的名称，通常等同于添加了资源的类型`resource_type`的软件包的名称（例如`rviz_default_plugins`）。
- `PREFIX_PATH`：要搜索的前缀路径，通常使用默认的`ament_index_get_prefix_path()`就足够了。

这个函数允许您获取特定资源标记文件的内容，这个内容通常包含了与该资源相关的信息，例如资源的位置或标识。通过提供正确的`resource_type`、`resource_name`和前缀路径，您可以检索ament索引中的资源信息以便在项目中使用。

请注意，如果资源不存在，`ament_index_get_resource`函数将引发错误。因此，在使用该函数之前，可能需要使用`ament_index_has_resource`函数进行检查，以确保资源存在。

3、`ament_index_get_resources`函数用于获取从索引中注册了特定类型资源的所有软件包。这个函数的目的是获取所有提供了特定类型资源的软件包的列表。

`ament_index_get_resources`函数有以下参数：

- `var`：这是一个输出参数，将包含所有注册了特定类型资源的软件包名称列表。
- `resource_type`：资源的类型（例如`rviz_common__pluginlib__plugin`）。
- `PREFIX_PATH`：要搜索的前缀路径，通常使用默认的`ament_index_get_prefix_path()`就足够了。

这个函数允许您获取所有注册了特定类型资源的软件包的名称列表。这对于在项目中需要了解提供了特定资源类型的软件包有多有用，以便进行相关的配置或其他操作。

### Adding to the ament index

定义一个资源需要两个关键信息：

- 资源的名称：资源的名称必须是唯一的，用于标识和引用该资源。资源名称用于在索引中查找和访问资源，因此每个资源必须有一个独一无二的名称。
- 标记文件的布局：资源的标记文件布局是一个文件，其中包含与资源相关的信息，这些信息可以是任何内容，甚至可以为空。这是因为不同类型的资源可能需要不同的信息，有些资源类型可能不需要额外的信息，因此它们的标记文件可以为空。例如，在ROS 2中，"package"资源用于标记ROS 2软件包，通常不需要附加信息，因此其标记文件可以为空。标记文件的布局取决于资源的类型和用途，它通常包含有关资源的位置、标识或其他相关信息。标记文件的布局是与资源类型和用途相关的，不同类型的资源可能有不同的标记文件布局。

对于RViz的网格资源，相应的选择通常包括以下内容：

- `rviz_ogre_media_exports`作为资源的名称。
- 安装路径相对于包含资源的所有文件夹的相对路径。这将使您能够编写使用包中相应资源的逻辑。

为了让用户轻松地为您的包注册资源，您应该提供宏或函数，例如`pluginlib`函数或`rviz_ogre_media_exports`函数。

要注册一个资源，使用ament函数`ament_index_register_resource`。这将创建并安装资源索引中的标记文件。例如，对于`rviz_ogre_media_exports`，相应的调用如下所示：

```cmake
ament_index_register_resource(rviz_ogre_media_exports CONTENT ${OGRE_MEDIA_RESOURCE_FILE})
```

这个操作会将一个名为`${PROJECT_NAME}`的文件安装到`resource_index`中的`rviz_ogre_media_exports`文件夹中，该文件的内容由`${OGRE_MEDIA_RESOURCE_FILE}`变量提供。这个宏有一些有用的参数，可以用于定制注册资源的行为:

- 未命名的第一个参数：这是资源的名称，它相当于`resource_index`中的文件夹名称。这个名称决定了资源将被放在哪个目录中。
- `CONTENT`：这个参数用于指定标记文件的内容，通常是一个字符串，可以包含相对路径等信息。这个参数用于定义标记文件的内容。`CONTENT`不能与`CONTENT_FILE`同时使用。
- `CONTENT_FILE`：这个参数指定了创建标记文件所需的文件的路径。这可以是一个普通文件，也可以是一个通过`configure_file()`扩展的模板文件。使用`CONTENT_FILE`允许您从现有文件中获取标记文件的内容。`CONTENT_FILE`不能与`CONTENT`同时使用。
- `PACKAGE_NAME`：这是导出资源的包或库的名称，它相当于标记文件的名称。默认情况下，它会设置为`${PROJECT_NAME}`，即您的ROS包的名称。
- `AMENT_INDEX_BINARY_DIR`：这是生成的ament索引的基本路径。通常，建议使用默认值`${CMAKE_BINARY_DIR}/ament_cmake_index`，除非有特殊需求。
- `SKIP_INSTALL`：如果将其设置为true，将跳过安装标记文件的步骤。这在某些情况下可能有用，例如在构建和测试阶段，不需要实际安装资源。

每个包通常只有一个标记文件，因此如果同一个项目多次调用CMake函数/宏来注册资源，可能会引发问题。这是因为每个资源注册会尝试创建并安装一个标记文件，但只能存在一个标记文件。对于大型项目，最好将资源注册的调用拆分为多个步骤或在不同的构建目标之间进行处理，以确保不会重复注册相同的资源。

因此，最佳实践是让一个注册资源的宏，比如`register_rviz_ogre_media_exports.cmake`，只填充一些变量。然后，实际的`ament_index_register_resource`调用可以在`ament_package`的ament扩展内添加。由于每个项目只能有一个对`ament_package`的调用，因此资源只会在一个地方进行注册。对于`rviz_ogre_media_exports`，这可以采用以下策略：

- `register_rviz_ogre_media_exports`宏接受一个文件夹列表，将它们附加到名为`OGRE_MEDIA_RESOURCE_FILE`的变量中。这个变量用于存储资源的路径信息。

- 另一个名为`register_rviz_ogre_media_exports_hook`的宏会检查`${OGRE_MEDIA_RESOURCE_FILE}`是否非空，如果非空，则调用`ament_index_register_resource`来注册这些资源。

- 创建一个名为`register_rviz_ogre_media_exports_hook-extras.cmake`的第三方CMake文件，将`register_rviz_ogre_media_exports_hook.cmake`文件注册为ament扩展，以确保它会在项目构建期间被调用。这可以通过在CMake中添加类似以下的代码来完成：

  ```cmake
  ament_register_extension("ament_package" "rviz_rendering"
    "register_rviz_ogre_media_exports_hook.cmake")
  ```

- 文件`register_rviz_ogre_media_exports.cmake`和`register_rviz_ogre_media_exports_hook-extra.cmake`被注册为`ament_package()`的`CONFIG_EXTRA`部分。

这是一种常见的做法，用于将额外的配置信息和CMake脚本包含到ament构建过程中。通过将这些文件注册为`CONFIG_EXTRA`，它们将在ament构建系统的上下文中执行，以实现资源的注册和其他自定义配置。
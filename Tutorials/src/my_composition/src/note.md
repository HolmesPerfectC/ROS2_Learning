## 函数说明

1. std::bind用来绑定函数，其中会使用占位符std::placeholders。
2. std::make_unique用来创建独立智能指针。
3. std::move用来转移变量所有权。使用时应该包含C++的utility头文件。





## CmakeList说明

### 环境设置

**find_package**---用于找到编译所需的功能包

**include_directories**---用于包含include目录

**set**---设置了一个变量



### 添加组件：

1. 添加目标，组件一般以共享库形式添加，例如：

   ```add_library(my_listener_component SHARED src/my_listener_component.cpp)```

   这里`my_listener_component`是库的名称，`SHARED`关键字用于指明要创建的库的类型，这里是共享库，方便组件可以在运行中加载到内存里。`src/my_listener_component.cpp`是代码文件位置，这里是在`src`目录下的`my_listener_component.cpp`文件。

2. ```target_compile_definitions(my_listener_component PRIVATE "MYCOMPOSITION_BUILDING_DLL")```

   这一段cmake命令为`my_listener_component`设置编译定义。编译定义是一种编译时的指令，用于控制编译过程中的条件编译（conditional compilation）以及在代码中添加特定的宏或标志。这里定义一个`MYCOMPOSITION_BUILDING_DLL`的宏，并将这个宏设置为`my_listener_component`的私有编译定义。

3. 为目标添加依赖。

   ```cmake
   ament_target_dependencies(my_listener_component 
       “rclcpp”
       "rclcpp_components"
       "std_msgs")
   ```

   这里`my_listener_component`有三个依赖，分别是`rclcpp`、`rclcpp_components`、`std_msgs`。

4. 注册节点组件。

   ```camke
   rclcpp_components_register_nodes(my_listener_component "my_composition::MyListener")
   ```

   将`my_listener_component`库注册为一个ROS节点组件，名字为`my_composition::MyListener`。

5. 使用`install`命令将指定的目标安装到文件系统中的目录中。

   ```cmake
   install(TARGETS
     my_listener_component
     ARCHIVE DESTINATION lib
     LIBRARY DESTINATION lib
     RUNTIME DESTINATION bin)
   ```

   这里将`my_listener_component`库安装到三个目录中，一般`ARCHIVE DESTINATION lib`存放静态库，`LIBRARY DESTINATION lib`存放动态库，`RUNTIME DESTINATION bin`存放可执行文件。




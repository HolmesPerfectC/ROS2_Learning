## 说明

请按照[鱼香ros的视频](https://www.bilibili.com/video/BV1gr4y1Q7j5/?spm_id_from=333.337.search-card.all.click&vd_source=dc1a673912bb920f8b728d4d19c5f88b)进行ros2基础学习。

## 使用说明

确保当前路径在town_ws目录下。

1. 进行编译。

   ```
   colcon build
   ```

2. 使用`source`命令加载环境变量。

   ```shell
   source install/setup.bahs
   ```

3. 使用`ros2 run`命令运行对应的功能包，以`li4_node`为例，例如：

   ```shell
   ros2 run village_li li4_node
   ```

## src

src里是各源代码文件。


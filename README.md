# 智元 G2 开发

智元 G2 机器人开发：GDK 接入、感知、运动控制、仿真与任务应用。

## GDK v2.6.3 开发文档

官方文档：[机器人开发套件 GDK v2.6.3](https://support.agibot.com/?gdk_version=2.6.3)。

本 README 汇集用户提供的正文和接口附件，去除重复的网页导航，按内容分组供本地查阅。ROS2 Camera Compress 使用用户后续补充的版本。全部收录内容直接保存在本 README，不依赖聊天记录即可查阅。尚未完成与官网所有章节的完整性核对，本页不将未收录内容判定为用户未提供。

### 阅读索引

- [概览、部署、工具和 ROS2 文档](#usage-and-ros2)：包含主页介绍、C++/ROS 快速开始、混合部署、TF 概念、部署、时间同步、ROS2 使用、关节控制工具、Web 相机查看器、C++ Common，以及 ROS2 IMU、Camera、Camera Compress、Control。
- [C++ IMU](#cpp-imu)
- [C++ Camera](#cpp-camera)
- [C++ TF](#cpp-tf)
- [C++ Robot](#cpp-robot)
- [C++ PNC](#cpp-pnc)

<a id="usage-and-ros2"></a>

## 概览、部署、工具和 ROS2 文档

GDK（Genie Development Kit）是为Genie机器人及其相关产品提供的开发工具包。它的主要作用是为用户和开发者提供丰富的二次开发接口，方便用户根据自身需求快速实现机器人在移动、感知、操作等方面的定制化功能。

通过GDK，用户可以：

- 快速集成和调用机器人的底层控制能力，如运动控制、传感器数据获取、任务调度等；
- 利用C++、Python、ROS2等多种主流开发语言进行开发，满足不同开发者的技术栈需求；
- 实现机器人与外部系统的高效对接，比如与VR、仿真、云端等模块的集成；
- 便捷地进行算法验证、功能扩展和系统集成，加速产品落地和迭代。

GDK适用于教育、科研、工业、服务等多种场景，是机器人开发者和行业用户提升开发效率、降低开发门槛的重要工具。

#### 示例场景

以下是GDK可能用到的一些典型场景：

- **教育与科研**：高校、研究机构可利用GDK快速搭建机器人实验平台，进行算法验证、课程教学、学术研究等。
- **工业自动化**：在工厂、仓储等场景下，开发者可基于GDK实现机器人自动搬运、巡检、分拣等功能。
- **服务机器人**：如酒店、医院、商场等公共场所的服务机器人，通过GDK实现定制化的人机交互、导航、物品递送等。
- **智能家居**：家庭服务机器人可通过GDK集成语音、视觉等多模态感知，实现智能清扫、安防巡逻等。
- **多机器人协作**：GDK支持多机器人系统的开发，便于实现机器人之间的协同作业、信息共享与任务分配。
- **感知与导航算法开发**：开发者可基于GDK快速接入传感器数据，进行SLAM、目标检测、路径规划等算法的开发与测试。
- **远程运维与监控**：通过GDK实现机器人远程控制、状态监测、故障诊断和远程升级。
- **二次开发与系统集成**：企业或个人可基于GDK进行功能扩展，将机器人与云平台、物联网、第三方系统无缝集成。

这些场景仅为部分示例，GDK的灵活性和开放性使其能够适应更多创新应用场景，助力机器人行业的快速发展。

---


### 安装GDK

将开发机与G02机器人通过网线直连，配置开发机的静态IP为10.42.1.102。确保ping 10.42.1.101通信正常。

在开发机环境安装GDK依赖：
```
curl -sSL http://10.42.1.101:8849/install.sh | bash
```

### 通过CMakeLists编译

安装cmake
```
sudo apt install cmake
```

编译
```ruby
cd ~/.cache/agibot/app/gdk/examples/cpp
cmake -B build
make -C build
```

### 运行机器人运控示例
```bash
source ~/.cache/agibot/app/env.sh
./build/mc_example joint_name1 pos1 joint_name2 pos2 ...
```

joint\_name为机器人关节名称，pos为关节目标位置，单位为弧度。

joint\_name列表如下：
```bash
"idx01_body_joint1", #腰部五自由度（从底部往上）
"idx02_body_joint2",
"idx03_body_joint3",
"idx04_body_joint4",
"idx05_body_joint5",
"idx11_head_joint1", #头部三自由度（r,p,y）
"idx13_head_joint3",
"idx12_head_joint2",
"idx21_arm_l_joint1", #左手臂七自由度（从肩部往下）
"idx22_arm_l_joint2",
"idx23_arm_l_joint3",
"idx24_arm_l_joint4",
"idx25_arm_l_joint5",
"idx26_arm_l_joint6",
"idx27_arm_l_joint7",
"idx61_arm_r_joint1", #右手臂七自由度（从肩部往下）
"idx62_arm_r_joint2",
"idx63_arm_r_joint3",
"idx64_arm_r_joint4",
"idx65_arm_r_joint5",
"idx66_arm_r_joint6",
"idx67_arm_r_joint7",
```


### 安装

将开发机与G02机器人通过网线直连，配置开发机的静态IP为10.42.1.102。确保ping 10.42.1.101通信正常。

在开发机环境安装GDK依赖：
```
curl -sSL http://10.42.1.101:8849/install.sh | bash
```

### 编译
```shell
cd <your_workspace>
cp -r ~/.cache/agibot/app/gdk/build_dep/ros/genie_msgs ./
colcon build
```

### 运行示例
```shell
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_controller
ros2 launch gdk_controller controller.launch.py
```

可订阅/hal/joint\_state话题查看机器人关节状态。
```shell
#新建终端
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_controller

ros2 topic list
#ros2 topic hz /hal/joint_state #查看发布频率
#ros2 topic echo /hal/joint_state #查看关节状态
```


## 混合部署

为了方便用户迭代，GDK支持混合部署的开发形式，即用户在自己的开发机上部署GDK依赖，然后可以使用GDK的接口和工具去开发应用。比如用户在算力较强的台式机上部署了具身模型，通过具身模型控制机器人的运动。

混合部署需要将机器人和开发机用网线直连，并给开发机设置静态IP，使开发机和机器人之间可以通信。

G02的调试IP如下：

| **机器人型号IP地址开发机地址** |             |             |
| ------------------ | ----------- | ----------- |
| G02                | 10.42.1.101 | 10.42.1.102 |

## TF (Transform) 坐标变换

### 什么是TF

TF即transform，坐标转换。GDK中，TF(transform)模块提供各个坐标系之间的转换关系。包含机器人上各个坐标系之间的转换关系以及各传感器之间的转换关系。
### 环境要求

#### 硬件需求

- 符合ISO/IEC 11801：2002和EIA/TIA 568B或ISO/IEC 11801:2002和EIA/TIA 568-B.2-1标准的网线
- 开发机（Ubuntu22.04，x86\_64，Intel i9及以上性能CPU）

#### 网络配置

使用网线连接G2接口面板的Debug网口和开发机网口，然后给开发机的网卡配置静态IP：
```
IP：10.42.1.xxx(10.42.1.10~10.42.1.99)
MASK：255.255.255.0
```

在开发机上验证与G2的通信是否正常：
```
ping 10.42.1.101
```

### 安装GDK

#### 混合部署

在开发机执行以下命令安装GDK：
```
curl -sSL http://10.42.1.101:8849/install.sh | bash
```

### 获取示例代码

#### 从G2上获取示例代码压缩包
```
curl -sSL http://10.42.1.101:8849/install_example.sh | bash
```

该示例文件夹主要包含运控控制，相机图像，传感器数据读取等示例demo，涉及C++、Python、ROS三种编程语言。

#### 文件夹结构
```
├── cpp
│   ├── CMakeLists.txt
│   └── src
├── python
│   ├── camera_demo.py
│   ├── camera_web_viewer.py
│   ├── imu_demo.py
│   ├── lidar_demo.py
│   ├── mc_example.py
│   ├── move_chassis.py
│   ├── pnc_example.py
│   ├── robot_demo.py
│   ├── slam_demo.py
│   ├── uss_demo.py
│   ├── proto
│   └── saved_commands
└── ros
  ├── camera_example
  └── control_example

```


## PTP 时间同步配置指南

### 概述

PTP（Precision Time Protocol，精确时间协议）是一种用于在计算机网络中同步时钟的协议，可以实现纳秒级的时间同步精度。GDK 提供了两个脚本用于在端侧（机器人端）和用户侧（客户端）之间建立 PTP 时间同步。

### 使用场景

- **多传感器数据融合**：需要精确时间戳对齐多个传感器数据
- **分布式系统同步**：多个设备需要高精度时间同步
- **实时控制系统**：需要纳秒级时间精度的控制应用
- **数据采集与分析**：需要精确时间戳的数据采集场景

### 前置要求

#### 用户侧（客户端）要求

- 网卡 IP 地址为 `10.42.1.*` 网段
- 具有 PTP 硬件时钟设备（`/dev/ptp*`）
- 已安装 `linuxptp` 工具包
- 需要 root 权限执行脚本

### 使用步骤

#### 1. 在端侧（机器人端）执行服务器脚本

首先在机器人端执行 `ptp_server.sh` 脚本：
```bash
cd /home/agi/app/gdk/scripts
sudo chmod +x ptp_server.sh
sudo ./ptp_server.sh
```

#### 2. 在用户侧（客户端）执行客户端脚本

保持机器人端ptp\_server.sh运行，在客户端机器上(不要在容器内运行)执行 `ptp_client.sh` 脚本：
```bash
cd ~/.cache/agibot/app/gdk/scripts
sudo chmod +x ptp_client.sh
sudo ./ptp_client.sh
```

**重要**：客户端脚本需要 root 权限，必须使用 `sudo` 执行。

### 注意事项

- **同步精度**：当前软件时间戳版本在同步完后可以达到10ms以内的延迟，同步完成后ptp\_client.sh自动退出,ptp\_server.sh需要手动停止
- **同步失败处理**：若延时过大，请重新进行同步
- **时间漂移**：同步完后误差会随着时间逐渐变大，一小时内会变到50ms
- **Lidar延迟**：lidar延迟机内机外都在100ms左右
- **传感器延迟**：调用传感器延迟接口前，需要先进行时间同步，否则延迟统计结果不准确  # GDK ROS2 humble版本使用说明
Genie 02使用高性能的DDS，默认不发送ROS2消息。如需使用ROS2，需要启动GDK的ROS2转发节点。 GDK在部署时会同时安装自定义的ROS消息，用户编译GDK自定义消息后即可使用ROS2来接收/发送GDK的消息。
### 启动转发节点来获取消息
#### 查看消息（以运控节点为例）
##### 启动controller的ROS转发节点
```ruby
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_controller
ros2 launch gdk_controller controller.launch.py

```
##### 声明ros环境变量
新打开一个终端，在终端中声明环境变量
```ruby
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_controller

```
##### 查看节点消息
```bash
ros2 topic list # 查看当前所有topic
ros2 topic echo /hal/joint_state  # 读取topic数据
ros2 topic hz /hal/joint_state # 读取发送频率

```
### 编写程序（以控制关节为例）
#### 引入需要用到的genie\_msg消息头文件
```cpp
#include "genie_msgs/msg/joint_position_requst.hpp"
#include "genie_msgs/msg/joint_state.hpp"

```
#### 创建/hal/joint\_state消息的subscriber获取机器人当前所有关节名称、关节角度、速度等信息
```cpp
sub_joint_ = this->create_subscription<genie_msgs::msg::JointState>(
            "/hal/joint_state",
            10,
            std::bind(&ControlExampleNode::joint_state_callback, this, std::placeholders::_1)
);

```
#### 创建/MotionControlService/JointPosition/request消息的publisher
```ini
pub_joint_position_ = create_publisher<genie_msgs::msg::JointPositionRequst>("/MotionControlService/JointPosition/request", 10);

```
#### 设置uuid
gdk的控制命令需要设置uuid来唯一标识，你可以通过以下方法来创建uuid
```cpp
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
inline std::string generate_uuid_boost()
{
    boost::uuids::random_generator gen;
    return boost::uuids::to_string(gen());
}

```
#### 设置控制命令并发布，即可控制对应的关节
```rust
genie_msgs::msg::JointPositionRequst request;
request.lifetime = 1.0;
request.joint_names = joint_names_;
request.joint_positions = target_positions;
request.joint_velocities = {velocity_};
request.uuid = generate_uuid_boost();
pub_joint_position_->publish(request);

```
### 获取genie\_msgs消息包并编译
#### 从部署包中获取编译需要用到的genie\_msgs消息包到工作空间并编译
```ruby
cd <your_workspace>
cp -r ~/.cache/agibot/app/gdk/build_dep/ros/genie_msgs ./
colcon build

```
### 运行程序
```bash
cd <your_workspace>
source install/setup.bash
ros2 launch <your_pkg> <your_launch>

```


## 关节控制工具 (mc\_example.py)

`mc_example.py` 是一个交互式的关节位置控制工具，可以通过键盘实时控制机器人关节位置，并支持播放预录制的动作序列。

### 功能特性

- 交互式键盘控制关节位置
- 支持所有22个关节的控制
- 播放预录制的动作序列
- 实时查看关节状态
- 支持多个动作文件切换

### 安装要求

在使用此工具前，请确保：

1. 已安装 GDK Python 包
2. 已配置好机器人连接（混合部署或机内部署）
3. 已准备好动作序列文件（JSON格式）

### 使用方法

#### 1. 准备动作序列文件

工具会从 `saved_commands/` 目录读取 JSON 格式的动作序列文件。确保该目录存在并包含动作文件：
```bash
cd ~/.cache/agibot/app/gdk/examples/python
mkdir -p saved_commands
```

动作序列文件格式示例：
```json
{
"recorded_commands": [
  {
    "joint_names": ["idx21_arm_l_joint1", "idx22_arm_l_joint2"],
    "joint_positions": [0.5, -0.3]
  },
  {
    "joint_names": ["idx21_arm_l_joint1", "idx22_arm_l_joint2"],
    "joint_positions": [0.8, -0.5]
  }
]
}
```

#### 2. 运行工具
```bash
cd ~/.cache/agibot/app/gdk/examples/python
source ~/.cache/agibot/app/env.sh
python3 mc_example.py
```

#### 3. 键盘控制

工具启动后，使用以下键盘按键进行控制：

| **按键功能**  |                   |
| --------- | ----------------- |
| `w` / `W` | 当前关节正向移动（+0.1 弧度） |
| `s` / `S` | 当前关节负向移动（-0.1 弧度） |
| `a` / `A` | 切换到上一个关节          |
| `d` / `D` | 切换到下一个关节          |
| `p` / `P` | 播放当前动作序列的下一帧      |
| `m` / `M` | 切换到下一个动作文件        |
| `q` / `Q` | 退出程序              |

#### 4. 支持的关节列表

工具支持控制以下22个关节：

**腰部关节（5个）：**

- `idx01_body_joint1` - 腰部关节1
- `idx02_body_joint2` - 腰部关节2
- `idx03_body_joint3` - 腰部关节3
- `idx04_body_joint4` - 腰部关节4
- `idx05_body_joint5` - 腰部关节5

**头部关节（3个）：**

- `idx11_head_joint1` - 头部关节1
- `idx12_head_joint2` - 头部关节2
- `idx13_head_joint3` - 头部关节3

**左手臂关节（7个）：**

- `idx21_arm_l_joint1` - 左手臂关节1
- `idx22_arm_l_joint2` - 左手臂关节2
- `idx23_arm_l_joint3` - 左手臂关节3
- `idx24_arm_l_joint4` - 左手臂关节4
- `idx25_arm_l_joint5` - 左手臂关节5
- `idx26_arm_l_joint6` - 左手臂关节6
- `idx27_arm_l_joint7` - 左手臂关节7

**右手臂关节（7个）：**

- `idx61_arm_r_joint1` - 右手臂关节1
- `idx62_arm_r_joint2` - 右手臂关节2
- `idx63_arm_r_joint3` - 右手臂关节3
- `idx64_arm_r_joint4` - 右手臂关节4
- `idx65_arm_r_joint5` - 右手臂关节5
- `idx66_arm_r_joint6` - 右手臂关节6
- `idx67_arm_r_joint7` - 右手臂关节7

### 配置参数

可以在代码中修改以下参数：

- `_step`: 每次按键移动的步长（默认：0.1 弧度）
- `_speed`: 关节运动速度（默认：0.3）

### 使用示例

#### 示例1：控制单个关节

1. 运行程序
2. 使用 `a`/`d` 键选择要控制的关节（例如：`idx21_arm_l_joint1`）
3. 使用 `w`/`s` 键调整关节位置
4. 观察机器人关节运动

#### 示例2：播放动作序列

1. 准备动作序列文件并放在 `saved_commands/` 目录
2. 运行程序
3. 使用 `m` 键切换到要播放的动作文件
4. 按 `p` 键逐帧播放动作序列
5. 连续按 `p` 键可以播放完整动作

### 注意事项

**安全提示：**

- 使用前请确保机器人周围有足够的空间
- 注意关节的运动范围，避免超出限位
- 建议先在小幅度范围内测试
- 紧急情况下按 `q` 键退出程序

**使用限制：**

- 工具需要从 `saved_commands/` 目录读取 JSON 文件，如果目录为空或文件格式错误，程序会报错
- 动作序列文件必须是有效的 JSON 格式
- 确保机器人已正确连接并初始化  # Web相机查看器 (camera\_web\_viewer.py)
`camera_web_viewer.py` 是一个基于 Web 的相机图像查看工具，可以在浏览器中实时查看机器人所有相机的图像画面，支持多相机同时显示。
### 功能特性
- Web 界面，无需安装客户端
- 支持多相机同时显示（最多9个相机）
- 自动检测可用相机
- 实时图像刷新（10fps）
- 智能缓存机制，减少重复处理
- 支持多种图像格式（JPEG、PNG、未压缩RGB/BGR/灰度、深度图）
- 深度相机伪彩色显示
- 显示相机信息（尺寸、帧率）
### 安装要求
#### 必需依赖
- Python 3.10+
- GDK Python 包 (`agibot_gdk`)
- Flask（用于 Web 服务器）
#### 可选依赖
- OpenCV（推荐，用于图像处理和优化）
- NumPy（推荐，用于图像数据处理）
#### 安装依赖
```bash
# 安装 Flask
pip install flask

# 安装 OpenCV（推荐）
pip install opencv-python

# 安装 NumPy（通常随 OpenCV 一起安装）
pip install numpy

```
### 使用方法
#### 1. 运行工具
```bash
cd ~/.cache/agibot/app/gdk/examples/python
source ~/.cache/agibot/app/env.sh
python3 camera_web_viewer.py

```
#### 2. 访问 Web 界面
工具启动后，会在终端显示访问地址：
```
访问地址: http://0.0.0.0:5000

```
在浏览器中打开该地址即可查看相机画面。
#### 3. 支持的相机类型
工具支持以下9种相机类型：
1. **头部后视鱼眼相机** (`kHeadBackFisheye`)
2. **头部左侧鱼眼相机** (`kHeadLeftFisheye`)
3. **头部右侧鱼眼相机** (`kHeadRightFisheye`)
4. **头部双目左相机** (`kHeadStereoLeft`)
5. **头部双目右相机** (`kHeadStereoRight`)
6. **左手彩色相机** (`kHandLeftColor`)
7. **右手彩色相机** (`kHandRightColor`)
8. **头部深度相机** (`kHeadDepth`)
9. **头部彩色相机** (`kHeadColor`)
#### 4. 功能说明
##### 自动检测可用相机
工具会自动检测哪些相机可用，只显示可用的相机画面。如果某个相机不可用，不会在界面上显示。
##### 实时图像刷新
- 所有可用相机的图像每 100ms 自动刷新一次（10fps）
- 使用智能缓存机制，避免重复处理相同帧
- 显示处理统计信息（新帧数、缓存数、错误数）
##### 相机信息显示
每个相机卡片显示：
- 相机名称
- 图像尺寸（宽 x 高）
- 实时帧率（FPS）
##### 深度相机特殊处理
深度相机会自动进行以下处理：
- 深度值归一化到 0-255 范围
- 应用伪彩色映射（JET 色彩方案）
- 显示深度范围信息（最小/最大深度值）
### 配置选项
#### 修改服务器地址和端口
在代码中修改 `WebCameraViewer` 的初始化参数：
```python
viewer = WebCameraViewer(host='0.0.0.0', port=5000)

```
- `host`: 服务器监听地址（默认：`0.0.0.0`，允许外部访问）
- `port`: 服务器端口（默认：`5000`）
#### 修改图像质量
在 `image_to_base64()` 方法中修改 `quality` 参数：
```python
image_b64 = self.image_to_base64(decoded_image, quality=75)

```
- 范围：1-100
- 默认：75
- 值越大，图像质量越高，但文件也越大
#### 修改刷新频率
在 HTML 模板中修改 `setInterval` 的时间间隔：
```javascript
// 每100ms更新一次（10fps）
setInterval(updateAllImages, 100);

```
### 使用示例
#### 示例1：本地访问
```bash
# 运行工具
python3 camera_web_viewer.py

# 在浏览器中打开
# http://localhost:5000

```
#### 示例2：远程访问
```bash
# 运行工具（监听所有网络接口）
python3 camera_web_viewer.py

# 在其他设备上访问
# http://<机器人IP>:5000

```
#### 示例3：自定义端口
修改代码中的端口号：
```python
viewer = WebCameraViewer(host='0.0.0.0', port=8080)

```
然后访问：`http://localhost:8080`

  # GDK Common 接口文档（C++）
### 概述
Common（通用）模块为G02机器人提供了GDK系统的初始化和释放功能。通过C++接口，开发者可以方便地管理GDK系统的生命周期，确保系统正确启动和资源正确释放。
### 接口说明
#### 全局函数
##### 1. `GDKInit()`
- **功能**：初始化GDK系统
- **参数**：无
- **返回值**：`GDKRes`，操作结果状态码
  - `GDKRes::kSuccess`：初始化成功
  - 其他值：初始化失败
- **说明**：
  - 必须在调用其他GDK功能之前调用此函数
  - 初始化GDK内部系统、DDS连接、配置管理等
  - 建议在程序开始时调用一次
- **示例**：
  ```cpp
  #include <iostream>
  #include "gdk/gdk.h"

  int main() {
      // 初始化GDK系统
      agibot::gdk::GDKRes init_result = agibot::gdk::GDKInit();

      if (init_result != agibot::gdk::GDKRes::kSuccess) {
          std::cout << "GDK初始化失败: " << static_cast<int>(init_result) << std::endl;
          return -1;
      }

      std::cout << "GDK初始化成功" << std::endl;

      // 使用GDK功能...

      return 0;
  }

  ```
##### 2. `GDKRelease()`
- **功能**：释放GDK系统资源
- **参数**：无
- **返回值**：`GDKRes`，操作结果状态码
  - `GDKRes::kSuccess`：释放成功
  - 其他值：释放失败
- **说明**：
  - 在程序结束前调用此函数释放GDK系统资源
  - 清理DDS连接、关闭文件句柄、释放内存等
  - 建议在程序退出前调用一次
- **示例**：
  ```cpp
  #include <iostream>
  #include "gdk/gdk.h"

  int main() {
      // 初始化GDK系统
      agibot::gdk::GDKRes init_result = agibot::gdk::GDKInit();

      if (init_result != agibot::gdk::GDKRes::kSuccess) {
          std::cout << "GDK初始化失败" << std::endl;
          return -1;
      }

      std::cout << "GDK初始化成功" << std::endl;

      // 使用GDK功能...

      // 释放GDK系统资源
      agibot::gdk::GDKRes release_result = agibot::gdk::GDKRelease();

      if (release_result != agibot::gdk::GDKRes::kSuccess) {
          std::cout << "GDK释放失败: " << static_cast<int>(release_result) << std::endl;
          return -1;
      }

      std::cout << "GDK释放成功" << std::endl;
      return 0;
  }

  ```
### 完整使用示例
```cpp
#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    std::cout << "GDK Common 示例程序" << std::endl;

    // 1. 初始化GDK系统
    std::cout << "正在初始化GDK系统..." << std::endl;
    agibot::gdk::GDKRes init_result = agibot::gdk::GDKInit();

    if (init_result != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "❌ GDK初始化失败: " << static_cast<int>(init_result) << std::endl;
        return -1;
    }

    std::cout << "✅ GDK初始化成功" << std::endl;

    // 2. 使用GDK功能
    std::cout << "开始使用GDK功能..." << std::endl;

    // 创建相机对象
    agibot::gdk::Camera camera;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 创建IMU对象
    agibot::gdk::Imu imu;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "GDK功能使用完成" << std::endl;

    // 3. 释放GDK系统资源
    std::cout << "正在释放GDK系统资源..." << std::endl;
    agibot::gdk::GDKRes release_result = agibot::gdk::GDKRelease();

    if (release_result != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "❌ GDK释放失败: " << static_cast<int>(release_result) << std::endl;
        return -1;
    }

    std::cout << "✅ GDK释放成功" << std::endl;
    std::cout << "程序正常结束" << std::endl;

    return 0;
}

```
### 使用注意事项  # Imu Node
Imu数据获取
### Topic
| **话题名称含义**        |         |
| ----------------- | ------- |
| /imu/livox\_front | 前侧雷达imu |
| /imu/livox\_back  | 背部雷达imu |
| /imu\_chassis     | 底盘imu   |
### 消息类型
#### sensor\_msgs::msg::Imu
| **FieldTypeDescription** |                        |                 |
| ------------------------ | ---------------------- | --------------- |
| header                   | std\_msgs/Header       | 消息头，包含时间戳和坐标系信息 |
| angular\_velocity        | geometry\_msgs/Vector3 | 三维角速度（rad/s）    |
| linear\_acceleration     | geometry\_msgs/Vector3 | 三维线性加速度（m/s²）   |
### 启动ROS2转发节点
#### 1. 使用默认配置启动
```bash
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_imu
ros2 launch gdk_imu imu.launch.py

```
这将启动所有默认的IMU topics：
- `/imu/livox_front`
- `/imu/livox_back`
- `/imu/chassis`
#### 2. 自定义IMU topics
```bash
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_imu

# 只启动特定的IMU topics
#ros2 launch gdk_imu imu.launch.py imu_topics:="/imu/livox_back,/imu/livox_front"

# 启动单个IMU topic
#ros2 launch gdk_imu imu.launch.py imu_topics:="/imu/chassis"

```
  # Camera Node
相机图像转发节点
### Topic
| **Topic描述**                  |          |
| ---------------------------- | -------- |
| /camera/head\_back\_fisheye  | 头部背部鱼眼相机 |
| /camera/head\_left\_fisheye  | 头部左侧鱼眼相机 |
| /camera/head\_right\_fisheye | 头部右侧鱼眼相机 |
| /camera/head\_stereo\_left   | 头部左眼相机   |
| /camera/head\_stereo\_right  | 头部右眼相机   |
| /camera/hand\_left           | 腕部深度相机   |
| /camera/hand\_right          | 腕部深度相机   |
| /camera/head\_color          | 头部rgb相机  |
| /camera/head\_depth          | 头部深度相机   |
| /camera/hand\_left\_depth    | 腕部左侧深度相机 |
| /camera/hand\_right\_depth   | 腕部右侧深度相机 |
### 消息类型
#### sensor::msgs::msg::Image
| **FieldTypeDescription** |                  |                  |
| ------------------------ | ---------------- | ---------------- |
| header                   | std\_msgs/Header | 消息头，包含时间戳和坐标系信息  |
| height                   | uint32           | 图像高度（像素行数）       |
| width                    | uint32           | 图像宽度（像素列数）       |
| encoding                 | string           | 像素数据的编码格式字符串     |
| is\_bigendian            | bool             | 数据字节序（true表示大端序） |
| step                     | uint32           | 单行数据占用的字节数       |
| data                     | uint8[]          | 图像的原始像素数据        |
##### 单通道图像
| **EncodingDescriptionBytes per Pixel** |               |   |
| -------------------------------------- | ------------- | - |
| mono8                                  | 8位灰度图         | 1 |
| mono16                                 | 16位灰度图        | 2 |
| bayer\_bggr8                           | Bayer BGGR 格式 | 1 |
| bayer\_rggb8                           | Bayer RGGB 格式 | 1 |
##### 多通道图像
| **EncodingDescriptionBytes per Pixel** |              |   |
| -------------------------------------- | ------------ | - |
| bgr8                                   | 8位 BGR 彩色    | 3 |
| rgb8                                   | 8位 RGB 彩色    | 3 |
| bgra8                                  | 8位 BGRA 带透明度 | 4 |
| rgba8                                  | 8位 RGBA 带透明度 | 4 |
### 启动方式
#### 1. 使用默认配置启动
```bash
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_camera_compress
ros2 launch gdk_camera camera.launch.py

```
这将启动所有默认的Camera topics：
- `/camera/head_back_fisheye`
- `/camera/head_left_fisheye`
- `/camera/head_right_fisheye`
- `/camera/head_stereo_left`
- `/camera/head_stereo_right`
- `/camera/hand_left_color`
- `/camera/hand_right_color`
- `/camera/head_color`
- `/camera/head_depth`
- `/camera/hand_left_depth`
- `/camera/hand_right_depth`
#### 2. 自定义Camera topics
```bash
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_camera

# 只启动特定的Camera topics
#ros2 launch gdk_camera camera.launch.py camera_topics:="/camera/head_color,/camera/head_depth"

# 启动单个Camera topic
#ros2 launch gdk_camera camera.launch.py camera_topics:="/camera/head_color"

# 启动鱼眼相机
#ros2 launch gdk_camera camera.launch.py camera_topics:="/camera/head_back_fisheye,/camera/head_left_fisheye,/camera/head_right_fisheye"

# 启动手部相机
#ros2 launch gdk_camera camera.launch.py camera_topics:="/camera/hand_left_color,/camera/hand_right_color"

# 启动手部深度相机
#ros2 launch gdk_camera camera.launch.py camera_topics:="/camera/hand_left_depth,/camera/hand_right_depth"

```
## Camera Compress Node

相机压缩图像转发节点

### Topic

| **Topic描述**                  |              |
| ---------------------------- | ------------ |
| /camera/head\_back\_fisheye  | 头部背部鱼眼相机压缩图像 |
| /camera/head\_left\_fisheye  | 头部左侧鱼眼相机压缩图像 |
| /camera/head\_right\_fisheye | 头部右侧鱼眼相机压缩图像 |
| /camera/head\_stereo\_left   | 头部左眼相机压缩图像   |
| /camera/head\_stereo\_right  | 头部右眼相机压缩图像   |
| /camera/hand\_left\_color    | 腕部左侧彩色相机压缩图像 |
| /camera/hand\_right\_color   | 腕部右侧彩色相机压缩图像 |
| /camera/head\_color          | 头部RGB相机压缩图像  |
| /camera/head\_depth          | 头部深度相机压缩图像   |
| /camera/hand\_left\_depth    | 腕部左侧深度相机压缩图像 |
| /camera/hand\_right\_depth   | 腕部右侧深度相机压缩图像 |

### 消息类型

#### sensor\_msgs::msg::CompressedImage

| **FieldTypeDescription** |                  |                          |
| ------------------------ | ---------------- | ------------------------ |
| header                   | std\_msgs/Header | 消息头，包含时间戳和坐标系信息          |
| format                   | string           | 压缩格式字符串（如 "jpeg", "png"） |
| data                     | uint8[]          | 压缩后的图像数据                 |

##### 压缩格式

| **FormatDescription** |               |
| --------------------- | ------------- |
| jpeg                  | JPEG 压缩格式（默认） |
| png                   | PNG 压缩格式      |

**注意**: 当前实现中，所有压缩图像均使用 JPEG 格式（`format = "jpeg"`）。

### 启动方式

#### 1. 使用默认配置启动
```bash
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_camera_compress
ros2 launch gdk_camera_compress camera_compress.launch.py
```

这将启动所有默认的Camera压缩图像 topics：

- `/camera/head_back_fisheye`
- `/camera/head_left_fisheye`
- `/camera/head_right_fisheye`
- `/camera/head_stereo_left`
- `/camera/head_stereo_right`
- `/camera/hand_left_color`
- `/camera/hand_right_color`
- `/camera/head_color`
- `/camera/head_depth`
- `/camera/hand_left_depth`
- `/camera/hand_right_depth`

#### 2. 自定义Camera topics
```bash
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_camera_compress

# 只启动特定的Camera topics
#ros2 launch gdk_camera_compress camera_compress.launch.py camera_topics:="/camera/head_color,/camera/head_depth"

# 启动单个Camera topic
#ros2 launch gdk_camera_compress camera_compress.launch.py camera_topics:="/camera/head_color"

# 启动鱼眼相机
#ros2 launch gdk_camera_compress camera_compress.launch.py camera_topics:="/camera/head_back_fisheye,/camera/head_left_fisheye,/camera/head_right_fisheye"

# 启动手部相机
#ros2 launch gdk_camera_compress camera_compress.launch.py camera_topics:="/camera/hand_left_color,/camera/hand_right_color"

# 启动手部深度相机
#ros2 launch gdk_camera_compress camera_compress.launch.py camera_topics:="/camera/hand_left_depth,/camera/hand_right_depth"
```

### 与 Camera Node 的区别

| **特性Camera NodeCamera Compress Node** |                           |                                     |
| ------------------------------------- | ------------------------- | ----------------------------------- |
| 消息类型                                  | `sensor_msgs::msg::Image` | `sensor_msgs::msg::CompressedImage` |
| 数据格式                                  | 未压缩的原始像素数据                | JPEG 压缩数据                           |
| 带宽占用                                  | 较高                        | 较低                                  |
| 适用场景                                  | 需要原始图像数据                  | 需要减少带宽占用                            |

**建议**:

- 需要原始图像数据进行分析或处理时，使用 `camera_node`
- 需要通过网络传输或减少带宽占用时，使用 `camera_compress_node`

1. **初始化顺序**：必须在调用任何其他GDK功能之前调用`GDKInit()`
2. **释放顺序**：在程序结束前调用`GDKRelease()`释放资源
3. **错误处理**：始终检查返回值，确保操作成功
4. **单次调用**：通常只需要在程序开始时调用一次`GDKInit()`，结束时调用一次`GDKRelease()`
5. **异常安全**：在异常情况下也要确保调用`GDKRelease()`释放资源
6. **多线程**：GDK初始化是全局的，多线程环境下只需要一个线程调用即可
### 错误码说明
| **错误码描述可能原因**                 |      |          |
| ----------------------------- | ---- | -------- |
| `GDKRes::kSuccess`            | 操作成功 | -        |
| `GDKRes::kInvalidInput`       | 无效输入 | 参数错误     |
| `GDKRes::kInvalidOutput`      | 无效输出 | 输出参数错误   |
| `GDKRes::kTimeout`            | 超时   | 操作超时     |
| `GDKRes::kNotInitialized`     | 未初始化 | 系统未正确初始化 |
| `GDKRes::kAlreadyInitialized` | 已初始化 | 重复初始化    |
| `GDKRes::kInternalError`      | 内部错误 | 系统内部错误   |
### 应用场景
- **系统启动**：在机器人系统启动时初始化GDK
- **资源管理**：确保GDK系统资源正确释放


## Control Node

机器人控制器节点

### 末端控制信息获取

#### Topic

/wbc/motion\_control\_status

#### 消息类型

genie\_msgs::msg::MotionControlStatus.msg
```csharp
std_msgs/Header header  # frame id 默认填写base_link, timestamp发送时间

# 反馈末端位姿状态
string[] frame_names   #运控参数配置定义
geometry_msgs/Pose[] frame_poses

# 反馈自碰撞状态
# [collision_pair_1， collision_pair_2]组成一组碰撞对的frame名称
string[] collision_pairs_1
string[] collision_pairs_2

# 运控模式
uint8 MODE_STOP=0
uint8 MODE_SERVO=1
uint8 MODE_PLANNING=2
uint8 mode

# 实时控制的运控错误码
# 0: no error
uint8 error_code
string error_msg

geometry_msgs/Twist[] frame_twists
geometry_msgs/Wrench[] frame_wrenchs
```

### 关节角度获取

#### Topic

/hal/joint\_state

#### 消息类型

genie\_msgs::msg::JointState
```php
# The state of each joint (revolute or prismatic) is defined by:
#  * the control mode (csp 0, cst 1)
#  * the position of the joint (rad or m),
#  * the velocity of the joint (rad/s or m/s),
#  * the effort that is applied in the joint (Nm or N),
#  * the position of the motor (rad or m),
#  * the velocity of the motor (rad/s or m/s),
#  * the current of the motor (A),
#  * the error_code of the joint.
#
# TODO: Error code description or joint error code page

std_msgs/Header header

string[] name
uint32[] mode
float64[] position
float64[] velocity
float64[] effort
float64[] motor_position
float64[] motor_velocity
float64[] motor_current
uint32[] error_code
```

### 通过关节角度控制机器人

#### Topic

/MotionControlService/JointPosition/request

#### 消息类型

genie\_msg::msg::CommonResponse.msg
```css
# frame id 无用, timestamp发送时间
std_msgs/Header header
float64 lifetime

string[] joint_names
float64[] joint_positions
float64[] joint_velocities

string uuid
string details
```

### 关节角控制命令反馈

#### Topic

/MotionControlService/JointPosition/response

#### 消息类型

genie\_msg::msg::CommonResponse.msg
```csharp
# frame id 无用, timestamp发送时间
std_msgs/Header header

uint8 data

string uuid
string detail
```

### 启动ROS2转发节点

#### 混合部署
```ruby
source ~/.cache/agibot/app/gdk/scripts/ros_env.sh gdk_controller
ros2 launch gdk_controller controller.launch.py
```

<a id="cpp-imu"></a>

## GDK IMU 接口文档（C++）

以下保留接口附件的纯文本排版，以避免改变代码缩进和参数表内容。

````text
概述
IMU（惯性测量单元）模块为G02机器人提供了获取实时惯性数据的功能。通过C++接口，开发者可以方便地获取机器人的方向、角速度和线性加速度信息，适用于姿态检测、运动分析、导航等多种场景。

接口说明
Imu 类
该类封装了IMU传感器的主要数据获取接口。

1. GetLatestImu()
功能：获取最新的IMU数据
参数：
参数名	类型	描述
imu_type	const ImuType&	IMU类型枚举值
timeout_ms	const float	超时时间（毫秒）
imu	std::shared_ptr<ImuData>&	输出参数，IMU数据指针
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，imu参数包含IMU数据
ImuData对象详细说明
ImuData结构体包含以下成员：

struct ImuData {
  Vector3 angular_velocity{};     ///< imu current angular velocity
  Vector3 linear_acceleration{}; ///< imu current linear acceleration
  uint64_t timestamp_ns{0};      ///< imu timestamp(ns)
};
成员名	类型	描述	单位
angular_velocity	Vector3	角速度，机器人在三个轴上的角速度	弧度/秒
linear_acceleration	Vector3	线性加速度，机器人在三个轴上的线性加速度	米/秒²
timestamp_ns	uint64_t	数据采集的时间戳，精度为纳秒	纳秒
Vector3 结构体说明：
成员名	类型	描述
x	double	X轴分量
y	double	Y轴分量
z	double	Z轴分量
struct Vector3 {
  double x{};
  double y{};
  double z{};
};
IMU类型：

ImuType::kImuFront: 前部IMU

ImuType::kImuBack: 后部IMU

ImuType::kImuChassis: 底盘IMU

示例：

#include <iostream>
#include <chrono>
#include <thread>
#include "gdk/gdk.h"

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    std::cout<< "IMU示例程序" << std::endl;
    agibot::gdk::Imu imu;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待1秒以确保DDS连接建立
    std::shared_ptr<agibot::gdk::ImuData> imu_data;
    imu.GetLatestImu(agibot::gdk::ImuType::kImuChassis, 500.0, imu_data);

    if (imu_data != nullptr) {
        std::cout << "\n--- IMU数据 ---" << std::endl;
        std::cout << "时间戳: " << imu_data->timestamp_ns << std::endl;

        // 角速度
        std::cout << "角速度: x=" << imu_data->angular_velocity.x << ", "
              << "y=" << imu_data->angular_velocity.y << ", "
              << "z=" << imu_data->angular_velocity.z << std::endl;

        // 线性加速度
        std::cout << "线性加速度: x=" << imu_data->linear_acceleration.x << ", "
              << "y=" << imu_data->linear_acceleration.y << ", "
              << "z=" << imu_data->linear_acceleration.z << std::endl;
    } else {
        std::cout << "未收到IMU数据" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
2. GetNearestImu()
功能：获取指定时间戳附近最近的IMU数据
参数：
参数名	类型	描述
imu_type	const ImuType&	IMU类型枚举值
timestamp_ns	const uint64_t	目标时间戳（纳秒）
timeout_ms	const float	超时时间（毫秒）
imu	std::shared_ptr<ImuData>&	输出参数，IMU数据指针
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，imu参数包含IMU数据

示例：

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "gdk/gdk.h"

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    std::cout << "IMU示例程序" << std::endl;
    agibot::gdk::Imu imu;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待1秒以确保DDS连接建立

    agibot::gdk::ImuType imu_type = agibot::gdk::ImuType::kImuChassis;
    std::shared_ptr<agibot::gdk::ImuData> imu_data;
    imu.GetLatestImu(imu_type, 500.0, imu_data);

    if (imu_data != nullptr) {
        std::cout << "\n--- IMU数据 ---" << std::endl;
        std::cout << "时间戳: " << imu_data->timestamp_ns << std::endl;

        // 角速度
        std::cout << "角速度: x=" << imu_data->angular_velocity.x << ", "
                  << "y=" << imu_data->angular_velocity.y << ", "
                  << "z=" << imu_data->angular_velocity.z << std::endl;

        // 线性加速度
        std::cout << "线性加速度: x=" << imu_data->linear_acceleration.x << ", "
                  << "y=" << imu_data->linear_acceleration.y << ", "
                  << "z=" << imu_data->linear_acceleration.z << std::endl;

        // 查找最近的IMU数据
        for (int i = 0; i < 10; ++i) {
            std::shared_ptr<agibot::gdk::ImuData> imu_data_nearest;
            agibot::gdk::GDKRes res = imu.GetNearestImu(
                imu_type,
                imu_data->timestamp_ns - 1000000000LL, // 往前1秒
                1000.0,
                imu_data_nearest
            );
            if (res == agibot::gdk::GDKRes::kSuccess && imu_data_nearest != nullptr) {
                std::cout << "✅ 最近IMU数据: " << imu_data_nearest->timestamp_ns << std::endl;
                std::cout << std::fixed << std::setprecision(4);
                std::cout << "角速度: x=" << imu_data_nearest->angular_velocity.x
                          << ", y=" << imu_data_nearest->angular_velocity.y
                          << ", z=" << imu_data_nearest->angular_velocity.z << std::endl;
                std::cout << "线性加速度: x=" << imu_data_nearest->linear_acceleration.x
                          << ", y=" << imu_data_nearest->linear_acceleration.y
                          << ", z=" << imu_data_nearest->linear_acceleration.z << std::endl;
            } else {
                std::cout << "❌ 未找到最近的 IMU 数据" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else {
        std::cout << "未收到IMU数据" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
3. GetImuFps()
功能：获取IMU数据采集帧率
参数：
参数名	类型	描述
imu_type	const ImuType&	IMU类型枚举值
fps	int&	输出参数，IMU帧率（FPS）
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，fps参数包含帧率值

示例：

#include <iostream>
#include <chrono>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Imu imu;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待1秒以确保DDS连接建立

    agibot::gdk::ImuType imu_type = agibot::gdk::ImuType::kImuChassis;

    float fps;
    if (imu.GetImuFps(imu_type, fps) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get imu fps" << std::endl;
    } else {
        std::cout << "IMU fps: " << fps << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
4. GetImuLatency()
注意事项：获取IMU数据延迟统计信息前，需要先进行时间同步，否则延迟统计结果不准确
功能：获取IMU数据延迟统计信息
参数：
参数名	类型	描述
imu_type	const ImuType&	IMU类型枚举值
window_seconds	const float	统计窗口时间（秒）
latency	LatencyStats&	输出参数，延迟统计信息
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，latency参数包含延迟统计信息

LatencyStats结构体说明：

struct LatencyStats {
  double max_latency_ms{0.0};    ///< max latency(ms)
  double avg_latency_ms{0.0};    ///< average latency(ms)
  double p99_latency_ms{0.0};    ///< 99th percentile latency(ms)
  double p999_latency_ms{0.0};   ///< 99.9th percentile latency(ms)
  double p9999_latency_ms{0.0};  ///< 99.99th percentile latency(ms)
};
成员名	类型	描述	单位
max_latency_ms	double	最大延迟	毫秒
avg_latency_ms	double	平均延迟	毫秒
p99_latency_ms	double	99分位延迟	毫秒
p999_latency_ms	double	99.9分位延迟	毫秒
p9999_latency_ms	double	99.99分位延迟	毫秒
示例：

#include <iostream>
#include <chrono>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Imu imu;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待1秒以确保DDS连接建立

    agibot::gdk::ImuType imu_type = agibot::gdk::ImuType::kImuChassis;

    agibot::gdk::LatencyStats latency;
    if (imu.GetImuLatency(imu_type, 1.0, latency) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get imu latency" << std::endl;
    } else {
        std::cout << "IMU latency stats:" << std::endl;
        std::cout << "  Max latency: " << latency.max_latency_ms << "ms" << std::endl;
        std::cout << "  Average latency: " << latency.avg_latency_ms << "ms" << std::endl;
        std::cout << "  P99 latency: " << latency.p99_latency_ms << "ms" << std::endl;
        std::cout << "  P99.9 latency: " << latency.p999_latency_ms << "ms" << std::endl;
        std::cout << "  P99.99 latency: " << latency.p9999_latency_ms << "ms" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
5. CloseImu()
功能：关闭IMU DDS连接

参数：无

返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include <iostream>
#include <chrono>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Imu imu;
    std::cout << "IMU init" << std::endl;

    // 使用IMU...

    // 关闭IMU
    if (imu.CloseImu() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to close imu" << std::endl;
    } else {
        std::cout << "IMU closed successfully" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
使用注意事项
GDK初始化：使用IMU功能前必须先调用agibot::gdk::GDKInit()初始化GDK系统
GDK释放：程序结束前必须调用agibot::gdk::GDKRelease()释放GDK系统资源
初始化等待：创建Imu对象后，建议等待1秒以确保DDS连接建立
超时设置：根据实际需求设置合适的超时时间，避免长时间阻塞
返回值检查：使用前请检查GDKRes返回值是否为kSuccess
智能指针管理：ImuData对象使用shared_ptr管理，注意生命周期
时间戳精度：时间戳单位为纳秒，可用于精确的时间同步
数据融合：IMU数据通常需要与其他传感器数据进行融合以提高精度
资源释放：使用完毕后调用CloseImu()释放资源
错误处理：始终检查GDKRes返回值，确保操作成功
未实现方法：GetImuFps()和GetImuLatency()当前未实现，使用时需注意
应用场景
运动分析：利用角速度和线性加速度分析机器人运动状态
导航定位：结合其他传感器进行机器人定位和导航
平衡控制：用于机器人的平衡和稳定性控制
数据融合：与其他传感器数据进行卡尔曼滤波等融合算法
运动预测：基于历史数据预测机器人运动轨迹
异常检测：检测机器人的异常运动状态
校准补偿：进行传感器校准和误差补偿
振动监测：监测机器人的振动和冲击情况
````

<a id="cpp-camera"></a>

## GDK Camera 接口文档（C++）

以下保留接口附件的纯文本排版，以避免改变代码缩进和参数表内容。

````text
概述
Camera（相机）模块为G02机器人提供了获取实时图像数据的功能。通过C++接口，开发者可以方便地获取机器人的视觉感知数据，适用于目标检测、图像识别、视觉导航、SLAM建图、环境监控等多种场景。

接口说明
Camera 类
该类封装了相机传感器的主要数据获取接口。

1. GetLatestImage()
功能：获取最新的图像数据
参数：
参数名	类型	描述
camera_type	const CameraType&	相机类型枚举值
timeout_ms	const float	超时时间（毫秒）
image	std::shared_ptr<Image>&	输出参数，图像数据指针
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，image参数包含图像数据
Image对象详细说明
Image结构体包含以下成员：

成员名	类型	描述	单位
timestamp_ns	uint64_t	图像采集的时间戳	纳秒
width	uint32_t	图像的宽度（像素）	像素
height	uint32_t	图像的高度（像素）	像素
encoding	Encoding	图像的编码格式枚举	枚举值
color_format	ColorFormat	图像的颜色格式枚举	枚举值
bit_depth	uint8_t	每个像素的位数	位
data_view	DataView	图像的原始像素数据视图	数据视图
struct Image {
  uint32_t width{0};   ///< image width
  uint32_t height{0};  ///< image height

  enum class Encoding : uint8_t {
    UNCOMPRESSED,  ///< uncompressed
    JPEG,          ///< JPEG
    PNG            ///< PNG
  } encoding{Encoding::UNCOMPRESSED};

  enum class ColorFormat : uint8_t {
    RGB,
    BGR,
    RGBA,
    BGRA,

    YUV420,
    YUV422,
    YUV444,
    NV12,
    NV21,

    GRAY8,
    GRAY16,

    BAYER_RGGB,
    BAYER_BGGR,
    BAYER_GBRG,
    BAYER_GRBG,

    RS2_FORMAT_Z16
  } color_format{ColorFormat::RGB};

  uint8_t bit_depth{8};  ///< bit depth

  DataView data_view{};      ///< image data view
  uint64_t timestamp_ns{0};  ///< image timestamp(ns)
};
encoding (编码格式)：

类型：Encoding枚举
常见值：
Encoding::UNCOMPRESSED: 未压缩
Encoding::JPEG: JPEG压缩
Encoding::PNG: PNG压缩
 enum class Encoding : uint8_t {
   UNCOMPRESSED,  ///< uncompressed
   JPEG,          ///< JPEG
   PNG            ///< PNG
 } encoding{Encoding::UNCOMPRESSED};
color_format (颜色格式)：

类型：ColorFormat枚举
常见值：
ColorFormat::RGB: 红绿蓝
ColorFormat::BGR: 蓝绿红
ColorFormat::RGBA: 红绿蓝透明度
ColorFormat::BGRA: 蓝绿红透明度
ColorFormat::GRAY8: 8位灰度
ColorFormat::GRAY16: 16位灰度
ColorFormat::YUV420: YUV420格式
ColorFormat::YUV422: YUV422格式
ColorFormat::YUV444: YUV444格式
ColorFormat::NV12: NV12格式
ColorFormat::NV21: NV21格式
ColorFormat::BAYER_RGGB: RGGB拜耳模式
ColorFormat::BAYER_BGGR: BGGR拜耳模式
ColorFormat::BAYER_GBRG: GBRG拜耳模式
ColorFormat::BAYER_GRBG: GRBG拜耳模式
ColorFormat::RS2_FORMAT_Z16: RealSense Z16深度格式
 enum class ColorFormat : uint8_t {
   RGB,
   BGR,
   RGBA,
   BGRA,

   YUV420,
   YUV422,
   YUV444,
   NV12,
   NV21,

   GRAY8,
   GRAY16,

   BAYER_RGGB,
   BAYER_BGGR,
   BAYER_GBRG,
   BAYER_GRBG,

   RS2_FORMAT_Z16
 } color_format{ColorFormat::RGB};
bit_depth (位深度)：

类型：uint8_t
常见值：
8: 8位（0-255）
16: 16位（0-65535）
32: 32位（浮点）
data_view (图像数据)：

类型：DataView
描述：图像的原始像素数据视图
用途：图像处理、显示、保存
注意：需要根据encoding和尺寸进行解析
相机类型：

CameraType::kHeadBackFisheye: 头部背部鱼眼相机

CameraType::kHeadLeftFisheye: 头部左侧鱼眼相机

CameraType::kHeadRightFisheye: 头部右侧鱼眼相机

CameraType::kHeadStereoLeft: 头部立体左相机

CameraType::kHeadStereoRight: 头部立体右相机

CameraType::kHandLeftColor: 左手彩色相机

CameraType::kHandRightColor: 右手彩色相机

CameraType::kHeadColor: 头部彩色相机

CameraType::kHeadDepth: 头部深度相机（输出为深度图）

CameraType::kHandLeftDepth: 左手深度相机（输出为深度图）

CameraType::kHandRightDepth: 右手深度相机（输出为深度图）

CameraType::kHandLeftUpperColor: 左手上部彩色相机 (预留)

CameraType::kHandRightUpperColor: 右手上部彩色相机 (预留)

CameraType::kHandLeftLowerColor: 左手下部彩色相机 (预留)

CameraType::kHandRightLowerColor: 右手下部彩色相机 (预留)

CameraType::kHandLeftUpperDepth: 左手上部深度相机（输出为深度图） (预留)

CameraType::kHandRightUpperDepth: 右手上部深度相机（输出为深度图） (预留)

CameraType::kHandLeftLowerDepth: 左手下部深度相机（输出为深度图） (预留)

CameraType::kHandRightLowerDepth: 右手下部深度相机（输出为深度图） (预留)

在常规模式下，默认打开头部立体左相机，头部立体右相机，左右彩色相机，右手彩色相机，头部彩色相机，头部深度相机，其余相机默认关闭，且不建议在常规模式下打开其余相机

可以在develop模式下开启或关闭其余相机

示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::shared_ptr<agibot::gdk::Image> image = std::make_shared<agibot::gdk::Image>();

    agibot::gdk::CameraType camera_type = agibot::gdk::CameraType::kHandLeftColor;

    if (gdk_camera.GetLatestImage(camera_type, 500, image) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get latest image" << std::endl;
    } else {
        std::cout << "Image shape: " << image->width << "x" << image->height << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
2. GetNearestImage()
功能：获取指定时间戳附近最近的图像数据
参数：
参数名	类型	描述
camera_type	const CameraType&	相机类型枚举值
timestamp_ns	const uint64_t	目标时间戳（纳秒）
timeout_ms	const float	超时时间（毫秒）
image	std::shared_ptr<Image>&	输出参数，图像数据指针
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，image参数包含图像数据，结构与GetLatestImage()相同

示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::shared_ptr<agibot::gdk::Image> image = std::make_shared<agibot::gdk::Image>();

    agibot::gdk::CameraType camera_type = agibot::gdk::CameraType::kHandLeftColor;

    if(gdk_camera.GetNearestImage(camera_type, 0, 2000.0, image) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GetNearestImage failed" << std::endl;
        return -1;
    } else {
        std::cout << "Image shape: " << image->width << " x " << image->height << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
3. GetImageShape()
功能：获取图像数据大小
参数：
参数名	类型	描述
camera_type	const CameraType&	相机类型枚举值
shape	std::tuple<int, int>&	输出参数，图像宽度和高度的元组
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，shape参数包含图像尺寸

示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::shared_ptr<agibot::gdk::Image> image = std::make_shared<agibot::gdk::Image>();

    agibot::gdk::CameraType camera_type = agibot::gdk::CameraType::kHandRightColor;

    std::tuple<int, int> shape;
    if (gdk_camera.GetImageShape(camera_type, shape) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get image shape" << std::endl;
    } else {
        std::cout << "Image shape: " << std::get<0>(shape) << "x" << std::get<1>(shape) << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
4. GetImageFps()
功能：获取图像捕获帧率
参数：
参数名	类型	描述
camera_type	const CameraType&	相机类型枚举值
fps	float&	输出参数，图像帧率（FPS）
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，fps参数包含帧率值

示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::shared_ptr<agibot::gdk::Image> image = std::make_shared<agibot::gdk::Image>();

    agibot::gdk::CameraType camera_type = agibot::gdk::CameraType::kHandLeftColor;

    float fps;
    if (gdk_camera.GetImageFps(camera_type, fps) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get image fps" << std::endl;
    } else {
        std::cout << "Image fps: " << fps << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
5. GetImageLatency()
注意事项：获取图像延迟统计信息前，需要先进行时间同步，否则延迟统计结果不准确
功能：获取图像延迟统计信息
参数：
参数名	类型	描述
camera_type	const CameraType&	相机类型枚举值
window_seconds	const float	统计窗口时间（秒）
latency	LatencyStats&	输出参数，延迟统计信息
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，latency参数包含延迟统计信息

示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::shared_ptr<agibot::gdk::Image> image = std::make_shared<agibot::gdk::Image>();

    agibot::gdk::CameraType camera_type = agibot::gdk::CameraType::kHandLeftColor;

    agibot::gdk::LatencyStats latency;
    if (gdk_camera.GetImageLatency(agibot::gdk::CameraType::kHeadStereoLeft, 1.0, latency) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get image latency" << std::endl;
    } else {
        std::cout << "Image latency: " << latency.max_latency_ms << "ms" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
6. GetCameraIntrinsic()
功能：获取相机内参信息
参数：
参数名	类型	描述
camera_type	const CameraType&	相机类型枚举值
intrinsic	CameraIntrinsic&	输出参数，相机内参信息
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，intrinsic参数包含相机内参

注意：并非所有相机类型都支持内参获取。支持内参的相机类型包括：kHeadBackFisheye、kHeadLeftFisheye、kHeadRightFisheye、kHeadStereoLeft、kHeadStereoRight、kHandLeftColor、kHandRightColor、kHeadColor、kHeadDepth、kHandLeftDepth、kHandRightDepth。对于不支持的相机类型，调用此接口将返回错误。

CameraIntrinsic结构体说明：

struct CameraIntrinsic {
  std::vector<double> intrinsic{};  ///< camera intrinsic, fx, fy, cx, cy
  std::vector<double> distortion{}; ///< camera distortion, k1, k2, p1, p2, k3, k4, k5, k6
};
成员名	类型	描述	索引	单位
intrinsic[0]	double	焦距x方向 (fx)	0	像素
intrinsic[1]	double	焦距y方向 (fy)	1	像素
intrinsic[2]	double	主点x坐标 (cx)	2	像素
intrinsic[3]	double	主点y坐标 (cy)	3	像素
distortion[0]	double	径向畸变系数1 (k1)	0	无量纲
distortion[1]	double	径向畸变系数2 (k2)	1	无量纲
distortion[2]	double	切向畸变系数1 (p1)	2	无量纲
distortion[3]	double	切向畸变系数2 (p2)	3	无量纲
distortion[4]	double	径向畸变系数3 (k3)	4	无量纲
distortion[5]	double	径向畸变系数4 (k4)	5	无量纲
distortion[6]	double	径向畸变系数5 (k5)	6	无量纲
distortion[7]	double	径向畸变系数6 (k6)	7	无量纲
不同相机类型的内参支持：
相机类型	intrinsic向量大小	distortion向量大小	说明
双目相机	4 (fx, fy, cx, cy)	8 (k1, k2, p1, p2, k3, k4, k5, k6)	完整的12参数畸变模型
RGBD相机	4 (fx, fy, cx, cy)	5 (k1, k2, p1, p2, k3)	9参数畸变模型
鱼眼相机	4 (fx, fy, cx, cy)	6 (k1, k2, p1, p2, k3, k4)	10参数畸变模型
畸变模型说明：

径向畸变：k1, k2, k3, k4, k5, k6 - 用于校正镜头径向畸变
切向畸变：p1, p2 - 用于校正镜头切向畸变
不同相机类型：根据镜头特性使用不同数量的畸变参数
示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

void printCameraIntrinsic(const agibot::gdk::CameraType& camera_type,
                         const agibot::gdk::CameraIntrinsic& intrinsic) {
    std::cout << "Camera intrinsic for " << static_cast<int>(camera_type) << ":" << std::endl;

    // 显示内参矩阵 (fx, fy, cx, cy)
    if (intrinsic.intrinsic.size() >= 4) {
        std::cout << "  fx: " << intrinsic.intrinsic[0] << ", fy: " << intrinsic.intrinsic[1] << std::endl;
        std::cout << "  cx: " << intrinsic.intrinsic[2] << ", cy: " << intrinsic.intrinsic[3] << std::endl;
    }

    // 显示畸变参数
    if (intrinsic.distortion.size() > 0) {
        std::cout << "  k1: " << intrinsic.distortion[0];
        if (intrinsic.distortion.size() > 1) std::cout << ", k2: " << intrinsic.distortion[1];
        if (intrinsic.distortion.size() > 2) std::cout << ", p1: " << intrinsic.distortion[2];
        if (intrinsic.distortion.size() > 3) std::cout << ", p2: " << intrinsic.distortion[3];
        if (intrinsic.distortion.size() > 4) std::cout << ", k3: " << intrinsic.distortion[4];
        std::cout << std::endl;

        // 根据相机类型显示额外的畸变参数
        if (camera_type == agibot::gdk::CameraType::kHeadStereoLeft ||
            camera_type == agibot::gdk::CameraType::kHeadStereoRight) {
            // 双目相机：显示 k4, k5, k6
            if (intrinsic.distortion.size() > 5) std::cout << "  k4: " << intrinsic.distortion[5];
            if (intrinsic.distortion.size() > 6) std::cout << ", k5: " << intrinsic.distortion[6];
            if (intrinsic.distortion.size() > 7) std::cout << ", k6: " << intrinsic.distortion[7];
            std::cout << " (双目相机，12参数畸变模型)" << std::endl;
        } else if (camera_type == agibot::gdk::CameraType::kHeadDepth) {
            // RGBD相机：只显示 k1, k2, k3
            std::cout << "  (RGBD相机，9参数畸变模型)" << std::endl;
        } else if (camera_type == agibot::gdk::CameraType::kHeadBackFisheye ||
                   camera_type == agibot::gdk::CameraType::kHandLeftColor ||
                   camera_type == agibot::gdk::CameraType::kHandRightColor) {
            // 鱼眼相机：显示 k4
            if (intrinsic.distortion.size() > 5) {
                std::cout << "  k4: " << intrinsic.distortion[5] << " (鱼眼相机，10参数畸变模型)" << std::endl;
            }
        }
    }
}

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 获取不同相机类型的内参
    std::vector<agibot::gdk::CameraType> camera_types = {
        agibot::gdk::CameraType::kHeadStereoLeft,    // 双目相机
        agibot::gdk::CameraType::kHeadDepth,         // RGBD相机
        agibot::gdk::CameraType::kHeadBackFisheye  // 鱼眼相机
    };

    for (auto camera_type : camera_types) {
        agibot::gdk::CameraIntrinsic intrinsic;
        if (gdk_camera.GetCameraIntrinsic(camera_type, intrinsic) != agibot::gdk::GDKRes::kSuccess) {
            std::cout << "Failed to get camera intrinsic for type " << static_cast<int>(camera_type) << std::endl;
        } else {
            printCameraIntrinsic(camera_type, intrinsic);
        }
        std::cout << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
7. SetDevCameraConfig()
功能：相机客制化功能(开关相机、设置帧率)
参数：
参数名	类型	描述
cam_conf_path	const std::string&	相机配置文件路径
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

注意：

配置文件路径必须存在，否则返回GDKRes::kInvalidInput
每次修改客制化相机配置文件且调用接口后，需要重新切换模式至develop模式
配置选项
GDK支持配置相机的开关与设置的帧率，相机客制化的配置文件在部署包下，其绝对路径通常为 ~/.cache/agibot/app/gdk/config/r1_camera_conf.json或~/.cache/agibot/app/gdk/config/thor_camera_conf.json（其中 ~ 表示用户主目录，如 /home/your_name） r1机器的配置文件为r1_camera_conf.json，thor机器的配置文件为thor_camera_conf.json，使用时注意文件名称 设置publish为true开启相机，false关闭相机，设置fps来控制相机帧率

相机具体配置形式如下

{
    "cam0": {
        "fps": "30",
        "name": "head_stereo_right",
        "publish": true
    },
    "cam3": {
        "fps": "30",
        "name": "head_stereo_left",
        "publish": true
    },
    "cam4": {
        "fps": "30",
        "name": "hand_left_depth",
        "publish": false
    },
    "cam5": {
        "fps": "30",
        "name": "hand_left_color",
        "publish": true
    },
    "cam6": {
        "fps": "30",
        "name": "hand_right_depth",
        "publish": false
    },
    "cam7": {
        "fps": "30",
        "name": "hand_right_color",
        "publish": true
    },
    "cam10": {
        "fps": "30",
        "name": "head_right_fisheye",
        "publish": false
    },
    "cam11": {
        "fps": "30",
        "name": "head_left_fisheye",
        "publish": false
    },
    "cam12": {
        "fps": "30",
        "name": "head_back_fisheye",
        "publish": false
    },
    "cam14": {
        "fps": "30",
        "name": "head_depth",
        "publish": true
    },
    "cam15": {
        "fps": "30",
        "name": "head_color",
        "publish": true
    }
}
模式切换
./mode_switch --mode develop # 切换到develop模式
如需切换回之前base模式，则执行

./mode_switch --mode base # 切换到base模式
示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 设置相机配置
    std::string config_path = "/home/<your_name>/.cache/agibot/app/gdk/config/r1_camera_conf.json";
    if (gdk_camera.SetDevCameraConfig(config_path) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to set camera config" << std::endl;
    } else {
        std::cout << "Camera config set successfully" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
8. CloseCamera()
功能：关闭相机DDS连接

参数：无

返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include <iostream>
#include <thread>
#include "gdk/gdk.h"

int main() {
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Camera gdk_camera;
    std::cout << "Camera init" << std::endl;

    // 使用相机...

    // 关闭相机
    if (gdk_camera.CloseCamera() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to close camera" << std::endl;
    } else {
        std::cout << "Camera closed successfully" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
使用注意事项
GDK初始化：使用Camera功能前必须先调用agibot::gdk::GDKInit()初始化GDK系统
GDK释放：程序结束前必须调用agibot::gdk::GDKRelease()释放GDK系统资源
初始化等待：创建Camera对象后，建议等待1秒以确保相机初始化完成
超时设置：根据实际需求设置合适的超时时间，避免长时间阻塞
数据有效性：使用前请检查返回的图像数据是否为nullptr
时间戳精度：时间戳单位为纳秒，可用于精确的时间同步
图像处理：图像数据量较大，处理时注意内存使用
相机选择：根据应用场景选择合适的相机类型（鱼眼/立体/深度等）
帧率控制：注意相机的帧率限制，避免过度请求
相机配置：使用SetDevCameraConfig()设置相机配置时，确保配置文件路径有效
错误处理：始终检查GDKRes返回值，确保操作成功
相机开关：在常规模式/develop模式下，若打开更多相机，存在性能风险
应用场景
目标检测：利用图像数据进行目标识别和检测
视觉导航：为机器人导航提供视觉信息
SLAM建图：结合图像数据进行同时定位与地图构建
环境监控：实时监控周围环境变化
深度感知：使用深度相机获取3D环境信息
立体视觉：利用双目相机进行距离测量
图像识别：进行物体分类和识别
数据融合：与其他传感器数据进行融合，提高感知精度
相机标定：使用相机内参进行图像校正和畸变补偿
3D重建：结合相机内参进行三维点云重建
视觉测量：利用相机内参进行精确的尺寸测量
````

<a id="cpp-tf"></a>

## GDK TF 接口文档（C++）

以下保留接口附件的纯文本排版，以避免改变代码缩进和参数表内容。

````text
概述
TF（坐标变换）模块为G02机器人提供了坐标变换查询功能。通过C++接口，开发者可以方便地获取机器人各部件之间的坐标变换关系，适用于坐标变换、传感器标定、多传感器融合、SLAM建图等多种场景。

接口说明
TF 类
该类封装了坐标变换的主要查询接口。

1. GetAllTfFromBaseLink()
功能：获取从base_link到所有子坐标系的变换关系
参数：
参数名	类型	描述
transforms	std::vector<TransformStamped>&	输出参数，变换关系列表
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，transforms参数包含所有变换关系
TransformStamped对象详细说明
TransformStamped结构体包含以下成员：

成员名	类型	描述	单位
frame_id	std::string	父坐标系ID	字符串
child_frame_id	std::string	子坐标系ID	字符串
transform	Transform	变换信息	变换对象
timestamp_ns	uint64_t	时间戳	纳秒
struct TransformStamped {
  std::string frame_id{};        ///< frame id
  std::string child_frame_id{};  ///< child frame id
  Transform transform{};         ///< transform
  uint64_t timestamp_ns{0};      ///< transform timestamp(ns)
};
Transform结构体：

成员名	类型	描述	单位
translation	Vector3	平移向量	米
rotation	Quaternion	旋转四元数	无单位
struct Transform {
  Vector3 translation{};  ///< translation
  Quaternion rotation{};  ///< rotation
};
Vector3结构体：

成员名	类型	描述	单位
x	double	X轴分量	米
y	double	Y轴分量	米
z	double	Z轴分量	米
Quaternion结构体：

成员名	类型	描述	单位
x	double	四元数X分量	无单位
y	double	四元数Y分量	无单位
z	double	四元数Z分量	无单位
w	double	四元数W分量	无单位
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<agibot::gdk::TransformStamped> transforms;
    if (tf.GetAllTfFromBaseLink(transforms) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get all transforms" << std::endl;
    } else {
        std::cout << "获取到 " << transforms.size() << " 个变换关系:" << std::endl;
        for (const auto& transform_stamped : transforms) {
            std::cout << "坐标系: " << transform_stamped.frame_id
                      << " -> " << transform_stamped.child_frame_id << std::endl;
            std::cout << "  平移: x=" << transform_stamped.transform.translation.x
                      << ", y=" << transform_stamped.transform.translation.y
                      << ", z=" << transform_stamped.transform.translation.z << std::endl;
            std::cout << "  旋转: x=" << transform_stamped.transform.rotation.x
                      << ", y=" << transform_stamped.transform.rotation.y
                      << ", z=" << transform_stamped.transform.rotation.z
                      << ", w=" << transform_stamped.transform.rotation.w << std::endl;
            std::cout << "  时间戳: " << transform_stamped.timestamp_ns << std::endl;
            std::cout << std::endl;
        }
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
2. GetTfFromBaseLink()
功能：获取从base_link到指定子坐标系的变换关系
参数：
参数名	类型	描述
child_frame_id	const std::string&	子坐标系ID
transform	Transform&	输出参数，变换信息对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，transform参数包含变换信息

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::Transform transform;
    std::string child_frame_id = "arm_l_end_link";

    if (tf.GetTfFromBaseLink(child_frame_id, transform) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get transform for " << child_frame_id << std::endl;
    } else {
        std::cout << "从base_link到 " << child_frame_id << " 的变换:" << std::endl;
        std::cout << "  平移: x=" << transform.translation.x
                  << ", y=" << transform.translation.y
                  << ", z=" << transform.translation.z << std::endl;
        std::cout << "  旋转: x=" << transform.rotation.x
                  << ", y=" << transform.rotation.y
                  << ", z=" << transform.rotation.z
                  << ", w=" << transform.rotation.w << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
3. GetTfFromSensor()
功能：获取传感器外参变换关系
参数：
参数名	类型	描述
sensor_extrinsic_type	const SensorExtrinsicType&	传感器外参类型枚举
transform	Transform&	输出参数，变换信息对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，transform参数包含传感器外参变换信息
SensorExtrinsicType枚举详细说明
支持的传感器外参类型：

枚举值	描述
kUnknown	未知类型
kHeadLeftStereoToHeadRightStereo	头部左立体相机到右立体相机
kLeftHandDepthToLeftHandColor	左手深度相机到彩色相机
kRightHandDepthToRightHandColor	右手深度相机到彩色相机
kHeadDepthToHeadColor	头部深度相机到彩色相机
kHeadLeftStereoToHeadLink3	头部左立体相机到头部链接3
kHeadRightStereoToHeadLink3	头部右立体相机到头部链接3
kHeadLeftFisheyeToHeadLink3	头部左鱼眼相机到头部链接3
kHeadRightFisheyeToHeadLink3	头部右鱼眼相机到头部链接3
kHeadBackFisheyeToHeadLink3	头部后鱼眼相机到头部链接3
kChassisFrontLidarToBaseLink	底盘前激光雷达到base_link
kChassisBackLidarToBaseLink	底盘后激光雷达到base_link
kChassisBackLidarToChassisFrontLidar	底盘后激光雷达到前激光雷达
kChassisMid360ImuToChassisMid360Lidar	底盘Mid360 IMU到底盘Mid360激光雷达
kChassisImuToBaseLink	底盘IMU到base_link
kLeftHandRGBDToArmLEndLink	左手RGBD到左臂末端链接
kRightHandRGBDToArmREndLink	右手RGBD到右臂末端链接
kHeadRGBDToHeadLink3	头部RGBD到头部链接3
enum class SensorExtrinsicType {
  kUnknown = 0,
  kHeadLeftStereoToHeadRightStereo,
  kLeftHandDepthToLeftHandColor,
  kRightHandDepthToRightHandColor,
  kHeadDepthToHeadColor,
  kHeadLeftStereoToHeadLink3,
  kHeadRightStereoToHeadLink3,
  kHeadLeftFisheyeToHeadLink3,
  kHeadRightFisheyeToHeadLink3,
  kHeadBackFisheyeToHeadLink3,
  kChassisFrontLidarToBaseLink,
  kChassisBackLidarToBaseLink,
  kChassisBackLidarToChassisFrontLidar,
  kChassisMid360ImuToChassisMid360Lidar,
  kChassisImuToBaseLink,
  kLeftHandRGBDToArmLEndLink,
  kRightHandRGBDToArmREndLink,
  kHeadRGBDToHeadLink3
};
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::Transform transform;
    agibot::gdk::SensorExtrinsicType sensor_type =
        agibot::gdk::SensorExtrinsicType::kHeadLeftStereoToHeadRightStereo;

    if (tf.GetTfFromSensor(sensor_type, transform) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get sensor extrinsic transform" << std::endl;
    } else {
        std::cout << "传感器外参变换:" << std::endl;
        std::cout << "  平移: x=" << transform.translation.x
                  << ", y=" << transform.translation.y
                  << ", z=" << transform.translation.z << std::endl;
        std::cout << "  旋转: x=" << transform.rotation.x
                  << ", y=" << transform.rotation.y
                  << ", z=" << transform.rotation.z
                  << ", w=" << transform.rotation.w << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
4. LookupTransformLatest()
功能：查询两个坐标系之间的最新变换关系
参数：
参数名	类型	描述
target_frame	const std::string&	目标坐标系ID
source_frame	const std::string&	源坐标系ID
transform	Transform&	输出参数，变换信息对象（从source到target）
timestamp_ns	uint64_t*	输出参数，时间戳指针（可选，可为nullptr）
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，transform参数包含变换信息

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::Transform transform;
    uint64_t timestamp_ns = 0;

    // 查询从arm_l_end_link到base_link的最新变换
    if (tf.LookupTransformLatest("base_link", "arm_l_end_link", transform, &timestamp_ns)
        != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to lookup transform" << std::endl;
    } else {
        std::cout << "从arm_l_end_link到base_link的最新变换:" << std::endl;
        std::cout << "  平移: x=" << transform.translation.x
                  << ", y=" << transform.translation.y
                  << ", z=" << transform.translation.z << std::endl;
        std::cout << "  旋转: x=" << transform.rotation.x
                  << ", y=" << transform.rotation.y
                  << ", z=" << transform.rotation.z
                  << ", w=" << transform.rotation.w << std::endl;
        std::cout << "  时间戳: " << timestamp_ns << " ns" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
5. LookupTransform()
功能：查询两个坐标系在特定时间的变换关系（支持时间插值）
参数：
参数名	类型	描述
target_frame	const std::string&	目标坐标系ID
source_frame	const std::string&	源坐标系ID
time_ns	uint64_t	查询时间（纳秒时间戳）
transform	Transform&	输出参数，变换信息对象（从source到target）
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，transform参数包含变换信息

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 获取当前时间戳
    auto now = std::chrono::system_clock::now();
    uint64_t current_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count();

    // 查询1秒前的变换
    uint64_t target_time_ns = current_time_ns - 1000000000ULL; // 1秒前

    agibot::gdk::Transform transform;
    if (tf.LookupTransform("base_link", "arm_l_end_link", target_time_ns, transform)
        != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to lookup transform at time " << target_time_ns << std::endl;
    } else {
        std::cout << "从arm_l_end_link到base_link在时间 " << target_time_ns << " 的变换:" << std::endl;
        std::cout << "  平移: x=" << transform.translation.x
                  << ", y=" << transform.translation.y
                  << ", z=" << transform.translation.z << std::endl;
        std::cout << "  旋转: x=" << transform.rotation.x
                  << ", y=" << transform.rotation.y
                  << ", z=" << transform.rotation.z
                  << ", w=" << transform.rotation.w << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
6. CanTransform()
功能：检查两个坐标系之间是否存在变换关系
参数：
参数名	类型	描述
target_frame	const std::string&	目标坐标系ID
source_frame	const std::string&	源坐标系ID
返回值：bool，如果存在变换关系返回true，否则返回false

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 检查是否存在变换
    if (tf.CanTransform("base_link", "arm_l_end_link")) {
        std::cout << "存在从arm_l_end_link到base_link的变换" << std::endl;
    } else {
        std::cout << "不存在从arm_l_end_link到base_link的变换" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
7. GetAllFrameNames()
功能：获取所有可用的坐标系名称

参数：无

返回值：std::vector<std::string>，包含所有坐标系名称的列表

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 获取所有坐标系名称
    std::vector<std::string> frame_names = tf.GetAllFrameNames();
    std::cout << "所有可用坐标系 (" << frame_names.size() << " 个):" << std::endl;
    for (const auto& name : frame_names) {
        std::cout << "  - " << name << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
8. GetLatestTimestamp()
功能：获取指定坐标系的最新时间戳
参数：
参数名	类型	描述
frame_id	const std::string&	坐标系ID
timestamp_ns	uint64_t&	输出参数，最新时间戳（纳秒）
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，timestamp_ns参数包含最新时间戳

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    uint64_t timestamp_ns = 0;
    if (tf.GetLatestTimestamp("arm_l_end_link", timestamp_ns)
        != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get latest timestamp" << std::endl;
    } else {
        std::cout << "arm_l_end_link 最新时间戳: " << timestamp_ns << " ns" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
9. Clear()
功能：清空TF缓存中的所有变换关系

参数：无

返回值：无（void）

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::TF tf;
    std::cout << "TF init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 清空TF缓存
    tf.Clear();
    std::cout << "TF缓存已清空" << std::endl;

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
使用注意事项
GDK初始化：使用TF功能前必须先调用agibot::gdk::GDKInit()初始化GDK系统
GDK释放：程序结束前必须调用agibot::gdk::GDKRelease()释放GDK系统资源
初始化等待：创建TF对象后，建议等待1秒以确保DDS连接建立
坐标系命名：使用正确的坐标系名称，可通过GetAllFrameNames()获取所有可用坐标系的名称
时间戳精度：时间戳单位为纳秒，可用于精确的时间同步
变换矩阵：变换信息包含平移和旋转，可用于坐标转换计算
传感器标定：使用GetTfFromSensor()获取传感器外参，用于多传感器数据融合
实时性：变换关系会实时更新，反映机器人当前状态
错误处理：始终检查GDKRes返回值，确保操作成功
变换查询：LookupTransformLatest()查询最新变换，LookupTransform()支持时间插值查询历史变换
变换检查：使用CanTransform()在查询前检查变换是否存在，避免查询失败
时间插值：LookupTransform()支持时间插值，可以查询历史任意时刻的变换关系
缓存管理：使用Clear()可以清空TF缓存，适用于需要重置变换关系的场景
时间戳查询：GetLatestTimestamp()可以获取指定坐标系的最新更新时间
应用场景
坐标变换：实现不同坐标系之间的坐标转换
传感器标定：获取传感器外参，用于多传感器标定
多传感器融合：结合多个传感器的数据，提高感知精度
SLAM建图：为SLAM算法提供坐标系变换信息
路径规划：在规划路径时考虑不同部件的坐标系关系
视觉处理：将图像坐标转换为机器人坐标系
运动控制：在控制机器人运动时考虑坐标系变换
数据同步：基于时间戳进行多传感器数据同步
````

<a id="cpp-robot"></a>

## GDK Robot 接口文档（C++）

以下保留接口附件的纯文本排版，以避免改变代码缩进和参数表内容。

````text
概述
Robot（机器人）模块为G02机器人提供了统一的机器人控制接口，集成了机器人本体状态获取、运动控制、关节控制、末端执行器控制等功能。通过C++接口，开发者可以方便地实现对机器人的全面控制，适用于机器人控制、状态监控、动作执行、路径规划等多种场景。

接口说明
Robot 类
该类封装了机器人的主要控制接口，集成了HAL（硬件抽象层）和运动控制功能。

1. GetJointStates()
注意事项：使用motor_position和motor_velocity获取电机位置和速度，position和velocity为低速电机预留字段，当前版本无需关注
功能：获取机器人关节状态信息
参数：
参数名	类型	描述
joint_states	JointStates&	输出参数，关节状态信息对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，joint_states参数包含关节状态信息
JointStates对象详细说明
JointStates结构体包含以下成员：

成员名	类型	描述	单位
nums	size_t	关节数量	无单位
states	std::vector<JointState>	关节状态列表	关节状态列表
timestamp	uint64_t	时间戳	纳秒
struct JointStates {
  size_t nums{};                     ///< number of joint states
  std::vector<JointState> states{};  ///< joint states
  uint64_t timestamp{};              ///< joint states timestamp(ns)
};
JointState结构体：

成员名	类型	描述	单位
name	std::string	关节名称	字符串
mode	uint32_t	关节模式	无单位
position	double	关节位置	弧度
velocity	double	关节速度	弧度/秒
effort	double	关节力矩	N·m
motor_position	double	电机位置	弧度
motor_velocity	double	电机速度	弧度/秒
motor_current	double	电机电流	A
error_code	uint32_t	错误码，0表示正常	无单位
struct JointState {
  std::string name{};
  uint32_t mode{};
  double position{};
  double velocity{};
  double effort{};
  double motor_position{};
  double motor_velocity{};
  double motor_current{};
  uint32_t error_code{};
};
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::JointStates joint_states;
    if (robot.GetJointStates(joint_states) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get joint states" << std::endl;
    } else {
        std::cout << "关节数量: " << joint_states.nums << std::endl;
        std::cout << "时间戳: " << joint_states.timestamp << std::endl;
        for (const auto& joint_state : joint_states.states) {
            std::cout << "关节: " << joint_state.name
                      << ", 位置: " << joint_state.position
                      << ", 速度: " << joint_state.velocity
                      << ", 力矩: " << joint_state.effort
                      << ", 错误码: " << joint_state.error_code << std::endl;
        }
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
2. GetEndState()
功能：获取末端执行器状态信息
参数：
参数名	类型	描述
end_state	DualEndState&	输出参数，双末端执行器状态信息对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，end_state参数包含末端执行器状态信息
DualEndState对象详细说明
DualEndState结构体包含以下成员：

成员名	类型	描述	单位
left_end_state	EndState	左末端执行器状态	末端状态
right_end_state	EndState	右末端执行器状态	末端状态
struct DualEndState {
  EndState left_end_state{};
  EndState right_end_state{};
};
EndState结构体：

成员名	类型	描述	单位
controlled	bool	是否被控制	布尔值
type	uint32_t	末端执行器类型	无单位
names	std::vector<std::string>	关节名称列表	字符串列表
end_states	std::vector<MotorState>	电机状态列表	电机状态列表
struct EndState {
  bool controlled{};
  uint32_t type{};
  std::vector<std::string> names{};
  std::vector<MotorState> end_states{};
};
MotorState结构体：

成员名	类型	描述	单位
id	uint32_t	电机ID	无单位
enable	bool	是否使能	布尔值
position	double	电机位置	弧度
velocity	double	电机速度	弧度/秒
effort	double	电机力矩	N·m
current	float	电机电流	A
voltage	float	电机电压	V
temperature	float	电机温度	°C
status	uint32_t	电机状态	无单位
err_code	uint32_t	错误码	无单位
struct MotorState {
  uint32_t id = 0;
  bool enable = false;
  double position = 0.0;
  double velocity = 0.0;
  double effort = 0.0;
  float current = 0.0f;
  float voltage = 0.0f;
  float temperature = 0.0f;
  uint32_t status = 0;
  uint32_t err_code = 0;
};
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::DualEndState end_state;
    if (robot.GetEndState(end_state) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get end state" << std::endl;
    } else {
        std::cout << "左末端执行器状态:" << std::endl;
        std::cout << "  控制状态: " << (end_state.left_end_state.controlled ? "是" : "否") << std::endl;
        std::cout << "  类型: " << end_state.left_end_state.type << std::endl;
        for (const auto& motor_state : end_state.left_end_state.end_states) {
            std::cout << "  电机ID: " << motor_state.id
                      << ", 位置: " << motor_state.position
                      << ", 电流: " << motor_state.current
                      << ", 温度: " << motor_state.temperature << std::endl;
        }

        std::cout << "右末端执行器状态:" << std::endl;
        std::cout << "  控制状态: " << (end_state.right_end_state.controlled ? "是" : "否") << std::endl;
        std::cout << "  类型: " << end_state.right_end_state.type << std::endl;
        for (const auto& motor_state : end_state.right_end_state.end_states) {
            std::cout << "  电机ID: " << motor_state.id
                      << ", 位置: " << motor_state.position
                      << ", 电流: " << motor_state.current
                      << ", 温度: " << motor_state.temperature << std::endl;
        }
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
3. GetWholeBodyStatus()
功能：获取机器人全身状态信息
参数：
参数名	类型	描述
whole_body_status	WholeBodyStatus&	输出参数，全身状态信息对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，whole_body_status参数包含全身状态信息
WholeBodyStatus对象详细说明
WholeBodyStatus结构体包含以下成员：

成员名	类型	描述	单位
right_arm_error	uint32_t	右臂错误码	无单位
left_arm_error	uint32_t	左臂错误码	无单位
right_arm_control	bool	右臂控制状态	布尔值
left_arm_control	bool	左臂控制状态	布尔值
right_arm_estop	bool	右臂急停状态	布尔值
left_arm_estop	bool	左臂急停状态	布尔值
right_end_error	uint32_t	右末端执行器错误码	无单位
left_end_error	uint32_t	左末端执行器错误码	无单位
right_end_model	std::string	右末端执行器型号	字符串
left_end_model	std::string	左末端执行器型号	字符串
waist_error	uint32_t	腰部错误码	无单位
lift_error	uint32_t	升降错误码	无单位
neck_error	uint32_t	颈部错误码	无单位
chassis_error	uint32_t	底盘错误码	无单位
timestamp	uint64_t	时间戳	纳秒
struct WholeBodyStatus {
  uint32_t right_arm_error{0};
  uint32_t left_arm_error{0};
  bool right_arm_control{false};
  bool left_arm_control{false};
  bool right_arm_estop{false};
  bool left_arm_estop{false};
  uint32_t right_end_error{0};
  uint32_t left_end_error{0};
  std::string right_end_model{};
  std::string left_end_model{};
  uint32_t waist_error{0};
  uint32_t lift_error{0};
  uint32_t neck_error{0};
  uint32_t chassis_error{0};
  uint64_t timestamp{};
};
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::WholeBodyStatus whole_body_status;
    if (robot.GetWholeBodyStatus(whole_body_status) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get whole body status" << std::endl;
    } else {
        std::cout << "全身状态信息:" << std::endl;
        std::cout << "右臂错误码: " << whole_body_status.right_arm_error << std::endl;
        std::cout << "左臂错误码: " << whole_body_status.left_arm_error << std::endl;
        std::cout << "右臂控制状态: " << (whole_body_status.right_arm_control ? "是" : "否") << std::endl;
        std::cout << "左臂控制状态: " << (whole_body_status.left_arm_control ? "是" : "否") << std::endl;
        std::cout << "右臂急停状态: " << (whole_body_status.right_arm_estop ? "是" : "否") << std::endl;
        std::cout << "左臂急停状态: " << (whole_body_status.left_arm_estop ? "是" : "否") << std::endl;
        std::cout << "右末端执行器型号: " << whole_body_status.right_end_model << std::endl;
        std::cout << "左末端执行器型号: " << whole_body_status.left_end_model << std::endl;
        std::cout << "腰部错误码: " << whole_body_status.waist_error << std::endl;
        std::cout << "升降错误码: " << whole_body_status.lift_error << std::endl;
        std::cout << "颈部错误码: " << whole_body_status.neck_error << std::endl;
        std::cout << "底盘错误码: " << whole_body_status.chassis_error << std::endl;
        std::cout << "时间戳: " << whole_body_status.timestamp << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
4. GetMotionControlStatus()
功能：获取末端控制状态信息
参数：
参数名	类型	描述
status	MotionControlStatus&	输出参数，末端控制状态对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，status参数包含运动控制状态信息
MotionControlStatus对象详细说明
MotionControlStatus结构体包含以下成员：

成员名	类型	描述	单位
frame_names	std::vector<std::string>	末端关节名称列表	字符串列表
frame_poses	std::vector<Pose>	末端关节位姿列表	位姿列表
collision_pairs_1	std::vector<std::string>	碰撞对列表1	字符串列表
collision_pairs_2	std::vector<std::string>	碰撞对列表2	字符串列表
mode	uint8_t	运动模式	无单位
error_code	uint8_t	错误码，0表示正常	无单位
error_msg	std::string	错误信息	字符串
twists	std::vector<Twist>	速度信息列表	速度列表
wrenches	std::vector<Wrench>	力/力矩信息列表	力/力矩列表
mode数值说明：

数值	含义
0	停止
1	G1_伺服
2	路径规划
5	G2_伺服
struct MotionControlStatus {
  std::vector<std::string> frame_names{};
  std::vector<Pose> frame_poses{};
  std::vector<std::string> collision_pairs_1{};
  std::vector<std::string> collision_pairs_2{};
  uint8_t mode{};
  uint8_t error_code{};
  std::string error_msg{};
  std::vector<Twist> twists{};
  std::vector<Wrench> wrenches{};
};
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::MotionControlStatus status;
    if (robot.GetMotionControlStatus(status) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get motion control status" << std::endl;
    } else {
        std::cout << "末端控制状态:" << std::endl;
        std::cout << "模式: " << status.mode << std::endl;
        std::cout << "错误码: " << status.error_code << std::endl;
        std::cout << "错误信息: " << status.error_msg << std::endl;
        std::cout << "关节数量: " << status.frame_names.size() << std::endl;
        for (size_t i = 0; i < status.frame_names.size(); i++) {
            std::cout << "关节: " << status.frame_names[i]
                      << ", 位置: x=" << status.frame_poses[i].position.x
                      << ", y=" << status.frame_poses[i].position.y
                      << ", z=" << status.frame_poses[i].position.z << std::endl;
        }
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
5. GetChassisPowerState()
功能：获取底盘电源状态
参数：
参数名	类型	描述
chassis_power_state	ChassisPowerState&	底盘电源状态对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess
ChassisPowerState对象详细说明
ChassisPowerState结构体包含以下成员：

成员名	类型	描述	单位
battery_main_power_switch_state	uint8_t	电池主电源开关状态	无单位
emergency_stop_pedal_state	uint8_t	急停踏板状态	无单位
battery_main_power_switch_fault_state	uint8_t	电池主电源开关故障状态	无单位
emergency_stop_pedal_fault_state	uint8_t	急停踏板故障状态	无单位
chassis_power_board_state	uint8_t	底盘电源板状态	无单位
chassis_left_traction_motor_power_state	uint8_t	底盘左牵引电机电源状态	无单位
chassis_right_traction_motor_power_state	uint8_t	底盘右牵引电机电源状态	无单位
chassis_left_steering_motor_power_state	uint8_t	底盘左转向电机电源状态	无单位
chassis_right_steering_motor_power_state	uint8_t	底盘右转向电机电源状态	无单位
chassis_lidar1_power_state	uint8_t	底盘激光雷达1电源状态	无单位
chassis_lidar2_power_state	uint8_t	底盘激光雷达2电源状态	无单位
chassis_ultrasonic_radar_power_state	uint8_t	底盘超声波雷达电源状态	无单位
chassis_tof_camera_power_state	uint8_t	底盘ToF相机电源状态	无单位
chassis_ethernet_switch_power_state	uint8_t	底盘以太网交换机电源状态	无单位
chassis_external_power_output_state	uint8_t	底盘外部电源输出状态	无单位
battery_main_power_output_switch_state	uint8_t	电池主电源输出开关状态	无单位
battery_states	std::vector<BatteryState>	电池状态列表	电池状态列表
charge_plug_insert_state	uint8_t	充电插头插入状态	无单位
charge_plug_input_voltage	float	充电插头输入电压	V
charge_plug_input_current	float	充电插头输入电流	A
charge_plug_input_short_circuit_fault_state	uint8_t	充电插头输入短路故障状态	无单位
charge_plug_input_open_circuit_fault_state	uint8_t	充电插头输入开路故障状态	无单位
chassis_led_strip_power_state	uint8_t	底盘LED灯带电源状态	无单位
chassis_power_board_temperature	float	底盘电源板温度	°C
power_48v_bus_power_on_fault_state	uint8_t	48V总线电源故障状态	无单位
power_poe_bus_power_on_fault_state	uint8_t	PoE总线电源故障状态	无单位
chassis_board_12v_output_fault_state	uint8_t	底盘板12V输出故障状态	无单位
chassis_board_5v_output_fault_state	uint8_t	底盘板5V输出故障状态	无单位
chassis_power_board_fault_state	uint32_t	底盘电源板故障状态	无单位
timestamp	uint64_t	时间戳	纳秒
struct ChassisPowerState {
  uint8_t battery_main_power_switch_state{0};
  uint8_t emergency_stop_pedal_state{0};
  uint8_t battery_main_power_switch_fault_state{0};
  uint8_t emergency_stop_pedal_fault_state{0};
  uint8_t chassis_power_board_state{0};
  uint8_t chassis_left_traction_motor_power_state{0};
  uint8_t chassis_right_traction_motor_power_state{0};
  uint8_t chassis_left_steering_motor_power_state{0};
  uint8_t chassis_right_steering_motor_power_state{0};
  uint8_t chassis_lidar1_power_state{0};
  uint8_t chassis_lidar2_power_state{0};
  uint8_t chassis_ultrasonic_radar_power_state{0};
  uint8_t chassis_tof_camera_power_state{0};
  uint8_t chassis_ethernet_switch_power_state{0};
  uint8_t chassis_external_power_output_state{0};
  uint8_t battery_main_power_output_switch_state{0};
  std::vector<BatteryState> battery_states{};
  uint8_t charge_plug_insert_state{0};
  float charge_plug_input_voltage{0.0};
  float charge_plug_input_current{0.0};
  uint8_t charge_plug_input_short_circuit_fault_state{0};
  uint8_t charge_plug_input_open_circuit_fault_state{0};
  uint8_t chassis_led_strip_power_state{0};
  float chassis_power_board_temperature{0.0};
  uint8_t power_48v_bus_power_on_fault_state{0};
  uint8_t power_poe_bus_power_on_fault_state{0};
  uint8_t chassis_board_12v_output_fault_state{0};
  uint8_t chassis_board_5v_output_fault_state{0};
  uint32_t chassis_power_board_fault_state{0};
  uint64_t timestamp{0};
};
BatteryState结构体：

成员名	类型	描述	单位
battery_charging_status	uint8_t	电池充电状态	无单位
battery_output_voltage	float	电池输出电压	V
battery_output_current	float	电池输出电流	A
battery_charging_current	float	电池充电电流	A
battery_temperature	float	电池温度	°C
battery_soc	float	电池电量百分比 (State of Charge)	%
battery_soh	uint8_t	电池健康度 (State of Health)	%
battery_short_circuit_fault_state	uint8_t	电池短路故障状态	无单位
battery_open_circuit_fault_state	uint8_t	电池开路故障状态	无单位
battery_other_fault_state	uint8_t	电池其他故障状态	无单位
battery_outside_output_voltage	float	电池外部输出电压	V
battery_outside_connection	uint8_t	电池外部连接状态	无单位
battery_outside_open_circuit_fault_state	uint8_t	电池外部开路故障状态	无单位
battery_switch_state	uint8_t	电池开关状态	无单位
battery_unlock_state	uint8_t	电池解锁状态	无单位
battery_input_fault_state	uint8_t	电池输入故障状态	无单位
battery_charging_mos_switch_state	uint8_t	电池充电MOS开关状态	无单位
struct BatteryState {
  uint8_t battery_charging_status{0};
  float battery_output_voltage{0.0};
  float battery_output_current{0.0};
  float battery_charging_current{0.0};
  float battery_temperature{0.0};
  float battery_soc{0.0};
  uint8_t battery_soh{0};
  uint8_t battery_short_circuit_fault_state{0};
  uint8_t battery_open_circuit_fault_state{0};
  uint8_t battery_other_fault_state{0};
  float battery_outside_output_voltage{0.0};
  uint8_t battery_outside_connection{0};
  uint8_t battery_outside_open_circuit_fault_state{0};
  uint8_t battery_switch_state{0};
  uint8_t battery_unlock_state{0};
  uint8_t battery_input_fault_state{0};
  uint8_t battery_charging_mos_switch_state{0};
};
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::ChassisPowerState chassis_power_state;
    if (robot.GetChassisPowerState(chassis_power_state) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to get chassis power state" << std::endl;
    } else {
        std::cout << "底盘电源状态信息:" << std::endl;
        std::cout << "  电池主电源开关: " << (int)chassis_power_state.battery_main_power_switch_state << std::endl;
        std::cout << "  急停踏板状态: " << (int)chassis_power_state.emergency_stop_pedal_state << std::endl;
        std::cout << "  底盘电源板状态: " << (int)chassis_power_state.chassis_power_board_state << std::endl;
        std::cout << "  底盘电源板温度: " << chassis_power_state.chassis_power_board_temperature << "°C" << std::endl;
        std::cout << "  充电插头输入电压: " << chassis_power_state.charge_plug_input_voltage << "V" << std::endl;
        std::cout << "  充电插头输入电流: " << chassis_power_state.charge_plug_input_current << "A" << std::endl;
        std::cout << "  电池数量: " << chassis_power_state.battery_states.size() << std::endl;

        for (size_t i = 0; i < chassis_power_state.battery_states.size(); i++) {
            const auto& battery = chassis_power_state.battery_states[i];
            std::cout << "  电池 " << i << ":" << std::endl;
            std::cout << "    电量: " << battery.battery_soc << "%" << std::endl;
            std::cout << "    健康度: " << (int)battery.battery_soh << "%" << std::endl;
            std::cout << "    电压: " << battery.battery_output_voltage << "V" << std::endl;
            std::cout << "    电流: " << battery.battery_output_current << "A" << std::endl;
            std::cout << "    温度: " << battery.battery_temperature << "°C" << std::endl;
        }

        std::cout << "  时间戳: " << chassis_power_state.timestamp << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
6. GetChestPowerState()
功能：获取胸部电源状态
参数：
参数名	类型	描述
chest_power_state	ChestPowerState&	输出参数，胸部电源状态对象
返回值：GDKRes，操作结果状态码。
ChestPowerState对象详细说明
ChestPowerState结构体包含以下成员：

成员名	类型	描述	单位
power_onoff_req	uint8_t	开关机请求	无单位
emergency_stop_button_req	uint8_t	急停按钮请求	无单位
power_switch_fault_state	uint8_t	电源开关故障状态	无单位
emergency_stop_button_fault_state	uint8_t	急停按钮故障状态	无单位
power_full_low_req	uint8_t	电源全/低请求	无单位
chest_power_board_power_state	uint8_t	胸部电源板电源状态	无单位
domain_controller_power_state	uint8_t	域控制器电源状态	无单位
head_interactive_board_power_state	uint8_t	头部交互板电源状态	无单位
curved_screen_power_state	uint8_t	曲面屏电源状态	无单位
head_yaw_motor_power_state	uint8_t	头部偏航电机电源状态	无单位
head_pitch_motor_power_state	uint8_t	头部俯仰电机电源状态	无单位
head_roll_motor_power_state	uint8_t	头部滚转电机电源状态	无单位
waist_yaw_motor_power_state	uint8_t	腰部偏航电机电源状态	无单位
head_motor_short_circuit_fault_state	uint8_t	头部电机短路故障状态	无单位
waist_pitch_motor_power_state	uint8_t	腰部俯仰电机电源状态	无单位
leg_bending1_motor_power_state	uint8_t	腿部弯曲1电机电源状态	无单位
leg_bending2_motor_power_state	uint8_t	腿部弯曲2电机电源状态	无单位
leg_bending3_motor_power_state	uint8_t	腿部弯曲3电机电源状态	无单位
waist_motor_short_circuit_fault_state	uint8_t	腰部电机短路故障状态	无单位
left_arm_power_state	uint8_t	左臂电源状态	无单位
left_arm_motor_short_circuit_fault_state	uint8_t	左臂电机短路故障状态	无单位
left_arm_brake_enable_state	uint8_t	左臂刹车使能状态	无单位
right_arm_power_state	uint8_t	右臂电源状态	无单位
right_arm_motor_short_circuit_fault_state	uint8_t	右臂电机短路故障状态	无单位
right_arm_brake_enable_state	uint8_t	右臂刹车使能状态	无单位
fan_power_state	uint8_t	风扇电源状态	无单位
chest_power_board_fan_fault_state	uint8_t	胸部电源板风扇故障状态	无单位
body_fan1_fault_state	uint8_t	身体风扇1故障状态	无单位
body_fan2_fault_state	uint8_t	身体风扇2故障状态	无单位
body_fan3_fault_state	uint8_t	身体风扇3故障状态	无单位
body_fan4_fault_state	uint8_t	身体风扇4故障状态	无单位
upper_body_led_strip_power_state	uint8_t	上身LED灯带电源状态	无单位
poe_power_state	uint8_t	PoE电源状态	无单位
ipad_power_state	uint8_t	iPad电源状态	无单位
chest_reserved_lidar_power_state	uint8_t	胸部预留激光雷达电源状态	无单位
chest_power_board_temperature	float	胸部电源板温度	°C
chest_power_board_fault_state	uint32_t	胸部电源板故障状态	无单位
timestamp	uint64_t	时间戳	纳秒
struct ChestPowerState {
  uint8_t power_onoff_req{0};
  uint8_t emergency_stop_button_req{0};
  uint8_t power_switch_fault_state{0};
  uint8_t emergency_stop_button_fault_state{0};
  uint8_t power_full_low_req{0};
  uint8_t chest_power_board_power_state{0};
  uint8_t domain_controller_power_state{0};
  uint8_t head_interactive_board_power_state{0};
  uint8_t curved_screen_power_state{0};
  uint8_t head_yaw_motor_power_state{0};
  uint8_t head_pitch_motor_power_state{0};
  uint8_t head_roll_motor_power_state{0};
  uint8_t waist_yaw_motor_power_state{0};
  uint8_t head_motor_short_circuit_fault_state{0};
  uint8_t waist_pitch_motor_power_state{0};
  uint8_t leg_bending1_motor_power_state{0};
  uint8_t leg_bending2_motor_power_state{0};
  uint8_t leg_bending3_motor_power_state{0};
  uint8_t waist_motor_short_circuit_fault_state{0};
  uint8_t left_arm_power_state{0};
  uint8_t left_arm_motor_short_circuit_fault_state{0};
  uint8_t left_arm_brake_enable_state{0};
  uint8_t right_arm_power_state{0};
  uint8_t right_arm_motor_short_circuit_fault_state{0};
  uint8_t right_arm_brake_enable_state{0};
  uint8_t fan_power_state{0};
  uint8_t chest_power_board_fan_fault_state{0};
  uint8_t body_fan1_fault_state{0};
  uint8_t body_fan2_fault_state{0};
  uint8_t body_fan3_fault_state{0};
  uint8_t body_fan4_fault_state{0};
  uint8_t upper_body_led_strip_power_state{0};
  uint8_t poe_power_state{0};
  uint8_t ipad_power_state{0};
  uint8_t chest_reserved_lidar_power_state{0};
  float chest_power_board_temperature{0.0};
  uint32_t chest_power_board_fault_state{0};
  uint64_t timestamp{0};
};
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::ChestPowerState chest_state;
    if (robot.GetChestPowerState(chest_state) == agibot::gdk::GDKRes::kSuccess) {
        std::cout << "胸部电源状态信息:" << std::endl;
        std::cout << "  开关机请求: " << (int)chest_state.power_onoff_req << std::endl;
        std::cout << "  急停按钮请求: " << (int)chest_state.emergency_stop_button_req << std::endl;
        std::cout << "  胸部电源板状态: " << (int)chest_state.chest_power_board_power_state << std::endl;
        std::cout << "  胸部电源板温度: " << chest_state.chest_power_board_temperature << "°C" << std::endl;
        std::cout << "  域控制器电源: " << (int)chest_state.domain_controller_power_state << std::endl;
        std::cout << "  左臂电源: " << (int)chest_state.left_arm_power_state << std::endl;
        std::cout << "  右臂电源: " << (int)chest_state.right_arm_power_state << std::endl;
        std::cout << "  左臂刹车使能: " << (int)chest_state.left_arm_brake_enable_state << std::endl;
        std::cout << "  右臂刹车使能: " << (int)chest_state.right_arm_brake_enable_state << std::endl;
        std::cout << "  头部偏航电机电源: " << (int)chest_state.head_yaw_motor_power_state << std::endl;
        std::cout << "  头部俯仰电机电源: " << (int)chest_state.head_pitch_motor_power_state << std::endl;
        std::cout << "  头部滚转电机电源: " << (int)chest_state.head_roll_motor_power_state << std::endl;
        std::cout << "  风扇电源: " << (int)chest_state.fan_power_state << std::endl;
        std::cout << "  时间戳: " << chest_state.timestamp << std::endl;
    } else {
        std::cout << "Failed to get chest power state" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
7. JointControl()
功能：关节控制接口（路径规划控制），执行到目标位置后，接口返回。
参数：
参数名	类型	描述
joint_control_req	const JointControlReq&	关节控制请求对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess
JointControlReq对象详细说明
JointControlReq结构体包含以下成员：

成员名	类型	描述	单位
uuid	std::string	请求唯一标识	字符串
life_time	double	请求生命周期	秒
joint_names	std::vector<std::string>	关节名称列表	字符串列表
joint_positions	std::vector<double>	关节位置列表	弧度
joint_velocities	std::vector<double>	关节速度列表	弧度/秒
detail	std::string	详细信息	字符串
struct JointControlReq {
  double life_time{0.0};
  std::vector<std::string> joint_names{};
  std::vector<double> joint_positions{};
  std::vector<double> joint_velocities{};
  std::string uuid{};
  std::string detail{};
};
关节限位值说明
各关节的限位值（单位：弧度）如下：

关节名称	最小值	最大值
idx01_body_joint1	-1.082104	0.000174
idx02_body_joint2	-0.000174	2.652900
idx03_body_joint3	-1.919862	1.570970
idx04_body_joint4	-0.436332	0.436332
idx05_body_joint5	-3.045599	3.045599
idx11_head_joint1	-1.570970	1.570970
idx12_head_joint2	-0.349240	0.349240
idx13_head_joint3	-0.534773	0.534773
idx21_arm_l_joint1	-3.071796	3.071796
idx22_arm_l_joint2	-2.059505	2.059505
idx23_arm_l_joint3	-3.071796	3.071796
idx24_arm_l_joint4	-2.495838	1.012308
idx25_arm_l_joint5	-3.071796	3.071796
idx26_arm_l_joint6	-1.012308	1.012308
idx27_arm_l_joint7	-1.535907	1.535907
idx61_arm_r_joint1	-3.071796	3.071796
idx62_arm_r_joint2	-2.059505	2.059505
idx63_arm_r_joint3	-3.071796	3.071796
idx64_arm_r_joint4	-2.495838	1.012308
idx65_arm_r_joint5	-3.071796	3.071796
idx66_arm_r_joint6	-1.012308	1.012308
idx67_arm_r_joint7	-1.535907	1.535907
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <sstream>

std::string generate_uuid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);
    std::stringstream ss;
    ss << std::hex << dis(gen) << "-" << dis(gen) << "-" << dis(gen) << "-" << dis(gen);
    return ss.str();
}

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    agibot::gdk::JointControlReq joint_control;
    joint_control.life_time = 5.0;
    joint_control.joint_names = {"idx21_arm_l_joint1","idx22_arm_l_joint2","idx23_arm_l_joint3"};
    joint_control.joint_positions = {0.0, 0.0, 0.0};
    joint_control.joint_velocities = {0.0, 0.0, 0.0};
    joint_control.detail = "左臂关节控制";

    if (robot.JointControl(joint_control) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to control joints" << std::endl;
    } else {
        std::cout << "关节控制指令发送成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
8. MoveHeadJoint()
功能：头部关节位置规划控制接口，执行到目标位置后，接口返回。
参数：
参数名	类型	描述
positions	std::vector<double>&	头部关节位置列表, 按照"idx11_head_joint1", "idx12_head_joint2", "idx13_head_joint3"填写目标关节角
velocities	const std::vector<double>&	头部关节速度列表, 按照"idx11_head_joint1", "idx12_head_joint2", "idx13_head_joint3"填写目标关节速度
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<double> head_positions = {0.0, 0.0, 0.0};  // 头部关节位置
    std::vector<double> head_velocities = {0.3, 0.3, 0.3};  // 头部关节速度

    if (robot.MoveHeadJoint(head_positions, head_velocities) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move head position" << std::endl;
    } else {
        std::cout << "头部位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
9. MoveWaistJoint()
功能：腰部关节位置规划控制接口，执行到目标位置后，接口返回。
参数：
参数名	类型	描述
positions	std::vector<double>&	腰部关节位置列表, 按照"idx01_body_joint1", "idx02_body_joint2", "idx03_body_joint3", "idx04_body_joint4", "idx05_body_joint5"填写目标关节角
velocities	const std::vector<double>&	腰部关节速度列表, 按照"idx01_body_joint1", "idx02_body_joint2", "idx03_body_joint3", "idx04_body_joint4", "idx05_body_joint5"填写目标关节速度
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<double> waist_positions = {0.0, 0.0, 0.0, 0.0, 0.0};  // 腰部关节位置
    std::vector<double> waist_velocities = {0.3, 0.3, 0.3, 0.3, 0.3};  // 腰部关节速度

    if (robot.MoveWaistJoint(waist_positions, waist_velocities) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move waist position" << std::endl;
    } else {
        std::cout << "腰部位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
10. MoveArmJoint()
功能：手臂关节位置规划控制接口，执行到目标位置后，接口返回。
参数：
参数名	类型	描述
positions	std::vector<double>&	手臂关节位置列表, 按照"idx21_arm_l_joint1", "idx22_arm_l_joint2", "idx23_arm_l_joint3",
  "idx24_arm_l_joint4", "idx25_arm_l_joint5", "idx26_arm_l_joint6",
  "idx27_arm_l_joint7", "idx61_arm_r_joint1", "idx62_arm_r_joint2",
  "idx63_arm_r_joint3", "idx64_arm_r_joint4", "idx65_arm_r_joint5",
  "idx66_arm_r_joint6", "idx67_arm_r_joint7"填写目标关节角 |
| velocities | const std::vector<double>& | 手臂关节速度列表, 按照"idx21_arm_l_joint1", "idx22_arm_l_joint2", "idx23_arm_l_joint3", "idx24_arm_l_joint4", "idx25_arm_l_joint5", "idx26_arm_l_joint6", "idx27_arm_l_joint7", "idx61_arm_r_joint1", "idx62_arm_r_joint2", "idx63_arm_r_joint3", "idx64_arm_r_joint4", "idx65_arm_r_joint5", "idx66_arm_r_joint6", "idx67_arm_r_joint7"填写目标关节速度 | | control_group | const int | 控制组，0表示控制左臂，1表示控制右臂，2表示控制双臂 |

返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<double> arm_positions = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};  // 手臂关节位置
    std::vector<double> arm_velocities = {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3};  // 手臂关节速度

    if (robot.MoveArmJoint(arm_positions, arm_velocities, 2) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move arm position" << std::endl;
    } else {
        std::cout << "手臂位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
11. JointServoControl()
功能：关节位置伺服控制接口，需要以100hz的控制频率进行控制，支持正常模式和低延时模式，默认使用正常模式。
注意：低延时模式无碰撞保护，使用时注意安全。如需同时控制末端执行器，需要使用该接口下发控制明令，具体参考以下示例。
参数：
参数名	类型	描述
joint_servo_control_req	const JointServoControlReq&	关节位置伺服请求对象
enable_low_latency	bool	是否启用低延时模式，默认为false ｜
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess
JointServoControlReq对象详细说明
JointServoControlReq结构体包含以下成员：

成员名	类型	描述	单位
control_period	double	控制周期	秒
joint_names	std::vector<std::string>	关节名称列表	字符串列表
joint_positions	std::vector<double>	关节位置列表	弧度
joint_velocities	std::vector<double>	关节速度列表	弧度/秒
struct JointServoControlReq {
  double control_period{0.0};
  std::vector<std::string> joint_names{};
  std::vector<double> joint_positions{};
  std::vector<double> joint_velocities{};
};
参数说明：

control_period 表示控制周期，单位为秒，建议比当前控制频率稍大
joint_names、joint_positions、joint_velocities 三个列表的长度必须相同
joint_positions 中的值必须在对应关节的限位范围内（见下方关节限位值说明），否则返回 ErrorCode::kInvalidInput
joint_names、joint_positions、joint_velocities 不能为空，否则返回 ErrorCode::kInvalidInput
joint_velocities 预留参数，目前不使用，可以为空
关节限位值说明
各关节的限位值（单位：弧度）如下：

关节名称	最小值	最大值
idx01_body_joint1	-1.082104	0.000174
idx02_body_joint2	-0.000174	2.652900
idx03_body_joint3	-1.919862	1.570970
idx04_body_joint4	-0.436332	0.436332
idx05_body_joint5	-3.045599	3.045599
idx11_head_joint1	-1.570970	1.570970
idx12_head_joint2	-0.349240	0.349240
idx13_head_joint3	-0.534773	0.534773
idx21_arm_l_joint1	-3.071796	3.071796
idx22_arm_l_joint2	-2.059505	2.059505
idx23_arm_l_joint3	-3.071796	3.071796
idx24_arm_l_joint4	-2.495838	1.012308
idx25_arm_l_joint5	-3.071796	3.071796
idx26_arm_l_joint6	-1.012308	1.012308
idx27_arm_l_joint7	-1.535907	1.535907
idx61_arm_r_joint1	-3.071796	3.071796
idx62_arm_r_joint2	-2.059505	2.059505
idx63_arm_r_joint3	-3.071796	3.071796
idx64_arm_r_joint4	-2.495838	1.012308
idx65_arm_r_joint5	-3.071796	3.071796
idx66_arm_r_joint6	-1.012308	1.012308
idx67_arm_r_joint7	-1.535907	1.535907
末端执行器（omnipicker）
idx31_gripper_l_inner_joint1	-0.785	0
idx71_gripper_r_inner_joint1	-0.785	0
末端执行器（dahuan）
idx31_gripper_l_inner_joint1	0	0.025
idx71_gripper_r_inner_joint1	0	0.025
末端执行器（ctek90d）
idx31_gripper_l_inner_joint1	-0.91	0
idx71_gripper_r_inner_joint1	-0.91	0
末端执行器（灵巧手 o10_t2 左手）
idx31_hand_l_thumb_roll_joint	-1.1213740444063567	0.029670597283903602
idx32_hand_l_thumb_abad_joint	-0.04537856055185257	1.642354826126664
idx33_hand_l_thumb_mcp_joint	-0.8415977653116657	0.0
idx36_hand_l_index_abad_joint	0.0	0.16406094968746698
idx37_hand_l_index_pip_joint	0.0	1.4835298641951802
idx39_hand_l_middle_pip_joint	0.0	1.4835298641951802
idx41_hand_l_ring_abad_joint	-0.16929693744344995	0.0
idx42_hand_l_ring_pip_joint	0.0	1.4835298641951802
idx44_hand_l_pinky_abad_joint	-0.1850049007113989	0.0
idx45_hand_l_pinky_pip_joint	0.0	1.4835298641951802
末端执行器（灵巧手 o10_t2 右手）
idx71_hand_r_thumb_roll_joint	-0.029670597283903602	1.1213740444063567
idx72_hand_r_thumb_abad_joint	-1.642354826126664	0.04537856055185257
idx73_hand_r_thumb_mcp_joint	0.0	0.8415977653116657
idx76_hand_r_index_abad_joint	-0.16406094968746698	0.0
idx77_hand_r_index_pip_joint	0.0	1.4835298641951802
idx79_hand_r_middle_pip_joint	0.0	1.4835298641951802
idx81_hand_r_ring_abad_joint	0.0	0.16929693744344995
idx82_hand_r_ring_pip_joint	0.0	1.4835298641951802
idx84_hand_r_pinky_abad_joint	0.0	0.1850049007113989
idx85_hand_r_pinky_pip_joint	0.0	1.4835298641951802
末端执行器（灵巧手 o12_t2 左手）
idx31_hand_l_thumb_roll_joint	-0.9425	0.0
idx32_hand_l_thumb_abad_joint	0.0	1.3875
idx33_hand_l_thumb_mcp_joint	-0.8273	0.0
idx34_hand_l_thumb_pip_joint	-1.2915	0.0
idx36_hand_l_index_abad_joint	-0.2618	0.2618
idx37_hand_l_index_mcp_joint	0.0	1.3526
idx38_hand_l_index_pip_joint	0.0	1.5307
idx40_hand_l_middle_abad_joint	-0.2618	0.2618
idx41_hand_l_middle_mcp_joint	0.0	1.3579
idx42_hand_l_middle_pip_joint	0.0	1.8151
idx44_hand_l_ring_mcp_joint	0.0	1.5359
idx47_hand_l_pinky_mcp_joint	0.0	1.5359
末端执行器（灵巧手 o12_t2 右手）
idx71_hand_r_thumb_roll_joint	0.0	0.9425
idx72_hand_r_thumb_abad_joint	-1.3875	0.0
idx73_hand_r_thumb_mcp_joint	-0.8273	0.0
idx74_hand_r_thumb_pip_joint	-1.2915	0.0
idx76_hand_r_index_abad_joint	-0.2618	0.2618
idx77_hand_r_index_mcp_joint	0.0	1.3526
idx78_hand_r_index_pip_joint	0.0	1.5307
idx80_hand_r_middle_abad_joint	-0.2618	0.2618
idx81_hand_r_middle_mcp_joint	0.0	1.3579
idx82_hand_r_middle_pip_joint	0.0	1.8151
idx84_hand_r_ring_mcp_joint	0.0	1.5359
idx87_hand_r_pinky_mcp_joint	0.0	1.5359
错误处理：

如果 joint_names、joint_positions为空，返回 ErrorCode::kInvalidInput
如果 joint_positions 中的值超出对应关节的限位范围，返回 ErrorCode::kInvalidInput
如果配置解析器获取失败，返回 ErrorCode::kRuntimeError
其他错误情况返回相应的错误码
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

using namespace agibot::gdk;

// 控制参数
const double CONTROL_PERIOD = 0.01;  // 控制周期（秒）
const double RATE_HZ = 100.0;        // 发送频率（Hz）
const double DURATION = 5.0;         // 控制持续时间（秒）

class JointServoControlController {
private:
    Robot robot_;

    double getJointPositionByName(const JointStates& joint_states, const std::string& joint_name) {
        for (const auto& state : joint_states.states) {
            if (state.name == joint_name) {
                return state.motor_position;
            }
        }
        throw std::runtime_error("Joint name " + joint_name + " not found");
    }

    double interpolatePosition(double start_pos, double target_pos, double t) {
        return start_pos + t * (target_pos - start_pos);
    }

public:
    void executeJointServoControl(const std::vector<std::string>& target_joint_names,
                                   const std::vector<double>& target_positions) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 等待1秒

        // 获取当前关节状态
        JointStates current_joint_states;
        if (robot_.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
            std::cout << "获取关节状态失败" << std::endl;
            return;
        }
        std::cout << "当前关节数量: " << current_joint_states.nums << std::endl;

        // 获取起始位置
        std::vector<double> start_positions;
        for (const auto& joint_name : target_joint_names) {
            try {
                double pos = getJointPositionByName(current_joint_states, joint_name);
                start_positions.push_back(pos);
                std::cout << "关节 " << joint_name << " 当前位置: " << pos << " 弧度" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "错误: " << e.what() << std::endl;
                return;
            }
        }

        // 计算步数
        int n_steps = static_cast<int>(DURATION * RATE_HZ);
        std::cout << "总步数: " << n_steps << ", 持续时间: " << DURATION << " 秒" << std::endl;

        // 执行轨迹
        double dt = 1.0 / RATE_HZ;
        auto start_time = std::chrono::steady_clock::now();

        for (int i = 0; i < n_steps; i++) {
            double t = static_cast<double>(i) / (n_steps - 1);

            // 创建关节位置伺服请求
            JointServoControlReq joint_position_servo_req;
            joint_position_servo_req.control_period = CONTROL_PERIOD;

            // 计算当前目标位置（线性插值）
            std::vector<double> current_positions;
            for (size_t j = 0; j < target_joint_names.size(); j++) {
                double interp_pos = interpolatePosition(
                    start_positions[j], target_positions[j], t
                );
                current_positions.push_back(interp_pos);
            }

            joint_position_servo_req.joint_names = target_joint_names;
            joint_position_servo_req.joint_positions = current_positions;

            // 使用普通模式（enable_low_latency=false，默认值）
            auto res = robot_.JointServoControl(joint_position_servo_req);
            // 如需使用低延时模式，可传入 enable_low_latency=true：
            // auto res = robot_.JointServoControl(joint_position_servo_req, true);
            if (res != GDKRes::kSuccess) {
                std::cout << "控制命令发送失败，步数: " << i << std::endl;
                return;
            }

            // 控制发送频率
            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_time = std::chrono::milliseconds(static_cast<int>((i + 1) * dt * 1000));
            auto sleep_time = expected_time - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }

        std::cout << "关节位置伺服控制完成" << std::endl;

        // 保持最终位置
        std::cout << "进入最终位置保持（Ctrl+C 结束）..." << std::endl;
        try {
            while (true) {
                JointServoControlReq joint_position_servo_req;
                joint_position_servo_req.control_period = CONTROL_PERIOD;
                joint_position_servo_req.joint_names = target_joint_names;
                joint_position_servo_req.joint_positions = target_positions;

                // 使用普通模式（enable_low_latency=false，默认值）
                auto res = robot_.JointServoControl(joint_position_servo_req);
                // 如需使用低延时模式，可传入 enable_low_latency=true：
                // auto res = robot_.JointServoControl(joint_position_servo_req, true);
                if (res != GDKRes::kSuccess) {
                    std::cout << "保持位置失败" << std::endl;
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
            }
        } catch (const std::exception& e) {
            std::cout << "已中断保持: " << e.what() << std::endl;
        }
    }
};

int main() {
    // 初始化GDK系统
    if (GDKInit() != GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 获取当前关节状态
    JointStates current_joint_states;
    if (robot.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
        std::cout << "获取关节状态失败" << std::endl;
        GDKRelease();
        return -1;
    }
    std::cout << "当前关节数量: " << current_joint_states.nums << std::endl;

    // 定义要控制的关节（示例：左臂前3个关节）
    std::vector<std::string> target_joint_names = {
        "idx21_arm_l_joint1",
        "idx22_arm_l_joint2",
        "idx23_arm_l_joint3"
    };

    // 获取当前位置作为起始位置（用于插值）
    std::vector<double> start_positions;
    for (const auto& joint_name : target_joint_names) {
        bool found = false;
        for (const auto& state : current_joint_states.states) {
            if (state.name == joint_name) {
                start_positions.push_back(state.motor_position);
                std::cout << "关节 " << joint_name << " 当前位置: " << state.motor_position << " 弧度" << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "错误: 关节 " << joint_name << " 未找到" << std::endl;
            GDKRelease();
            return -1;
        }
    }

    // 设置目标角度（直接指定目标角度值，单位：弧度）
    std::vector<double> target_positions = {
        0.0,  // idx21_arm_l_joint1: 目标角度 0.0 弧度
        0.0,  // idx22_arm_l_joint2: 目标角度 0.0 弧度
        0.0   // idx23_arm_l_joint3: 目标角度 0.0 弧度
    };

    std::cout << "\n目标角度:" << std::endl;
    for (size_t i = 0; i < target_joint_names.size(); i++) {
        std::cout << "  " << target_joint_names[i] << ": " << target_positions[i] << " 弧度" << std::endl;
    }

    // 执行关节位置伺服控制
    JointServoControlController controller;
    controller.executeJointServoControl(
        target_joint_names, target_positions);

    // 释放GDK系统资源
    if (GDKRelease() != GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
同时控制机械臂与末端的示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace agibot::gdk;

const double CONTROL_PERIOD = 0.01;
const double RATE_HZ = 100.0;
const double DURATION = 3.0;
const double HOLD_DURATION = 0.5;    // 在 -0.785 或 0 处保持的时间（秒）
const int NUM_CYCLES = 3;            // 往复运动次数

static const std::vector<std::string> ARM_L_JOINT_NAMES = {
    "idx21_arm_l_joint1", "idx22_arm_l_joint2", "idx23_arm_l_joint3",
    "idx24_arm_l_joint4", "idx25_arm_l_joint5", "idx26_arm_l_joint6",
    "idx27_arm_l_joint7",
};

// 从 GetJointStates 的返回中按关节名取出位置列表
std::vector<double> getArmPositionsByName(const JointStates& joint_states,
                                          const std::vector<std::string>& joint_names) {
    std::vector<double> positions;
    for (const auto& name : joint_names) {
        for (const auto& state : joint_states.states) {
            if (state.name == name) {
                positions.push_back(state.motor_position);
                break;
            }
        }
    }
    return positions;
}

// 从 GetEndState 的返回中取出指定侧末端的关节名列表和位置列表
// use_left 为 true 取 left_end_state，为 false 取 right_end_state
void getEENamesAndPositions(const DualEndState& end_state,
                            bool use_left,
                            std::vector<std::string>& names,
                            std::vector<double>& positions) {
    const EndState& state = use_left ? end_state.left_end_state : end_state.right_end_state;
    names = state.names;
    positions.clear();
    for (const auto& motor : state.end_states) {
        positions.push_back(motor.position);
    }
}

int main() {
    if (GDKInit() != GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    Robot robot;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    JointStates joint_states;
    if (robot.GetJointStates(joint_states) != GDKRes::kSuccess) {
        std::cout << "获取关节状态失败" << std::endl;
        GDKRelease();
        return -1;
    }

    DualEndState end_state;
    if (robot.GetEndState(end_state) != GDKRes::kSuccess) {
        std::cout << "获取末端状态失败" << std::endl;
        GDKRelease();
        return -1;
    }

    std::vector<std::string> ee_names;
    std::vector<double> ee_positions;
    getEENamesAndPositions(end_state, true, ee_names, ee_positions);  // 左侧末端

    std::vector<std::string> all_names = ARM_L_JOINT_NAMES;
    all_names.insert(all_names.end(), ee_names.begin(), ee_names.end());

    std::vector<double> arm_positions = getArmPositionsByName(joint_states, ARM_L_JOINT_NAMES);
    if (arm_positions.size() != ARM_L_JOINT_NAMES.size()) {
        std::cout << "左臂关节数量不匹配" << std::endl;
        GDKRelease();
        return -1;
    }

    // 机械臂按之前方式做小幅关节空间运动（来回），末端关节在 -0.785 和 0 之间往复运动
    std::vector<double> arm_start = arm_positions;                    // 机械臂初始姿态
    std::vector<double> arm_target = arm_positions;                   // 机械臂目标姿态（小幅偏移）
    for (auto& v : arm_target) v += 0.05;
    const double ee_low = -0.785;                                     // 末端下限
    const double ee_high = 0.0;                                       // 末端上限

    std::cout << "控制关节数: 机械臂 " << ARM_L_JOINT_NAMES.size()
              << " + 末端 " << ee_names.size() << " = " << all_names.size() << std::endl;
    std::cout << "机械臂将在关节空间 arm_start ↔ arm_target 之间运动，末端关节在 "
              << ee_low << " 和 " << ee_high << " 之间往复 " << NUM_CYCLES << " 次" << std::endl;

    int n_steps = static_cast<int>(DURATION * RATE_HZ);           // 单次移动的步数
    int hold_steps = static_cast<int>(HOLD_DURATION * RATE_HZ);   // 保持阶段的步数
    double dt = 1.0 / RATE_HZ;

    // 辅助函数：发送控制命令
    auto sendControlCommand = [&](const std::vector<double>& arm_vals, const std::vector<double>& ee_vals) -> bool {
        std::vector<double> current = arm_vals;
        current.insert(current.end(), ee_vals.begin(), ee_vals.end());
        JointServoControlReq req;
        req.control_period = CONTROL_PERIOD;
        req.joint_names = all_names;
        req.joint_positions = current;
        req.joint_velocities = std::vector<double>(current.size(), 0.0);
        return robot.JointServoControl(req) == GDKRes::kSuccess;
    };

    for (int cycle = 0; cycle < NUM_CYCLES; cycle++) {
        std::cout << "\n=== 周期 " << (cycle + 1) << "/" << NUM_CYCLES
                  << ": 机械臂 arm_start -> arm_target, 末端 " << ee_low << " -> " << ee_high << " ===" << std::endl;
        auto start_time = std::chrono::steady_clock::now();

        // 第一段：机械臂 arm_start -> arm_target，末端 ee_low -> ee_high
        for (int i = 0; i < n_steps; i++) {
            double t = (n_steps > 1) ? static_cast<double>(i) / (n_steps - 1) : 1.0;
            std::vector<double> current_arm;
            for (size_t j = 0; j < arm_start.size(); j++) {
                current_arm.push_back(arm_start[j] + t * (arm_target[j] - arm_start[j]));
            }
            std::vector<double> current_ee(ee_names.size(), ee_low + t * (ee_high - ee_low));

            if (!sendControlCommand(current_arm, current_ee)) {
                std::cout << "发送失败，周期=" << (cycle + 1) << ", 阶段=0->1, 步数=" << i << std::endl;
                GDKRelease();
                return -1;
            }

            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_ms = static_cast<int>((i + 1) * dt * 1000);
            auto sleep_time = std::chrono::milliseconds(expected_ms) - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }

        // 第二段：在 arm_target / ee_high 处保持
        std::cout << "=== 周期 " << (cycle + 1) << "/" << NUM_CYCLES
                  << ": 在 arm_target / " << ee_high << " 处保持 " << HOLD_DURATION << " 秒 ===" << std::endl;
        start_time = std::chrono::steady_clock::now();
        std::vector<double> current_arm = arm_target;
        std::vector<double> current_ee(ee_names.size(), ee_high);

        for (int i = 0; i < hold_steps; i++) {
            if (!sendControlCommand(current_arm, current_ee)) {
                std::cout << "发送失败，周期=" << (cycle + 1) << ", 阶段=保持@1, 步数=" << i << std::endl;
                GDKRelease();
                return -1;
            }

            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_ms = static_cast<int>((i + 1) * dt * 1000);
            auto sleep_time = std::chrono::milliseconds(expected_ms) - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }

        // 第三段：机械臂 arm_target -> arm_start，末端 ee_high -> ee_low
        std::cout << "=== 周期 " << (cycle + 1) << "/" << NUM_CYCLES
                  << ": 机械臂 arm_target -> arm_start, 末端 " << ee_high << " -> " << ee_low << " ===" << std::endl;
        start_time = std::chrono::steady_clock::now();

        for (int i = 0; i < n_steps; i++) {
            double t = (n_steps > 1) ? static_cast<double>(i) / (n_steps - 1) : 1.0;
            std::vector<double> current_arm;
            for (size_t j = 0; j < arm_target.size(); j++) {
                current_arm.push_back(arm_target[j] + t * (arm_start[j] - arm_target[j]));
            }
            std::vector<double> current_ee(ee_names.size(), ee_high + t * (ee_low - ee_high));

            if (!sendControlCommand(current_arm, current_ee)) {
                std::cout << "发送失败，周期=" << (cycle + 1) << ", 阶段=1->0, 步数=" << i << std::endl;
                GDKRelease();
                return -1;
            }

            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_ms = static_cast<int>((i + 1) * dt * 1000);
            auto sleep_time = std::chrono::milliseconds(expected_ms) - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }

        // 第四段：在 arm_start / ee_low 处保持
        std::cout << "=== 周期 " << (cycle + 1) << "/" << NUM_CYCLES
                  << ": 在 arm_start / " << ee_low << " 处保持 " << HOLD_DURATION << " 秒 ===" << std::endl;
        start_time = std::chrono::steady_clock::now();
        current_arm = arm_start;
        current_ee = std::vector<double>(ee_names.size(), ee_low);

        for (int i = 0; i < hold_steps; i++) {
            if (!sendControlCommand(current_arm, current_ee)) {
                std::cout << "发送失败，周期=" << (cycle + 1) << ", 阶段=保持@0, 步数=" << i << std::endl;
                GDKRelease();
                return -1;
            }

            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_ms = static_cast<int>((i + 1) * dt * 1000);
            auto sleep_time = std::chrono::milliseconds(expected_ms) - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }
    }

    std::cout << "\n机械臂 arm_start↔arm_target、末端 " << ee_low << "↔" << ee_high << " 往复控制结束" << std::endl;

    if (GDKRelease() != GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;
    return 0;
}
12. MoveHeadJointServo()
功能：头部关节位置伺服控制接口，需要以100hz的控制频率进行控制，支持正常模式和低延时模式，默认使用正常模式。
注意：低延时模式无碰撞保护，使用时注意安全。
参数：
参数名	类型	描述
positions	const std::vector<double>&	头部关节位置列表（弧度），按照"idx11_head_joint1", "idx12_head_joint2", "idx13_head_joint3"顺序
control_period	const double	控制周期（秒），建议比控制频率稍大
enable_low_latency	const bool	是否启用低延时模式，默认为false
参数说明：

positions 长度必须为3
positions 中的值必须在对应关节的限位范围内（见下方关节限位值说明），否则返回 ErrorCode::kInvalidInput
control_period 表示控制周期，单位为秒，建议比控制频率稍大
enable_low_latency 用于选择控制通道，低延时模式适用于对实时性要求更高的场景
关节限位值说明
头部关节的限位值（单位：弧度）如下：

关节名称	最小值	最大值
idx11_head_joint1	-1.570970	1.570970
idx12_head_joint2	-0.349240	0.349240
idx13_head_joint3	-0.534773	0.534773
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

错误处理：

如果 positions 的长度不为3，返回 ErrorCode::kInvalidInput
如果 positions 中的值超出对应关节的限位范围，返回 ErrorCode::kInvalidInput
其他错误情况返回相应的错误码
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

using namespace agibot::gdk;

// 控制参数
const double CONTROL_PERIOD = 0.01;  // 控制周期（秒）
const double RATE_HZ = 100.0;        // 发送频率（Hz）
const double DURATION = 5.0;         // 控制持续时间（秒）

class HeadJointServoController {
private:
    Robot robot_;

    double getJointPositionByName(const JointStates& joint_states, const std::string& joint_name) {
        for (const auto& state : joint_states.states) {
            if (state.name == joint_name) {
                return state.motor_position;
            }
        }
        throw std::runtime_error("Joint name " + joint_name + " not found");
    }

    double interpolatePosition(double start_pos, double target_pos, double t) {
        return start_pos + t * (target_pos - start_pos);
    }

public:
    void executeHeadJointServoControl(const std::vector<double>& target_positions) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 等待1秒

        // 获取当前关节状态
        JointStates current_joint_states;
        if (robot_.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
            std::cout << "获取关节状态失败" << std::endl;
            return;
        }

        // 获取起始位置
        std::vector<std::string> head_joint_names = {
            "idx11_head_joint1", "idx12_head_joint2", "idx13_head_joint3"
        };
        std::vector<double> start_positions;
        for (const auto& joint_name : head_joint_names) {
            try {
                double pos = getJointPositionByName(current_joint_states, joint_name);
                start_positions.push_back(pos);
                std::cout << "关节 " << joint_name << " 当前位置: " << pos << " 弧度" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "错误: " << e.what() << std::endl;
                return;
            }
        }

        // 计算步数
        int n_steps = static_cast<int>(DURATION * RATE_HZ);
        std::cout << "总步数: " << n_steps << ", 持续时间: " << DURATION << " 秒" << std::endl;

        // 执行轨迹
        double dt = 1.0 / RATE_HZ;
        auto start_time = std::chrono::steady_clock::now();

        for (int i = 0; i < n_steps; i++) {
            double t = static_cast<double>(i) / (n_steps - 1);

            // 计算当前目标位置（线性插值）
            std::vector<double> current_positions;
            for (size_t j = 0; j < 3; j++) {
                double interp_pos = interpolatePosition(
                    start_positions[j], target_positions[j], t
                );
                current_positions.push_back(interp_pos);
            }

            // 使用普通模式（enable_low_latency=false，默认值）
            auto res = robot_.MoveHeadJointServo(
                current_positions, CONTROL_PERIOD);
            // 如需使用低延时模式，可传入 enable_low_latency=true：
            // auto res = robot_.MoveHeadJointServo(
            //     current_positions, target_velocities, CONTROL_PERIOD, true
            // );
            if (res != GDKRes::kSuccess) {
                std::cout << "控制命令发送失败，步数: " << i << std::endl;
                return;
            }

            // 控制发送频率
            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_time = std::chrono::milliseconds(static_cast<int>((i + 1) * dt * 1000));
            auto sleep_time = expected_time - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }

        std::cout << "头部关节位置伺服控制完成" << std::endl;

        // 保持最终位置
        std::cout << "进入最终位置保持（Ctrl+C 结束）..." << std::endl;
        try {
            while (true) {
                // 使用普通模式（enable_low_latency=false，默认值）
                auto res = robot_.MoveHeadJointServo(
                    target_positions, CONTROL_PERIOD);
                // 如需使用低延时模式，可传入 enable_low_latency=true：
                // auto res = robot_.MoveHeadJointServo(
                //     target_positions, target_velocities, CONTROL_PERIOD, true
                // );
                if (res != GDKRes::kSuccess) {
                    std::cout << "保持位置失败" << std::endl;
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
            }
        } catch (const std::exception& e) {
            std::cout << "已中断保持: " << e.what() << std::endl;
        }
    }
};

int main() {
    // 初始化GDK系统
    if (GDKInit() != GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 获取当前关节状态
    JointStates current_joint_states;
    if (robot.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
        std::cout << "获取关节状态失败" << std::endl;
        GDKRelease();
        return -1;
    }

    // 定义目标位置（示例：头部关节）
    std::vector<double> target_positions = {
        0.0,  // idx11_head_joint1: 目标角度 0.0 弧度
        0.0,  // idx12_head_joint2: 目标角度 0.0 弧度
        0.0   // idx13_head_joint3: 目标角度 0.0 弧度
    };

    std::cout << "\n目标角度:" << std::endl;
    std::vector<std::string> head_joint_names = {
        "idx11_head_joint1", "idx12_head_joint2", "idx13_head_joint3"
    };
    for (size_t i = 0; i < head_joint_names.size(); i++) {
        std::cout << "  " << head_joint_names[i] << ": " << target_positions[i] << " 弧度" << std::endl;
    }

    // 执行头部关节位置伺服控制
    HeadJointServoController controller;
    controller.executeHeadJointServoControl(target_positions);

    // 释放GDK系统资源
    if (GDKRelease() != GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
13. MoveWaistJointServo()
功能：腰部关节位置伺服控制接口，需要以100hz的控制频率进行控制，支持正常模式和低延时模式，默认使用正常模式。
注意：低延时模式无碰撞保护，使用时注意安全。
参数：
参数名	类型	描述
positions	const std::vector<double>&	腰部关节位置列表（弧度），按照"idx01_body_joint1", "idx02_body_joint2", "idx03_body_joint3", "idx04_body_joint4", "idx05_body_joint5"顺序
control_period	const double	控制周期（秒），建议比控制频率稍大
enable_low_latency	const bool	是否启用低延时模式，默认为false
参数说明：

positions 的长度必须为5
positions 中的值必须在对应关节的限位范围内（见下方关节限位值说明），否则返回 ErrorCode::kInvalidInput
control_period 表示控制周期，单位为秒，建议比控制频率稍大
enable_low_latency 用于选择控制通道，低延时模式适用于对实时性要求更高的场景
关节限位值说明
腰部关节的限位值（单位：弧度）如下：

关节名称	最小值	最大值
idx01_body_joint1	-1.082104	0.000174
idx02_body_joint2	-0.000174	2.652900
idx03_body_joint3	-1.919862	1.570970
idx04_body_joint4	-0.436332	0.436332
idx05_body_joint5	-3.045599	3.045599
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

错误处理：

如果 positions 的长度不为5，返回 ErrorCode::kInvalidInput
如果 positions 中的值超出对应关节的限位范围，返回 ErrorCode::kInvalidInput
其他错误情况返回相应的错误码
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

using namespace agibot::gdk;

// 控制参数
const double CONTROL_PERIOD = 0.01;  // 控制周期（秒）
const double RATE_HZ = 100.0;        // 发送频率（Hz）
const double DURATION = 5.0;         // 控制持续时间（秒）

class WaistJointServoController {
private:
    Robot robot_;

    double getJointPositionByName(const JointStates& joint_states, const std::string& joint_name) {
        for (const auto& state : joint_states.states) {
            if (state.name == joint_name) {
                return state.motor_position;
            }
        }
        throw std::runtime_error("Joint name " + joint_name + " not found");
    }

    double interpolatePosition(double start_pos, double target_pos, double t) {
        return start_pos + t * (target_pos - start_pos);
    }

public:
    void executeWaistJointServoControl(const std::vector<double>& target_positions) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 等待1秒

        // 获取当前关节状态
        JointStates current_joint_states;
        if (robot_.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
            std::cout << "获取关节状态失败" << std::endl;
            return;
        }

        // 获取起始位置
        std::vector<std::string> waist_joint_names = {
            "idx01_body_joint1", "idx02_body_joint2", "idx03_body_joint3",
            "idx04_body_joint4", "idx05_body_joint5"
        };
        std::vector<double> start_positions;
        for (const auto& joint_name : waist_joint_names) {
            try {
                double pos = getJointPositionByName(current_joint_states, joint_name);
                start_positions.push_back(pos);
                std::cout << "关节 " << joint_name << " 当前位置: " << pos << " 弧度" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "错误: " << e.what() << std::endl;
                return;
            }
        }

        // 计算步数
        int n_steps = static_cast<int>(DURATION * RATE_HZ);
        std::cout << "总步数: " << n_steps << ", 持续时间: " << DURATION << " 秒" << std::endl;

        // 执行轨迹
        double dt = 1.0 / RATE_HZ;
        auto start_time = std::chrono::steady_clock::now();

        for (int i = 0; i < n_steps; i++) {
            double t = static_cast<double>(i) / (n_steps - 1);

            // 计算当前目标位置（线性插值）
            std::vector<double> current_positions;
            for (size_t j = 0; j < 5; j++) {
                double interp_pos = interpolatePosition(
                    start_positions[j], target_positions[j], t
                );
                current_positions.push_back(interp_pos);
            }

            // 使用普通模式（enable_low_latency=false，默认值）
            auto res = robot_.MoveWaistJointServo(
                current_positions, CONTROL_PERIOD);
            // 如需使用低延时模式，可传入 enable_low_latency=true：
            // auto res = robot_.MoveWaistJointServo(
            //     current_positions, target_velocities, CONTROL_PERIOD, true
            // );
            if (res != GDKRes::kSuccess) {
                std::cout << "控制命令发送失败，步数: " << i << std::endl;
                return;
            }

            // 控制发送频率
            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_time = std::chrono::milliseconds(static_cast<int>((i + 1) * dt * 1000));
            auto sleep_time = expected_time - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }

        std::cout << "腰部关节位置伺服控制完成" << std::endl;

        // 保持最终位置
        std::cout << "进入最终位置保持（Ctrl+C 结束）..." << std::endl;
        try {
            while (true) {
                // 使用普通模式（enable_low_latency=false，默认值）
                auto res = robot_.MoveWaistJointServo(
                    target_positions, CONTROL_PERIOD);
                // 如需使用低延时模式，可传入 enable_low_latency=true：
                // auto res = robot_.MoveWaistJointServo(
                //     target_positions, target_velocities, CONTROL_PERIOD, true
                // );
                if (res != GDKRes::kSuccess) {
                    std::cout << "保持位置失败" << std::endl;
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
            }
        } catch (const std::exception& e) {
            std::cout << "已中断保持: " << e.what() << std::endl;
        }
    }
};

int main() {
    // 初始化GDK系统
    if (GDKInit() != GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 获取当前关节状态
    JointStates current_joint_states;
    if (robot.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
        std::cout << "获取关节状态失败" << std::endl;
        GDKRelease();
        return -1;
    }

    // 定义目标位置（示例：腰部关节）
    std::vector<double> target_positions = {
        0.0,  // idx01_body_joint1: 目标角度 0.0 弧度
        0.0,  // idx02_body_joint2: 目标角度 0.0 弧度
        0.0,  // idx03_body_joint3: 目标角度 0.0 弧度
        0.0,  // idx04_body_joint4: 目标角度 0.0 弧度
        0.0   // idx05_body_joint5: 目标角度 0.0 弧度
    };

    std::cout << "\n目标角度:" << std::endl;
    std::vector<std::string> waist_joint_names = {
        "idx01_body_joint1", "idx02_body_joint2", "idx03_body_joint3",
        "idx04_body_joint4", "idx05_body_joint5"
    };
    for (size_t i = 0; i < waist_joint_names.size(); i++) {
        std::cout << "  " << waist_joint_names[i] << ": " << target_positions[i] << " 弧度" << std::endl;
    }

    // 执行腰部关节位置伺服控制
    WaistJointServoController controller;
    controller.executeWaistJointServoControl(target_positions);

    // 释放GDK系统资源
    if (GDKRelease() != GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
14. MoveArmJointServo()
功能：手臂关节位置伺服控制接口，需要以100hz的控制频率进行控制，支持正常模式和低延时模式，默认使用正常模式。
注意：低延时模式无碰撞保护，使用时注意安全。
参数：
参数名	类型	描述
positions	const std::vector<double>&	手臂关节位置列表（弧度），按照"idx21_arm_l_joint1", "idx22_arm_l_joint2", "idx23_arm_l_joint3", "idx24_arm_l_joint4", "idx25_arm_l_joint5", "idx26_arm_l_joint6", "idx27_arm_l_joint7", "idx61_arm_r_joint1", "idx62_arm_r_joint2", "idx63_arm_r_joint3", "idx64_arm_r_joint4", "idx65_arm_r_joint5", "idx66_arm_r_joint6", "idx67_arm_r_joint7"顺序
control_period	const double	控制周期（秒），建议比控制频率稍大
control_group	const int	控制组，0表示控制左臂，1表示控制右臂，2表示控制双臂
enable_low_latency	const bool	是否启用低延时模式，默认为false
参数说明：

positions 的长度为7(左臂或右臂)或14(双臂)
positions 中的值必须在对应关节的限位范围内（见下方关节限位值说明），否则返回 ErrorCode::kInvalidInput
control_period 表示控制周期，单位为秒，建议比控制频率稍大
control_group 表示控制组，0表示控制左臂，1表示控制右臂，2表示控制双臂
enable_low_latency 用于选择控制通道，低延时模式适用于对实时性要求更高的场景
关节限位值说明
手臂关节的限位值（单位：弧度）如下：

关节名称	最小值	最大值
idx21_arm_l_joint1	-3.071796	3.071796
idx22_arm_l_joint2	-2.059505	2.059505
idx23_arm_l_joint3	-3.071796	3.071796
idx24_arm_l_joint4	-2.495838	1.012308
idx25_arm_l_joint5	-3.071796	3.071796
idx26_arm_l_joint6	-1.012308	1.012308
idx27_arm_l_joint7	-1.535907	1.535907
idx61_arm_r_joint1	-3.071796	3.071796
idx62_arm_r_joint2	-2.059505	2.059505
idx63_arm_r_joint3	-3.071796	3.071796
idx64_arm_r_joint4	-2.495838	1.012308
idx65_arm_r_joint5	-3.071796	3.071796
idx66_arm_r_joint6	-1.012308	1.012308
idx67_arm_r_joint7	-1.535907	1.535907
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

错误处理：

如果 positions 的长度不为7(左臂或右臂)或14(双臂)，返回 ErrorCode::kInvalidInput
如果 positions 中的值超出对应关节的限位范围，返回 ErrorCode::kInvalidInput
其他错误情况返回相应的错误码
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

using namespace agibot::gdk;

// 控制参数
const double CONTROL_PERIOD = 0.01;  // 控制周期（秒）
const double RATE_HZ = 100.0;        // 发送频率（Hz）
const double DURATION = 5.0;         // 控制持续时间（秒）

class ArmJointServoController {
private:
    Robot robot_;

    double getJointPositionByName(const JointStates& joint_states, const std::string& joint_name) {
        for (const auto& state : joint_states.states) {
            if (state.name == joint_name) {
                return state.motor_position;
            }
        }
        throw std::runtime_error("Joint name " + joint_name + " not found");
    }

    double interpolatePosition(double start_pos, double target_pos, double t) {
        return start_pos + t * (target_pos - start_pos);
    }

public:
    void executeArmJointServoControl(const std::vector<double>& target_positions, const int control_group) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 等待1秒

        // 获取当前关节状态
        JointStates current_joint_states;
        if (robot_.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
            std::cout << "获取关节状态失败" << std::endl;
            return;
        }

        // 获取起始位置
        std::vector<std::string> arm_joint_names = {
            "idx21_arm_l_joint1", "idx22_arm_l_joint2", "idx23_arm_l_joint3",
            "idx24_arm_l_joint4", "idx25_arm_l_joint5", "idx26_arm_l_joint6",
            "idx27_arm_l_joint7",  // 左臂7个关节
            "idx61_arm_r_joint1", "idx62_arm_r_joint2", "idx63_arm_r_joint3",
            "idx64_arm_r_joint4", "idx65_arm_r_joint5", "idx66_arm_r_joint6",
            "idx67_arm_r_joint7"   // 右臂7个关节
        };
        std::vector<double> start_positions;
        for (const auto& joint_name : arm_joint_names) {
            try {
                double pos = getJointPositionByName(current_joint_states, joint_name);
                start_positions.push_back(pos);
                std::cout << "关节 " << joint_name << " 当前位置: " << pos << " 弧度" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "错误: " << e.what() << std::endl;
                return;
            }
        }

        // 计算步数
        int n_steps = static_cast<int>(DURATION * RATE_HZ);
        std::cout << "总步数: " << n_steps << ", 持续时间: " << DURATION << " 秒" << std::endl;

        // 执行轨迹
        double dt = 1.0 / RATE_HZ;
        auto start_time = std::chrono::steady_clock::now();

        for (int i = 0; i < n_steps; i++) {
            double t = static_cast<double>(i) / (n_steps - 1);

            // 计算当前目标位置（线性插值）
            std::vector<double> current_positions;
            for (size_t j = 0; j < 14; j++) {
                double interp_pos = interpolatePosition(
                    start_positions[j], target_positions[j], t
                );
                current_positions.push_back(interp_pos);
            }

            // 使用普通模式（enable_low_latency=false，默认值）
            auto res = robot_.MoveArmJointServo(
                current_positions, CONTROL_PERIOD, control_group
            );
            // 如需使用低延时模式，可传入 enable_low_latency=true：
            // auto res = robot_.MoveArmJointServo(
            //     current_positions, CONTROL_PERIOD, control_group, true
            // );
            if (res != GDKRes::kSuccess) {
                std::cout << "控制命令发送失败，步数: " << i << std::endl;
                return;
            }

            // 控制发送频率
            auto elapsed = std::chrono::steady_clock::now() - start_time;
            auto expected_time = std::chrono::milliseconds(static_cast<int>((i + 1) * dt * 1000));
            auto sleep_time = expected_time - elapsed;
            if (sleep_time.count() > 0) {
                std::this_thread::sleep_for(sleep_time);
            }
        }

        std::cout << "手臂关节位置伺服控制完成" << std::endl;

        // 保持最终位置
        std::cout << "进入最终位置保持（Ctrl+C 结束）..." << std::endl;
        try {
            while (true) {
                // 使用普通模式（enable_low_latency=false，默认值）
                auto res = robot_.MoveArmJointServo(
                    target_positions, CONTROL_PERIOD, control_group
                );
                // 如需使用低延时模式，可传入 enable_low_latency=true：
                // auto res = robot_.MoveArmJointServo(
                //     target_positions, CONTROL_PERIOD, control_group, true
                // );
                if (res != GDKRes::kSuccess) {
                    std::cout << "保持位置失败" << std::endl;
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
            }
        } catch (const std::exception& e) {
            std::cout << "已中断保持: " << e.what() << std::endl;
        }
    }
};

int main() {
    // 初始化GDK系统
    if (GDKInit() != GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 获取当前关节状态
    JointStates current_joint_states;
    if (robot.GetJointStates(current_joint_states) != GDKRes::kSuccess) {
        std::cout << "获取关节状态失败" << std::endl;
        GDKRelease();
        return -1;
    }

    // 定义目标位置（示例：手臂关节）
    std::vector<double> target_positions = {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  // 左臂7个关节
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0   // 右臂7个关节
    };

    std::cout << "\n目标角度:" << std::endl;
    std::vector<std::string> arm_joint_names = {
        "idx21_arm_l_joint1", "idx22_arm_l_joint2", "idx23_arm_l_joint3",
        "idx24_arm_l_joint4", "idx25_arm_l_joint5", "idx26_arm_l_joint6",
        "idx27_arm_l_joint7",  // 左臂7个关节
        "idx61_arm_r_joint1", "idx62_arm_r_joint2", "idx63_arm_r_joint3",
        "idx64_arm_r_joint4", "idx65_arm_r_joint5", "idx66_arm_r_joint6",
        "idx67_arm_r_joint7"   // 右臂7个关节
    };
    for (size_t i = 0; i < arm_joint_names.size(); i++) {
        std::cout << "  " << arm_joint_names[i] << ": " << target_positions[i] << " 弧度" << std::endl;
    }

    // 执行手臂关节位置伺服控制
    ArmJointServoController controller;
    controller.executeArmJointServoControl(target_positions, 2);

    // 释放GDK系统资源
    if (GDKRelease() != GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
15. EndEffectorPoseControl()
功能：末端执行器位姿控制接口
注意：该接口要求发送端以50hz频率发布控制命令，不允许阶越信号；该接口无碰撞检测，注意使用时环境。
参数：
参数名	类型	描述
end_pose	const EndEffectorPose&	末端执行器位姿控制对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess
EndEffectorPose对象详细说明
EndEffectorPose结构体包含以下成员：

成员名	类型	描述	单位
life_time	double	控制生命周期	秒
group	int32_t	控制组，0: 未知，4: 左臂，8: 右臂，12: 双臂	无单位
left_end_effector_pose	Pose	左末端执行器位姿（base_link坐标系下）	位姿
right_end_effector_pose	Pose	右末端执行器位姿（base_link坐标系下）	位姿
struct EndEffectorPose {
  double life_time{0.0};
  int32_t group{0};
  Pose left_end_effector_pose{};
  Pose right_end_effector_pose{};
};
Pose结构体：

成员名	类型	描述	单位
position	Position	位置信息	米
orientation	Orientation	方向信息	四元数
Position结构体：

成员名	类型	描述	单位
x	double	X坐标	米
y	double	Y坐标	米
z	double	Z坐标	米
Orientation结构体：

成员名	类型	描述	单位
x	double	四元数X分量	无单位
y	double	四元数Y分量	无单位
z	double	四元数Z分量	无单位
w	double	四元数W分量	无单位
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace agibot::gdk;

const std::string LEFT_NAME = "arm_l_end_link";
const std::string RIGHT_NAME = "arm_r_end_link";
const int32_t CONTROL_GROUP = 12;  // kBothArms

const Pose TARGET_LEFT = {
    {0.516, 0.433, 1.081},  // position
    {0.382, -0.146, 0.663, 0.626}  // orientation
};

const Pose TARGET_RIGHT = {
    {0.579, -0.306, 1.158},  // position
    {0.320, 0.655, 0.651, 0.206}  // orientation
};

const double MAX_STEP_CM = 0.1;  // 最大步长（厘米）
const double LIFETIME = 0.02;    // 生命周期（秒）
const double RATE_HZ = 50.0;     // 发送频率（Hz）
const bool HOLD_FINAL = true;    // 是否保持最终位姿

class EndEffectorController {
private:
    Robot robot_;

    void slerp(const double q0[4], const double q1[4], double t, double result[4]) {
        double dot = q0[0]*q1[0] + q0[1]*q1[1] + q0[2]*q1[2] + q0[3]*q1[3];

        // 如果点积为负，取反q1以确保最短路径
        if (dot < 0.0) {
            dot = -dot;
            for (int i = 0; i < 4; i++) {
                result[i] = q0[i] + t * (-q1[i] - q0[i]);
            }
        } else {
            for (int i = 0; i < 4; i++) {
                result[i] = q0[i] + t * (q1[i] - q0[i]);
            }
        }

        // 限制点积范围
        dot = std::clamp(dot, -1.0, 1.0);

        if (dot > 0.9995) {
            // 线性插值
            double norm = 0.0;
            for (int i = 0; i < 4; i++) {
                norm += result[i] * result[i];
            }
            norm = std::sqrt(norm);
            if (norm > 0.0) {
                for (int i = 0; i < 4; i++) {
                    result[i] /= norm;
                }
            }
        } else {
            // 球面线性插值
            double theta_0 = std::acos(dot);
            double sin_theta_0 = std::sin(theta_0);
            double theta = theta_0 * t;
            double sin_theta = std::sin(theta);
            double s0 = std::cos(theta) - dot * sin_theta / sin_theta_0;
            double s1 = sin_theta / sin_theta_0;

            for (int i = 0; i < 4; i++) {
                result[i] = s0 * q0[i] + s1 * q1[i];
            }
        }
    }

    double distanceBetweenPoints(const Vector3& p1, const Vector3& p2) {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        double dz = p2.z - p1.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }

    int calculateNSteps(const Vector3& start, const Vector3& goal, double max_step_cm) {
        double dist_cm = distanceBetweenPoints(start, goal) * 100.0;
        return std::max(static_cast<int>(std::ceil(dist_cm / max_step_cm)), 1);
    }

    std::vector<Pose> planTrajectory(const Pose& start, const Pose& goal, int n_steps) {
        std::vector<Pose> trajectory;

        for (int i = 0; i < n_steps; i++) {
            double t = static_cast<double>(i) / (n_steps - 1);
            Pose pose;

            // 位置线性插值
            pose.position.x = start.position.x + t * (goal.position.x - start.position.x);
            pose.position.y = start.position.y + t * (goal.position.y - start.position.y);
            pose.position.z = start.position.z + t * (goal.position.z - start.position.z);

            // 四元数SLERP插值
            double q0[4] = {start.orientation.x, start.orientation.y, start.orientation.z, start.orientation.w};
            double q1[4] = {goal.orientation.x, goal.orientation.y, goal.orientation.z, goal.orientation.w};
            double result[4];
            slerp(q0, q1, t, result);

            pose.orientation.x = result[0];
            pose.orientation.y = result[1];
            pose.orientation.z = result[2];
            pose.orientation.w = result[3];

            trajectory.push_back(pose);
        }

        return trajectory;
    }

    Pose findPoseByName(const std::vector<std::string>& frame_names,
                       const std::vector<Pose>& frame_poses,
                       const std::string& target_name) {
        for (size_t i = 0; i < frame_names.size(); i++) {
            if (frame_names[i] == target_name) {
                return frame_poses[i];
            }
        }
        throw std::runtime_error("Frame name " + target_name + " not found");
    }

public:
    void executeEndPoseControl() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 等待1秒

        // 获取当前状态
        MotionControlStatus status;
        GDKRes result = robot_.GetMotionControlStatus(status);
        if (result != GDKRes::kSuccess) {
            std::cout << "获取运动控制状态失败" << std::endl;
            return;
        }

        // 获取起始位姿
        Pose start_left_pose = findPoseByName(status.frame_names, status.frame_poses, LEFT_NAME);
        Pose start_right_pose = findPoseByName(status.frame_names, status.frame_poses, RIGHT_NAME);

        // 计算步数
        int n_left = calculateNSteps(start_left_pose.position, TARGET_LEFT.position, MAX_STEP_CM);
        int n_right = calculateNSteps(start_right_pose.position, TARGET_RIGHT.position, MAX_STEP_CM);
        int n_steps = std::max(n_left, n_right);

        std::cout << "左臂步数: " << n_left << ", 右臂步数: " << n_right << ", 总步数: " << n_steps << std::endl;

        // 规划轨迹
        std::vector<Pose> traj_left = planTrajectory(start_left_pose, TARGET_LEFT, n_steps);
        std::vector<Pose> traj_right = planTrajectory(start_right_pose, TARGET_RIGHT, n_steps);

        // 执行轨迹
        double dt = 1.0 / RATE_HZ;
        for (int i = 0; i < n_steps; i++) {
            EndEffectorPose end_pose;
            end_pose.life_time = LIFETIME;
            end_pose.group = CONTROL_GROUP;
            end_pose.left_end_effector_pose = traj_left[i];
            end_pose.right_end_effector_pose = traj_right[i];

            result = robot_.EndEffectorPoseControl(end_pose);
            if (result != GDKRes::kSuccess) {
                std::cout << "控制命令发送失败，步数: " << i << std::endl;
                return;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
        }

        // 保持最终位姿（对应Python版本）
        if (HOLD_FINAL) {
            std::cout << "进入末端位姿保持（Ctrl+C 结束）..." << std::endl;
            try {
                while (true) {
                    EndEffectorPose end_pose;
                    end_pose.life_time = LIFETIME;
                    end_pose.group = CONTROL_GROUP;
                    end_pose.left_end_effector_pose = traj_left.back();
                    end_pose.right_end_effector_pose = traj_right.back();

                    result = robot_.EndEffectorPoseControl(end_pose);
                    if (result != GDKRes::kSuccess) {
                        std::cout << "保持位姿失败" << std::endl;
                        break;
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
                }
            } catch (const std::exception& e) {
                std::cout << "已中断保持: " << e.what() << std::endl;
            }
        }
    }
};

int main() {
    EndEffectorController controller;
    controller.executeEndPoseControl();
    return 0;
}
16. MoveEEPos()
功能：控制末端执行器位置
参数：
参数名	类型	描述
joint_states	const JointStates&	关节状态控制参数
JointStates对象详细说明（用于MoveEEPos）
JointStates结构体包含以下成员：

成员名	类型	描述	单位
nums	size_t	关节数量，应等于 states.size()	无单位
group	std::string	控制组，必须为 "left_tool"、"right_tool" 或 "dual_tool"	字符串
target_type	std::string	目标类型，支持的值见下表	字符串
states	std::vector<JointState>	关节状态列表（必需）	关节状态列表
target_type 支持的值及对应的关节数量要求：

target_type 值	关节数量要求	说明
"omnipicker"	1	全向抓取器，需要1个关节
"dahuan"	1	大环末端执行器，需要1个关节
"ctek90d"	1	CTEK90D末端执行器，需要1个关节
"o10_t2"	10	O10灵巧手末端执行器，需要10个关节
"o12_t2"	12	O12灵巧手节末端执行器，需要12个关节
各末端类型的关节位置取值范围：

注意：关节取值范围与版本绑定，使用时注意当前版本的取值范围，当前版本取值范围以文档为主

omnipicker：position 取值范围为 [-0.785,0]，其中 -0.785 表示打开，0 表示关闭

dahuan：position 取值范围为 [0,0.025]，其中 0 表示打开，0.025 表示关闭

ctek90d：position 取值范围为 [-0.91, 0]，其中 -0.91 表示打开，0 表示关闭

o10_t2：各关节位置取值范围如下（单位：弧度）

左手关节限位值：

关节索引	关节名称	最小值	最大值
0	idx31_hand_l_thumb_roll_joint	-1.1213740444063567	0.029670597283903602
1	idx32_hand_l_thumb_abad_joint	-0.04537856055185257	1.642354826126664
2	idx33_hand_l_thumb_mcp_joint	-0.8415977653116657	0.0
3	idx36_hand_l_index_abad_joint	0.0	0.16406094968746698
4	idx37_hand_l_index_pip_joint	0.0	1.4835298641951802
5	idx39_hand_l_middle_pip_joint	0.0	1.4835298641951802
6	idx41_hand_l_ring_abad_joint	-0.16929693744344995	0.0
7	idx42_hand_l_ring_pip_joint	0.0	1.4835298641951802
8	idx44_hand_l_pinky_abad_joint	-0.1850049007113989	0.0
9	idx45_hand_l_pinky_pip_joint	0.0	1.4835298641951802
右手关节限位值：

关节索引	关节名称	最小值	最大值
0	idx71_hand_r_thumb_roll_joint	-0.029670597283903602	1.1213740444063567
1	idx72_hand_r_thumb_abad_joint	-1.642354826126664	0.04537856055185257
2	idx73_hand_r_thumb_mcp_joint	0.0	0.8415977653116657
3	idx76_hand_r_index_abad_joint	-0.16406094968746698	0.0
4	idx77_hand_r_index_pip_joint	0.0	1.4835298641951802
5	idx79_hand_r_middle_pip_joint	0.0	1.4835298641951802
6	idx81_hand_r_ring_abad_joint	0.0	0.16929693744344995
7	idx82_hand_r_ring_pip_joint	0.0	1.4835298641951802
8	idx84_hand_r_pinky_abad_joint	0.0	0.1850049007113989
9	idx85_hand_r_pinky_pip_joint	0.0	1.4835298641951802
典型状态值：

左手开：[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
左手握：[-0.2, 1.45, -0.75, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0]
右手开：[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
右手握：[0.2, -1.45, 0.75, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0]
o12_t2：各关节位置取值范围如下（单位：弧度）

左手关节限位值：

关节索引	关节名称	最小值	最大值
0	idx31_hand_l_thumb_roll_joint	-0.9425	0.0
1	idx32_hand_l_thumb_abad_joint	0.0	1.3875
2	idx33_hand_l_thumb_mcp_joint	-0.8273	0.0
3	idx34_hand_l_thumb_pip_joint	-1.2915	0.0
4	idx36_hand_l_index_abad_joint	-0.2618	0.2618
5	idx37_hand_l_index_mcp_joint	0.0	1.3526
6	idx38_hand_l_index_pip_joint	0.0	1.5307
7	idx40_hand_l_middle_abad_joint	-0.2618	0.2618
8	idx41_hand_l_middle_mcp_joint	0.0	1.3579
9	idx42_hand_l_middle_pip_joint	0.0	1.8151
10	idx44_hand_l_ring_mcp_joint	0.0	1.5359
11	idx47_hand_l_pinky_mcp_joint	0.0	1.5359
右手关节限位值：

关节索引	关节名称	最小值	最大值
0	idx71_hand_r_thumb_roll_joint	0.0	0.9425
1	idx72_hand_r_thumb_abad_joint	-1.3875	0.0
2	idx73_hand_r_thumb_mcp_joint	-0.8273	0.0
3	idx74_hand_r_thumb_pip_joint	-1.2915	0.0
4	idx76_hand_r_index_abad_joint	-0.2618	0.2618
5	idx77_hand_r_index_mcp_joint	0.0	1.3526
6	idx78_hand_r_index_pip_joint	0.0	1.5307
7	idx80_hand_r_middle_abad_joint	-0.2618	0.2618
8	idx81_hand_r_middle_mcp_joint	0.0	1.3579
9	idx82_hand_r_middle_pip_joint	0.0	1.8151
10	idx84_hand_r_ring_mcp_joint	0.0	1.5359
11	idx87_hand_r_pinky_mcp_joint	0.0	1.5359
典型状态值：

左手开：[-0.53, 0.42, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
左手握：[-0.77, 0.5, -0.4, -0.36, -0.12, 0.69, 0.46, 0.0, 0.72, 0.5, 0.63, 0.63]
右手开：[0.53, -0.42, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
右手握：[0.77, -0.5, -0.4, -0.36, 0.12, 0.69, 0.46, 0.0, 0.72, 0.5, 0.63, 0.63]
参数说明：

group 必须为 "left_tool"（左末端执行器）、"right_tool"（右末端执行器）或 "dual_tool"（双末端执行器），其他值将返回 ErrorCode::kInvalidInput
当 group 为 "left_tool" 或 "right_tool" 时，states.size() 必须与 target_type 对应的关节数量要求完全匹配
当 group 为 "dual_tool" 时，states.size() 必须为 target_type 对应的关节数量要求的 2 倍（前半部分用于左末端执行器，后半部分用于右末端执行器）
target_type 必须为上述支持的值之一，其他值将返回 ErrorCode::kInvalidInput
nums 必须等于 states 向量的大小
states 不能为空，states.size() 必须大于0，否则返回 ErrorCode::kInvalidInput
JointState结构体：

成员名	类型	描述	单位
position	double	关节位置（必需）	开合度
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

错误处理：

如果 joint_states.states.size() <= 0，返回 ErrorCode::kInvalidInput
如果 target_type 不是支持的值（"omnipicker", "dahuan", "ctek90d", "o10_t2", "o12_t2"），返回 ErrorCode::kInvalidInput
如果 joint_states.states.size() 与 target_type 对应的关节数量要求不匹配（对于 "dual_tool"，必须是 2 倍），返回 ErrorCode::kInvalidInput
如果 group 不是 "left_tool"、"right_tool" 或 "dual_tool"，返回 ErrorCode::kInvalidInput
如果关节位置值超出对应末端类型的取值范围，返回 ErrorCode::kInvalidInput
其他错误情况返回相应的错误码
示例：

示例1：控制左夹爪（omnipicker类型，需要1个关节）

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 控制左夹爪（omnipicker类型，需要1个关节）
    agibot::gdk::JointStates left_joint_states;
    left_joint_states.group = "left_tool";
    left_joint_states.target_type = "omnipicker";
    left_joint_states.states.resize(1);
    left_joint_states.states[0].position = 0;  // 取值范围 [-0.785, 0]
    left_joint_states.nums = left_joint_states.states.size();

    if (robot.MoveEEPos(left_joint_states) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move left end effector position" << std::endl;
    } else {
        std::cout << "左末端执行器位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
示例2：控制右夹爪（dahuan类型，需要1个关节）

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 控制右夹爪（dahuan类型，需要1个关节）
    agibot::gdk::JointStates right_joint_states;
    right_joint_states.group = "right_tool";
    right_joint_states.target_type = "dahuan";
    right_joint_states.states.resize(1);
    right_joint_states.states[0].position = 0;  // 取值范围 [0, 0.025]
    right_joint_states.nums = right_joint_states.states.size();

    if (robot.MoveEEPos(right_joint_states) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move right end effector position" << std::endl;
    } else {
        std::cout << "右末端执行器位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
示例3：控制左夹爪（ctek90d类型，需要1个关节）

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 控制左夹爪（ctek90d类型，需要1个关节）
    agibot::gdk::JointStates left_joint_states;
    left_joint_states.group = "left_tool";
    left_joint_states.target_type = "ctek90d";
    left_joint_states.states.resize(1);
    left_joint_states.states[0].position = 0;  // 取值范围 [-0.91, 0]
    left_joint_states.nums = left_joint_states.states.size();

    if (robot.MoveEEPos(left_joint_states) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move left end effector position" << std::endl;
    } else {
        std::cout << "左末端执行器位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
示例4：控制左末端执行器（o10_t2类型，需要10个关节）

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 控制左末端执行器（o10_t2类型，需要10个关节）
    agibot::gdk::JointStates left_o10_states;
    left_o10_states.group = "left_tool";
    left_o10_states.target_type = "o10_t2";
    left_o10_states.states.resize(10);
    for (size_t i = 0; i < 10; ++i) {
        left_o10_states.states[i].position = 0.0;
    }
    left_o10_states.nums = left_o10_states.states.size();

    if (robot.MoveEEPos(left_o10_states) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move left end effector (o10_t2)" << std::endl;
    } else {
        std::cout << "左末端执行器（o10_t2）位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
示例5：控制右末端执行器（o12_t2类型，需要12个关节）

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 控制右末端执行器（o12_t2类型，需要12个关节）
    agibot::gdk::JointStates right_o12_states;
    right_o12_states.group = "right_tool";
    right_o12_states.target_type = "o12_t2";
    right_o12_states.states.resize(12);
    for (size_t i = 0; i < 12; ++i) {
        right_o12_states.states[i].position = 0.0;
    }
    right_o12_states.nums = right_o12_states.states.size();

    if (robot.MoveEEPos(right_o12_states) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move right end effector (o12_t2)" << std::endl;
    } else {
        std::cout << "右末端执行器（o12_t2）位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
示例6：控制双末端执行器（dual_tool，需要2倍关节数量）

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // 初始化GDK系统
    if (agibot::gdk::GDKInit() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK初始化失败" << std::endl;
        return -1;
    }
    std::cout << "GDK初始化成功" << std::endl;

    agibot::gdk::Robot robot;
    std::cout << "Robot init" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 控制双末端执行器（dual_tool，需要2倍关节数量）
    // 例如：使用 omnipicker 类型，需要 2 个关节（左1个 + 右1个）
    agibot::gdk::JointStates dual_states;
    dual_states.group = "dual_tool";
    dual_states.target_type = "omnipicker";
    dual_states.states.resize(2);
    // 前半部分用于左末端执行器
    dual_states.states[0].position = 0.0;
    // 后半部分用于右末端执行器
    dual_states.states[1].position = 0.0;
    dual_states.nums = dual_states.states.size();

    if (robot.MoveEEPos(dual_states) != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "Failed to move dual end effector" << std::endl;
    } else {
        std::cout << "双末端执行器位置控制成功" << std::endl;
    }

    // 释放GDK系统资源
    if (agibot::gdk::GDKRelease() != agibot::gdk::GDKRes::kSuccess) {
        std::cout << "GDK释放失败" << std::endl;
        return -1;
    }
    std::cout << "GDK释放成功" << std::endl;

    return 0;
}
使用注意事项
GDK初始化：使用Robot功能前必须先调用agibot::gdk::GDKInit()初始化GDK系统
GDK释放：程序结束前必须调用agibot::gdk::GDKRelease()释放GDK系统资源
初始化等待：创建Robot对象后，建议等待1秒以确保DDS连接建立
关节名称：使用前请确认关节名称的正确性，可通过GetJointStates()获取
位置范围：关节位置应在安全范围内，避免超出机械限制
速度限制：设置合理的关节速度，避免过快运动造成危险
生命周期：合理设置请求生命周期，避免命令过期
错误处理：及时检查返回值，处理可能的错误情况
控制组选择：末端执行器控制时选择合适的控制组（左臂/右臂/双臂）
位姿设置：设置末端执行器位姿时注意坐标系的正确性
状态监控：定期检查错误码，确保机器人安全运行
温度监控：注意电机温度，避免过热损坏
急停状态：检查急停状态，确保机器人可以正常控制
数据同步：基于时间戳进行多传感器数据同步
错误处理：始终检查GDKRes返回值，确保操作成功
应用场景
机器人控制：实现机器人的全面运动控制
状态监控：实时监控机器人各部件状态
动作执行：执行复杂的机器人动作序列
路径规划：结合状态信息进行路径规划
安全检测：监控机器人异常状态，确保安全运行
末端控制：精确控制末端执行器的位姿
双臂协调：实现双臂机器人的协调控制
关节控制：实现高精度的关节位置控制
故障诊断：通过错误码进行故障诊断和处理
数据融合：结合多传感器数据进行机器人控制
````

<a id="cpp-pnc"></a>

## GDK PNC 接口文档（C++）

以下保留接口附件的纯文本排版，以避免改变代码缩进和参数表内容。

````text
概述
PNC（Planning and Control，规划与控制）模块为G02机器人提供了路径规划和导航控制功能。通过C++接口，开发者可以方便地实现机器人的自主导航、路径规划、任务状态管理等功能，适用于自主导航、路径规划、任务调度等多种场景。

接口说明
Pnc 类
该类封装了机器人路径规划和导航控制的主要接口。

1. GetTaskState()
功能：获取当前任务状态
参数：
参数名	类型	描述
task_state	PNCTaskState&	输出参数，任务状态信息对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess，task_state参数包含任务状态信息
PNCTaskState对象详细说明
PNCTaskState结构体包含以下成员：

成员名	类型	描述	单位
id	uint32_t	任务ID	无单位
state	uint32_t	任务状态码	无单位
type	uint32_t	任务类型	无单位
message	std::string	状态描述信息	字符串
任务状态码说明：

0: 空闲
1: 启动中
2: 运行中
3: 暂停中
4: 已暂停
5: 恢复中
6: 取消中
7: 已取消
8: 失败
9: 成功
任务类型说明：

0: 空闲

1: 正常导航

2: 远程控制

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace agibot::gdk;

int main() {
    Pnc pnc;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待1秒以确保DDS连接建立
    PNCTaskState task_state;
    GDKRes result = pnc.GetTaskState(task_state);

    if (result == GDKRes::kSuccess) {
      std::cout << "PNC任务状态: " << task_state.state << std::endl;
      std::cout << "PNC任务ID: " << task_state.id << std::endl;
      std::cout << "PNC任务内容: " << task_state.message << std::endl;
      std::cout << "PNC任务种类: " << task_state.type << std::endl;
    } else {
      std::cout << "获取任务状态失败" << std::endl;
    }

    return 0;
}
2. NormalNavi()
功能：执行正常导航到指定目标点, 执行之前需要在G02 Pad上进行重定位
参数：
参数名	类型	描述
navi_req	const NaviReq&	导航请求对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess
NaviReq对象详细说明
NaviReq结构体包含以下成员：

成员名	类型	描述	单位
target	Pose	目标位姿	位姿
timestamp_ns	uint64_t	导航时间戳	纳秒
Pose结构体：

成员名	类型	描述
position	Position	位置信息
orientation	Orientation	方向信息
Position结构体：

成员名	类型	描述	单位
x	double	目标位置X坐标	米
y	double	目标位置Y坐标	米
z	double	目标位置Z坐标	米
Orientation结构体：

成员名	类型	描述	单位
x	double	目标方向四元数X分量	无单位
y	double	目标方向四元数Y分量	无单位
z	double	目标方向四元数Z分量	无单位
w	double	目标方向四元数W分量	无单位
示例：

#include "gdk/gdk.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace agibot::gdk;

int main() {
    Pnc pnc;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待1秒以确保DDS连接建立
    NaviReq navi_req;
    navi_req.target.position.x = 2.0;  // 目标X坐标
    navi_req.target.position.y = 3.0;  // 目标Y坐标
    navi_req.target.position.z = 0.0;  // 目标Z坐标
    navi_req.target.orientation.x = 0.0;  // 目标方向四元数X
    navi_req.target.orientation.y = 0.0;  // 目标方向四元数Y
    navi_req.target.orientation.z = 0.0;  // 目标方向四元数Z
    navi_req.target.orientation.w = 1.0;  // 目标方向四元数W
    navi_req.timestamp_ns = 0;  // 时间戳

    GDKRes result = pnc.NormalNavi(navi_req);

    if (result == GDKRes::kSuccess) {
        std::cout << "正常导航启动成功" << std::endl;
    } else {
        std::cout << "正常导航启动失败" << std::endl;
    }

    return 0;
}
3. HighPrecisionNavi()
功能：执行高精度导航到指定目标点, 执行之前需要在G02 Pad上进行重定位
参数：
参数名	类型	描述
navi_req	const NaviReq&	导航请求对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include <iostream>

using namespace agibot::gdk;

int main() {
    Pnc pnc;

    NaviReq navi_req;
    navi_req.target.position.x = 1.5;  // 目标X坐标
    navi_req.target.position.y = 2.5;  // 目标Y坐标
    navi_req.target.position.z = 0.0;  // 目标Z坐标
    navi_req.target.orientation.x = 0.0;  // 目标方向四元数X
    navi_req.target.orientation.y = 0.0;  // 目标方向四元数Y
    navi_req.target.orientation.z = 0.0;  // 目标方向四元数Z
    navi_req.target.orientation.w = 1.0;  // 目标方向四元数W
    navi_req.timestamp_ns = 0;  // 时间戳

    GDKRes result = pnc.HighPrecisionNavi(navi_req);

    if (result == GDKRes::kSuccess) {
        std::cout << "高精度导航启动成功" << std::endl;
    } else {
        std::cout << "高精度导航启动失败" << std::endl;
    }

    return 0;
}
4. RelativeMove()
功能：执行小范围平移, 简单停障，无避障，执行之前需要在G02 Pad上进行重定位
参数：
参数名	类型	描述
navi_req	const NaviReq&	导航请求对象
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include <iostream>

using namespace agibot::gdk;

int main() {
    Pnc pnc;

    NaviReq navi_req;
    navi_req.target.position.x = 0.5;  // 相对X移动距离
    navi_req.target.position.y = 0.0;  // 相对Y移动距离
    navi_req.target.position.z = 0.0;  // 相对Z移动距离
    navi_req.target.orientation.x = 0.0;  // 相对旋转X
    navi_req.target.orientation.y = 0.0;  // 相对旋转Y
    navi_req.target.orientation.z = 0.0;  // 相对旋转Z
    navi_req.target.orientation.w = 1.0;  // 相对旋转W
    navi_req.timestamp_ns = 0;  // 时间戳

    GDKRes result = pnc.RelativeMove(navi_req);

    if (result == GDKRes::kSuccess) {
        std::cout << "相对移动启动成功" << std::endl;
    } else {
        std::cout << "相对移动启动失败" << std::endl;
    }

    return 0;
}
5. CancelTask()
功能：取消指定ID的导航任务
参数：
参数名	类型	描述
task_id	uint32_t	要取消的任务ID
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include <iostream>

using namespace agibot::gdk;

int main() {
    Pnc pnc;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 先获取当前任务状态以获取任务ID
    PNCTaskState task_state;
    if (pnc.GetTaskState(task_state) == GDKRes::kSuccess) {
        uint32_t task_id = task_state.id;
        GDKRes result = pnc.CancelTask(task_id);

        if (result == GDKRes::kSuccess) {
            std::cout << "任务取消成功" << std::endl;
        } else {
            std::cout << "任务取消失败" << std::endl;
        }
    }

    return 0;
}
6. PauseTask()
功能：暂停指定ID的导航任务
参数：
参数名	类型	描述
task_id	uint32_t	要暂停的任务ID
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace agibot::gdk;

int main() {
    Pnc pnc;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 先获取当前任务状态以获取任务ID
    PNCTaskState task_state;
    if (pnc.GetTaskState(task_state) == GDKRes::kSuccess) {
        uint32_t task_id = task_state.id;
        GDKRes result = pnc.PauseTask(task_id);

        if (result == GDKRes::kSuccess) {
            std::cout << "任务暂停成功" << std::endl;
        } else {
            std::cout << "任务暂停失败" << std::endl;
        }
    }

    return 0;
}
7. ResumeTask()
功能：恢复指定ID的导航任务
参数：
参数名	类型	描述
task_id	uint32_t	要恢复的任务ID
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace agibot::gdk;

int main() {
    Pnc pnc;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 先获取当前任务状态以获取任务ID
    PNCTaskState task_state;
    if (pnc.GetTaskState(task_state) == GDKRes::kSuccess) {
        uint32_t task_id = task_state.id;
        GDKRes result = pnc.ResumeTask(task_id);

        if (result == GDKRes::kSuccess) {
            std::cout << "任务恢复成功" << std::endl;
        } else {
            std::cout << "任务恢复失败" << std::endl;
        }
    }

    return 0;
}
8. RequestChassisControl()
功能：请求底盘控制权限，用于远程控制模式
参数：
参数名	类型	描述
control_mode	int32_t	控制请求：0
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess
控制模式说明：

阿克曼模式：适用于前轮转向的车辆运动学模型，通过线速度(linear.x)和角速度(angular.z)控制

蟹行模式：支持全向移动，通过linear.x和linear.y分别控制前后和左右移动

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace agibot::gdk;

int main() {
    Pnc pnc;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 请求远程控制
    GDKRes res = pnc.RequestChassisControl(0);
    if (res == GDKRes::kSuccess) {
        std::cout << "远程控制请求成功" << std::endl;
    } else {
        std::cout << "控制请求失败" << std::endl;
        return 1;
    }

    // 等待控制权限生效
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 现在可以使用 MoveChassis() 控制底盘
    Twist twist;
    twist.linear.x = 0.3;
    twist.angular.z = 0.0;
    pnc.MoveChassis(twist);

    return 0;
}
9. MoveChassis()
功能：移动底盘，用于远程控制模式下的底盘运动控制
参数：
参数名	类型	描述
twist	const Twist&	速度指令对象，包含线速度和角速度
返回值：GDKRes，操作结果状态码。成功时返回GDKRes::kSuccess
Twist对象详细说明
Twist结构体包含以下成员：

成员名	类型	描述	单位
linear	Vector3	线速度向量	米/秒 (m/s)
angular	Vector3	角速度向量	弧度/秒 (rad/s)
Vector3结构体：

成员名	类型	描述	单位
x	double	X轴分量	根据上下文
y	double	Y轴分量	根据上下文
z	double	Z轴分量	根据上下文
使用说明：

在调用MoveChassis()之前，需要先调用RequestChassisControl()请求底盘控制权限

linear.x：前进/后退速度（正值为前进，负值为后退）

linear.y：左右平移速度（蟹行模式使用，正值为左移，负值为右移）

linear.z：通常为0

angular.z：绕Z轴旋转角速度（正值为逆时针，负值为顺时针）

示例：

#include "gdk/gdk.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace agibot::gdk;

int main() {
    Pnc pnc;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 请求底盘控制权限
    GDKRes res = pnc.RequestChassisControl(0);
    if (res != GDKRes::kSuccess) {
        std::cout << "请求底盘控制失败" << std::endl;
        return 1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 阿克曼模式：前进并右转
    Twist twist;
    twist.linear.x = 0.5;   // 前进速度 0.5 m/s
    twist.linear.y = 0.0;
    twist.linear.z = 0.0;
    twist.angular.x = 0.0;
    twist.angular.y = 0.0;
    twist.angular.z = -0.3; // 右转角速度 0.3 rad/s

    res = pnc.MoveChassis(twist);
    if (res == GDKRes::kSuccess) {
        std::cout << "底盘移动指令发送成功" << std::endl;
    }

    // 运行一段时间后停止
    std::this_thread::sleep_for(std::chrono::seconds(2));

    res = pnc.get_task_state(task_state);
    if (res == GDKRes::kSuccess) {
        std::cout << "任务状态: " << task_state.state << std::endl;
    } else {
        std::cout << "获取任务状态失败" << std::endl;
    }
    auto task_id = task_state.id;
    res = pnc.CancelTask(task_id);
    if (res != GDKRes::kSuccess) {
        std::cout << "任务取消失败" << std::endl;
    }

    // 蟹行模式：向左平移
    Twist twist;
    twist.linear.x = 0.0;
    twist.linear.y = 0.5; // 向左平移速度 0.5 m/s
    twist.linear.z = 0.0;
    twist.angular.x = 0.0;
    twist.angular.y = 0.0;
    twist.angular.z = 0.0;
    pnc.MoveChassis(twist);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    res = pnc.get_task_state(task_state);
    if (res == GDKRes::kSuccess) {
        std::cout << "任务状态: " << task_state.state << std::endl;
    } else {
        std::cout << "获取任务状态失败" << std::endl;
    }
    auto task_id = task_state.id;
    res = pnc.CancelTask(task_id);
    if (res != GDKRes::kSuccess) {
        std::cout << "任务取消失败" << std::endl;
    }

    return 0;
}
10. 完整使用示例
功能：演示PNC模块的完整使用流程

示例：

  #include <iostream>
  #include <chrono>
  #include <thread>
  #include <csignal>
  #include "gdk/gdk.h"

  void signal_handler(int signum) {
      std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
      exit(signum);
  }

  int main(int argc, char** argv) {
      if (argc != 8) {
          std::cerr << "Usage: " << argv[0]
                  << " position_x position_y position_z orientation_x "
                      "orientation_y orientation_z orientation_w"
                  << std::endl;
          return 1;
      }
      double position_x = std::stod(argv[1]);
      double position_y = std::stod(argv[2]);
      double position_z = std::stod(argv[3]);
      double orientation_x = std::stod(argv[4]);
      double orientation_y = std::stod(argv[5]);
      double orientation_z = std::stod(argv[6]);
      double orientation_w = std::stod(argv[7]);
      agibot::gdk::Pnc pnc;
      std::cout << "Pnc init" << std::endl;
      agibot::gdk::NaviReq navi_req;
      navi_req.target.position.x = position_x;
      navi_req.target.position.y = position_y;
      navi_req.target.position.z = position_z;
      navi_req.target.orientation.x = orientation_x;
      navi_req.target.orientation.y = orientation_y;
      navi_req.target.orientation.z = orientation_z;
      navi_req.target.orientation.w = orientation_w;

      std::this_thread::sleep_for(std::chrono::seconds(1));

      auto res = pnc.NormalNavi(navi_req);
      if (res != agibot::gdk::GDKRes::kSuccess) {
          std::cerr << "NormalNavi failed" << std::endl;
          return 1;
      }
      // std::this_thread::sleep_for(std::chrono::seconds(1));

      // 获取任务ID
      agibot::gdk::PNCTaskState task_state;
      res = pnc.GetTaskState(task_state);
      if (res != agibot::gdk::GDKRes::kSuccess) {
          std::cerr << "GetTaskState failed" << std::endl;
          return 1;
      }
      uint32_t task_id = task_state.id;

      std::cout << "PauseTask" << std::endl;
      res = pnc.PauseTask(task_id);

      if (res != agibot::gdk::GDKRes::kSuccess) {
          std::cerr << "PauseTask failed" << std::endl;
          return 1;
      }
      std::cout << "ResumeTask" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      res = pnc.ResumeTask(task_id);
      if (res != agibot::gdk::GDKRes::kSuccess) {
          std::cerr << "ResumeTask failed" << std::endl;
          return 1;
      }
      std::cout << "CancelTask" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      res = pnc.CancelTask(task_id);
      if (res != agibot::gdk::GDKRes::kSuccess) {
          std::cerr << "CancelTask failed" << std::endl;
          return 1;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
      if (res != agibot::gdk::GDKRes::kSuccess) {
          // until ctrl c to exit
          std::signal(SIGINT, signal_handler);
          while (true) {
          std::this_thread::sleep_for(std::chrono::seconds(1));
          }

          return 0;
      }
  }
使用注意事项
初始化等待：创建Pnc对象后，建议等待一段时间以确保系统初始化完成
地图准备：执行导航前确保已有可用的地图
目标点设置：设置目标点时注意坐标系的正确性
任务状态监控：建议定期检查任务状态以了解导航进度
任务管理：合理使用暂停、恢复、取消功能
精度选择：根据需求选择合适的导航精度（正常/高精度）
相对移动：使用相对移动时注意移动距离的合理性
应用场景
自主导航：实现机器人的自主路径规划和导航
精确导航：执行高精度的位置控制
相对移动：执行基于当前位置的相对移动
任务调度：管理多个导航任务的执行
路径规划：为机器人规划最优路径
避障导航：在复杂环境中进行安全导航
多目标导航：实现多个目标点的连续导航
远程控制：支持远程控制模式下的导航
````

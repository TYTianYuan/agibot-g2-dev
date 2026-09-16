# example：G2 上肢关节与夹爪控制

这个 C++17 示例用于验证“开发机 → GDK → 实机”的控制链路，不依赖相机、ROS2、视觉模型或仿真。

接口依据是[仓库 README](../README.md) 中用户提供的 GDK v2.6.3 文档：[官方入口](https://support.agibot.com/?gdk_version=2.6.3)。

开发流程：本机使用 Codex 修改代码并提交、推送 Git；远程开发机不需要 Codex，只需拉取代码、编译和连接机器人运行。将远程编译或运行日志反馈到本机会话后继续迭代。本机缺少 GDK 不影响代码交付，但真实 SDK 的编译结果以远程开发机为准。

## 编译

在已经安装 GDK 的远程 Linux 开发机上执行：

```bash
git clone https://github.com/TYTianYuan/agibot-g2-dev.git
cd agibot-g2-dev
source ~/.cache/agibot/app/env.sh
cmake -S example -B example/build -DCMAKE_BUILD_TYPE=Release
cmake --build example/build -j2
```

已拉取过仓库时，在仓库目录执行 `git pull --ff-only`，然后重新编译即可。

需要 CMake 3.16 及以上、C++17 编译器和与机器人匹配的 GDK 安装包。安装 GDK、网线连接和 IP 配置参见根目录 README；示例不会自动安装软件或修改网络配置。

CMake 默认在 `~/.cache/agibot/app/gdk` 下查找 `gdk/gdk.h` 和 `libgdk`。**现有文档没有提供 SDK 的 CMake 导出目标及库布局，本机也没有安装 GDK，默认查找路径尚未通过实际 SDK 验证。** 安装在其他目录时可指定：

```bash
cmake -S example -B example/build -DGDK_ROOT=/实际的/gdk/目录
```

如果安装包库名或目录不同，以安装包中的 `examples/cpp/CMakeLists.txt` 为准，指定 `GDK_INCLUDE_DIR`（包含 `gdk/gdk.h` 的目录）、`GDK_LIBRARY`（实际库文件的绝对路径）。若官方示例还链接其他库，可通过 `GDK_EXTRA_LIBRARIES` 传入分号分隔的列表。运行时也需在同一个终端 `source ~/.cache/agibot/app/env.sh`。

## 1. 查看连接、关节状态和夹爪型号

```bash
./example/build/example state
./example/build/example --help
```

直接运行 `example` 与 `state` 相同，只读状态，不发送运动命令。

`state` 通过 `GetWholeBodyStatus()` 打印 `left_end_model` / `right_end_model`、双臂急停和错误码，再通过 `GetJointStates()` 打印每个关节的 `motor_position`、`motor_velocity`、`error_code`。按照文档，关节反馈使用 `motor_position`，不使用预留的 `position` 字段。

这一步可以读取实际配置的夹爪型号，无需推测“默认型号”。

## 2. 单关节小幅运动

先确认机器人周围空间和当前姿态，保持急停可用。以下命令会立即下发运动，不是预览。首次验证建议逐个关节执行，小幅测试；不要把全部关节同时归零。

```bash
# 左臂关节 1 在实测当前位置上增加 0.03 rad（约 1.7 度）。
./example/build/example nudge idx21_arm_l_joint1 0.03 0.1

# 查看反馈，再执行下一步。
./example/build/example state

# 在此刻的实测位置上减少 0.03 rad。
./example/build/example nudge idx21_arm_l_joint1 -0.03 0.1

# 右臂关节 1 同样可以单独测试。
./example/build/example nudge idx61_arm_r_joint1 0.03 0.1
```

`nudge JOINT DELTA [SPEED]` 使用当前反馈计算目标；重复运行会继续累加。反向移动同样大小是从新的实测位置计算，不是精确回到保存的起点。

也可指定绝对目标：

```text
./example/build/example joint JOINT POSITION_RAD [SPEED_RAD_PER_SEC]
```

速度默认 `0.1 rad/s`，必须为正数。使用 `JointControl()` 的规划接口，一次控制一个指定关节；根据文档，此接口在执行到目标位置后返回。程序打印发送前的位置、目标、速度、接口返回结果和发送后的反馈。

程序按文档检查关节位置范围、反馈有效性、所选关节及分组的错误/急停状态。位置范围检查不等于碰撞检测，示例不自行规划避障。请求生命周期按行程和速度估算并留余量，不保证阻塞调用的墙钟超时。Ctrl+C 结束本机进程不等于实机急停，也不保证撤销已下发的运动。

支持的关节：

| 部位 | 关节名称 |
| --- | --- |
| 左臂 7 关节 | `idx21_arm_l_joint1` 至 `idx27_arm_l_joint7` |
| 右臂 7 关节 | `idx61_arm_r_joint1` 至 `idx67_arm_r_joint7` |
| 腰部 5 关节 | `idx01_body_joint1` 至 `idx05_body_joint5` |
| 头部 3 关节 | `idx11_head_joint1`、`idx12_head_joint2`、`idx13_head_joint3` |

`--help` 列出全部名称和文档中的限位。每次只控制一个指定关节，按需要更换名称即可。

## 3. 夹爪张开、闭合

```bash
./example/build/example gripper left open
./example/build/example gripper left close
./example/build/example gripper right open
./example/build/example gripper right close
```

每条命令先读取对应侧的末端型号，再调用 `MoveEEPos()`。不执行自动循环。夹爪张开/闭合映射来自 README 中的 `MoveEEPos` 参数说明：

| GDK 类型 | 张开 position | 闭合 position |
| --- | --- | --- |
| `omnipicker` | -0.785 | 0 |
| `dahuan` | 0 | 0.025 |
| `ctek90d` | -0.91 | 0 |

这些是各型号的原生接口值，不统一解释为百分比或距离。型号字符串仅忽略大小写；未知值或空值会报错，不自动选一个型号。此示例不控制 `o10_t2` / `o12_t2` 灵巧手。

如果实机反馈的型号名称与 GDK 类型名称不同，在核实硬件型号后可显式选择，例如：

```bash
# 仅在确认是 omnipicker 时使用。
./example/build/example gripper left omnipicker open
```

若实机返回了可识别的类型，但与显式选择不同，程序拒绝执行。接口返回成功只代表 GDK 调用成功；夹爪最终张开/闭合效果仍需观察实机。

## 验证范围

本地已验证参数解析、22 个关节名称、限位检查、相对位移计算，以及三种夹爪左右两侧的开合映射。当前开发环境没有 GDK 和机器人，尚未完成真实 SDK 链接、DDS 通信和运动验证。

不连接机器人即可运行参数测试：

```bash
cmake -S example -B example/build/offline -DEXAMPLE_WITH_GDK=OFF
cmake --build example/build/offline -j2
ctest --test-dir example/build/offline --output-on-failure
```

`EXAMPLE_WITH_GDK=OFF` 只构建测试，不生成控制机器人的可执行程序，不模拟真实 GDK。

退出码：`0` 表示调用流程成功，`1` 表示 GDK/状态/运行失败，`2` 表示命令行参数错误。遇到失败时保留终端中的具体 GDK 错误码或编译器输出，便于核对远程安装包。

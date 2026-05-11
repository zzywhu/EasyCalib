# EasyCalib 使用说明

## 1. 构建与使用

### 1.1 环境依赖

* **Ubuntu** 18 / 20
* **CMake** ≥ 3.10（推荐）
* **GCC / Clang**（支持 C++11 及以上）
* **PCL** ≥ 1.8
* **Eigen3**
* **Ceres Solver**
* **OpenCV**
* **OpenMP**（可选，用于加速）

---

### 1.2 构建步骤

在项目根目录 `EasyCalib` 下执行：

```bash
mkdir -p build
cd build
cmake ..
make -j8
```

生成的可执行文件位于：

```
build/calib
```

---

## 2. 运行标定

基础运行方式：

```bash
.build/calib param/*.yaml
```

代码提供了一些常见传感器的示例配置文件：

* `avia.yaml` — 适用于 Livox AVIA / Horizon 系列固态 LiDAR
* `mid360.yaml` — 适用于 Livox MID 系列固态 LiDAR
* `vlp16.yaml` — 适用于机械式激光雷达

---

### 配置文件内容说明

| 参数                         | 说明                                  |
| -------------------------- | ----------------------------------- |
| `data_num`                 | 图像 + 点云配对数量（建议≥6），需要对定制标定板采集相机和激光雷达数据，采集时传感器姿态每组需不同     |
| `image_path`               | 图像目录（按 1,2,3... 命名）                 |
| `pcd_path`                 | 点云目录（对应编号 `.pcd` 文件，**仅支持 PCD 格式**） |
| `ext_file`                 | 图像扩展名（如 `png` / `jpg`）              |
| `initial_guess_result`（可选） | 初始外参文件（一般无需设置，算法会自动解算外参初始值                    |

---

### 程序流程

1. 读取配置与数据
2. 自动生成初始外参（若未提供 `initial_guess_result`）
3. 多轮 Ceres 优化，逐步缩小匹配阈值
4. 输出外参文件至：

   ```
   result/extrinsic.txt
   ```
5. 在 `EasyCalib` 目录生成投影效果图：

   * `initcalib.png`
   * `final.png`

---

## 3. 结果文件说明

`result/extrinsic.txt` 格式如下：

```
R00 R01 R02 Tx
R10 R11 R12 Ty
R20 R21 R22 Tz
0   0   0   1
```

表示 **LiDAR 坐标系到相机坐标系** 的刚性变换：

[
P_\text{cam} = K \cdot ( R \cdot P_\text{lidar} + T )
]

其中：

* ( P_\text{cam} )：图像坐标系中的齐次像素坐标
* ( K )：相机内参矩阵
* ( P_\text{lidar} )：LiDAR 坐标系中的三维点

---

## 4. 常见问题简述

1. **库缺失 / 找不到依赖**

   * 检查 Ceres / PCL / OpenCV 是否已安装
   * 查看 `cmake ..` 输出确认是否被正确找到

2. **标定偏差大**

   * 确保图像与点云一一对应 （1.jpg ↔ 1.pcd）
   * 确保每组数据在同一时刻采集

3. **未生成 extrinsic.txt**

   * 确认 `result/` 目录存在且有写权限

---

## 5. 快速验证

若配置正确，程序将输出初始与优化后的外参，并生成：

* `final.png`

`final.png` 显示点云投影到图像的效果，可通过观察点云边缘与图像边缘是否贴合来判断标定精度。

---

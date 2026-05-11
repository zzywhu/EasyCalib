<div align="center">
  <h1>EasyCalib: A Novel Target for High-Accuracy Fully Automatic Extrinsic Calibration of Camera and LiDAR</h1>
  <p><strong><i>IEEE Transactions on Instrumentation and Measurement, 2026</i></strong></p>
  <br>

  <a href="https://github.com/zzywhu/EasyCalib">
    <img src="https://img.shields.io/badge/Code-GitHub-black?logo=github" alt="Code">
  </a>
  <a href="https://ieeexplore.ieee.org/abstract/document/11495237">
    <img src="https://img.shields.io/badge/Paper-IEEE%20Xplore-00629B" alt="Paper">
  </a>
  <a href="https://doi.org/10.1109/TIM.2026.3687975">
    <img src="https://img.shields.io/badge/DOI-10.1109%2FTIM.2026.3687975-blue" alt="DOI">
  </a>
</div>

<br>

Official implementation of **EasyCalib**, a fully automatic camera-LiDAR extrinsic calibration method with a novel calibration target for high-accuracy sensor alignment.

## Quick Start

### Prerequisites

- PCL >= 1.8
- Eigen3
- Ceres Solver
- OpenCV
- OpenMP

### Build

```bash
mkdir -p build
cd build
cmake ..
make -j8
```

### Run

```bash
./build/calib param/avia.yaml
```

Example configuration files:

- `param/avia.yaml`
- `param/mid360.yaml`
- `param/vlp16.yaml`

The calibration result will be written to `result/extrinsic.txt`.

## Configuration File

| Parameter | Description |
| --- | --- |
| `data_num` | Number of image and point cloud pairs. At least 6 pairs are recommended. Camera images and LiDAR point clouds should be collected using the customized calibration target, and the sensor pose should be different for each pair. |
| `image_path` | Directory containing the input images, named as `1`, `2`, `3`, ... |
| `pcd_path` | Directory containing the point cloud files with matching indices. Only `.pcd` format is supported. |
| `ext_file` | Image file extension, such as `png` or `jpg`. |
| `initial_guess_result` (optional) | Initial extrinsic file. In most cases this does not need to be set, because the algorithm will automatically estimate the initial extrinsic parameters. |

## Citation

If you find this project useful, please consider citing our paper:

```bibtex
@ARTICLE{11495237,
  author={Zhou, Zhiyu and Gao, Zhi and Cao, Min and Wang, Jingshi and Li, Yong and Lin, Zhipeng and Yang, Wenbin and Wang, Xiaonan and Zhang, Qiyuan},
  journal={IEEE Transactions on Instrumentation and Measurement},
  title={EasyCalib: A Novel Target for High-Accuracy Fully Automatic Extrinsic Calibration of Camera and LiDAR},
  year={2026},
  volume={75},
  pages={9519815-9519815},
  keywords={Aerospace control;Antenna radiation patterns;Oscillators;Central Processing Unit;Pixel;Radio access networks;Regional area networks;Electronic mail;Digital images;Protocols;Calibration target;extrinsic calibration;light detection and ranging (LiDAR) and camera},
  doi={10.1109/TIM.2026.3687975}
}
```

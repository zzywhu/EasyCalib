# EasyCalib

Official code for the paper  
**EasyCalib: A Novel Target for High-Accuracy Fully Automatic Extrinsic Calibration of Camera and LiDAR**

[IEEE Xplore](https://ieeexplore.ieee.org/abstract/document/11495237)

**Authors**  
Zhiyu Zhou, Zhi Gao, Min Cao, Jingshi Wang, Yong Li, Zhipeng Lin, Wenbin Yang, Xiaonan Wang, Qiyuan Zhang

## Configuration File

| Parameter | Description |
| --- | --- |
| `data_num` | Number of image and point cloud pairs. At least 6 pairs are recommended. Camera images and LiDAR point clouds should be collected using the customized calibration target, and the sensor pose should be different for each pair. |
| `image_path` | Directory containing the input images, named as `1`, `2`, `3`, ... |
| `pcd_path` | Directory containing the point cloud files with matching indices. Only `.pcd` format is supported. |
| `ext_file` | Image file extension, such as `png` or `jpg`. |
| `initial_guess_result` (optional) | Initial extrinsic file. In most cases this does not need to be set, because the algorithm will automatically estimate the initial extrinsic parameters. |


**Citation**

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
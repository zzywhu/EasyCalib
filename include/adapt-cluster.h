// Copyright (C) 2018  Zhi Yan and Li Sun

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

// PCL
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/common/common.h>
#include <pcl/common/centroid.h>
#include <pcl/point_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
#include <stack>
#include <pcl/search/kdtree.h>
#include <omp.h>
//#include <pcl/visualization/cloud_viewer.h>

//#define LOG
extern int dataProcessingNum;

int leaf_ = 1;
float z_axis_min_ = -0.8;
float z_axis_max_ = 2.0;
int cluster_size_min_ = 3;
int cluster_size_max_ = 2200000;

const int region_max_ = 10; // Change this value to match how far you want to detect.
int regions_[100];

int frames;
clock_t start_time;
bool reset = true; //fps
void pointCloudcluster(
    const pcl::PointCloud<pcl::PointXYZI>::Ptr &pcl_pc_in,
    std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr,
                Eigen::aligned_allocator<pcl::PointCloud<pcl::PointXYZRGB>::Ptr>> &clusters) {
    clusters.clear();

    // 构建kdtree
    pcl::search::KdTree<pcl::PointXYZI>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZI>);
    tree->setInputCloud(pcl_pc_in);

    // 欧式聚类
    std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZI> ec;
    ec.setClusterTolerance(0.05); // 5cm
    ec.setMinClusterSize(10);
    ec.setMaxClusterSize(1000000);
    ec.setSearchMethod(tree);
    ec.setInputCloud(pcl_pc_in);
    ec.extract(cluster_indices);

    // 赋予不同颜色并保存
    int color_idx = 0;
    for (const auto &indices : cluster_indices) {
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cluster(new pcl::PointCloud<pcl::PointXYZRGB>);
        uint8_t r = (color_idx * 77) % 255;
        uint8_t g = (color_idx * 151) % 255;
        uint8_t b = (color_idx * 211) % 255;
        for (int idx : indices.indices) {
            pcl::PointXYZRGB pt;
            pt.x = pcl_pc_in->points[idx].x;
            pt.y = pcl_pc_in->points[idx].y;
            pt.z = pcl_pc_in->points[idx].z;
            pt.r = r;
            pt.g = g;
            pt.b = b;
            cluster->points.push_back(pt);
        }
        cluster->width = cluster->size();
        cluster->height = 1;
        cluster->is_dense = true;
        clusters.push_back(cluster);
        color_idx++;
    }

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr merged_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    merged_cloud->height = 1;
    merged_cloud->width = 0;
    for (int i = 0; i < clusters.size(); i++) {
        // Append all points from the cluster to the merged cloud
        for (int j = 0; j < clusters[i]->points.size(); j++) {
            merged_cloud->points.push_back(clusters[i]->points[j]);
        }
        merged_cloud->width += clusters[i]->width;
    }

    pcl::io::savePCDFileASCII("check/" + std::to_string(dataProcessingNum) + "_cluster.pcd", *merged_cloud);

    std::cout << "Euclidean clustering finished, found " << clusters.size() << " clusters." << std::endl;
}
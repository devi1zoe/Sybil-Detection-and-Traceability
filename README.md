# Sybil-Detection-and-Traceability

## 论文

**MVDetector: Malicious Vehicles Detection Under Sybil Attacks in VANETs**

Yiming Wei, Weiye Qi, Zechuan Li, Yufan Han, Yingxu Lai.

- [正式出版页面](https://link.springer.com/chapter/10.1007/978-3-031-75764-8_16)
- [DOI](https://doi.org/10.1007/978-3-031-75764-8_16)
- 会议：ISC 2024；论文集：*Information Security*，LNCS 15258，pp. 307–322。
- 首次在线日期为 2024-10-17；出版社推荐引用年份为 2025。
- [BibTeX 引用](paper/citation.bib)

- **[论文作者稿：录用阶段版本（PDF）](paper/mvdetector-author-manuscript.pdf)**

本仓库提供车辆检测与溯源系统的模拟展示界面及论文作者稿。正式出版信息与引用见上方链接。

## 项目与个人贡献

其他成果：作为北京工业大学“星火基金”重点项目，获得第十七届全国大学生信息安全竞赛作品赛优胜奖。

在资源受限且网络拓扑快速变化的车联网环境中，利用多种轻量级机器学习模型进行实时分析，高效识别攻击者和其恶意制造的Sybil车辆。

我本人负责制作车辆检测和溯源系统的模拟展示界面，以及ISC论文撰写和latex排版。

上传内容为本人负责部分

## 运行环境

本仓库的模拟界面为 Windows C++ 桌面程序，工程使用 Visual Studio 2022 的 MSVC v143 工具集和 Windows 10 SDK，并依赖 EasyX 图形库（`graphics.h` / `easyx.h`）。请安装 Visual Studio 的“使用 C++ 的桌面开发”工作负载，并为所用工具集配置 EasyX。

使用 Visual Studio 打开 `Sybil车辆检测与溯源模拟系统.vcxproj`。工程的 `Debug | x64` 配置保留了原机器的 Visual Studio Community 2022 头文件和库目录，编译前请按实际安装位置检查并调整这些路径。

程序通过 `./images/` 读取界面资源，运行时请将工作目录设为仓库根目录，并保留 `images/` 文件夹。

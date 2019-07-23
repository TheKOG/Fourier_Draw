# Chinese

项目使用流程: 

1. 运行kruskal.exe

2. 按照流程输入图片路径(bmp格式)和梯度阀值(默认为200)

   注: 阀值越高, 轮廓越稀疏

3. 运行fourier.exe

4. 按F5开始绘制

-----------------------------------以下内容可以不看-----------------------------------

fourier.exe使用进阶教程:

1. 按顺序点击屏幕形成点阵

2. 按Z撤销一个点

3. 按X恢复一个点

4. 按Esc清除所有点

5. 按F5开始/结束绘制

6. 按F1显示/隐藏点阵

   注: 绘制时, 程序默认不显示点阵, 此时按F1以显示点阵

7. 按空格暂停绘制

8. 可以修改data.in以设置初始点阵

   注: kruskal.exe会将运算结果输出到data.in中

## 编译指令

对于kruskal.cpp:	g++ kruskal.cpp -o kruskal -lgdi32

对于fourier.cpp: 	g++ fourier.cpp -o fourier -lgdi32 -mwindows 

## 算法介绍

对于kruskal.cpp:	边缘算子, Delaunay三角剖分算法, kruskal最小生成树算法, Douglas算法;

对于fourier.cpp:	快速傅里叶变换算法, 逆离散傅里叶变换算法;

## 版权声明

本程序源代码可任意修改并任意使用，但禁止商业化用途。一旦使用，任何不可知事件都与原作者无关，原作者不承担任何后果。

如果您喜欢，希望可以在页面某处保留原作者(KOG)版权信息。

联系方式: 1458038842@qq.com

感谢。

<br>

# English

Project usage process:

1. Run the kruskal.exe
2. Input image path (the bitmap format) and gradient threshold (default is 200) according to the process 

  Note: the higher the threshold, the more sparse the contour

3. Run the Fourier.exe
4. Press F5 to start drawing

-----------------------------------You can skip the following-----------------------------------

fourier.exe using advanced tutorials:

1. Click the screen in order to form a dot matrix
2. Press Z to undo a point
3. Press X to restore a point
4. Press Esc to clear all points
5. Press F5 to start/end the drawing
6. Press F1 to show/hide the dot matrix

  Note: when drawing, the program does not display the dot matrix by default. Press F1 to display the dot matrix

7. Pause drawing by space

8. You can modify data.in to set the initial lattice

   Note: kruskal.exe will output the calculation result to data.in

## Compiled instruction

For kruskal.cpp:	g++ kruskal.cpp -o kruskal -lgdi32

For fourier.cpp: 	g++ fourier.cpp -o fourier -lgdi32 -mwindows 

## Introduction to algorithms

For kruskal.cpp: edge operator, Delaunay triangulation algorithm, kruskal minimum spanning tree algorithm, Douglas algorithm;

For fourier.cpp: fast Fourier transform algorithm, inverse discrete Fourier transform algorithm;

## Copyright statement

The program source code can be modified and used arbitrarily, but commercial use is prohibited.Once used, any unknowable event has nothing to do with the original author and the original author bears no consequences.

If you like, you would like to have the original author (KOG) copyright information somewhere on the page.

Contact information: 1458038842@qq.com

Thank you.


# 课程笔记

## Sep.18 光栅化

### 直线段的光栅化

给定直线段的两个端点 $P_1(x_1, y_1)$ 和 $P_2(x_2, y_2)$，如何将直线段光栅化为像素？

首先找到对应直线方程：$y=mx+b$。

- 朴素算法：遍历 $x_1, x_1+1, \cdots, x_2$，计算对应的 $y$ 坐标并取整
- [:simple-wikipedia: Digital Differential Analyzer (DDA)](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
    - 选择 $\mathrm{d}x$ 和 $\mathrm{d}y$ 中较小的一个作为单位步长，对每个单位间隔采样。

        例如，斜率大于 1 时以 $\mathrm{d}y=1$ 进行采样：

        $$
        x_{i+1} = x_i + \frac1m, 
        y_{i+1} = y_i + 1
        $$

    - 每次插值只需要一次加法和一次取整。
- [:simple-wikipedia: Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
    - 这是一种**累积误差算法（incremental error algorithm）**。这种算法使用简单的整数算术更新**误差项**，决定其他量是否要更新，从而避免昂贵的乘除运算。

### 圆的光栅化

- [Bresenham’s circle drawing algorithm](https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/)
- [:simple-wikipedia: Midpoint circle algorithm](https://en.wikipedia.org/wiki/Midpoint_circle_algorithm)

### 多边形填充

- even-odd test
- winding test
- scan-line
- seed fill

### 裁切

- Clipping

### 作业：椭圆的光栅化

可以参考 [The Beauty of Bresenham's Algorithm: A simple implementation to plot lines, circles, ellipses and Bézier curves.](http://members.chello.at/~easyfilter/bresenham.html) 中对上述算法的泛化。

下周换课：9.22 周日 9、10 节

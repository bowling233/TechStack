---
tags:
  - 不完善
---

# Matlab

## 基础

-   三个部分：命令行、编辑器、工作区。
-   脚本（注释 `%`）、实时脚本（文本编辑、节）、函数文件。
-   分号、`clc`、`clear`。

## 矩阵、变量、运算符、表达式

字符和字符串：

-   String、`"`、字符串连接 `+`。
-   `char` 矩阵 `'`、矩阵连接 `[,]`。

矩阵：

-   `plot(x)` 以索引为横坐标绘图。
-   `[ , ; ]` 逗号或空格分隔行内元素，分号分隔各行。
-   常用操作：`eig`、`inv`、`*`、`.*`。
-   求解线性方程组：`A\b`，即用 `A` 的逆矩阵乘以 `b`。
-   **标量、不同维度向量的广播**。（类似 NumPy）
    -   标量乘矩阵变成对角矩阵。
    -   单维度向量加法直接广播。

矩阵生成：

-   `sparse(i, j, s)` 生成稀疏矩阵。 

## 绘图

线图：

```matlab
plot(x, y)
```

条形图：

```matlab
bar(x, y)
barh(x, y)
```

极坐标：

```matlab
polarplot(theta, rho)
```

散点图：

```matlab
scatter(x, y)
```

三维曲面图：

```matlab
[x, y] = meshgrid(-2:0.2:2);
surf(x, y, z);
```

修饰：

```matlab
xlabel('x')
grid on
axis([0, 10, 0, 10])
colormap hsv
colorbar
title('title')
```

子图：

```matlab
subplot(2, 2, 1);
subplot(2, 2, 2);
```

## 数据处理

-   导入数据
-   清理缺失值、清理离群数据等

## 树和图的绘制

生成图：`graph(s, t, weights)`

```matlab
biograph
highlight
```
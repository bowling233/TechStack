# Python 数据科学手册

Python DAta Science Handbook

## Ch4. Matplotlib

### 使用方法

1. 在脚本中：使用 `plt.show()` 显示图像。该函数启动一个事件循环，找到当前所有可用的图形对象，然后打开一个或多个交互式显示窗口。
    - 在一个 Python 会话中只能使用一次 `plt.show()`。
2. IPython Shell 中：使用 `%matplotlib` 魔术命令，此后的任何 `plt` 命令都会自动打开图形窗口。
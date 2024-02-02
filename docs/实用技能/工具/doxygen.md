---
tags:
  - 不完善
---

# Doxygen

## 其他

有时，你需要一个程序来统计代码中的注释数（比如在 FDS 课中），可以使用 [cloc](https://github.com/AlDanial/cloc) 这个工具。

## 基本使用

## 基本语法

<!-- prettier-ignore-start -->
!!! info
    
    [这里](https://www.mitk.org/images/1/1c/BugSquashingSeminars%242013-07-17-DoxyReference.pdf)是一份 Doxygen 的语法速查表。
<!-- prettier-ignore-end -->

## 配置文件

Doxygen 的配置文件较为复杂，虽然每个选项都有详细的说明。这里总结一些经常实用的配置项：

- `PROJECT_NAME`
- `INPUT`：指定源文件的路径。
- `GENERATE_HTML`：是否生成 HTML 文档。
- `FULL_PATH_NAMES`：在文档中显示完整路径名。默认为 `YES`，此时文档的 File Documentation 等处将显示源文件的绝对路径，可能暴露用户名字等信息。建议设置为 `No`，以免暴露路径信息。
- `COMPACT_LATEX`：生成紧凑的 LaTeX 文档，将去除空白页面、不将目录与内容页面分开等。

## 细节

### 注释放在头文件还是源文件？

<!-- prettier-ignore-start -->
!!! info

    - [StackOverflow: Where to put the doxygen comment blocks for an internal library - in H or in CPP files?](https://stackoverflow.com/questions/355619/where-to-put-the-doxygen-comment-blocks-for-an-internal-library-in-h-or-in-cpp)
    - 这是一个使用 Doxygen 的小型 C 项目，值得参考：[GitHub: libcsv](https://github.com/scatmanFATMAN/libcsv)
<!-- prettier-ignore-end -->

一般来说，头文件尽量保持简洁，不放置注释或仅放置说明接口信息的注释。详细的注释放置在源文件中。

```c title="mymodule.h"
/// @brief This method adds two integers.
/// @param a First integer to add.
/// @param b Second integer to add.
/// @return The sum of both parameters.
int add(int a, int b);
```

```c title="mymodule.cpp"
/// This method uses a little-known variant of integer addition known as
/// Sophocles' Scissors. It optimises the function's performance on many
/// platforms that we may or may not choose to target in the future.
/// @TODO make sure I implemented the algorithm correctly with some unit tests.
int add(int a, int b) {
  return b + a;
}
```

这样做有一些好处：

-   头文件中的注释一旦发生变动，会导致所有引用该头文件的源文件都被重新编译。而源文件中的注释变动不会导致其他源文件重新编译。

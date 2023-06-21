---
tags:
  - Todo
---

# Python 编程：从入门到实践

Python Crash Course: A Hands-On, Project-Based Introduction to Programming

| 出版社 | 作者 | 年份 |
| - | - | - |
| 人民邮电出版社 | Eric Matthes | 2016 |

<!-- prettier-ignore-start -->
!!! abstract
    
    本书仅作项目部分笔记。
<!-- prettier-ignore-end -->

## 前置知识

<!-- prettier-ignore-start -->
!!! abstract

    这里介绍一些创建 Python 项目的基本知识，比如虚拟环境、`pip` 包管理器等。
<!-- prettier-ignore-end -->

### 命令相关

Python 的命令容易引起困惑，我现在也依旧没有搞懂。如果你安装了 Python 后执行 `python3` 显示找不到，可以尝试替换为 `python` 或 `py`。如果还找不到，请检查 `$PATH` 环境变量。一般来说，Windows 系统中默认命令为 `py`，而 Unix 系统中默认命令为 `python3`。`pip` 包管理器也会默认安装，如果找不到可以尝试替换为 `pip3`。

### 虚拟环境

创建虚拟环境的理由有很多：不同项目的依赖不同、版本不同，或者是为了保持系统的干净整洁。

从 Python 3.3 开始，一般使用 Python 自带的模块 `venv` 来创建虚拟环境：

```bash
python3 -m venv <DIR>
source <DIR>/bin/activate
```

第一行的命令创建了虚拟环境，第二行命令（限 Unix 系统）将虚拟环境的环境变量载入终端。

创建虚拟环境并加载环境变量后，就能使用 `pip` 命令来安装依赖包了。

需要注意的是，Windows 和 Linux 下的虚拟环境并不能通用，因为其配置文件使用绝对路径。因此应当为不同的系统配置不同的虚拟环境，最好的方式是使用 `requirements.txt` 文件来记录依赖包，这样可以保证不同系统下的依赖包一致。

## Projects

### 


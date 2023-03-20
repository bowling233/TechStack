---
tags:
  - Ongoing
---

# Q&A 2022

## 问题格式

约定一个格式，用以清晰地记录问题，方便自己和他人查找。

每年开一个 Q&A 文档，每个问题都当做二级标题。问题包括以下模块：

* 必须：
    * 产生原因
    * 解决方法
* 可选：
    * 参考文献
    * 相关问题

## 这是一个问题

### 产生原因

有问题要帮忙，没有问题制造问题也要帮忙。

### 解决方法

把提出问题的人解决了就好了。

## Syncthing 和 git 共用

### 问题背景

[Syncthing Forum](https://forum.syncthing.net/t/is-putting-a-git-workspace-in-a-synced-floder-really-a-good-idea) 上的帖子表示：将 git 仓库放在 Syncthing 文件夹中不会导致问题，并且能让 git 状态在所有 Syncthing 文件夹中保持一致。我采用了这一方法。但在新配置 git 的系统上编辑时，我的远程系统上的 git 显示仓库中的所有文件被更新。

我真是吐了 ![fatal: CRLF would be replaced by LF](https://toub.es/2012/05/28/fatal-crlf-would-be-replaced-by-lf/firstcommit.png)

### 产生原因

Linux 和 Windows 系统换行符不一致。git 默认在检出时让文件换行适应当前系统，但如果再套上一层非 git 同步就会导致令人哭笑不得的结果。比如，仓库中所有文件都是 LF，在 Windows 上用 git 检出为 CRLF，这一更改又被 Syncthing 同步到其他 Linux 系统上，在这些 Linux 系统上就会检测到大量更改。

### 解决办法

最好在所有系统、所有编辑器中统一配置为 Unix 换行符 `LF`，并为 git 仓库添加 `.gitattribute` 文件。具体配置参考这篇文章：[git 多平台统一换行符](https://juejin.cn/post/6844903591258357773)。

## Windows 使用 Python

参考 [知乎](https://zhuanlan.zhihu.com/p/38603105) 的教程。官网下载 Python 安装包。注意，在 Windows 命令行中，所有 `python` 的命令都以 `py` 执行。安装 `pip` ：下载 pip 安装脚本，解压后运行 `py setup.py install`。完成安装后在系统 `PATH` 中添加 `pip` （在我安装完后已自动添加）。输入 `py -m pip --version` 返回版本号说明安装成功。

此后，所有 pip 的命令全部改成：`py -m pip <command>`，所有 Python 包的执行命令也改成以 `py -m` 开头。

> -m mod : run library module as a script (terminates option list)

## Typora 与 Obsidian 协作

### 问题背景

Typora 依然是最好的 Markdown 编辑器，Obsidian 是最好的知识管理工具，Mkdocs 和 Hexo 是最好的文档发布工具。将这些工具搭配协作，能发挥它们各自的长处。

### 产生原因

Obsidian 和 Typora 的一些配置不同，需要统一一些设置才能使用。

### 解决办法

有大佬已经写好了 Typora 和 Obsidian 协作的[笔记](https://crazt.moe/archives/54/)，和我的想法差不多。

## 在 Markdown 中隐藏内容

### 产生原因

想在实现类似萌娘百科的黑幕效果，但这很可能需要用到CSS，我懒。

### 解决方法

在网上搜寻一圈，发现 HTML 的 `<details>` 元素基本可以满足我的要求，在各个终端的显示也统一。以下是结合嵌套列表的示范：

<ol>
    <li>这是一个列表</li>
    <li>这里可以放置一些介绍</li>
    <li>details（不要忘记s）元素，应当放置在一个li元素的内部</li>
    <li>
        <details><summary>提示</summary>答案</details>
    </li>
</ol>

这真是太方便了，很符合我对未来Markdown的想象。其实，我可以把很多Markdown元素嵌套在 `<details>` 元素中，但是我们需要使用对应的HTML元素。这可能会让你更自由一些，但你也要付出一些时间编辑代码。比如跨行的表格：

<details>
<table>
    <thead>
        <tr>
            <th colspan="2">The table header</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>The table body</td>
            <td>with two columns</td>
        </tr>
    </tbody>
</table>
</details>
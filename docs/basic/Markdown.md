---
tags:
  - Ongoing
---

# Markdown 生态

我喜欢使用 Markdown 做笔记，原因很简单，它非常通用。我接触过的笔记软件和 Blog 也都基于 Markdown，它们共同构建起了一个比较好的生态。

在本文档中，我将记录自己跨软件、跨平台使用 Markdown 遇到过的问题和解决方案。

## 我的笔记结构

* 我使用 **Obsidian** 管理所有 Markdown 笔记。这个笔记库在一个更大的同步库中，由 Syncthing 和 Onedrive 分别将该同步库同步至我的各个设备和云端备份。
    * 我会将 Obsidian 的双向链接配置为 Markdown 格式的 **相对链接**，附件存储于当前文件夹下的 `assest` 文件夹。这将为 MkDocs 和 Typora 提供便利
* 我使用 **Typora** 作为主力编辑器。它可以胜任基于 GFM 的基础语法的 Markdown 编辑工作。
    * 为了兼容 MkDocs 语法，Typora 列表缩进设定为 Tab

* 我使用 **MkDocs** 发布自己的笔记。MkDocs 提供了一些扩展语法，我会调整 Obsidian 的配置使之适应 MkDocs，若有冲突，MkDocs 规则优先。
    * 需要发布的笔记存放在 Obsidian 库的子文件夹中，它们也是独立的 git 仓库。因为同步库的存在，我不需要在各个设备间重复 pull/push 操作，只需要在其中一台设备上完成，git 状态即可同步至其他设备。
* ~~我会使用 VSCode 扩展 `MarkdownLint` 来自动格式化文档。~~ 因为 MkDocs 的扩展语法，我已不在使用自动格式化，这会破坏 Admonition 等扩展的工作。

## 扩展语法

* 现行 Markdown 标注中以 [GFM](https://github.github.com/gfm) 最为通用。

> From:
> 《了不起的 Markdown》

* `<u>` 下划线
* `$` 内联公式
* `~`, `^` 上下标
* `==` 高亮
* `<!-->` 注释
* `$$` 数学公式块
* `[TOC]` 目录
* `[^ref]` 脚注
* `:----:` 表格对齐符

???+ note "For Compatible with MkDocs"

    * MkDocs **只能识别** 4 个空格或 1 个制表符的列表缩进。
    * MkDocs 的代码块必须使用支持的语言标签才能正常工作。这些标签涵盖了几乎所有语言，因此只要设置正常，无需担心无法工作。
        * 配置正确后，嵌套在列表中的代码块应该不会出现问题，比如
        ```markdown title="example"
        this is markdown
        ```
    * 为了让该警告块在 Obsidian 不会被渲染成一行，顶部应该与内容有一行的距离。
    * 这样做使得警告体在 Typora/Obsidian 中被渲染代码块，请自己注意。
    * 为了便于解析，MkDocs 的各种 **粗体** 等格式，两侧都需要有空格！

## Mermaid

> 官方文档: [GitHub Pages](https://mermaid-js.github.io/mermaid/#/)
> [Mermaid Live Editor](https://mermaid-js.github.io/mermaid-live-editor/)

* 首先声明图表的类型
* 流程图 `flowchart <type>`
    * 流程图朝向有：`TD`, `TB`, `LR`, `BT`, `RL`
    * 由 **nodes** 和 **edges** 组成
    * `node[optional text] --> node`
        * 圆框节点 `node(text)`
        * 标准圆框 `node([text])`
        * 大圆 `node((node))`
        * 六边形 `node{{node}}`
* [更多节点和连接线](https://mermaid-js.github.io/mermaid/#/flowchart)

## MkDocs

* 设置页脚
```yaml
extra:
  social:
    - icon: fontawesome/brands/twitter 
      link: https://twitter.com/squidfunk
```
* 代码块
    * MkDocs 中的代码块可以有标题 `title="xxx.py"`、脚注 `//(1)` （需要开启扩展）等
    * 请不要在嵌套的代码块中使用脚注，这会导致下面的子列表消失
* 导航栏
    * 建议开启这些功能：
    ```yaml
    theme:
      features:
        - navigation.instant
        - navigation.tracking
        - navigation.tabs
    ```


### Python Markdown

* 配置推荐的 [Markdown 扩展](https://squidfunk.github.io/mkdocs-material/setup/extensions/#recommended-configuration)
* 缩写 Abbreviations
    * 可以创建一个全局的术语表 `includes/abbreviations.md`
    ```yaml
    markdown_extensions:
      - pymdownx.snippets:
          auto_append:
            - includes/abbreviations.md
    ```
    ```markdown
    *[abbr]: details
    ```
    * 所有文档中的缩写都会得到应用
* 警告 Admonition
    * 警告体用四个空格缩进
    ```markdown
    !!! note "optional title"
     details
    ??? note "expandable block"
     details
    ```
    * 支持这些 type
        * `note` `abstract` `info` `tip` `success` `warning` `failure` `danger` `bug` `example` `quote`
* 清单 List
    * 待办列表：语法符合 Markdown 通用标准，但需要启用扩展
* 目录 Table of Contents
    * 需要配置的：目录深度默认为 6
    ```yaml
    - toc:
     toc_depth: 3
    ```

### Python Markdown Extensions

* Arithmatex 数学公式块 `$$` 语法支持
* Keys 按键标识
    * 例：++ctrl+alt+del++
    * 用 `++` 将按键组合包裹起来即可
* SuperFences 超级栅栏
    * 开启该扩展允许各类东西嵌套
    !!! note
        Marmaid 也需要在这里开启
* Tabbed 卡片
    * 可以把内容组织成卡片，并且可以把卡片嵌套在警告中：
    !!! example

    === "Unordered List"
    
        ``` markdown
            * Sed sagittis eleifend rutrum
            * Donec vitae suscipit est
            * Nulla tempor lobortis orci
        ```
    
    === "Ordered List"
    
        ``` markdown
        1. Sed sagittis eleifend rutrum
        2. Donec vitae suscipit est
        3. Nulla tempor lobortis orci
        ```

### Plugins

* 搜索插件 `search`
    * 不包括文件
    ```yaml
    search:
      exclude: true
    ```
    * 不包括部分或文段
    ```markdown
    ## section {data-search-exclude}
    ```
* 标签插件 `tags`
    * 配置 tag 页面
    ```yaml
    - tags:
        tags_file: tags.md
    ```
    ```markdown
    # Tags
    Following is a list of relevant tags:
    [TAGS]
    ```
    * 为文章设置 tag
    ```yaml
    tags:
      - HTML5
    ```

### MathJax

需要在 `docs/javascripts` 中添加脚本，即可渲染内嵌 Latex。请参考官方文档。

## 编辑器

### Typora 快捷键

* 编辑操作

| 组合                    | 用途                                                     |
| ----------------------- | -------------------------------------------------------- |
| Ctrl + `B, I, K, U`     | 粗体、斜体、超链接、下划线（识别方法同 Vim 的一个 word） |
| Alt + Shift + `5, I`    | 删除线、图片                                             |
| Ctrl + `<num>, =, -, 0` | 设置标题、提升、降低、普通文本                           |
| `[, ], X`               | 有序、无序、任务列表                                     |
| Ctrl + `], [`           | 增加、减少缩进                                           |
| Ctrl + Shift + `Q`      | 引用                                                     |
| Ctrl + Shift + `- +`    | 界面缩放                                                 |
| Ctrl + `T, Enter`       | 表格（**不如自己写表头方便**）、新增行                   |
| Ctrl + `Del`            | 删除表格下空行                                           |
| Ctrl + Shift + `Del`    | 删除表格行                                               |
| Alt + `↑↓←→`            | 移动行列                                                 |
|                         | 表格侧边出现双向箭头支持上下拖动行、列调整顺序           |
| Ctrl + `\`              | 清除样式                                                 |
| Ctrl + Shift + `M`      | 公式块                                                   |

* 文件和窗口操作

| 组合             | 用途                 |
| ---------------- | -------------------- |
| Ctrl + `P`       | 快速打开最近关闭文件 |
| Ctrl + Shift + C | 复制 Markdown 源码   |
| Ctrl + Shift + V | 粘贴纯文本           |
| Ctrl + W         | 关闭                 |

* 选择操作

| 组合 | 用途      |
| ---- | --------- |
| D    | 词        |
| L    | 行/**句** |
| E    | 当前格式  |
| A    | 全选      |
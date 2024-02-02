# 我的工作流

<!-- prettier-ignore-start -->
!!! abstract "摘要"
    
    本篇笔记介绍了我在学习、工作中使用的工作流，主要是我使用的工具和软件，并提供一些参考建议。
<!-- prettier-ignore-end -->

## 选择合适的设备

<!-- prettier-ignore-start -->
??? tip "设备并非越多越好"

    一台设备的使用成本并不仅仅是购买成本，还包括**学习成本、维护成本、使用成本**等。如果你有多台设备，那么你需要在多台设备上**安装软件、配置环境、同步数据并维护设备**，这些都是成本。你需要权衡这些成本，决定是否需要多台设备。
    
    切记：**不要创造需求**。
<!-- prettier-ignore-end -->

对于计算机系学生来说，**Windows 系统是必不可少的**，我们需要在其中配置各种开发环境，因此也需要足够的性能支撑。大家一般会选择 Windows 游戏本（Windows 轻薄本目前还没有做到性能和便携性兼备），但厚重的游戏本并不适合外带，因此部分同学会再购买一台 MacBook Air 用于日常外出使用。平板用处并不大，最主要的功能是看书和手写笔记（数理化等学科），请考虑自己的需求慎重选配。

<!-- prettier-ignore-start -->
??? note "我的设备搭配：台式机+笔记本+平板"
    
    -   台式机：
        -   安装 Windows 作为主力系统，配置了各种开发环境。
        -   安装 Ubuntu 作为辅助系统，主要用于学习服务器知识。
        -   使用第三块 exFAT 格式硬盘作为数据交换盘。系统盘上只存放系统和软件，所有数据都在数据盘上，保证两个系统工作状态一致。
        -   通过远程桌面，随时可以访问。
        -   双屏幕。
    -   MacBook Air M2 (8+256)：日常外带使用。
    -   XiaoMi Book Pro 15'6 (2018)：备用机，安装了 Windows 系统和 Ubuntu 系统，用于 macOS 无法配置的环境。
    -   MatePad：日常外带使用，主要用于阅读。

    出门时携带 MacBook Air 和 MatePad，回宿舍时使用台式机。使用同步软件在设备间无缝同步文档、笔记等数据，保持流畅的工作体验。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "其他计算机系学生的设备使用情况"    

    以下是我见过的其他人的设备搭配：

    - Windows 本 + MacBook：个人比较推荐的配置。
    - Windows 本 + Pad：远程桌面可以满足基本使用，但体验并不舒适，非常依赖网络。
    - 只用一台高配 MacBook Pro：肯定要装 Windows 虚拟机，因此需要一些折腾。
    - Linux 笔记本 + Linux ITX 主机：适合极客。但是风险极大，我见过有同学考试周两个设备全挂了（ArchLinux）。
<!-- prettier-ignore-end -->

## 构建自己的笔记系统

<!-- prettier-ignore-start -->
!!! tip "做笔记最重要的事情"
    
    在着手构建自己的笔记系统前，应当思考这两个问题：
    
    1. 我的笔记习惯和思维是怎样的？
    2. 我做笔记的目的是什么？
<!-- prettier-ignore-end -->

这两个问题是构建笔记系统的关键。以我自己为例：

1. 我的笔记大部分是计算机学科内容，适合使用 Markdown 格式做笔记。它学习成本低，排版效果美观。
2. 我习惯于线性的笔记思维，因此我选择使用 VSCode 辅以 Typora 作为笔记软件，按文件夹对笔记分类。
3. 我做笔记的目的除了防止自己遗忘，还有和他人交流。我的笔记应当易于他人阅读，所以我选择使用 Mkdocs 作为笔记发布工具。由它生成的文档美观易读，可定制程度高。

我的笔记体系也将针对我的两个目的进行优化。

<!-- prettier-ignore-start -->
??? note "浅谈 Obsidian 使用体验"
    
    我曾使用过一段时间的 Obsidian，它是一个很不错的笔记系统：双向链接的笔记思维也非常新颖，各类插件提供了丰富的定制功能。但最终我没有坚持下去，因为它使得我的笔记过于碎片化。至少目前在本科阶段，学习的内容较为系统的情况下，我更加习惯于线性的学习方式、构建线性的知识体系。而 Obsidian 的笔记思维更加适合于碎片化的知识，比如读书笔记、灵感记录等，对于我目前的学习来说反而会打乱思维。
<!-- prettier-ignore-end -->

### 笔记软件

我的笔记基于 Markdown。选择 Markdown 做笔记的优势很多：

-   广泛支持：几乎所有的笔记软件都支持 Markdown，它也可以在 GitHub 上直接显示。
-   简洁易用：Markdown 的语法简单易懂，学习成本低，排版效果美观。

请注意：不要同时使用多种基于 Markdown 的笔记软件 🙅

<!-- prettier-ignore-start -->
??? tip "不要同时使用多种笔记软件"
    
    **如果你要使用多种基于 Markdown 的笔记软件，那么最好*只使用 Markdown 的基础语法。***

    我曾经同时使用 Typora、Obsidian、VSCode 作为文档编辑器，Mkdocs 作为发布工具。Mkdocs 和 Obsidian 可以说是功能最多的两种 Markdown 扩展格式，但它们并不互相兼容。有人开发了 [Obsidian Github Publisher](https://obsidian-publisher.netlify.app/)，能够自动将 Obsidian 库发布为 Mkdocs，但使用体验并没有达到令我满意的程度，比如无法使用 Mkdocs admonition 的展开和折叠。

    对我而言，笔记的一大用处就是与他人共享、交流，因此 Mkdocs 的功能远比 Obsidian 的功能重要。最后我放弃了 Obsidian 作为主力编辑器，使用 VSCode 作为主力编辑器，在其中添加 Mkdocs 的用户代码片段方便编辑。
<!-- prettier-ignore-end -->

目前我使用的笔记软件及其功能如下：

-   VSCode：主力编辑器，编辑纯文本体验不输其他编辑器。不足就是进行图片插入、表格编辑等操作并不方便。
-   Typora：辅助编辑器，毫无疑问的世界上最好的纯 Markdown 编辑器。如果你不需要任何额外的特性，用它能大大提高你写作的效率。你能很方便地编辑表格、管理图片、导出成优美的 PDF 文档。它的缺点是几乎没有扩展能力，但这也正是它成为最好 Markdown 编辑器的原因。一般实验报告等文档我都直接使用 Typora 撰写并导出。
-   Obsidian：笔记浏览器。特别是在移动设备上，Obsidian 一定是体验最好的 Markdown 笔记浏览器。
-   Mkdocs：笔记发布器。

<!-- prettier-ignore-start -->
??? note "Mkdocs 的扩展语法"
    
    我经常使用 Mkdocs 的这些扩展语法：

    - [Admonition](https://squidfunk.github.io/mkdocs-material/reference/admonitions/)：警告、注意、提示等。
    - [Code Blocks](https://squidfunk.github.io/mkdocs-material/reference/code-blocks/)：代码块。
        - 开启代码复制功能：在 `mkdocs.yaml` 中添加 
            ```yaml
            theme:
                features:
                    - content.code.copy
            ```
        - 代码块标题：`title="标题"`
        - 行数和高亮：`linenums="1", hl_lines="2 3"`。行数可以不从 1 开始，但高亮行从 1 开始计数。
    
    这里提供我在 VSCode 中使用的自定义代码片段：

    ??? example "snippets"
    
        ```json title="markdown.json" linenums="1"
        "mkdocs-admonition": {
            "prefix": "mk-admonition",
            "body": [
                "<!-- prettier-ignore-start -->",
                "${1|!!!,???,???+|} ${2|note,abstract,info,tip,success,question,warning,failure,danger,bug,example,quote|} \"${3:title}\"",
                "",
                "    ${4:text}",
                "<!-- prettier-ignore-end -->"
            ],
            "description": "mkdocs-admonition",
        },
        "mkdocs-codeblock": {
            "prefix": "mk-codeblock",
            "body": [
                "```${1:format}${2: title=\"${3}\"}${4: linenums=\"${5:1}\"}${6: hl_lines=\"${7}\"}",
                "${8:code}",
                "```"
            ],
            "description": "mkdocs-codeblock"
        },
        "mkdocs-tabs": {
            "prefix": "mk-tab",
            "body": [
                "<!-- prettier-ignore-start -->",
                "=== \"$1\"",
                "    $2",
                "=== \"$3\"",
                "    $4",
                "<!-- prettier-ignore-end -->"
            ],
            "description": "mkdocs-tabs"
        }
        ```
<!-- prettier-ignore-end -->

### 笔记管理

我用一个 Obsidian 仓库管理所有笔记，其中 Mkdocs 的笔记作为一个 Git 仓区嵌套在其中。这个 Obsidian 库使用同步软件同步到各个设备上去：

```
ObsidianRepository
├── Mkdocs
│   ├── .git
│   ├── docs
│   └── mkdocs.yml
├── weekly
├── Archive
├── Doing
└── .obsidian
```

### 图片与附件管理

这个问题也困扰了我挺久，我不太想把图片放在仓库里，感觉那样会污染 Git 仓库。一个解决方法是使用图床。在图片量不多的时候我手动把图片放到我的 CDN 上，等图片量较大时我再去学习如何搭建一个图床。

<!-- prettier-ignore-start -->
??? note "其他人的解决办法"

    -   xg：使用一个在根目录的 `assets/images` 文件夹存储图片，图片拥有在 `docs` 文件夹中一样的路径。
    -   Isshiki：每个笔记文件都有一个独立的文件夹，附件和笔记一起存在里面。

!!! tip "小技巧"
    
    - 使用 [mkdocs-glightbox](https://github.com/blueswen/mkdocs-glightbox) 能够增强图片浏览体验。
<!-- prettier-ignore-end -->

## 文件同步

我的设备很多：笔记本、台式机、手机、平板。我的文档、笔记、书本、相片、代码等资源需要在这些设备之间同步，随时可以查阅，并保证流畅的工作体验。

我使用的跨设备同步软件是 [Syncthing](https://syncthing.net/)，它是一个开源的、去中心化的文件同步软件，能够在多个设备之间同步文件夹。

跨终端同步文件会遇到非常多麻烦，主要来源是系统的不同。比如 macOS 烦人的 `.DS_Store` 文件，Windows 的 `Thumbs.db` 文件，Linux 的 `.directory` 文件，以及各种隐藏文件。这些文件会污染 Git 仓库，也会增加同步的时间。一般情况下，如果你不在意，其实可以不管它们，不会对实际使用造成多大影响。但如果你在同步代码文件和 Git 仓库，就会产生非常多的困扰。

### 使用 Syncthing 同步 Git 仓库

最容易产生问题的就是不同系统的换行符不同，导致修改文件时产生大量的无用修改。需要进行两部操作解决这一问题：

-   将所有编辑器的换行符都设置为 `LF`。

可以使用 [EditorConfig](https://editorconfig.org/) 插件来统一编辑器的换行符设置，它已经支持了大部分编辑器和 IDE。

```title=".editorconfig"
# Unix-style newlines with a newline ending every file
[*]
end_of_line = lf
charset = utf-8
```

-   在 Git 仓库中添加 `.gitattributes` 文件，指定换行符为 `LF`。

```title=".gitattributes"
* text eol=lf
```
# Windows 使用杂记

## Windows 11 美化

Windows 当然也需要美化啦。在网上看过各式各样的美化效果，最后还是觉得：美化的尽头是 macOS。

想在 Windows 上获得最好的 dock 体验，可以在 Steam 购买 [MyDockFinder](https://www.mydockfinder.com/)，体验非常好，动画流畅。

如果希望让桌面丰富一些，可以安装 Rainmeter 的 [Big Sur RC1](https://www.deviantart.com/fediafedia/art/Big-Sur-RC1-for-Rainmeter-846882462)。

!!! bug "Weather 组件无法使用"

    作者的 apikey 似乎过期了，因此组件显示不了数据。在 `UserVariables.inc`文件中将 apikey 更改为 `21d8a80b3d6b444998a80b3d6b1449d3` 就可以使用了，当然这一密钥也随时面临无法使用的情况。密钥来源：[Weather.com API Access Denied](https://github.com/raiguard/ModernGadgets/issues/274)。

## 硬件部分

### 配置

台式机是因为看上了华硕的 AP201 机箱配的，具体配置如下：

- 机箱：华硕 AP201
- 主板：微星 B66OM 迫击炮 WIFI DDR4
- 处理器：Intel Core i5-12400
- 内存：镁光 16 GB 普条
- 电源：酷冷至尊 GX750 白色版
- 固态硬盘：三星 980 PRO 500 GB + MZVLW256HEHP
- 机械硬盘：Hitachi 4 TB x2
- 散热器：九州风神 AK400 HW

### 第一次装机

装机前，请务必看一遍硬件茶谈的装机视频：[【装机教程】全网最好的装机教程，没有之一](https://www.bilibili.com/video/BV1BG4y137mG/?spm_id_from=333.1007.top_right_bar_window_default_collection.content.click&vd_source=3010141ca72391f9e3cb40e673c1414e)。该视频几乎囊括了所有细节，比如内存插槽可能只有一侧有锁扣，这正巧是我在安装时遇到的问题。

1. 查看机箱的说明书，它一般会告诉你：对于这个机箱，整机的各个组件应当按照什么样的顺序组装。
2. 在主板上安装 CPU、内存、SSD 和风冷散热器。**动手前请完整阅读**各部分的安装说明，比如 SSD 全长是不需要安装卡扣的，我就为此疑惑了半天。
3. 将各组件装入机箱。在做每一步前，回看硬件茶谈的视频，有一些细节还是需要注意，比如主板可能需要斜插放入机箱，我垂直放进去的时候对不上 IO 挡板。
4. 确保 IO 面板的各个接口线缆**安插到位**，要用力试试。我第一次开机点不亮就是因为 HDMI 线没有完全插入。
5. 打开电源，尝试点亮。

---
tags:
  - Ongoing
---

# HTML 基础

> 大部分内容来自《Head First HTML》

* [W3C 验证工具](https://validator.w3.org)

## 概念性知识

### 概念

* **属性**：浏览器只认识每个元素 **预定义** 的一组属性，我们说浏览器支持这个属性。
    * HTML5 支持了定制数据属性，你可以为新属性构造定制的属性名。
    * **布尔属性**：没有值，只有存不存在。
* 元素
    * 元素的意义是让页面 **更结构化，更有意义**。比如面对视障人群，浏览器会选择最合适的方法来显示那些元素。
    * **块 （block） 元素、内联 （inline） 元素和空（void）元素**
    * 不要只是为了显示效果而使用 HTML 元素，比如 `<em>`

### 代码

* 浏览器会忽略 HTML 文档中的制表符、回车和大部分空格，根据你的标记确定在哪里换行/分段。
* 注释写在 `<!--` 和 `-->` 之间。
* **字符实体**：用于输入 `<` 和 `>` 等特殊字符
    * `<`: `&gt;`
    * `>`: `&lt;`
    * `&`: `&amp;`
    * 查找：[W3C](https://www.w3schools.com/charsets/ref_html_symbols.asp), [Unicode](http://www.unicode.org/charts)
    * 使用编号 `&#100;`

### 标准

* **HTML5** 是 HTML 的最新版本，它让编写 HTML 的很多做法大大简化，提供一些新的功能，并通过 JS API 提供一些高级特性。

* HTML 的发展历史

    * HTML 已经发展成为了一个 **活的标准**，不再会有版本号。现在只有 HTML。

    > 关键是向后兼容性

    * 现在的 HTML 规范会记录 Web 开发人员常犯的错误，并帮助浏览器处理这些错误。

* `<!doctype html>` 

    * 这是 HTML5 的 doctype，它告诉浏览器：这个页面使用 HTML 标准。

    * 老的 doctype 一般长这样

    ```html
    <!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
    ```

* `<meta charset="utf-8">` 指定编码类型。这一行必须放在 `<head>` 中最上方。

* 一些元素的 `alt` 属性是**必要的**

### 网站文件组织

* 为了复用，图片一般放在根目录的 `images` 文件夹中。
* 路径统一使用：斜杠 `/` （记忆：这是用右手划斜线最自然的方向）
    * `\` 是反斜杠，是 Windows 常用的
* 访问父文件夹：`../`
* 路径当心超过**255个字符**
* 网站的**文件夹和文件名不要有空格**

### 媒体

#### 图像

* JPEG
    * 适合连续色调图像
    * 有损格式，缩小时丢失信息
    * 不支持透明度
    * 文件较小，适用于 Web
    * 不支持动画
* PNG
    * 适合单色图像、线条构成图像：logo，剪贴画，小文本
    * 有 PNG-8 PNG-24 PNG-32
    * 无损格式，会压缩但不会丢掉信息
    * 支持透明
    * 文件更大一些
* GIF
    * 256色
    * “无损”格式
    * 只允许一种颜色设置为“透明”（这会导致锯齿透明区）
    * 支持动画

* 像素：CSS 像素是1英寸的1/96（96ppi）
* 使用**缩略图**并**链接到原始图像**。 
* 文本图像记得**柔化文本边缘（反锯齿）**，增强可读性。

#### 视频

## [元素手册](https://developer.mozilla.org/zh-CN/docs/Web/HTML/Element/)

Web 三部曲：计划、`<div>` 和 `<span>`

### 标准 HTML 结构

* `<!doctype html>`

* `<html>`
    * `<head>`
    * `<meta charset="utf-8">`
    * `<link>`
      * `rel`
      * `href`
      * 
    * `<style>` 可以在 HTML 中插入 CSS
      * 可选的属性：`type="text/css"`
    * `<body>`

### 通用属性

* `id`

    * 所有元素都能设置id

    * 值在一个页面中必须唯一

    * 必须字母开头，使用数字、横线、下划线、冒号或点号

### 简单元素

* `<a>`
    * 内容可以放置段落 `<p>`、图片 `<img>` 等，将它们作为超链接。
    * `href` 读作 h-ref
    * 使用 `#id` 链接到特定元素：`href="#chai"`（到本页面元素的链接）。
    * `title` 鼠标悬停时显示。
    * `target` 指定目标名，相同目标名的链接在同一个窗口中打开
    * `_blank` 总是新建一个窗口。

* `<h1>`
    * HTML 的标题有6级
* `<q>`  `<blockquote>`

* `<br>`

* [`<img>`](https://developer.mozilla.org/zh-CN/docs/Web/HTML/Element/img) 内联元素
    * `src="xx.png"`
    * `alt` 文本描述
    * `width` 和 `height`：使用像素指定。当然，**属性最好的用处是提供信息，如果是提供表现请使用 CSS**。

* `<ul>`, `<ol>`, `<dl>`
    * 只允许嵌套 `<li>`
    * 定义列表使用 `<dt>` （术语）和 `<dd>` （描述）

* `<em>`, `<strong>`, `<pre>`, `<code>`

* `<time>`

* `<del>` `<ins>`

### 表格

* `<table>`
    * `<tr>` table row
    * `<th>` table head
    * `<td>` table data
    * `rowspan="2"` 该单元格将跨入下一行
    * `colspan`
    * 可以同时跨行跨列
    * `<caption>` 表格标题
    * 表格可以嵌套（怎么指定样式呢？想象子孙选择器）

### 现代 HTML 结构

`<div>` 不是一个好结构。HTML 提供了更特定、更合适某些结构的标记。

|          |       |        |
| -------- | ----- | ------ |
| article  | nav   | header |
| footer   | time  | aside  |
| section  | video |        |
| mark     | audio | canvas |
| progress | meter | figure |

> 为什么提供这些新标签？
>
> * 浏览器、搜索引擎、屏幕阅读器能了解这个元素的信息

* `<time>` 

    * 如果元素内容没有采用 Internet 日期/时间格式写，就必须有 `datetime` 属性

    ```internet time
    2012-02-18
    2012-02
    2012-02-18 09:00
    2012-02-18 18:00
    05:00
    2012-02-18 05:00Z（UTC时间）
    ```

* `<video>`

    * 有一些属性：`controls` `autoplay` `loop` （这些是**布尔属性**） `width` `height` `src` `poster` 
    * `preload` 可以设置为 `none` ，播放前不自动下载视频；`metadata` 下载元数据。浏览器一般会根据用户带宽决定。
    * 可以为每一种视频格式使用一个 `<source src="">` 元素。对每个 `<source>` 元素，浏览器加载元数据看能不能播放这个视频。在这个元素中还可以给出 MIME 类型和编解码器信息 `type='video/ogg; codecs="theora, vorbis"' `
  
* `<audio>`

    * 与 `<video>` 元素很相似


### HTML 表单

表单是一个包含**输入域**的 Web 页面。

* `<form>`

    * `action="url"` 将处理表单数据的服务器脚本文件名
    * `method="POST"` 方法名
    * `<label>` 标签，内容会显示为文本。跟随在表单控件后。这时应当为相应的表单元素增加 `id` 属性。
    * `for=id` 表明是哪个元素的标签
    * `<fieldset>` 将公共元素组织在一起（对于复选框等很有用）
    * `<legend>` 是这一组的组标题，内容显示为文本。


    > **控件概述：** 每个控件都有 `name`，空间的作用是提供 `value` 以便脚本使用。

    * `<input>` 单行控件，void 内联元素

    * `type=""` 你希望得到什么输入

      * `text` 文本

      * `submit` 提交按钮，**它的值就是显示的文本**

      * `radio` 单选按钮，一组相关联的按钮应当有相同的 `name` 和不同的 `value`

      * `chechbox` 复选框，一组相关联的复选框应当有相同的 `name` 和不同的 `value`

        > 复选框的值被 `&` 合并

      * `number` 数字输入

      * `range` 滑动条（范围输入）

      * `color` 颜色输入

      * `date` 日期输入

      * `password` 输入的文本将被掩码

      * `file`

      * 

      * `email`

      * `tel` 电话

      * `url` 

        > 后面这三种类型看不出区别，不过是你在移动设备上输入时能得到一些快捷键盘

    * `value` 默认值

    * `placeholder` 提示信息

    * `required` 布尔属性，指示域是必要的。

    * `min`

    * `max`

    * `step`

    * `maxlength`

    * `checked` 布尔属性，默认选项

    * `<select>` 菜单

    * `multiple` 布尔属性，多选菜单。这时菜单从下拉式变为滚动式。按住 `Ctrl` 可以选择多个选项。
    * `<option>` 内容作为选项的显示
      * `value`

    * `<textarea>` 多行文本，内容会成为初始文本。

    * `rows` 多少行
    * `cols` 多少列
    * `maxlength`

    * 

`method` 中的 HTTP 方法：

* GET
    * 表单数据追加到 URL 的最后
    * 例：`http://web.com/contest.php?firstname=buck&lastname=banzai`
    * 如果你希望用户能对提交后的返回结果加书签的话，使用 GET 方法
* POST
    * 表单数据作为请求的一部分发送
    * 例：`http://web.com/contest.php`
    * 如果有私有信息，选择 POST 方法
    * 如果使用了 `<textarea>`，也选择 POST 方法
    * 文件也使用
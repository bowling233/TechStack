---
tags:
  - Todo
---

# CSS 进阶

## 更多选择器

* 伪元素
    * `:first-letter` 选择一个块元素中文本的第一个字母
* 属性选择器
    * `img[width="300"]` 选择宽度为 300 的图片元素
* 按兄弟选择
    * `h1+p` 前面有一个 `h1` 的 `p` 元素
* 结合选择器
    * 先定义上下文，再给出元素，最后指定伪类或伪元素
    * `div:greentea > blockquote p:first-line`

## 开发商特定 CSS 属性

名称一般为：`-开发商标识符-属性` 如：`-moz-transform`


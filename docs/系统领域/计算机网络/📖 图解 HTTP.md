---
tags:
  - 读书笔记
  - 正在做
---

# 📖 图解 HTTP

- Hypertext Transfer Protocol，超文本传输协议

## 预置知识

> 预置知识：IP、TCP 和 DNS

- IP 协议的作用是把数据包传送给对方，重要的条件是 IP 地址和 MAC 地址。
    - ARP 协议：用以解析地址，根据通信方的 IP 地址反查出对应 MAC 地址。不在同一局域网的通信中转需要用到该协议。
    - 路由选择：在到达通信目标前的中转过程中，计算机和路由器只能获悉很粗略的传输路线。没有人能够全面掌握互联网中的传输状况。
- TCP 协议的作用是确保数据能够到达对方，提供字节流服务（Byte Stream Service）
    - 它采用三次握手（three-way handshaking）策略。
        - TCP 标志：`SYN` 表示 synchronize，`ACK` 表示 acknowledgement。
        - 发送端首先发送 `SYN`，接收端回传 `SYN/ACK`，发送端再回传 `ACK` 代表握手结束。
        - 如果握手的某个阶段异常中断，TCP 会再次以相同顺序发送数据包。
    - 它将大块数据分割成报文段管理。
- DNS 协议提供域名到 IP 地址之间的解析服务，或逆向从 IP 地址反查域名的服务。
- URL 和 URI
    - 完整的绝对 URI 格式：`http://user:pass@www.example.jp:90/dir/index.htm?uid=1#ch1`
        - 依次为：方案名、登录信息、服务器地址、服务器端口号、带层次的文件路径、查询字符串、片段标识符。
            - 方案名可以指定协议（http、ftp 等）、数据（data）或脚本程序（javascript）等。不区分大小写。

## 基础

> 来自：《图解 HTTP》

一些概念：

- 现在讲解的是 **HTTP/1.1**。
- HTTP 协议用于 **客户端和服务器** 端之间的通信，通过 **请求和响应** 的交换达成通信。
- HTTP 是 **不保存状态**（stateless）的协议，即不保存之前发送过的请求或响应。
    - 为了保持状态，引入了 Cookie 技术。
- 使用 **方法** 下达命令，指定请求的资源按期望产生某种行为。
- **持久连接**（HTTP Persistent Connections，HTTP keep-alive 或 HTTP connection reuse）节省通信量。

    - HTTP 初始版本中，每次通信就要断开一次 TCP 连接。
    - 只要任意一端没有明确提出断开连接，则保持 TCP 状态。
    - **管线化**：同时并行发送多个请求，不需要一个接一个等待响应。

- **Cookie 技术**：在请求和响应报文中写入 Cookie 信息来控制客户端的状态。
    - `Set-Cookie` 首部字段：从服务器发送，通知客户端保存 Cookie。
    - 服务器端发现客户端 Cookie 后，查询是哪一个客户端的请求，并对比服务器记录，得到之前的状态信息。

### 报文

来看一个简单的请求报文：

```http
POST /form/entry HTTP/1.1
Host: hackr.jp
Connection: keep-alive
Content-Type: application/x-www-form-unlencoded
Content-Length: 16

name=ueno&age=37
```

> 读到这里，你有没有想起 HTML 表单中关于 POST 方法的讲解？

- 请求报文是由请求方法、请求 URI、协议版本、可选的请求首部字段和内容实体构成的。
    - 请求 URI：
        - 完整的请求 URI。
        - 在首部字段 `Host` 中写明网络域名或 IP 地址，则使用相对的请求 URI。
        - 对服务器本身发起请求，用 `*` 代替请求 URI，如 `OPTIONS * HTTP/1.1`。

来看一个简单的响应报文：

```http
HTTP/1.1 200 OK
Date: Tue, 10 Jul 2012 06:50:15 GMT
Content-Length: 362
Content-Type: text/html

<html>
...
```

- 响应报文由协议版本、状态码、状态码的原因短语、可选的响应首部字段和实体主体构成的。

### HTTP 方法

- GET：获取资源
- POST：传输实体主体
- PUT：传输文件
    - 因为没有验证机制，任何人都可以上传文件，一般网站不使用该方法。
- HEAD：获得报文首部
    - 不返回报文主体，用于确认 URI 有效性及资源更新日期时间等。
- DELETE：删除文件
    - 一般也不使用
- OPTIONS：询问支持的方法
- TRACE：追踪路径
    - 让服务器端将之前的请求通信环回给客户端。
    - `Max-Forwads` 首部字段中填入数值，每经过一个服务器端就减 1，当数值减到 0 时停止继续传输，最后接收请求的服务器端返回 200 OK 响应。
    - 可以查询发出去的请求是怎样被加工修改的。
    - 容易引发 XST 攻击，一般也不使用。
- CONNECT：要求用隧道协议连接代理
    - `CONNECT proxy.hackr.jp:8080 HTTP/1.1`
    - 主要使用 SSL 和 TLS。

## 进阶

> 来自：《图解 HTTP》

### HTTP 报文内的信息

- HTTP 报文本身是字符串文本，用 `CR(0x0d)+LF(0x0a)` 作换行符。
- 报文首部和报文主体由最初出现的空行来划分。
    - 报文首部：请求/状态行 + 各种首部字段
        - 请求行：请求方法、请求 URI 和 HTTP 版本。
        - 状态行：HTTP 版本、状态码和原因短语。
        - 4 种首部：通用首部、请求首部、响应首部、实体首部。
- 编码：提升传输速率
    - 辨析：报文主体和实体主体，通常这两者相等，当使用编码时产生差异
        - 报文：HTTP 通信的基本单位，由 8 位字节流组成。
        - 实体：请求或响应的有效载荷数据，由实体首部和 **实体主体** 组成。
    - 压缩传输的 **内容编码**：gzip（GNU zip）、compress（UNIX 系统标准压缩）、deflate（zlib）、identity（不编码）。
    - 分割发送的 **分块传输编码（Chunked Transfer Coding）**：将 **实体主体** 分成多个块，每一块用十六进制标记块大小，实体最后一块使用 `0(CR+LF)` 标记。
- 多部份对象集合（Multipart）方法：发送多种数据
    - 首部字段：`Content-Type`
    - 来源于 MIME。
    - 二进制数据以 ASCII 码字符串编码方式指明。
    - 发送的一份 **报文主体** 内可以含有多类型实体。
- 范围请求（Range Request）：获取部分内容
    - 首部字段：`Range`
    - 状态码：`206 Partial Content`
        - 若无法响应范围请求，则返回 `200 OK` 和完整实体内容。
        - 对于多重范围请求，会在 `Content-Type` 标明 `multipart/byteranges`
- 内容协商（Content Negotiation）：返回最合适内容
    - 三种类型：服务器驱动协商、客户端驱动协商、透明协商。

### HTTP 状态码

第一位指定了响应类别。常用的有 14 个状态码。

| 码                        | 信息                                                                                     |
| ------------------------- | ---------------------------------------------------------------------------------------- |
| 1XX                       | Informational 信息性状态码：接收的请求正在处理                                           |
| 2XX                       | Success 成功状态码：请求正常处理完毕                                                     |
| 200 OK                    |                                                                                          |
| 204 No Content            |                                                                                          |
| 206 Partial Content       |                                                                                          |
| 3XX                       | Redirection 重定向状态码：需要进行附加操作以完成请求                                     |
| 301 Moved Permanently     | 永久性重定向。指定资源路径最后忘记添加斜杠会产生该状态码。                               |
| 302 Found                 | 临时性重定向。希望用户（本次）能使用新 URI 访问，已移动的资源 URI 将来还有可能发生改变。 |
| 303 See Other             | 与 302 功能相同，但明确表示客户端应当采用 GET 方法获取资源。                             |
| 304 Not Modified          | 资源已找到，但未符合条件请求。                                                           |
| 307 Temporary Redirect    | 与 302 功能相同，不会从 POST 变成 GET。                                                  |
| 4XX                       | Client Error 客户端错误状态码：服务器无法处理请求                                        |
| 400 Bad Request           | 请求报文中存在语法错误。浏览器当作 200 OK 对待。                                         |
| 401 Unauthorized          |                                                                                          |
| 403 Forbidden             | 服务器没有必要给出拒绝理由。                                                             |
| 404 Not Found             | 可在拒绝请求且不想说明理由时使用。                                                       |
| 5XX                       | Server Error 服务器错误状态码：服务器处理请求出错                                        |
| 500 Internal Server Error |                                                                                          |
| 503 Service Unavailable   |                                                                                          |

- 不少返回的状态码响应都是错误的，但用户可能察觉不到这点。Web 应用程序内发生错误也依然返回 200 OK。

### Web 服务器

> 回忆一下你对 Nginx、Apache 等服务器的认识。

- 一台虚拟主机实现多个域名
    - 经过 DNS 解析后，请求发送到服务器时，已经是 IP 地址的形式了。如果一台服务器内托管多个域名，就需要弄清楚请求要访问哪个域名。
    - 因此，必须在 `Host` 首部内完整指定主机名或域名 URI。
- 通信数据转发程序：代理、网关、隧道
    - 代理：位于服务器和客户端中间，只负责转发。
        - 每次通过代理服务器时会追加 `Via` 首部。
        - 功能：利用缓存减少网络流量、针对特定网站的访问控制等。
        - 分类：缓存代理和透明代理。
    - 网关：转发其他服务器通信数据的服务器。接收请求时，就像源服务器一样对请求进行处理。用户可能不会察觉自己的通信目标是一个网关。
        - 和代理类似，但允许服务器使用非 HTTP 协议。
        - 能在客户端与网关之间的通信线路加密提高通信的安全性。
    - 隧道：在相隔很远的客户端和服务器之间进行中转，保持双方通信连接。
        - 确保安全的通信。
        - 隧道本身不会解析 HTTP 请求。
        - 会在通信双方断开连接时结束。
        - 隧道本身透明，客户端无需在意隧道的存在。
- 缓存

### HTTP 首部

- 首部字段（Header Fields）结构：`首部字段名:字段值`，可以有多个字段值。

!!! danger "首部字段重复"
规范尚未明确，根据浏览器内部处理逻辑不同，结果可能不一致。

HTTP 首部字段分为 4 种类型：

- 通用首部字段：双方都会使用的首部

| 字段名            | 说明                       |
| ----------------- | -------------------------- |
| Cache-Control     | 控制缓存的行为             |
| Connection        | 逐跳首部、连接的管理       |
| Date              | 创建报文的日期时间         |
| Pragma            | 报文指令                   |
| Trailer           | 报文末端的首部一览         |
| Transfer-Encoding | 指定报文主体的传输编码方式 |
| Upgrade           | 升级为其他协议             |
| Via               | 代理服务器的相关信息       |
| Warning           | 错误通知                   |

- 请求首部字段：请求报文使用的首部

| 字段名              | 说明                           |
| ------------------- | ------------------------------ |
| Accept              | 用户代理可处理的媒体类型       |
| Authorization       | Web 认证信息                   |
| Expect              | 期待服务器的特定行为           |
| From                | 用户电子邮箱地址               |
| Host                | 请求资源所在服务器             |
| If-Math             | 比较实体标记                   |
|                     |                                |
| Max-Forwards        | 最大传输逐跳数                 |
| Proxy-Authorization | 代理服务器要求客户端的认证信息 |
| Range               | 实体的字节流范围请求           |
| Referer             | 对请求中 URI 的原始获取方      |
| TE                  | 传输编码的优先级               |
| User-Agent          | HTTP 客户端程序的信息          |

- 响应首部字段

| 字段名 | 说明 |
| ------ | ---- |
| Accept |      |

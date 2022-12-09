---
tags:
  - Deprecated
---

#  Service Deployment

## Overview

> NOTE FOR SECURITY:
>
> Why not deploy web service in root?
>
> * 

* First step: create an account to run the service independently:

  ```bash
  useradd service-name
  ```

  

> NOTE FOR MANUFACTURING:
>
> * 生产环境的用户权限：
>
>   部署到生产环境运行时是不能用root等最高权限的，一切都给予以最小权限，在RedHat系的系统还有SELinux等限制。公司应该是为了让你们熟悉相应的环境。如果不限制你们使用root等最高权限，你用yum update升级了系统组件，你想要什么软件就想都装到系统里面，那别人的东西可能就乱了。
>
>   在生产环境运行的系统本身可能已经有很多东西在运行，一旦系统的东西被更改，会影响原来的环境。很多东西是可以静态编译进去的，不需要局限于服务器本身的环境。
>
>   yum这种东西虽然说方便，但是对于有要求的环境没什么帮助，所以Linux上面很多东西都是要自己编译的。
>
>   Nginx本身可以加很多的第三方模块，如果你不习惯Linux下面这种编译的欢乐时光，而是靠yum、apt，很可能会影响以后的发展。
>
> * 当你用非 root 启动 nginx（即没有进程能监听 80 或 443 端口），你需要用其它的方式将流量重定向到它们上面。例如开一个内网下专门应对流量的”前端“服务器，监听 80 并代理过来，由于环境隔离安全性可以提高很多。或者使用 iptables 将 80 端口流量重定向到 nginx 上。其它方式等等。
>
>   但一般来讲 nginx 这种可靠软件不需要这样做。更多时候漏洞是 web 应用自身导致的。
>
>   在 linux 下，只有以 root 启动的进程才能监听小于 1024 的端口。nginx 如果设置了监听 80 或 443 端口，则一定得以 root 帐号启动。如果只是测试，则可将端口设成 8080 之类大于 1024 的端口。
>
>   其他还需要注意日志文件和 pid 文件的写入权限问题。




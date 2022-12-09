# 1. Syncthing 同步服务器搭建记录

* 安装：[APT Syncthing](https://apt.syncthing.net/)

## 服务用户新建

使用 root 用户运行 syncthing 是不合适的，应当创建专门的用户。

> 参考：[](https://0xzx.com/2022020423502061657.html)
>
> [](https://www.linuxfordevices.com/tutorials/ubuntu/syncthing-install-and-setup)

按照正常方式新建名为 Syncthing 的用户，分配 `~` 作为文件存储目录。

### 自动启动配置

* syncthing 设置了需要的 systemd service 文件：`/lib/systemd/system/syncthing@.service`
* 设置你自己的服务：`systemctl enable syncthing@username.service`
* 启动前，记得检查 `syncthing@.service` 文件的内容。Execution 行的内容应该被配置为： ` ExecStart=/usr/bin/syncthing  -no-browser -gui-address="0.0.0.0:8384" -no-restart -logflags=0`
  * 暂时没有查明，为什么不能启用 `serve` 参数。这会导致远程访问被拒绝连接。

* 更改连接后，需要运行 `systemctl daemon-reload` 应用更改
* 接下来启动 `systemctl start syncthing@syncthing.service`

## SSH 端口转发

## Syncthing 相关配置

> 参考文档：[syncthing-faq](https://www.mankier.com/7/syncthing-faq)
>
> [syncthing域名配置](https://www.wenjinyu.me/syncthing-accesses-domain-names-through-nginx-anti-proxy/)

### 忘记 GUI 密码

* 停止 syncthing 服务
* `syncthing generate --gui-password=myNewPassword --gui-user=newUserName`
* 重新启动 syncthing

或者你可以在 syncthing 的配置文件 `config.xml` 中进行更改：

```xml
<gui enabled="true" tls="false" debugging="false">
   <address>127.0.0.1:8384</address>
   <user>syncguy</user>
   <password>[protected]</password>
   <apikey>[protected]</apikey>
   <theme>default</theme>
</gui>
```


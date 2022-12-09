---
tags:
  - Todo
---

# sudo: execute a command as another user

## 配置

* 配置文件 `/etc/sudoers`
* 修改配置文件必须使用 `visudo` 命令，避免文件出问题导致 `sudo` 无法运行
  * 这会在检查语法无误后写入
  * 该命令默认调用 `nano` 编辑器
* 常用配置：
  * 在 `sudoers` 文件中有提示，可以直接看
  * 允许用户组成员无密码使用 `sudo`：`%wheel ALL=(ALL) NOPASSWD: ALL`


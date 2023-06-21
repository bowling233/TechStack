# 搭建个人电子图书馆

本文基于 [Calibre-Web](https://github.com/janeczku/calibre-web)。

## 安装

Calibre-Web 的安装过程并不复杂，按照教程来即可。

## Nginx 反向代理

Calibre-Web 默认监听本地 8083 端口，可以使用 Nginx 反向代理出去。

```nginx
server {
    listen       80;
    server_name  your_domain_name;

    location / {
        proxy_pass http://127.0.0.1:8083;
        proxy_set_header Host $proxy_host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
}
```

## 配置

参考 GitHub 仓库的 Wiki。建议开启匿名访问。开启匿名访问后，用户列表中新增 `Guest` 用户，可以进行配置。为了免受爬虫和攻击，可以考虑不向匿名用户开放阅读和下载权限。
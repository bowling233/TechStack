# 网络

## CORS

!!! info

    - [MWD](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS)

- 出于安全的考虑，**浏览器**会限制跨域请求。
- 服务器使用 CORS，标示允许哪些源跨域访问。
- 浏览器先向服务器发送预检请求，确认是否允许跨域，再发送真正的请求。
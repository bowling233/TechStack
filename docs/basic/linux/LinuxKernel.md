---
tags:
  - Doing
---

# Linux 内核

## 进程状态

* R: running 运行或运行队列等待
* S: sleep 休眠 等待条件或信号脱离状态
* D: 不响应异步信号 不能被 `kill` 中断
* Z: zombie 已终止 但进程描述符存在 需要父进程调用系统函数释放
* T: ternimated
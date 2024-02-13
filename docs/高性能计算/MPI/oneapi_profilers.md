# oneAPI 性能分析工具

oneAPI 有几个工具可以用来分析性能：`vtune`、`traceanalyzer`、

!!! warning "一些老旧的命令"

    如 `amplxe-cl` 等工具已经被 `vtune` 取代，这里不再介绍。

## VTune

!!! note "`vtune` 命令助记卡"

    <embed src="../attachment/vtune-profiler-cheat-sheet.pdf" style="width:100%; height:60vh;" type="application/pdf">

服务器端一般没有 GUI，本地 VTune 远程调试也需要将远程服务器 SSH 设置为无密码登陆（我们一般不会这样做）。因此常见的调试流程是：

- 在服务器端运行数据收集
- （可能）在服务器上完成数据处理
- 下载到本地，使用 GUI 工具查看结果

```bash
vtune -collect hotspots -r result -- ./a.out
vtune -report summary -r result
```

上面的两行命令分别执行了数据收集和数据处理，其中 `-collect` 选项指定了收集的数据类型，`-r` 选项指定了结果保存的文件夹，`--` 后面是要运行的程序及其参数。`-report` 选项指定了数据处理的类型，`-r` 选项指定了数据处理的结果文件夹。

## `itac`


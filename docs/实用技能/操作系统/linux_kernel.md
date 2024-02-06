# Linux 内核

<!-- prettier-ignore-start -->
!!! info "参考资料"

    -   书籍：
        -   The Linux Programming Interface
        -   Linux Kernel Development
<!-- prettier-ignore-end -->

## 设备和模块

<!-- prettier-ignore-start -->
!!! success "Linux 思想：一切皆文件"
<!-- prettier-ignore-end -->

-   设备类型：块、字符、网络。
    -   只有网络设备不是通过 device node 访问的，而是通过 socket API。
    -   块设备可寻址，字符设备看作流。
    -   还有虚拟设备，如 `/dev/random` 等，提供内核功能。
-   模块：Linux 内核用这个机制来支持动态加载和卸载。
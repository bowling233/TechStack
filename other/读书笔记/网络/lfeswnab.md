# Linux Firewalls: Enhancing Security with nftables and Beyond (4th Edition)

## 第一到三章

书籍的前面几章还是基础知识，但侧重于安全内容，有提及一些攻击方法。

- 第一章讲基本概念，OSI 网络模型，跳过。
- 第二章讲包过滤防火墙的概念，下文有一些笔记。
- 第三章讲 iptables，因为已经读过相关书籍，直接跳过。

## 第四章：nftables

与 iptables 不同，nftables 没有内置任何表。

### 基本概念

与 iptables 类似：address family、table、chain、rule。不过 nftables 有更多的 address family，可以处理 ARP、桥接等功能。

nftables 具有独特的语法，且提供编程接口，更加灵活。

### `nft` 命令

`nft` 命令的格式与 SQL 类似，比 `iptables` 更加直观：

```shell
nft <command> <subcommand> <chain> <rule definition>
```

`command` 包括：

```text
add, list, insert, delete, flush, raname
```

`subcommand` 包括：

```text
table, chain, rule
```

列出 rules 时：

- 带上 `-a` 可以显示 handle（句柄），方便删除和修改。
- 会尝试解析端口和地址，可以使用 `-nn` 禁用。

### Chain

```shell
nft add chain filter input { }
```

### Rule

nftables rule 由 statement 和 expression 组成。

```text title="statement"
accept
continue
drop
goto
jump
limit
log
queue
reject
return
```

Expression:

- Payload：主要用来匹配包头

    === 'IPv4'

        ```text
        daddr, saddr, version, length
        checksum, frag-off, hdrlength, id, tos, ttl, protocol 
        ```

    === 'IPv6'

        ```text
        daddr, saddr, version, length
        flowlabel, hoplimit, nexthdr, priority
        ```

    === 'TCP'

        ```text
        checksum, dport, sport
        ackseq, doff, flags, sqeuence, urgptr, window
        ```

    === 'UDP'

        ```text
        checksum, dport, sport
        length
        ```

    === 'ARP'

        ```text
        hlen, htype, op, plen, ptype
        ```

- Meta

    ```text
    protocol
    iif, iifname, iiftype
    oif, oifname, oiftype
    length, mark, priority
    rtclassid
    skgid, skuid
    ```

- Conntrack：由关键字 `ct` 加上下面的选项

    ```text
    daddr, saddr, proto-src, proto-dst
    direction, helper, mark 
    protocol, l3proto
    expiration, state, status
    ```

- State:

    ```text
    new, established, invalid, related, untracked
    ```
# nfsv4 WG

## 前置 RFC

> The reader should be familiar with the XDR and RPC protocols as described in [RFC4506] and [RFC5531].

### RFC 4506 - XDR: External Data Representation Standard

> XDR uses a language to describe data formats. The language can be used only to describe data; it is not a programming language.

XDR 是一种用来描述数据格式的语言。和 C 语言比较类似。

```text
+--------+--------+...+--------+--------+...+--------+
| byte 0 | byte 1 |...|byte n-1|    0   |...|    0   |   BLOCK
+--------+--------+...+--------+--------+...+--------+
|<-----------n bytes---------->|<------r bytes------>|
|<-----------n+r (where (n+r) mod 4 = 0)>----------->|
```

XDR 数据的 item 总是由 4 字节的 block 组成。如果 item 长度不是 4 的倍数，会用 0 补齐。

XDR 定义以下数据类型：

| 英文 | 中文 | 类型名 | 说明 |
| --- | --- | --- | --- |
| Integer | 整数 | `int` | 32 bits |
| Unsigned Integer | 无符号整数 | `unsigned int` | 32 bits |
| Enumeration | 枚举 | `enum { name-identifier = constant, ... }` | |
| Boolean | 布尔 | `bool` | |
| Hyper Integer and Unsigned Hyper Integer | 高精度整数和无符号高精度整数 | `hyper`, `unsigned hyper` | 64 bits |
| Floating-point | 浮点数 | `float` | |
| Double-Precision Floating-point | 双精度浮点数 | `double` | |
| Quadruple-Precision Floating-point | 四精度浮点数 | `quadruple` | 128 bits|
| Fixed-Length Opaque Data | 固定长度的不透明数据 | `opaque identifier[n]` | |
| Variable-Length Opaque Data | 可变长度的不透明数据 | `opaque identifier<n>` | **至多**前四个字节用于表示长度，之后接数据，故最长 $2^{32}-1$ bytes |
| String | 字符串 | `string object<m>` | **至多**前四个字节用于表示长度，之后接数据，故最长 $2^{32}-1$ bytes |
| Fixed-Length Array | 固定长度的数组 | `type-name identifier[n]` | 每个元素类型相同，但长度可以不同，比如 `string` 作为元素 |
| Variable-Length Array | 可变长度的数组 | `type-name identifier<m>` | **至多**前四个字节用于表示长度，之后接数据，故最长 $2^{32}-1$ 个元素 |
| Structure | 结构体 | `struct { component-declaration-A; ... }` | |
| Discriminated Union | 区分联合 | `union switch (discriminant-declaration) { case discriminant-value-A: arm-declaration-A; ... default: default-declaration; }` | `discriminant` 可以是 `int`、`unsigned int`、`enum`，均为 4 bytes，后接对应的数据 |
| Void | 空 | `void` | 0 bytes，可以放在 `union` 中 |
| Constant | 常量 | `const` | 不代表数据，只是符号常量 |
| Typedef | 类型定义 | `typedef` | |
| Optional Data | 可选数据 | `type-name *` | “可选”的意思是数据可能不存在，等价于最长长度为 1 的变长数组，常用于递归数据结构（链表的 `next` 指针） |

RFC 第五部分解释了 XDR 中一些设计的原因，比如块大小为四字节是为了内存对齐。

其余部分描述了 BNF 范式下的语法定义和一些范例。

### RFC 5531 - RPC: Remote Procedure Call Protocol Specification Version 2

RFC 建议阅读一些背景文献：

> The paper by Birrell and Nelson [XRPC] is recommended as an excellent background for the remote procedure call concept.

RPC 不对传输层协议做要求。

- 如果传输层不可靠，则需要实现超时、重传等机制，RPC 不提供这些服务。
- 如果传输层可靠，则不需要做其他工作。即使如此，应用也可能需要实现超时、重连等机制以应对服务器崩溃等情况。

因此无法推断远程过程的状态，比如发送两次请求但没有收到回复，不能确定远程过程是否执行了两次。如果收到一次回复，只能确定远程过程执行了至少一次。

每个 RPC 消息都有事务 ID，一方面用于客户端匹配回复与对应的函数调用，另一方面方便服务器实现最多执行一次的语义（execute-at-most-once semantics）。

第 8 章讲述 RPC 对实现的要求：

- RPC 程序和过程：
    - 远程 program number、program version number、procedure number 唯一确定调用的过程。
        - program number 其中一部分由 IANA 分配。有点类似于 IP 地址范围，开发者可以定义一部分本地使用的 program number。
        - procedure number 由特定程序的文档描述。
    - RPC version number 在本文中为 `2`。
- 认证、完整性和隐私：
    - 调用含有两个认证字段：credential 和 verifier；回复含有 response verifier。字段定义为如下的 `opaque_auth` 结构体。

        ```text
        enum auth_flavor {
           AUTH_NONE       = 0,
           AUTH_SYS        = 1,
           AUTH_SHORT      = 2,
           AUTH_DH         = 3,
           RPCSEC_GSS      = 6
           /* and more to be defined */
        };

        struct opaque_auth {
           auth_flavor flavor;
           opaque body<400>;
        };
        ```

第 9 章描述 RPC 消息的具体结构，一些重要的部分摘录如下。结合前文的叙述，这些结构一目了然，不需要进一步解释。

```text
enum msg_type {
   CALL  = 0,
   REPLY = 1
};

enum accept_stat {
   SUCCESS       = 0, /* RPC executed successfully       */
   PROG_UNAVAIL  = 1, /* remote hasn't exported program  */
   PROG_MISMATCH = 2, /* remote can't support version #  */
   PROC_UNAVAIL  = 3, /* program can't support procedure */
   GARBAGE_ARGS  = 4, /* procedure can't decode params   */
   SYSTEM_ERR    = 5  /* e.g. memory allocation failure  */
};

struct rpc_msg {
   unsigned int xid;
   union switch (msg_type mtype) {
   case CALL:
      call_body cbody;
   case REPLY:
      reply_body rbody;
   } body;
};

struct call_body {
   unsigned int rpcvers;       /* must be equal to two (2) */
   unsigned int prog;
   unsigned int vers;
   unsigned int proc;
   opaque_auth cred;
   opaque_auth verf;
   /* procedure-specific parameters start here */
};

union reply_body switch (reply_stat stat) {
case MSG_ACCEPTED:
   accepted_reply areply;
case MSG_DENIED:
   rejected_reply rreply;
} reply;

struct accepted_reply {
   opaque_auth verf;
   union switch (accept_stat stat) {
   case SUCCESS:
      opaque results[0];
      /*
       * procedure-specific results start here
       */
    case PROG_MISMATCH:
       struct {
          unsigned int low;
          unsigned int high;
       } mismatch_info;
    default:
       /*
        * Void.  Cases include PROG_UNAVAIL, PROC_UNAVAIL,
        * GARBAGE_ARGS, and SYSTEM_ERR.
        */
       void;
    } reply_data;
};

union rejected_reply switch (reject_stat stat) {
case RPC_MISMATCH:
   struct {
      unsigned int low;
      unsigned int high;
   } mismatch_info;
case AUTH_ERROR:
   auth_stat stat;
};
```

第 12 章描述 RPC 语言，其实就是在 XDR 的基础上定义了 `program`、`procedure`、`version` 等关键字。示例程序如下：

```text
program PING_PROG {
      /*
       * Latest and greatest version
       */
      version PING_VERS_PINGBACK {
         void
         PINGPROC_NULL(void) = 0;
         /*
          * Ping the client, return the round-trip time
          * (in microseconds).  Returns -1 if the operation
          * timed out.
          */
         int
         PINGPROC_PINGBACK(void) = 1;
      } = 2;

      /*
       * Original version
       */
      version PING_VERS_ORIG {
         void
         PINGPROC_NULL(void) = 0;
      } = 1;
   } = 1;

   const PING_VERS = 2;      /* latest version */
```

这段样例程序展示了两个版本的 RPC 程序。其中新的版本增加了一个 `PINGPROC_PINGBACK` 过程。通过 RPC 调用中的 `vers` 字段，就能实现不同版本程序的兼容。

RFC 的剩余部分主要是已分配的 program number。其中比较重要的有：

```text
# Description/Owner        RPC Program Number        Short Name
# -----------------------------------------------------------------
nfs                                100003    nfs   
NFS Automount File System          100099    autofs
NFS ACL Service                    100227    nfs_acl
rdmaconfig                         100417    rpc.rdmaconfig
```

### Implementing Remote Procedure Calls

这是一篇 1984 年发表在 ACM 上的文章。在那时，Linux 还没有出现，RPC 在文章中也是一种实验性的新技术。这篇文章主要讲述研究者实现 RPC 时的一些考虑和决策。

- 不实现共享内存空间，因为实现带来的复杂性和不稳定性远远超过了好处。

!!! todo "阅读到 1.5 节"

## RFC 7530 - Network File System (NFS) Version 4 Protocol

### 第一部分：介绍

NFSv4 的特性：

- 安全，包括 Kerberos 等。
- `NULL` 和 `COMPOUND` 过程，后者能够将多个逻辑文件系统操作打包到一个 RPC 调用中，比如 `LOOKUP`、`OPEN` 和 `READ`。需要注意：`COMPOUND` 不提供原子性。
- 文件和目录名使用 UTF-8 编码。
- filehandle 的类型在 persistent 之外添加了 volatile，提供的文件可能在声明周期内失效。
- ACL 作为 recommended 的文件属性。
- 新增 `OPEN` 和 `CLOSE` 操作。
- 支持字节范围的文件锁，且不再需要 RPC 调用。基于租借的锁机制，客户端需要定期续约，否则状态会被释放。
- 客户端缓存：
    - 文件属性和目录信息定时向服务器查询。
    - 文件数据在打开时向服务器确认有效性。
- 文件 open 时，服务器可以向客户端提供 read/write delegation，提供期间保证没有其他客户端执行相关操作。这样客户端就可以在本地执行 read/write 操作，不需要与服务器即时交互。服务器可以回收 delegation。

### 第四部分：Filehandles

File handle 包含服务端区分单一文件的信息，对客户端不透明（逐字节比较）。服务器尽力维持一一映射。相同的 filehandle 必定指向相同文件，注意不同的 filehandle 可能指向同一个文件。

NFS 操作基于 filehandle。在 NFSv4 以前，通过 `MOUNT` 协议获取第一个 filehandle，该协议在安全和防火墙方面存在问题。NFSv4 中弃用了该方式，定义了两个特殊的 filehandle 作为 NFS 客户端的起点：

- Root filehandle：
    - `PUTROOTFH` 使服务器将当前 filehandle 设置为服务端文件树的根。
- Public filehandle：
    - 没有限制绑定到的文件，由管理员确定。
    - `PUTPUBFH` 使用 public filehandle。

File handle 的类型由 `fh_expire_type` 文件属性表示：

- Persistent：即使服务器重启仍然指向对应的文件系统对象。
    - 对象可能消失，返回 `NFS4ERR_STALE`。
- Volatile
    - 如果服务端能确定文件对象消失，返回 `NFS4ERR_STALE`。
    - 其他情况：`NFS4ERR_FHEXPIRED`。
    - 对于这种类型的 filehandle，客户端需要处理过期后恢复。客户端可以存储路径等通向文件系统对象的信息，以从根重新获取 filehandle。如果文件对象消失，则客户端无法恢复。

### 第五部分：属性

属性可以通过 `GETATTR` 和 `SETATTR` 操作获取和设置。

与 NFSv4 之前的版本不同，NFSv4 客户端可以查询服务器支持哪些属性，并构造相应的查询。属性被分为三种：`REQUIRED`、`RECOMMENDED` 和 named。前两者使用向量中的位表示，而 named 属性需要通过下面的方法查询：

```text
+----------+-----------+---------------------------------+
| LOOKUP   | "foo"     | ; look up file                  |
| GETATTR  | attrbits  |                                 |
| OPENATTR |           | ; access foo's named attributes |
| LOOKUP   | "x11icon" | ; look up specific attribute    |
| READ     | 0,4096    | ; read stream of bytes          |
+----------+-----------+---------------------------------+
```

一般来说，named 属性是应用所考虑的，NFS Client 不需要考虑。使用 named 属性较为复杂，见 RFC 原文。

下面列出了按属性相同的范围分组的属性：

- The per-server attribute is:

    ```text
    lease_time
    ```

- The per-file system attributes are:

    ```text
    supported_attrs, fh_expire_type, link_support, symlink_support,
    unique_handles, aclsupport, cansettime, case_insensitive,
    case_preserving, chown_restricted, files_avail, files_free,
    files_total, fs_locations, homogeneous, maxfilesize, maxname,
    maxread, maxwrite, no_trunc, space_avail, space_free,
    space_total, and time_delta
    ```

- The per-file system object attributes are:

    ```text
    type, change, size, named_attr, fsid, rdattr_error, filehandle,
    acl, archive, fileid, hidden, maxlink, mimetype, mode,
    numlinks, owner, owner_group, rawdev, space_used, system,
    time_access, time_backup, time_create, time_metadata,
    time_modify, and mounted_on_fileid
    ```

NFSv4 具体文件属性的说明见 RFC 原文。

值得注意的是，`RECOMMENDED` 属性 `owner` 和 `owner_group` 是字符串，而不是数字。这是为了避免在不同系统上的 UID 和 GID 不一致的问题。在协议中传递时，必须转换为 `identifier@dns_domain` 的形式。当然，转换会有不少问题和考虑，RFC 中有详细说明。

### 第六部分：ACL

!!! todo

### 第七、八部分：单、多 NFS 服务器命名空间

!!! todo

### 第九部分：文件锁与共享预约

!!! todo

### 第十部分：客户端缓存

!!! todo

### 第十四到十八部分：NFSv4 请求、过程、操作及回调

## RFC 5661 - Network File System (NFS) Version 4 Minor Version 1 Protocol

读完了 RFC 7530，抓包时却发现 `NULL` 后接的 `EXCHANGE_ID` 操作找不到，才知道这是 NFSv4.1 的内容。

https://www.snia.org/sites/default/files/ESF/Part2-Advances%20in%20NFS%20%E2%80%93%20NFSv4.1%20and%20pNFS%5B1%5D.pdf

NFSv4.1 introduces Sessions

> Major extensions introduced in NFS version 4 minor version 1 include Sessions, Directory Delegations, and parallel NFS (pNFS).
>
> NFS version 4 minor version 1 has no dependencies on NFS version 4 minor version 0, and it is considered a separate protocol.

接下来，我们针对 NFSv4.1 引入的 Sessions 进行学习

### Session

目录中，可以看到有关 Session 的改变：

- 第二章：核心基础设施
- 第八章：状态管理（新增章节）

第二章详细介绍了 Session 的概念：

> Limited trunking over multiple network paths.
>
> The NFSv4.1 client can associate an arbitrary number of connections with the session, and thus provide trunking (Section 2.10.5).

先前的协议不能充分利用多条网络路径。NFSv4.1 客户端可在会话中联结任意数量的连接以实现多条网络路径的聚合。

> A session is a dynamically created, long-lived server object created by a client and used over time from one or more transport connections.

会话的定义：为一个客户端动态分配，长期保持，在多个传输连接中复用。

> A client may have one or more sessions associated with it so that client-associated state may be accessed using any of the sessions associated with that client's client ID, when connections are associated with those sessions

客户端可以建立多个会话，连接和会话之间也没有一一对应的限制。

> Client ID and Session Association
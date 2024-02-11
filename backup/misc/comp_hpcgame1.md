# 1st PKU HPCGame

## B. 流量席卷土豆

!!! info "题目省流"

    使用 Slurm 提交任务，在 4 个节点上，每个节点运行 4 个进程，同时读取 16 个文件。

步骤如下：

- Slurm 并行运行 `tshark` 过滤 SSH 数据，`mergecap` 合并为单 PCAP 文件。前者需要保留 Slurm JobID。
- 将合并后的 PCAP 文件输入 `quantum-cracker` 得到结果。

```bash
srun -p C064M0256G -N4 --ntasks-per-node=4 bash -c 'tshark -r /lustre/shared_data/potato_kingdom_univ_trad_cluster/pcaps/${SLURM_PROCID}.pcap -Y ssh -w ${SLURM_PROCID}.ssh.pcap'
sacct -u $(whoami) --format JobID | tail
mergecap -w merged.pcap *.ssh.pcap
quantum-cracker merged.pcap
```

## D. 小北问答 Classic

1. 65.396
2. 105.26 107.14
3. iv. GCC
4. 进程、线程、线程
5. 8 i ii
6. xi. OpenACC
7. 未找到正确选项。
8. iv. HBM
9. ii. Slurm
10. i. 缓存未命中

## F. 高性能数据校验

!!! info "题目省流"

    输入一个文件，使用 SHA512 进行分块文件校验，输出校验码。校验过程如下：

    -   分块，`M=1MB`，不足补 0。
    -   每块末尾连接前一块的校验码，得到的数据进行校验，得到本块校验码。
    -   最后一块的校验码为文件校验码。
    
    需要了解一下 `libcrypto` 库，运用拆分出的各个函数安排并行任务。
    
    环境：OpenMPI，并行节点 2 个，每个节点 4 个进程。

### 简单了解一下 `libcrypto`

![Libcrypto API](https://wiki.openssl.org/index.php/Libcrypto_API).

Libcrypto 提供高级和低级接口，其中高级接口称为 EVP interface，直接提供加密解密、校验码等功能，也是我们在基准代码中看到的。低级接口则需要直接与各种算法打交道。

![EVP](https://wiki.openssl.org/index.php/EVP).

EVP 提供一些对象：

- `EVP_PKEY`s：用于存储密钥，支持 RSA、EC 等等。
- `EVP_CIPHER`s：用于存储
- `EVP_MD`s：Message Digest，消息摘要，正是本题关注的。

一点密码学概念：消息完整性。

> 有些场合我们不需要保密，但需要完整性。这是与加密不同的安全服务。
>
> 这里我们需要用到**密码散列函数**，建立消息的压缩影像。这些散列函数从长度不一的消息中创建**长度固定**的消息摘要，一般都采用**迭代**完成。
>
> MD（Message Digest）消息摘要算法由罗恩·李维斯设计，最新的 MD5 版本将消息分为长度为 512 位的分组，创建大小为 128 位的摘要，但摘要太小了无法阻挡攻击。
>
> SHA（Secure Hash Algorithm）安全散列算法由 NIST 设计，有许多版本。本题基于 SHA 512。

![EVP Message Digests](https://wiki.openssl.org/index.php/EVP_Message_Digests)

使用 OpenSSL 消息摘要/散列函数的步骤如下：

- Create a Message Digest context
- Initialise the context by identifying the algorithm to be used (built-in algorithms are defined in evp.h)
- Provide the message whose digest needs to be calculated. Messages can be divided into sections and provided over a number of calls to the library if necessary
- Caclulate the digest
- Clean up the context if no longer required

### 程序结构

了解了上面的这些背景，程序的基本结构也就一目了然了。

在 `main` 中调用 `checksum`，消息读入 `buffer`，摘要输出到 `obuf`。

注意一下消息的数据格式，都是用 `uint8_t` 即以字节为单位，之后计算数据结构大小需要用到。`BLOCK_SIZE` 已定为 1MB。

`checksum` 中：

- `prev_md` 存储上一次的摘要。
- `EVP_DigestUpdate(ctx, d, cnt)` Hashes `cnt` bytes of data at `d` into the digest context `ctx`. This function can be called several times on the same `ctx` to **hash additional data**.
- `EVP_DigestFinal_ex(ctx, md, s)` Retrieves the digest value from `ctx` and places it in `md`. If the `s` parameter is not NULL then the number of bytes of data written (i.e. the length of the digest) will be written to the integer at `s`, at most EVP_MAX_MD_SIZE bytes will be written unless the digest implementation allows changing the digest size and it is set to a larger value by the application. **After calling `EVP_DigestFinal_ex()` no additional calls to `EVP_DigestUpdate()` can be made**, but `EVP_DigestInit_ex2()` can be called to initialize a new digest operation.

### 思路与探索

一眼看过去，各个数据块之间有联系，前一个没计算完无法计算下一个，似乎不能并行。但 `EVP_DigestUpdate` 函数可以被多次调用，给任务提供了分阶段进行的可能。

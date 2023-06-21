# Lab1 Construct simple cluster

<!-- prettier-ignore-start -->
!!! tip "Keep in mind"
    
    **Always redirect the output of your commands to a file.** It helps to store informations in files. You may need them later to get information or debug.
    
    ```bash
    # Redirect stdout and stderr to files
    command > stdout.log 2> stderr.log
    ```
    
    If you want to see the information in your terminal, you can use `tee` to print the output to both stdout and files.
    
    ```bash
    # Redirect stdout and stderr to files and print them to terminal
    command 2>&1 | tee stdout.log stderr.log
    ```
<!-- prettier-ignore-end -->

## 0. Create a virtual machine

Procedures of installation are skipped.

If you can't bear low display resolution in terminals, see [Configuring Network and SSH](#4-configuring-network-and-ssh) to use SSH to connect to the virtual machine.

## 1. Build and install OpenMPI from source

Follow the official tutorial [OpenMPI: FAQ:Building Open MPI](https://www.open-mpi.org/faq/?category=building#easy-build) to install OpenMPI. 

```bash
wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.1.tar.gz
tar -xvf openmpi-4.1.1.tar.gz
cd openmpi-4.1.1
./configure --prefix=/usr/local
make all install
```

You may need `sudo` privilege to execute `make all install` because it needs to change `/usr/local/`. After installation, the binary files are in `/usr/local/bin` and you don't need to change PATH.

<!-- prettier-ignore-start -->
!!! note "Remember directory paths"
    
    You'll need to configure paths to OpenMPI when compiling and running MPI programs. In my case, the paths are:
    
    - binary: `/usr/local/bin/`
    - header files: `/usr/local/include`
    - hostfile: `/usr/local/etc/openmpi-default-hostfile`
    
    After I've done the lab, I understood that I should have used an independent path to save the OpenMPI files and other components, so that they can be found more easily. For example, I can use `/usr/local/openmpi-4.1.1` to save the files.
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "Test your OpenMPI installation"
    
    You can test your OpenMPI installation by executing `mpirun`:
    
    ```bash
    mpirun --version
    ```
    
    If you see the version information, then you've installed OpenMPI successfully.
    
    If you want to test the compilation and execution of MPI programs, you can try to compile and run the `hello.c`. Follow the instructions on [Using MPI with C](https://curc.readthedocs.io/en/latest/programming/MPI-C.html)

<!-- prettier-ignore-end -->

## 2. Build and install BLAS and CBLAS

Prepare tools:

```bash
sudo apt install build-essential gfortran cmake
```

Get the source code and extract them:

```bash
wget "https://netlib.org/benchmark/hpl/hpl-2.3.tar.gz"
wget "http://www.netlib.org/blas/blas-3.11.0.tgz"
wget "http://www.netlib.org/blas/blast-forum/cblas.tgz"
tar xvf hpl-2.3.tar.gz -C hpl
tar xvf blas-3.11.0.tgz -C blas
tar xvf cblas.tgz -C cblas
```

### Install BLAS

```bash
cd blas
make
```

Then you'll Find the line `BLASLIB = ../../blas$(PLAT).a` and change it to `BLASLIB = /usr/local/lib/libblas.a`. Then save and exit. Then execute `make`, get the binary file `cblas_LINUX.a` in the folder. Copy it to `/usr/local/lib`:

```bash
cp blas_LINUX.a /usr/local/lib/libblas.a
```

Run the test program for BLAS and passed:

![BLAS Test](https://cdn.bowling233.top/images/2023/06/202306220048488.png)

### Install CBLAS

```bash
cd ../cblas
more README
```

Read the instructions in `README` to install CBLAS.

```bash
cp Makefile.LINUX Makefile.in
vim Makefile.in
```

Find the line `BLASLIB = ../../blas$(PLAT).a` and change it to `BLASLIB = /usr/local/lib/libblas.a`. Then save and exit. Then execute `make`, get the binary file `cblas_LINUX.a` in the folder. Copy it to `/usr/local/lib`:

```bash
make
cp cblas_LINUX.a /usr/local/lib/libcblas.a
```

<!-- prettier-ignore-start -->
??? failure "Error when compiling CBLAS"
    
    If you encountered the same error when executing make in CBLAS folder and stopped at testing process, receiving the error message like:
    
    ```
    Error: rank mismatch in argument 'strue1' at (1) (rank-1 and scalar)
    ```
    
    ![CBLAS Error](https://cdn.bowling233.top/images/2023/06/202306220048489.png)
    
    The reason is that there are some old-fashioned code deprecated by recent version of gcc-10. You can try to modify the `Makefile` in test folder, adding `-std=legacy` or `-fallow-argument-mismatch` to the flags.
    
    Here are more information:
    
    - [GitHub: Compilation error using gfortran-10?](https://github.com/xianyi/OpenBLAS/issues/2625)
    - [GitHub: Compilation error with GCC 10](https://github.com/xianyi/OpenBLAS/issues/2262)
    
    After edit, run `make` again and you'll see the test passed.
    
    ![CBLAS Test](https://cdn.bowling233.top/note/hpc/l1/cblas_test.png)

<!-- prettier-ignore-end -->

## 3. Build HPL

There are some difference between the experiment manual and `INSTALL` file, you should follow the manual. 

```bash
cp setup/Make.Linux_PII_CBLAS Make.test
```

Edit some lines in `Make.test`:

```
# diff from Make.test and Make.Linux_PII_CBLAS
64c64
< ARCH         = test
---
> ARCH         = Linux_PII_CBLAS
84,86c84,86
< MPdir        =
< MPinc        = -I/usr/local/include
< MPlib        = /usr/local/lib/libmpi.so
---
> MPdir        = /usr/local/mpi
> MPinc        = -I$(MPdir)/include
> MPlib        = $(MPdir)/lib/libmpich.a
95,97c95,97
< LAdir        =
< LAinc        = #/home/bowling/CBLAS/include
< LAlib        = /usr/local/lib/libcblas.a /usr/local/lib/libblas.a /usr/lib/gcc/x86_64-linux-gnu/10/libgfortran.a /usr/lib/gcc/x86_64-linux-gnu/10/libquadmath.a /usr/lib/x86_64-linux-gnu/libm.a
---
> LAdir        = $(HOME)/netlib/ARCHIVES/Linux_PII
> LAinc        =
> LAlib        = $(LAdir)/libcblas.a $(LAdir)/libatlas.a
169c169
< CC           = /usr/local/bin/mpicc
---
> CC           = /usr/bin/gcc
176c176
< LINKER       = $(CC)
---
> LINKER       = /usr/bin/g77
```

<!-- prettier-ignore-start -->
??? failure "Error in linking"
    
    You may encounter the error message like this:
    
    ![HPC_error](https://cdn.bowling233.top/images/2023/06/202306220048496.png)
    
    Search the web and you'll find the libs containing missing symbols. They are:
    
    -   `/usr/lib/gcc/x86_64-linux-gun/10/libgfortran.a`
    -   `/usr/lib/gcc/x86_64-linux-gun/10/libquadmath.a`
    -   `/usr/lib/gcc/x86_64-linux-gun/10/libm.a`
    
    Searching for the missing library was hard, because it happens everywhere. Solutions to others may not take effect on you.
    
    I'm still wondering why these libraries were not linked automatically, they are in the default `PATH`.

<!-- prettier-ignore-end -->

After make, you'll get the binary file `xhpl` in the folder `bin/test`.

## 4. Configuring network and SSH

To construct a cluster, we need to use NAT network to connect them together. The host cannot connect to virtual machine inside NAT network directly, but we can use port forwarding:

![Port Forwarding](https://cdn.bowling233.top/images/2023/06/202306220048497.png)

Now we can ssh into the `master` machine:

```bash
ssh -p 3022 bowling@localhost
```

![](https://cdn.bowling233.top/images/2023/06/202306220048487.png)

## 5. Experiment

<!-- prettier-ignore-start -->
??? failure "Error: cannot open file HPL.dat"
    
    You may encounter error like this:
    
    ![HPL.dat](https://cdn.bowling233.top/images/2023/06/202306220048495.png)
    
    Refer to this issue:
    
    - [HPL Segmentation Fault](https://github.com/spack/spack/issues/6340)
<!-- prettier-ignore-end -->

Final result:

![Result](https://cdn.bowling233.top/images/2023/06/202306220048498.png)

## Bonus: Docker

Using docker, we can skip the process of building everything. We only need to configure SSH connection and write `HPL.dat`, then enjoy. **DOCKERS ARE AWESOME.**

### Find docker

I use the docker from [ashael/hpl - Docker Image | Docker Hub](https://hub.docker.com/r/ashael/hpl), which contains configured `hpl-2.2`.

Here I've opened 4 containers from the same image:

![docker image](https://cdn.bowling233.top/images/2023/06/202306220048491.png)

### Setting up connection

Dockers are connected within a bridge by default.

![docker network](https://cdn.bowling233.top/images/2023/06/202306220052179.png)

Attach to each of them and get their ip address:

![docker ip](https://cdn.bowling233.top/images/2023/06/202306220048492.png)

Select the host of `172.17.0.5` as master, `172.17.0.4`-`172.17.0.2` as slaves.

**In master:**

```bash
ssh-keygen
cat ~/.ssh/id_rsa.pub
```

**In slaves:**

```bash
mkdir /var/run/sshd
vim /etc/ssh/sshd_config
```

find these lines:

```config
#ListenAddress ::
#ListenAddress 0.0.0.0
#AuthorizedKeyFile %h/.ssh/authorized_keys
```

uncomment them and save.

Then add master's public key to `authorized_keys` and start `sshd`.

![docker ssh](https://cdn.bowling233.top/images/2023/06/202306220048494.png)

Succeeded.

### Execute experiment

![docker result](https://cdn.bowling233.top/images/2023/06/202306220048493.png)

I found the computing speed in dockers is much faster then clusters. **DOCKERS ARE EXTREMELY AWESOME.**

## Related links

- [45gfg9's Note](https://heap.45gfg9.net/t/2023-ZJU-HPC101-Lab1/)

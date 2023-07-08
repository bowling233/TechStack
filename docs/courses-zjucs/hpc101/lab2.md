# Lab2 Vector Calculation

## Basic usage of NumPy

### Conda

Actually this may be our first time to manage Python project. So a package management system is needed. Let's learn [Conda](https://docs.conda.io/en/latest/) first.

Most used conda commands:

- `conda create -n myenv`: create a new environment
- `conda activate myenv`: activate an environment
- `conda deactivate`: deactivate current environment
- `conda install numpy`: install a package
- `conda list`: list all packages installed in current environment
- `conda remove numpy`: remove a package
- `conda update numpy`: update a package
- `conda search numpy`: search a package
- `conda env export > environment.yml`: export an environment
- `conda env create -f environment.yml`: create an environment from a file
- `conda env remove -n myenv`: remove an environment
- `conda env list`: list all environments

### Idea

**Vectorization** and **broadcasting** are two important concepts in NumPy. They are the key to make NumPy faster than pure Python.

- Vectorization describes the absence of any explicit looping, indexing, etc., in the code.
- Broadcasting is the term used to describe the implicit element-by-element behavior of operations.

### Check it

You should learn:

- Array creation
- Indexing on `ndarrays`
- I/O with NumPy
- Data types
- Broadcasting
- Copies and views
- Structured arrays
- Universal functions (ufuncs) basics

### Array

Some terminology in NumPy:

- vector: 1d array
- matrix: 2d array
- tensor: 3d or higher dimensional array
- axes: dimensions

Attributes of array:

- `dtype`: data type
- `ndim`: number of dimensions
- `shape`: a tuple of integers, indicating the size of the array in each dimension

Create an array:

- `np.array(list)`: create an array from a list
- `np.zeros(n)`: create an n-dimensional array full of zeros
- `np.ones(n)`: create an n-dimensional array full of ones
- `np.empty(n)`: create an n-dimensional array full of random numbers
- `np.arange(start, end, step)`: create an array from start to end with step
- `np.linspace(start, end, num=)`: create an array from start to end with num elements

Use `dtype` keyword argument to specify the data type of the array. For example, `np.array([1, 2, 3], dtype=np.float32)`.

### Manipulate

Operating on arrays with different types will **upcast** to the more precise one.

Arithmetic operations: usually **element-wise**.

- `+`, `-`, `*`, `/`, `**`, `%`, `//`
- inplace operations: `+=`, `-=`, `*=`, `/=`, `**=`, `%=`, `//=`

Matrix product:

- `@` operator: `a @ b`
- `dot` function: `A.dot(B)`



Sorting:

- `np.sort(arr)`: sort an array, return a sorted copy
- `np.argsort()`
- `np.lexsort()`
- `np.searchsorted()`: find elements in a sorted array
- `np.partition()`: partial sort

Concatenate:

- Vectors: `np.concatenate((a1, a2, ...))`: concatenate arrays
- Multidimensional arrays: `np.concatenate((a1, a2, ...), axis=)`: concatenate arrays along a specific axis.
    - Note: You can only concatenate arrays on existing axes.

Info:

- `ndarray.ndim`: number of dimensions
- `ndarray.size`: total number of elements
- `ndarray.shape`: mentioned above

Reshape: 
- `arr.reshape(shape)`
- `np.reshape(arr, newshape=(,), order='C')`
    - `newshape`: a tuple of integers
    - `order`:
        - `C`: row-major, C-like index order
        - `F`: column-major, Fortran-like index order
        - `A`: if `a` is Fortran contiguous then Fortran-like, otherwise row-major

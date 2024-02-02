# Lab2 Vector Calculation

## Basic usage of NumPy

### Idea

**Vectorization** and **broadcasting** are two important concepts in NumPy. They are the key to make NumPy faster than pure Python.

- Vectorization describes the absence of any explicit looping, indexing, etc., in the code.
- Broadcasting is the term used to describe the implicit element-by-element behavior of operations.

### Learn NumPy

I recommend you to learn following tutorials:

- [A Visual Intro to NumPy and Data Representation – Jay Alammar – Visualizing machine learning one concept at a time.](http://jalammar.github.io/visual-numpy/)
    - Creating Arrays:`np.array([1, 2, 3])`, `np.ones()`, `np.zeros()`, `np.random.random()`
    - Array Arithmetic: `+`, `-`, `*`, `/` all position-wise
    - Indexing: `data[0:2]`, `data[1:]`
    - Aggregation: `min()`, `max()`, `sum()`
    - Creating Matrices
    - Matrix Arithmetic
        - position-wise
        - broadcast
    - Dot Product `data.dot(otherMatrix)`
    - Matrix Indexing
        - `data[0:2, 0]`
        - `data[1:3]`
    - Transposing and Reshaping: `data.T`, `data.reshape()`
    - More dimension: the last axis is looped over the fastest, while the first is the slowest.
    - Practical usage:
        - `error = (1/n) * np.sum(np.square(y - y_predicted))`
- [NumPy Illustrated: The Visual Guide to NumPy | by Lev Maximov | Better Programming](https://betterprogramming.pub/numpy-illustrated-the-visual-guide-to-numpy-3b1d4976de1d)
    - NumPy Array vs. Python List
    - 1D Arrays
        - `dtype`, `shape`
        - `np.zeros_like(a)`, `np.zeros(n, int)`
        - 

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

You can make use of this cheetsheet for review: [Python_Cheat_Sheets.pdf (itu.edu.tr)](https://web.itu.edu.tr/iguzel/files/Python_Cheat_Sheets.pdf)

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

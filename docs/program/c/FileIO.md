## Chapter 13 File Input/Output

* functions
  * fopen, getc, putc, exit, fclose
  * fprintf, fscanf, fgets, fputs
  * rewind, fseek, ftell, fflush
  * fgetpos, fsetpos, feof, ferror
  * ungetc, setvbuf, fread, fwrite

### 13.1 Communicating with Files

* about *line break*
  * C and Unix: `\n` (the line-feed character)
  * pre-OS X Macintosh: `\r`  (the carriage-return character)
  * early MS-DOS and Windows Notepad: `\r\n`, with `Ctrl+Z` to denote EOF, pad with null character
  * **NOTICE:** but in C (text mode), all these things are **mapped** to the C view `\n`
* Standard Files
  * standard input/output/error output

### 13.2 Standard I/O

* input and output are **buffered** (transferred in large chunks)
* `exit()`: in `stdlib.h`; terminate, *closing any open files*, argument is passed to operating systems
  * different between `return` and `exit`: exit terminates the program even if called in a function
* `fopen()`: (address of a string containing file name, open mode)
  * r, w (truncate exist, create not exist), a (append exist, create not exist) 
  * r+ (r and w), w+ (truncate, r and w), a+ (read all file, only append)
  * rb, ab+, a+b: binary mode
  * wx, wbx, wb+x: fail if **already exists**, and open in **exclusive mode**
  * return: *file pointer*, or **null pointer** if cannot open the file
* `FILE *`: points to a data object containing information about the file and the buffer
* `getc(fp)` and `putc(ch, fpout)`: like `getchar()` and `putchar()` 
* **NOTICE:** C discovers it has reached the end of a file **only after it tries to read past the end of the file**, so you should use an **entry-condition loop** (not a do while loop)
* *dummy value*
* `fclose(fp)`: close file, flush buffers
  * return value: 0 (successful), EOF (not succeeded)
  * example: disk is full, removable storage device has been removed, or there has been an I/O error


### 13.3 A simple-Minded File-condensing Program



### 13.4 File I/O: `fprintf(), fscanf(), fgets()` and `fputs()`

### 13.5 Adventures in Random Access: `fseek()` and `ftell()`

### 13.6 Behind the scenes with Standard I/O

### 13.7 Other Standard I/O Functions
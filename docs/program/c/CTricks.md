# Something to make your program more friendly

## 一、I/O

### Discard unwanted input

`scanf()` always leave blanks and newline of one line. If the user uses `\n` to stop input, this can make the program exit without confirmation.

* `getchar()` until the newline

  ```C
  while (getchar() != '\n') continue;
  ```

If `scanf()` doesn't read the value it requires, the input data will be left unused in the buffer, preventing the program to advance. We can discard the wrong value by this method:

* `scanf()` suppress assignment

  ```C
  while(scanf("%f", &floatNumber) != 1){
      scanf("%*s"); //discard wrong input
      puts("Please use correct input.");
  }
  ```

  



## 2. Program Control

### Loop Condition

* arrive the end of file
* entered the stop signal
* come to the max length of an array
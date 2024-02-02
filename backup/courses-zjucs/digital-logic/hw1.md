<div class="cover" style="page-break-after:always;font-family:方正公文仿宋;width:100%;height:100%;border:none;margin: 0 auto;text-align:center;">
    <div style="width:60%;margin: 0 auto;height:0;padding-bottom:10%;">
        </br>
        <img src="https://raw.githubusercontent.com/Keldos-Li/pictures/main/typora-latex-theme/ZJU-name.svg" alt="校名" style="width:100%;"/>
    </div>
    </br></br></br></br></br>
    <div style="width:60%;margin: 0 auto;height:0;padding-bottom:40%;">
        <img src="https://raw.githubusercontent.com/Keldos-Li/pictures/main/typora-latex-theme/ZJU-logo.svg" alt="校徽" style="width:100%;"/>
	</div>
    </br></br></br></br></br></br></br></br>
    <span style="font-family:华文黑体Bold;text-align:center;font-size:20pt;margin: 10pt auto;line-height:30pt;">Logic and Computer Design Fundamentals</span>
    <p style="text-align:center;font-size:14pt;margin: 0 auto">Homework 1</p>
    </br>
    </br>
    <table style="border:none;text-align:center;width:72%;font-family:仿宋;font-size:14px; margin: 0 auto;">
    <tbody style="font-family:方正公文仿宋;font-size:12pt;">
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">Teacher</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">马德 </td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">Name</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 朱宝林</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">Student ID</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋" </td>   3220106026  </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">Date</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">2023.10.06</td>     </tr>
    </tbody>              
    </table>
</div>

<!-- 注释语句：导出PDF时会在这里分页 -->

## 1-3 Number Systems

| Number | Binary | Octal | Hex |
| ------ | ------ | ----- | --- |
| 16     | 10000  | 20    | 10  |
| 17    | 10001  | 21    | 11  |
| 18    | 10010  | 22    | 12  |
| 19    | 10011  | 23    | 13  |
| 20    | 10100  | 24    | 14  |
| 21    | 10101  | 25    | 15  |
| 22    | 10110  | 26    | 16  |
| 23    | 10111  | 27    | 17  |
| 24    | 11000  | 30    | 18  |
| 25    | 11001  | 31    | 19  |
| 26    | 11010  | 32    | 1A  |
| 27    | 11011  | 33    | 1B  |
| 28    | 11100  | 34    | 1C  |
| 29    | 11101  | 35    | 1D  |
| 30    | 11110  | 36    | 1E  |
| 31    | 11111  | 37    | 1F  |

## 1-9 Convert Numbers

| Decimal | Binary | Octal | Hex |
| ------- | ------ | ----- | --- |
| 369.3125 | 1 0111 0001.0101 | 561.24 | 171.5 |
| 189.625 | 1011 1101.101 | 275.5 | BD.A |
| 214.625 | 1101 0110.1010 | 326.5 | D6.A |
| 61831.625 | 1111 0011 1100 1110.1010 | 171716.5 | F3C7.A |

## 1-12 Binary Multiplications

(a) 

$$
\begin{equation*}\begin{array}{c}
\phantom{\times9999}1010\\
\underline{\times\phantom{9999}1100}\\
\phantom{\times9999999}0\\
\phantom{\times999999}0\phantom9\\
\phantom{\times99}1010\phantom{99}\\
\underline{\phantom{\times9}1010\phantom{999}}\\
\phantom{\times9}1111000
\end{array}\end{equation*}
$$

(b) 

$$
\begin{equation*}\begin{array}{c}
\phantom{\times9999}0110\\
\underline{\times\phantom{9999}1001}\\
\phantom{\times9999}0110\\
\phantom{\times999999}0\phantom9\\
\phantom{\times99999}0\phantom{99}\\
\underline{\phantom{\times9}0110\phantom{999}}\\
\phantom{\times99}110110
\end{array}\end{equation*}
$$

(c) 

$$
\begin{equation*}\begin{array}{c}
\phantom{\times9999}1111001\\
\underline{\times\phantom{99999}011101}\\
\phantom{\times9999}1111001\\
\phantom{\times999999999}0\phantom9\\
\phantom{\times99}1111001\phantom{99}\\
\phantom{\times9}1111001\phantom{999}\\
\underline{\phantom{\times}1111001\phantom{9999}}\\
\phantom{1}110110110101
\end{array}\end{equation*}
$$

## 1-13 Binary Divisions

```
              1 0001
            ---------
      101 | 101 0110
            101
            ---
                0110
                0101
                ----
                   1
```

Quotient: $ 1 0001 $, Remainder: $ 1 $

## 1-16 Radix

(a) 

$$
B\times r^2 + E\times r^1 + E\times r^0 = 2699\\
\Rightarrow r = 15
$$

(b)

$$
3\times r^2 + 6\times r^1 + 5\times r^0 = 194\\
\Rightarrow r = 7
$$

## 1-18 BCD

(a) 

Decimal: 4867
Binary: 0001 0011 0000 0011

(b) 

Decimal: 378.75
Binary: 0001 0111 1010.1100

## 1-19 BCD

$$
(715)_{10} = (0111\ 0001\ 0101)_{BCD}\\
(354)_{10} = (0011\ 0101\ 0100)_{BCD}
$$

## 1-28 Gray code

| Binary | Gray Code | Hexdecimal |
| ------ | --------- | ---------- |
| 0000   | 0000      | 0          |
| 0001   | 0001      | 1          |
| 0010   | 0011      | 2          |
| 0011   | 0010      | 3          |
| 0100   | 0110      | 4          |
| 0101   | 0111      | 5          |
| 0110   | 0101      | 6          |
| 0111   | 0100      | 7          |
| 1000   | 1100      | 8          |
| 1001   | 1101      | 9          |
| 1010   | 1111      | A          |
| 1011   | 1110      | B          |
| 1100   | 1010      | C          |
| 1101   | 1011      | D          |
| 1110   | 1001      | E          |
| 1111   | 1000      | F          |






# one2III

a commandline utility that generates possible ways of reading a number.

or more formally:
- given a string of digits and a list of conversion rules
- split the string into all possible combination of substrings
- convert every substring using every possible conversion rule

a bit like the ["Worst Wifi Password Ever"](https://www.youtube.com/watch?v=bLE7zsJk4AI), but for numbers only.

sample:

![sample](sample.gif)

## available rules:

| rule                   | from | to                       |
| ---------------------- | ---- | ------------------------ |
| as number              | 55   | 55                       |
| run length encoding    | 335  | 2:2 1:5                  |
| run length decoding    | 3211 | 2221                     |
| roman numeral          | 123  | CXXIII                   |
| to english             | 321  | three hundred twenty one |
| look and say           | 770  | two sevens one zero      |

## example: 123 with rules "run length encoding" & "roman numeral":

- "123"
  - 1:1 1:2 1:3 , CXXIII
- "12 3"
  - 1:1 1:2 1:3 , XII III
  - 1:1 1:2 III , XII 1:3
- "1 23"
  - 1:1 1:2 1:3 , I XXIII
  - 1:1 XXIII , I 1:2 1:3
- "1 2 3"
  - 1:1 1:2 1:3 , I II III
  - 1:1 1:2 III , 1:1 II 1:3 , I 1:2 1:3
  - 1:1 I I III , I II 1:3 , I 1:2 III

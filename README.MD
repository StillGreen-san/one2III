# one2III

a commandline utility that:

- given a string of digits and a list of conversion rules
- splits the string into all possible combination of substrings
- converts every substring using every possible conversion rule

A bit like the [Worst Wifi Password Ever](https://www.youtube.com/watch?v=bLE7zsJk4AI), but for numbers only.

## available rules:

| rule                   | from | to                       |
| ---------------------- | ---- | ------------------------ |
| as number              | 55   | 55                       |
| run length encoding    | 112  | 2:1 1:2                  |
| as run length encoding | 3211 | 2221                     |
| roman numeral          | 123  | CXXIII                   |
| to english             | 321  | three hundred twenty one |
| look and say           | 770  | two sevens one zero      |

## e.g. 123 with rules rle & roman:

! UDATE THIS !
- "123"
  - 111213 , CXXIII
- "12" "3"
  - 1112 13 , XII III
  - 1112 III , XII 13
- "1" "23"
  - 11 1213 , I XXIII
  - 11 XXIII , I 1213
- "1" "2" "3"
  - 11 12 13 , I II III
  - 11 12 III , 11 II 13 , I 12 13
  - 11 II III , I II 13 , I 12 III
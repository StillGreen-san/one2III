# one2III

given a string of digits and a list of conversion rules

split the string into all possible combination of substrings

convert every substring using every possible conversion rule

## available rules:

- number: (just take the number as is) 55 -> 55
- run length encoding: 112 -> 2112
- roman numerals: 123 -> CXXIII
- words in english: 321 -> three hundred twenty one
- look and say: (combination of rle (converted/interpreted) and english) 770 -> two zewens one zero

## e.g. 123 with rules rle & roman:

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
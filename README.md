# Anagram-Solver 
This program will take a string of letters and ouput any words that are an anagram of it.
It will also be able to deal with wildcards (?) and should work in linear time!

There will be two parts to this program, seting up a data structure to store all english words in
the linux dictionary file, then searching that data structure to find all posible anagrams of a
given word.

## Linear Time
With my other anagram problem solver, the time complexity was exponential (yikes!) - meaning that
you could only really use it with words shorter than 10 characters long. This new approach will
use a hashmap of hashmaps to store words. The first hashmap will store hashmaps that contain 
words of equal length:


| 3 | ------> HashMap {  hashmaps containing e.g bat, cat mat, etc. }

 

| 4 | ------> HashMap {  hashmaps containing e.g fish, tree, cool, etc. }
            
 Then the second hashmap (the internal ones) will then contain any words that have an equal sum 
 of character values. e.g. 'bat' and 'tab' have the same sum of character values 
 (b + a + t = t + a + b as + is commutative) and would be stored in the same internal hashmap.
 
 The reason you need these two hashmaps instead of the last one (internal), is because of the reason that a three letter word can have the same sum of values as a two letter word, but they aren't anagrams. This is why we split the internal hashmaps into groups of words that equal the same length.
 
 

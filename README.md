# MTH-4300-Algorithms-Computers-and-Programming-Final-Project
Let 𝑝∈(0,1) be a real number. An unfair coin has probability 𝑝 of landing heads and probability 1−𝑝 for landing tails. 
Let 𝑛∈ℕ and let 𝑠→=(𝑠1, 𝑠2, …, 𝑠𝑛)∈{𝐻,𝑇}𝑛 be a sequence of heads and tails of length 𝑛. 
Let 𝐸𝑠→ be the expected number of coin tosses until the first occurrence of the sequence 𝑠→.  
The first line of the input contains the real number 𝑝 and the integer 𝑛. 
The second line of the input consists of the sequence of zeroes and ones of length 𝑛. 
Zero represents a tail and one represents a head.  Write a program that outputs 𝐸𝑠→ accurate to at least 6 decimal places.

Examples:

Example 1 Input:
0.5 1
1

Output:

2

Example 2 Input:
0.2 1
1

Output:

5

Example 3 Input:
0.5 4
1 0 1 0

Output:

20

Example 4 Input:
0.3 7
1 1 1 0 0 1 1

Output:

854.286554127793

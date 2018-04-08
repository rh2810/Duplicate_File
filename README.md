# Duplicate_File
Duplicate a given input file under the same or new name up to 100 times!

Directions:

- This program must be run on a Linux system or any system that can use GCC.

- Compile the program inside of the directory that you saved the duplicate.c program in:

  - Make sure that the file you want to make copies of (input file) is in the same directory as duplicate.c
  
  - In a terminal, type: "gcc -Wall -o duplicate duplicate.c"

- After compilation is complete, run the program:

  - From terminal, type: "./duplicate **<input_file>** **<output_file>** *<number_of_copies>*"
  
    - **Bolded text** - required fields
    
    - *Italicized text* - optional fields
    
  - Examples:
  
    - ./duplicate in.txt out.txt
    
      - Creates a file named out.txt. The contents of in.txt are then copied into out.txt.
      
    - ./duplicate in.txt out.txt 10
    
      - Creates 10 files named out.txt, out(1).txt, ..., and out(9).txt. The contents of in.txt are then copied into the output files.
      
    - ./duplicate copy.txt copy.txt
    
      - Creates a file named copy(1).txt. The contents of copy.txt are then copied into copy(1).txt
      
    - ./duplicate copy.txt copy.txt 100
    
      - Creates 100 files named copy(1).txt, copy(2).txt, ..., and copy(100).txt. The contents of copy.txt are then copied into the output files.

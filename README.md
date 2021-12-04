### processor - a program emulating the work of a real life processor

# Table of contents:

    1) Assembler - a program that translates assembler code into binary code
    2) Disassembler - a program that translates binary into assembler (used to check if assembler works correctly)
    3) Processor - a program that runs binary code

# Setup:

    1) Create your build directory 
    2) cd into this directory
    3) run cmake "path to processor root dir"
    4) run make

# Short description of the language

    register names - {ax, bx, cx, dx}

    1) push *argument*
        where *argument*:
            
            *number* - pushes a number onto stack
            *register name* - pushes a number onto stack which is stored in the registers
            *register name + number* - pushes a value onto stack equal to val in register + number
            [x] - pushes a number from operative memory and x is cell in memory

    2) pop *argument*

        where *argument*:
            
            can be empty - pops a value off the stack
            *register name* - pops a value into register
            [x] - pops a value into memory cell x

    3) jmp *argument*

        if *argument*:

            *number* - jumps to code on line number
            *label:* - jumps to label with the same name

    4) ja, same as jmp if the last value on stack is bigger than the one before the last
    
    5) jae, same as ja, jumps if equal or bigger

    6) jb, same as ja, jumps if lower

    7) jbe, same as ja, jumps if lower or equal

    8) je, same as ja, jumps if equal

    9) jne, reverse je

    10) call, calls code and returns to the line where it was called + 1 after executing it

    11) ret, shows where call should return

    12) sqrt - evaluates square root of last number on stack

    13) sub - divides last number on stack by the the number before the last on stack

    14) prnt - prints the value on stack

    15) add - adds two last numbers on stack

    16) mul - multiplies two last numbers on stack

    17) sub - substracts the last nubmber on stack from the prev from last number on stack

    18) halt - shows where to stop executing the program

    19) in - reads a value from the stack
            
                

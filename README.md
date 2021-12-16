# Making Cellular Automata in C
So I wanted to learn the C language, and the first thing I thought about making is the Conway's Game of Life. It took a while to figure out how to use a library in C, and then figuring out which library to use, and then actually implementing everything. I didn't follow any C tutorials for making this, just past knowledge and a lot of Google searches. Making the CGoL was the most difficult because I had to figure everything out from the start, but making the Falling Sand Game was easier because I just needed to change the rules.


# How to compile:
Here is how to compile everything (Make sure you have cloned this repo recursively to also get the rawdraw library)
## CGol
tcc main.c fns.c -o CGoL.exe -luser32 -lgdi32 -lopengl32 C:/windows/system32/msvcrt.dll

## FSG
tcc mainSand.c fns.c -o FSG.exe -luser32 -lgdi32 -lopengl32 C:/windows/system32/msvcrt.dll

You can also compile everything at once using the tccbuild.bat script, just make sure "tcc" points to your tcc executable.


# Thanks To
[CNlohr rawdraw](https://github.com/cntools/rawdraw)
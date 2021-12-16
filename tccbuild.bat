rem #make sure to change this#
set TCC=C:\bin\tcc\tcc.exe 

%TCC% main.c fns.c -o CGoL.exe -luser32 -lgdi32 -lopengl32 C:/windows/system32/msvcrt.dll
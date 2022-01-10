XCOPY /E /Q /Y filler-test\resources bin\resources\
MD bin
clang -Ifiller-test\include -Ifiller-core\include -o bin\test.exe filler-test\src\*.c -L bin -l filler-core
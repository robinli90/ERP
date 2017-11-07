@ECHO OFF

ECHO ************** build lib files *********************
make -f Build_GTest

ECHO ************** clean up  ***************************
del *.o

ECHO ************** copy lib files **********************
md .\lib\
move /Y gtest.a .\lib\
move /Y gtest_main.a .\lib\

ECHO ************** copy header files *******************
md .\inc\gtest\
copy /Y .\GTest\include\gtest\*.* .\inc\gtest\

@echo off
setlocal enabledelayedexpansion

rem Set compiler
set CC=gcc

rem Set source files and object files
set SRCS=merge_sort.c generate_random_numbers.c clone.c parallel_merge_sort.c vector_mode.c main.c
set OBJS=

rem Set target executable name
set TARGET=main.exe

rem Compile each source file
for %%f in (%SRCS%) do (
    rem Compile the source file and append the object file to OBJS
    %CC% -c "%%f" -o "%%~nf.o"
    set "OBJS=!OBJS! "%%~nf.o""
)

rem Link object files to create executable
%CC% !OBJS! -o %TARGET%

rem Display completion message
echo Compilation and linking complete.

rem Pause to keep the command prompt window open
pause
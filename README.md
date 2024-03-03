Para compilar los archivos:
```
gcc -c generate_random_numbers.c -o generate_random_numbers.o
gcc -c merge_sort.c -o merge_sort.o
gcc -c clone.c -o clone.o
gcc -c parallel_merge_sort.c -o parallel_merge_sort.o
gcc -c vector_mode.c -o vector_mode.o
gcc -c main.c -o main.o 
```

Crear un único archivo ejecutable:

```
gcc main.o generate_random_numbers.o merge_sort.o parallel_merge_sort.o clone.o vector_mode.o -o main
```

Para ejecutarlo:

- Windows:
  ```
  .\main
  ```
- Linux:
  ```
  ./main
  ```

Para compilar los archivos:
```
gcc -c generate_random_numbers.c -o generate_random_numbers.o
gcc -c merge_sort.c -o merge_sort.o
gcc -c main.c -o main.o 
```

Crear un único archivo ejecutable:

```
gcc main.o generate_random_numbers.o merge_sort.o -o main
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

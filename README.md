# primelist [![Actions Status](https://github.com/Fullaxx/primelist/workflows/CI/badge.svg)](https://github.com/Fullaxx/primelist/actions)
Print a list of prime numbers

## Compile the Code
Note: You must have libgmp development package installed
```
./compile.sh
```

## Print prime numbers forever
```
./simple_list.exe
```

## Print the first 100 prime numbers
```
./simple_list.exe 100
```

## Print prime numbers greater than 500
```
START_P=500 ./simple_list.exe
START_P=500 ./simple_list.exe 100
```

## Use a thread to print prime numbers
```
./threaded_list.exe
```

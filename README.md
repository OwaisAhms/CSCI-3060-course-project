# Games Distribution Inc

## Running main Program
#### cd into 'main'
#### root -> src -> main
```
cd src/main
```
### Run to compile
```
g++ -o main Main.cpp User.cpp Admin.cpp                
```
### Run executable
```
./main.exe          
```
## Running test cases
#### cd into 'test cases'
#### root -> src -> main -> Testing -> test_cases
```
cd src/main/Testing/test_cases                                                     
```
### Running test cases .sh file
```
./test.sh                                                         
```
### if that does not work try
```
& "C:\Program Files\Git\bin\bash.exe" ./test.sh                                                      
```
### or to compile directly
```
g++ test.cpp ../../User.cpp ../../Admin.cpp -o test.exe                                          
```
### and run
```
./test.exe                                        
```



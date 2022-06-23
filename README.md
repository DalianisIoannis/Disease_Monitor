# Disease_Monitor
Project implemented for the course of Systems Programming (2020) in Department of Informatics and Telecommunications at University of Athens.
A program that processes querries on viruses' data through various Data Structures(Hashtable, AVL-Trees, Linked Lists and Max-Heap).
File "instrs.txt" contains some instuctions that show the functionality of the program. "validator.sh" is an autograder for the project.

## Compile
```bash
make
```
## Execution
```bash
./diseaseMonitor -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize
```
where patientRecordsFile can be a file from Assets, while diseaseHashtableNumOfEntries, countryHashtableNumOfEntries, bucketSize are integers.

# Disease_Monitor
An app that saves, edits and receives querries on viruses outbreaks' data. Maybe printKlargest should not check if getting to a neighbor node.
## Compile
```bash
make
```
## Execution
```bash
./diseaseMonitor -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize
```
where patientRecordsFile can be a file from Assets
      diseaseHashtableNumOfEntries, countryHashtableNumOfEntries, bucketSize are integers

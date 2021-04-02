## [File Conversion from Python to C++ to decrease the execution time](https://github.com/charlie219/Nevaeh-Technology/tree/main/File_Conversion)

Here we are assigned the task to convert merge_dump.py file to its equivalent C++ file in order to speed up the execution of the program. The merge_dump.py works on a CSV file which contains the daily Price log with various other fields. It reades the file from a prescribed location and selectively merges it to another CSV file with certian field. The runtime complexity of the given code was O(n^2), where n is the number of lines in the data set. The test data for the given merge_dump.py was very very huge because of which the execution time of the program was over 10 hours. 

Our task was make an C++ equivalent of the given Python file and also improve its content if necessary. I have made merge.cpp file which has a time complexity of O(n log n) and does the prescribed job efficently.

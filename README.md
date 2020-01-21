# ex4

### Introduction
In this assignment,  we are connecting with the server that give us problems and wait for solution.

There is a 10 clients that we handle all of them in parallel. We built the program in generic type. 

The program take care of all the problems that implement Searchable. But we focused at Matrix that it is a kind of Searchable. 

The client give us matrix with start point and goal point. We would like to give him the shortest route.  

The solutions will be saved at files. The class FileCacheManager handle this part. 

First, we have a class that connected to the server with the port the we get at argument. 

Take the data and convert it to matrix.  

The data contain positive numbers or -1 that represent a block that we cant use this place for our route. 

After that, we will check at our cache If there is a solution to this problem. 

In case of there is a solution, we return to the server the solution. 

If not, we will solve the problem and after that we will insert the solution to the cache. 

The name of the file will be the hash code of the string of the matrix.

Second, we have 4 algorithms that we implement in our program. BFS, DFS, BestFs and Astar. 

The fastest algorithm will be used to help to the client. 
We make an experiment to determine which algorithm is the best. The data was 10 matrix.

###How to run the code:

Take all the files and put them at the same file. After that, open in the terminal the location of the folder.

After thar, compile the code with the following instruction:

_g ++ -std = c ++ 14 * .cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread_

Then, run the code.

After that, run the port:	

./a.out –number port-

You can run a python script that will send the data. 

Just send the values of the matrix and then the start point and after that the goal state and after that write "end".

We used github, https://github.com/Amitai-p/ex4.1


Nerya Aberdam and Amitai Popovsky.

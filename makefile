all:	parseCommandLine.o myShellExecute.o 
	gcc -Wall -g parseCommandLine.o myShellExecute.o main.c -o myShell

parseCommandLine.o:	parseCommandLine.c
	gcc -Wall -g -c parseCommandLine.c

myShellExecute.o:	myShellExecute.c
	gcc -Wall -g -c myShellExecute.c

clean:
	rm *.o myShell

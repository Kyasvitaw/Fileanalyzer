a.out : main.o file_analysis.o text_processing.o utils.o
		gcc main.o file_analysis.o text_processing.o utils.o

file_analysis.o: file_analysis.c file_analysis.h
		gcc -c file_analysis.c

utils.o: utils.c utils.h
		gcc -c utils.c

text_processing.o: text_processing.c text_processing.h utils.h
		gcc -c text_processing.c

main.o: main.c file_analysis.h utils.h text_processing.h
		gcc -c main.c

clean:
		rm *.o a.out *.png graph.dot
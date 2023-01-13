EXEC = Project2
OBJS = Project2.o SortingList.o term.o autocomplete.o magicString.o
CC = /usr/bin/g++
$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@
Project2.o : Project2.cpp
	$(CC) -c $^
TermSortingList.o : SortingList.cpp SortingList.h
	$(CC) -c $<
term.o : term.cpp term.h
	$(CC) -c $<
autocomplete.o : autocomplete.cpp autocomplete.h
	$(CC) -c $<
magicString.o : magicString.cpp magicString.h
	$(CC) -c $<
clean :
	rm -i *.o $(EXEC)

FLAGS = -pedantic-errors -std=c++11

shop.o: shop.cpp functions.h
	g++ $(FLAGS) -c $<

minigames.o: minigames.cpp goodbadoutcomes.cpp functions.h #
	g++ $(FLAGS) -c $<

goodbadoutcomes.o: goodbadoutcomes.cpp shop.cpp functions.h  #
	g++ $(FLAGS) -c $<	
 
main.o: main.cpp  functions.h 
	g++ $(FLAGS) -c $<
	
main: main.o shop.o minigames.o goodbadoutcomes.o #total_time_used.o #char_skillset.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o goodbadoutcomes.o shop.o minigames.o

.PHONY: clean

# command to run this: make main
# and then to play game: ./main
# make clean

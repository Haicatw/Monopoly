OBJS = display.o game.o board.o player.o utility.o setup.o diceroller.o rules.o gamelogic.o playerlogic.o propertylogic.o main.o
CC = g++
CPPFLAGS = -Wall -Werror -Wno-unused-result -c -std=c++14
LFLAGS = -Wall -Werror -Wno-unused-result -o -std=c++14

hoarding.out : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o hoarding.out

board.o : board.cpp board.h utility.h
	$(CC) $(CPPFLAGS) board.cpp

rules.o : rules.cpp utility.h rules.h
	$(CC) $(CPPFLAGS) rules.cpp

game.o : game.cpp game.h board.h player.h diceroller.h rules.h
	$(CC) $(CPPFLAGS) game.cpp

utility.o : utility.cpp utility.h
	$(CC) $(CPPFLAGS) utility.cpp

setup.o : setup.cpp setup.h game.h utility.h
	$(CC) $(CPPFLAGS) setup.cpp

display.o : display.cpp display.h game.h
	$(CC) $(CPPFLAGS) display.cpp

player.o : player.cpp player.h utility.h
	$(CC) $(CPPFLAGS) player.cpp

diceroller.o : diceroller.cpp utility.h diceroller.h
	$(CC) $(CPPFLAGS) diceroller.cpp

propertylogic.o : propertylogic.cpp game.h playerlogic.h propertylogic.h
	$(CC) $(CPPFLAGS) propertylogic.cpp

playerlogic.o : playerlogic.cpp game.h playerlogic.h propertylogic.h
	$(CC) $(CPPFLAGS) playerlogic.cpp

gamelogic.o : gamelogic.cpp game.h gamelogic.h
	$(CC) $(CPPFLAGS) gamelogic.cpp

main.o : main.cpp setup.h display.h game.h gamelogic.h playerlogic.h
	$(CC) $(CPPFLAGS) main.cpp

clean:
	rm -f *.o main setup display game board player rules utility diceroller gamelogic playerlogic propertylogic

tar:
	tar cfv hoarding.out main.cpp setup.cpp display.cpp game.cpp board.cpp player.cpp rules.cpp utility.cpp diceroller.cpp gamelogic.cpp playerlogic.cpp propertylogic.cpp setup.h display.h game.h board.h player.h utility.h rules.h diceroller.h gamelogic.h playerlogic.h propertylogic.h

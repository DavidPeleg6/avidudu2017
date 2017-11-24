#Author: Avihai Didi
#ID: 313137846

a.out: main.o Board.o ConsoleDisplay.o Display.o Game.o Player.o PlayerHumanLocal.o Rules.o
	g++ main.o Board.o ConsoleDisplay.o Display.o Game.o Player.o PlayerHumanLocal.o Rules.o
main.o: main.cpp Board.h ConsoleDisplay.cpp ConsoleDisplay.h PlayerHumanLocal.cpp PlayerHumanLocal.h Rules.cpp Rules.h Game.cpp Game.h
	g++ -c main.cpp Board.h ConsoleDisplay.cpp ConsoleDisplay.h PlayerHumanLocal.cpp PlayerHumanLocal.h Rules.cpp Rules.h Game.cpp Game.h
Board.o: Board.cpp Board.h
	g++ -c Board.cpp
ConsoleDisplay.o: ConsoleDisplay.cpp ConsoleDisplay.h Board.cpp Board.h
	g++ -c ConsoleDisplay.cpp ConsoleDisplay.h Board.cpp Board.h
Display.o: Display.cpp Display.h
	g++ -c Display.cpp
Game.o: Game.cpp Game.h Player.cpp Player.h Display.cpp Display.h Board.cpp Board.h Rules.cpp Rules.h
	g++ -c Game.cpp Game.h Player.cpp Player.h Display.cpp Display.h Board.cpp Board.h Rules.cpp Rules.h
Player.o: Player.cpp Player.h
	g++ -c Player.cpp
PlayerHumanLocal.o: PlayerHumanLocal.cpp PlayerHumanLocal.h
	g++ -c PlayerHumanLocal.cpp
Rules.o: Rules.cpp Rules.h Board.cpp Board.h
	g++ -c Rules.cpp Rules.h Board.cpp Board.h
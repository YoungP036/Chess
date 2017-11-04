PGMS=Chess

all:    ${PGMS}

Chess: 	main.cpp
	g++ -w -o Chess.exe main.cpp -lsfml-graphics -lsfml-window -lsfml-system
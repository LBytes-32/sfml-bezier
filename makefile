all:
	g++ ./*.cpp -o ./sfml-bezier -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-bezier
all:
	@g++ ./*.cpp ./bezier/*.cpp -o ./sfml-bezier -lsfml-graphics -lsfml-window -lsfml-system
	@./sfml-bezier
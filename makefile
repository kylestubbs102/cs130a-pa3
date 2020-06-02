all: prog1.out

prog1.out: AVLTree.cpp TwoFiveTree.cpp prog1.cpp
	g++ -g AVLTree.cpp TwoFiveTree.cpp prog1.cpp -o prog1.out

clean:
	rm prog1.out
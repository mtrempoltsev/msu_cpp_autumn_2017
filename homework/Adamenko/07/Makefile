all:
		g++ -o calculator/res.o calculator/calculator/main.cpp -std=c++11
run:
		./calculator/res.o '1+2-3+(4*5)-20/2+(((2*2.5)*(0.5*4)))'
clean:
		rm calculator/res.o
help:   
		echo "all - cimpile\nrun - calculate expression\nclean - delete temp files"
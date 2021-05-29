all: alchemy

clean:
	rm -f alchemy

alchemy: main.cpp recipes.h bag.h ingredients.h colorconstants.h
	g++ -std=c++11 main.cpp -o alchemylab
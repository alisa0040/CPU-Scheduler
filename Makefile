all: cmpe351

cmpe351:
	g++ cmpe351.cpp -o cmpe351

clean:
	rm -f cmpe351

test: cmpe351
	bash test.sh

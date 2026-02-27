default: clean
	g++ -std=c++17 -g3 test_global_mutex.cpp -o test_global_mutex.out -lpthread

assembly: clean
	g++ -std=c++17 -g3 -S test_global_mutex.cpp -o test_global_mutex.S -lpthread

clean:
	-rm -rf *.o
	-rm -rf *.out

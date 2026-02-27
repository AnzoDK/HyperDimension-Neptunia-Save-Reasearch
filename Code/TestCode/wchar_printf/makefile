default: clean
	g++ -std=c++17 -g3 test_wchar_printf.cpp -o test_wchar_printf.out

assembly: clean
	g++ -std=c++17 -g3 -S test_wchar_printf.cpp -o test_wchar_printf.S

clean:
	-rm -rf *.o
	-rm -rf *.out

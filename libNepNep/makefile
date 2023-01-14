CXX:=g++
DEBUG:=-g3
CXX_FLAGS:=-std=c++17
LDD_FLAGS:=-Wl,-rpath,./
CXX_TEST_FLAGS:=-L./
LIB_VERSION:=0.1
default: clean ReBirth1
	$(CXX) *.nepO $(DEBUG) $(CXX_FLAGS) --shared -o libNepNep.so.$(LIB_VERSION)
	make tests
	#Running Tests
	make run_tests
	make clean
clean:
	-rm *.o
	-rm *.out
	-rm *.nepO
	-rm *.so
ReBirth1:
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC ./src/ReBirth/1/libReBirth1.cpp -o rebirth1.nepO

run_tests:
	./libNepNep_test_rebirth1.out
	echo -e "Success!!"

tests: ReBirth1Test
	
ReBirth1Test:
	$(CXX) $(DEBUG) $(CXX_FLAGS) $(CXX_TEST_FLAGS) $(LDD) ./tests/ReBirth1Test.cpp -o libNepNep_test_rebirth1.out -l:./libNepNep.so.$(LIB_VERSION)

CXX:=g++
DEBUG:=-g3
CXX_VERSION:=c++20
CXX_FLAGS:=-std=$(CXX_VERSION)
LDD_FLAGS:=-Wl,-rpath,./
CXX_TEST_FLAGS:=-L./
CXX_LINKER_FLAGS:=-lssl -lcrypto
LIB_VERSION:=0.1
#ALL_NEP_COMPONENTS:=ReBirth1

#Rebirth 1
REBIRTH_1_LIB_OBJECTS:=rebirth1.nepO
REBIRTH_1_TEST_OBJECT:=

#Combined
ALL_REBIRTH_OBJECTS:=common.nepO reBirthBase.nepO $(REBIRTH_1_LIB_OBJECTS)
default: $(ALL_REBIRTH_OBJECTS)
	$(CXX) $(ALL_REBIRTH_OBJECTS) $(DEBUG) $(CXX_FLAGS) --shared -o libnepnep.so.$(LIB_VERSION) $(CXX_LINKER_FLAGS)
	make tests
	#Running Tests
	make run_tests
	make clean

clean:
	-rm *.o
	-rm *.nepO

rebirth1.nepO:
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC ./src/ReBirth/1/libReBirth1.cpp -o rebirth1.nepO

common.nepO:
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC ./src/Common/commonFunc.cpp -o common.nepO

reBirthBase.nepO:
	$(CXX) $(DEBUG) $(CXX_FLAGS) -c -fPIC ./src/ReBirth/ReBirthBase.cpp -o reBirthBase.nepO

run_tests:
	./libNepNep_test_rebirth1.out
	echo -e "Success!!"

tests: ReBirth1Test
	
ReBirth1Test:
	$(CXX) $(DEBUG) $(CXX_FLAGS) $(CXX_TEST_FLAGS) $(LDD) ./tests/ReBirth1Test.cpp -o libNepNep_test_rebirth1.out -l:./libnepnep.so.$(LIB_VERSION)

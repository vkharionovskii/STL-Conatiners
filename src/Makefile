CC=gcc
CFLAGS=-std=c++17 -g 
FLAGS_LIBA= -lgtest -lstdc++ -lpthread -std=c++17 -g
SRC=set/*.hpp map/*.hpp multiset/*.hpp \
	list/*.hpp queue/*.hpp stack/*.hpp \
	array/*.hpp
TEST= test/test_*.cpp
SRC_ASSOTITIVE = test/test_assotiative_cont.cpp
SRC_ARRAY = test/test_array.cpp
SRC_VECTOR = vector/test_vector.cpp
SRC_LIST = test/list_tests.cpp
SRC_QUEUE = test/queue_tests.cpp
SRC_STACK = test/stack_tests.cpp

OBJ=$(patsubst %.cpp, %.o, $(SRC))
HEADER=s21_containers.hpp s21_containersplus.hpp

.PHONY: all build s21_containers test report clean m 

all: build

build: 
	$(CC) $(CFLAGS) $(HEADER) -o s21_containers.a 

s21_containers: build

test: clean set_map_mset_test vector_test queue_test array_test stack_test
# $(CC) $(CFLAGS) $(SRC) $(TEST) $(FLAGS_LIBA) -o g_test
# ./g_test --gtest_brief=1

set_map_mset_test:
	$(CC) $(SRC_ASSOTITIVE) $(FLAGS_LIBA) -o test_set
	./test_set --gtest_brief=1

vector_test:
	$(CC) $(SRC_VECTOR) $(FLAGS_LIBA) -o test_vector
	./test_vector --gtest_brief=1

list_test:
	$(CC) $(SRC_LIST) $(FLAGS_LIBA) -o test_list
	./test_list --gtest_brief=1

queue_test:
	$(CC) $(SRC_QUEUE) $(FLAGS_LIBA) -o test_queue
	./test_queue --gtest_brief=1

stack_test:
	$(CC) $(SRC_STACK) $(FLAGS_LIBA) -o test_stack
	./test_stack --gtest_brief=1

array_test:
	$(CC) $(SRC_ARRAY) $(FLAGS_LIBA) -o test_array
	./test_array --gtest_brief=1

clean:
	rm -rf *.gch *.out *.o *.a m *.gcda *.gcdo *.gcno *.dSYM coverage_report gcov_test g_test \
	*.html report  test_vector test_queue test_array test_stack test_list test_set

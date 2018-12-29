src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LIBDIRS= 
LDLIBS = 
CPPFLAGS= 
LDFLAGS= $(CPPFLAGS) $(LIBDIRS) $(LDLIBS)

CXX = g++

anagram_solver: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) anagram_solver 


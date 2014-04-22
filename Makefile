SRC1= main.cpp fractions.cpp dict.cpp linearProg.cpp parser.cpp tests.cpp
OBJ1= ${SRC1:.cpp=.o}
CXX	 = g++
LFLAGS   =
CXXFLAGS = -O2 -s -Wall -Wextra

all : simplex


simplex: $(OBJ1) $(HDR) 
	${CXX} $(CXXFLAGS) -o $@ $(OBJ1) $(LFLAGS)  $(LIB)

clean: 
	rm -f $(OBJ1) $(DEP)

destroy: clean
	rm -f simplex


%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

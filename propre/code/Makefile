SRC1= mainSimplex.cpp fractions.cpp dict.cpp linearProg.cpp parser.cpp
OBJ1= ${SRC1:.cpp=.o}
SRC2= mainTests.cpp fractions.cpp dict.cpp linearProg.cpp parser.cpp tests.cpp
OBJ2= ${SRC2:.cpp=.o}
SRC3= mainTransportation.cpp fractions.cpp dict.cpp linearProg.cpp parser.cpp tests.cpp transportation.cpp
OBJ3= ${SRC3:.cpp=.o}
SRC4= mainAssignement.cpp fractions.cpp dict.cpp linearProg.cpp parser.cpp tests.cpp transportation.cpp
OBJ4= ${SRC4:.cpp=.o}
SRC5= printKleeMinty.cpp
OBJ5= ${SRC5:.cpp=.o}
CXX	 = g++
LFLAGS   =
CXXFLAGS = -O2 -s -Wall -Wextra

all : simplex tests transportation assignement KleeMinty


simplex: $(OBJ1) $(HDR) 
	${CXX} $(CXXFLAGS) -o ../executables/$@ $(OBJ1) $(LFLAGS)  $(LIB)
	
tests: $(OBJ2) $(HDR) 
	${CXX} $(CXXFLAGS) -o ../executables/$@ $(OBJ2) $(LFLAGS)  $(LIB)
	
transportation: $(OBJ3) $(HDR) 
	${CXX} $(CXXFLAGS) -o ../executables/$@ $(OBJ3) $(LFLAGS)  $(LIB)
	
assignement: $(OBJ4) $(HDR) 
	${CXX} $(CXXFLAGS) -o ../executables/$@ $(OBJ4) $(LFLAGS)  $(LIB)
	
KleeMinty: $(OBJ5) $(HDR) 
	${CXX} $(CXXFLAGS) -o ../executables/$@ $(OBJ5) $(LFLAGS)  $(LIB)

clean: 
	rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(DEP)

destroy: clean
	rm -f ../executables/simplex ../executables/tests ../executables/transportation ../executables/assignement ../executables/KleeMinty


%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

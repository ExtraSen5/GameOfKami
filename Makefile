OBJ = 1.o
PROG = test
NAME = 1.cpp

all: $(PROG)

$(PROG):$(OBJ)
	g++ -o $(PROG) $(OBJ) -lsfml-network -lsfml-system -lsfml-graphics

$(OBJ):
	g++ -c $(NAME)

clean: 
	$(RM) $(OBJ)
	$(RM) $(PROG)


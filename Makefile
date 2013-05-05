SRC = src/
INCL = include/
inc = -I./include

PROJECT = Metro.o Correspondance.o Parcours.o Ligne.o Fichier.o Main.o

TARGET = metro

CFLAGS = -Wall -ansi -g -pedantic 

CC = colorgcc

all: $(TARGET) clean

$(TARGET) : $(PROJECT)
	@echo "Création de l'exécutable -> $@"
	@$(CC) $(PROJECT) $(LDLIBS) -o $@ -lm

%.o : $(SRC)%.c $(INCL)%.h
	@echo "Création de l'objet $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@

clean :
	@echo "Suppression des fichiers objets : "
	rm -f *.o

mrproper : clean
	rm -f $(TARGET)

SRC = src/
INCL = include/
inc = -I./include

PROJECT = Parcours.o Fichier.o Metro.o Main.o Correspondance.o Ligne.o Tableau.o

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

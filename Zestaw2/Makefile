# make run, clean, tar
# Rozszerzenia
.SUFFIXES: .c .x .h .o .cpp
# Nazwa obecnego katalogu
DIR = `basename $(CURDIR)`

# Wspólna czesc nazwy pliku
NAME1 = AnyBubbleSort
NAME2 = AnyQuickSort

# Program wykonawczy *.x i zrodlowy (object files) *.o
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o


# Flagi kompilatora i linkera
CFLAGS = -Wall -pedantic -std=c++11 -O -fPIC
LFLAGS = -Wall -pedantic -std=c++11 -O
# Biblioteki linkera zainstalowane w systemie
LDLIBS =
# Kompilator i linker
CO = g++
LD = $(CO)

# Regula wzorcowa - jak otrzymac plik *.o z pliku *.c
%.o: %.cpp
	$(CO) $(CFLAGS) -c $<

# Jawna regula zaleznosci - najpierw uaktualnij pliki po prawej stronie
# dwukropka, a potem wykonaj komende, ktora jest w nastepnej linijce
$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)
# Uruchom program $(EXEC3A); najpierw sprawdz, czy kod wykonawczy jest aktualny
.PHONY: run
run: $(EXEC1) $(EXEC2)
	./$(EXEC1)
	./$(EXEC2)

# Sprzataczka
.PHONY: clean tar
clean:
	rm -f *.o *.x *.out *.exe *.stackdump
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

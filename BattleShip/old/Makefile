CC=gcc				    	# compilador c
CFLAGS=-c -Wall -g			# flags pasados al complilador
LDFLAGS=-g			    	# flags pasados al linker
OBJS=funcReference.o mein.o 	# lista de todos los archivos objeto
SOURCES=$(OBJS:.o=.c)		# lista de todos los archivos fuente
HEADERS=*.h			    	# lista de todos los archivos header
EXE=proyecto					# nombre del ejecutable
MAKEFILE=Makefile

# regla para generar el ejecutable
$(EXE): $(OBJS)
	@echo "### Generando ejecutable"
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# regla para generar los archivos objeto
%.o: %.c $(MAKEFILE) $(HEADERS)
	@echo "### Compilando" $<
	$(CC) $(CFLAGS) -o $@ $<

# regla para borrar el resultado de la compilacion anterior
clean:
	@echo "### Borrando todo..."
	rm -f ./*.o
	rm -f $(EXE)

# regla para hacer todo desde el comienzo (borrar todo, compilar y linkear)
all: clean $(EXE)


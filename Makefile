CC = g++
CFLAGS = -O2
LFLAGS =
OBJ = obj/csv.o obj/main.o
BIN = yield_search.cgi

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

obj/main.o: src/main.cpp src/csv.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/csv.o: src/csv.cpp src/csv.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

install:
	sudo -u apache -g apache cp yield_search.html /srv/httpd/htdocs
	sudo -u apache -g apache cp yield_search.js /srv/httpd/htdocs
	sudo -u apache -g apache cp yield_curve.js /srv/httpd/htdocs
	sudo -u apache -g apache cp yield_search.cgi /srv/httpd/cgi-bin
	sudo -u apache -g apache cp yields.dat /srv/httpd/cgi-bin

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)

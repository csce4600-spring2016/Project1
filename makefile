CC = g++
CFLAGS = -c
BINARIES = fifo fifo_quad rr rr_quad sjf sjf_quad

all: $(BINARIES) clean

gen_proc.o: gen_proc.cpp gen_proc.h
	$(CC) $(CFLAGS) gen_proc.cpp

fifo: fifo.o gen_proc.o
	$(CC) -o fifo fifo.o gen_proc.o

fifo.o: fifo.cpp gen_proc.h
	$(CC) $(CFLAGS) fifo.cpp

fifo_quad: fifo_quad.o gen_proc.o
	$(CC) -o fifo_quad fifo_quad.o gen_proc.o

fifo_quad.o: fifo_quad.cpp gen_proc.h
	$(CC) $(CFLAGS) fifo_quad.cpp

rr: rr.o gen_proc.o
	$(CC) -o rr rr.o gen_proc.o

rr.o: rr.cpp gen_proc.h
	$(CC) $(CFLAGS) rr.cpp

rr_quad: rr_quad.o gen_proc.o
	$(CC) -o rr_quad rr_quad.o gen_proc.o

rr_quad.o: rr_quad.cpp gen_proc.h
	$(CC) $(CFLAGS) rr_quad.cpp

sjf: sjf.o gen_proc.o
	$(CC) -o sjf sjf.o gen_proc.o

sjf.o: sjf.cpp gen_proc.h
	$(CC) $(CFLAGS) sjf.cpp

sjf_quad: sjf_quad.o gen_proc.o
	$(CC) -o sjf_quad sjf_quad.o gen_proc.o

sjf_quad.o: sjf_quad.cpp gen_proc.h
	$(CC) $(CFLAGS) sjf_quad.cpp

clean:
	$(info Cleaning...)
	\rm fifo.o fifo_quad.o rr.o rr_quad.o sjf.o sjf_quad.o gen_proc.o

uninstall:
	$(info Removing binaries...)
	\rm $(BINARIES)

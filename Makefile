CC   = g++ -std=c++0x
ARCH = $(shell getconf LONG_BIT)

LIBXLPATH = ../Lib/libxl

ifeq ($(ARCH), 32)
	LIBPATH = $(LIBXLPATH)/lib
else
	LIBPATH = $(LIBXLPATH)/lib64
endif

CFLAGS = -I $(LIBXLPATH)/include_cpp -L $(LIBPATH) -lxl -Wl,-rpath,$(LIBPATH)
TARGETFILE = readexcel

all:	clean readexcel

clean:
	rm -rf *.o $(TARGETFILE)

readexcel:
	$(CC) -o $(TARGETFILE) $(TARGETFILE).cpp $(CFLAGS)

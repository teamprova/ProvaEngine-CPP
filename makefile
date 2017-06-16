CC = g++
OUTDIR = out
OUT = $(OUTDIR)/libProva.a
ODIR = $(OUTDIR)/obj
SDIR = src
CFLAGS = -O2
INC = -Iinclude -Ideps -Ldeps/lib -lSOIL $(shell pkg-config --libs sdl2 glew)

CPP_FILES = $(wildcard $(SDIR)/*.cpp)
OBJS = $(addprefix $(ODIR)/,$(notdir $(CPP_FILES:.cpp=.o)))


all: folders $(OBJS) $(OUT)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OUT): $(OBJS)
	ar rs $(OUT) $^

folders:
	mkdir -p $(OUTDIR) && \
	mkdir -p $(ODIR)

.PHONY: clean test build

clean:
	rm -rf $(ODIR) $(OUT) $(OUTDIR) test/game

test: all
	$(CC) $(CFLAGS) -o test/game test/src/*.cpp $(OUT) $(INC) &&\
	cd test &&\
	./game
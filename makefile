# hello
### https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html ###

CC := clang
# tells the *linker* to search that dir for rpath. why? still dunno
#                          vvvvvvvvvvvvvvvvvvvvvvvvv
CFLAGS := -g -Wall -Wextra -Wl,-rpath,/usr/local/lib
INCLUDES := -I /usr/local/include/SDL3
LFLAGS := -L /Users/squidward/Downloads/SDL-release-3.2.8/build
LIBS := -l SDL3

MAIN := picky

VPATH := src:src/*.c
OBJ_DIR := obj
_OBJS := main.o
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(_OBJS) )

.PHONY: depend clean

all: $(MAIN)
	@echo \`$(MAIN)\' hath compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LFLAGS) $(LIBS) -o $(MAIN)

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(MAIN) $(OBJ_DIR)/*.o *~

depend: $(SRCS)
	makedepend $(INCLUDES) $^

bundle_contents = Picky.app/Contents
Picky_bundle: $(MAIN)
		mkdir -p $(bundle_contents)/MacOS
		mkdir -p $(bundle_contents)/Resources
		echo "APPL????" > $(bundle_contents)/PkgInfo
		$(INSTALL_PROGRAM) $< $(bundle_contents)/MacOS/

# DO NOT DELETE

CC = gcc
CFLAGS = -g
OUTFILE = yalang
LIBS = -lm

all: parser.c lexer.c
	$(CC) $(CFLAGS) parser.c lexer.c -o $(OUTFILE) $(LIBS)


parser.c: yalang.y
	bison -y -d -v yalang.y -o parser.c

lexer.c: yalang.lex
	flex -o lexer.c yalang.lex


clean:
	rm -rf parser.c lexer.c
	rm -f *~
	rm -f *.o
	rm -f yalang
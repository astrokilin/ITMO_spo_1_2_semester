CC=gcc
PARSERC=bison
LEXERC=flex
CFLAGS=-Wall -Wextra -Werror -I.
LEXYACCFLAGS=-I.
YYFLAGS=-d -Wnone
LLFLAGS=
TARGETS=compiller

PARSING_DIR=parsing
LANG_DIR=lang
DATA_STRUCTS_DIR=data_structs

OBJS_DIR=build

.PHONY: all debug clear 

clear:
	rm -rf $(OBJS_DIR)

all: CFLAGS += -O3 -ftree-vectorizer-verbose=2
all: LLFLAGS += -F
all: LEXYACCFLAGS += -O2
all: $(OBJS_DIR)
all: compiller

debug: YYFLAGS += -Wall --debug -v
debug: CFLAGS += -DDEBUG -g3 -fsanitize=address -fsanitize=undefined
debug: LEXYACCFLAGS += -DYYDEBUG=1
debug: $(OBJS_DIR)
debug: compiller

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

compiller: main.c $(OBJS_DIR)/cfg_ir.o $(OBJS_DIR)/sizes_map.o $(OBJS_DIR)/string_map.o $(OBJS_DIR)/syntax_tree.o $(OBJS_DIR)/parser.o $(OBJS_DIR)/lexer.o
	$(CC) $(CFLAGS) $(INCLUDE_ALL) -o $@ $^

$(OBJS_DIR)/cfg_ir.o : $(LANG_DIR)/cfg_ir.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)/sizes_map.o : $(DATA_STRUCTS_DIR)/sizes_map.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)/string_map.o : $(DATA_STRUCTS_DIR)/string_map.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)/syntax_tree.o : $(LANG_DIR)/syntax_tree.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)/parser.o : $(PARSING_DIR)/parser.c $(PARSING_DIR)/lexer.c 
	$(CC) $(LEXYACCFLAGS) -o $@ -c $<

$(OBJS_DIR)/lexer.o : $(PARSING_DIR)/lexer.c
	$(CC) $(LEXYACCFLAGS) -o $@ -c $<

$(PARSING_DIR)/parser.c : $(PARSING_DIR)/parse.y
	$(PARSERC) $(YYFLAGS) -o $@ $<

$(PARSING_DIR)/lexer.c : $(PARSING_DIR)/lex.l $(PARSING_DIR)/parser.c
	$(LEXERC) $(LLFLAGS) --header-file=$(PARSING_DIR)/lexer.h -o $@ $<


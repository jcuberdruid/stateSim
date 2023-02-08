CFLAGS = ""
LIBS = ""


StateSim: main.c
	$(CC) $(CFLAGS) $? $(LDFLAGS) $(LIBS) -o $@


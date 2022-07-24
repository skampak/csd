CC = gcc
DBUG = -g
LIBSSL = -ldl -lssl -lcrypto
SHARED = -fPIC -shared

TARGETS =  logger monitor tester

all: $(TARGETS)

logger:
	$(CC) $(SHARED) $(DBUG) -o logger.so logger.c $(LIBSSL)
	LD_PRELOAD=./logger.so ./example
monitor:
	$(CC) monitor.c -o monitor

tester:
	$(CC) tester.c -o tester

clean:
	rm -f logger.so monitor tester

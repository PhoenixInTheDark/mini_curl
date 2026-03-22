all: ./src/curl

OBJ = ./obj/main.o ./obj/parse_url.o
SRCS = main.c parse_url.c

./src/curl: $(OBJ)
	gcc $(OBJ) -o ./src/curl

./obj/%.o: %.c
	gcc -c $< -o $@

clean:
	rm -f $(OBJ) ./src/curl

run_test: ./src/curl
	./src/curl -d '{"value": "hello"}' -H 'Content-Type: application/json' https://example.com/api/v1/test/
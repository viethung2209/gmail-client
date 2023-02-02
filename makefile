main: ./main.c ./base64.c ./base64.h ./para.h
	gcc -o main ./main.c ./base64.c ./base64.h ./para.h -g  -lssl -lcrypto -Wall

clean:
	rm -f main
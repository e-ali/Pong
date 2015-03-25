CFLAGS=-std=c99 `pkg-config --cflags sdl2 SDL2_ttf SDL2_image SDL2_mixer`
LDFLAGS=`pkg-config --libs sdl2 SDL2_ttf SDL2_image SDL2_mixer`

pong: init.o common.o menu.o paddle.o ball.o game.o main.o
	${CC} ${CFLAGS} ${LDFLAGS} init.o common.o menu.o paddle.o ball.o main.o game.o -o pong

main.o: main.c main.h
	${CC} ${CFLAGS} ${LDFLAGS} -c main.c

game.o: game.c game.h
	${CC} ${CFLAGS} ${LDFLAGS} -c game.c

paddle.o: paddle.c paddle.h
	${CC} ${CFLAGS} ${LDFLAGS} -c paddle.c

ball.o: ball.c ball.h
	${CC} ${CFLAGS} ${LDFLAGS} -c ball.c

menu.o: menu.c menu.h
	${CC} ${CFLAGS} ${LDFLAGS} -c menu.c

common.o: common.c common.h
	${CC} ${CFLAGS} ${LDFLAGS} -c common.c

init.o: init.c init.h
	${CC} ${CFLAGS} ${LDFLAGS} -c init.c

clean:
	rm *.o

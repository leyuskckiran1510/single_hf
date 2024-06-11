
#define  IMPLE_MEMMNG
#include "memmng.c"

#include "cli_src/src/canvas.h"
#include "cli_src/src/cli-engine.h"
#include "cli_src/src/colors.h"
#include "cli_src/src/event.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


#define FPS 30



void chess_board(Canvas *c, uint width, uint height) {
  uint box_width = width / 8;
  uint box_height = height / 8;
  uint x = 0, y = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((i + j) % 2) {
        rectangle(c, x, y, box_width, box_height, WHITE, STROKED);
      } else {
        rectangle(c, x, y, box_width, box_height, BLACK, STROKED);
      }
      x += box_width;
    }
    x = 0;
    y += box_height;
  }
}

void free_canvas(Canvas *c) {
  free(c->surface);
  free(c);
  c = NULL;
}

int main() {
  clear_screen();
  int HEIGHT = 40, WIDTH = 80;
  Canvas *c = InitWindow(WIDTH, HEIGHT, "CLI-chess");
  // defer;
  int loop = 1;
  int cont = 0;
  chess_board(c, WIDTH, HEIGHT);
  c->draw(c);
  while (loop) {
    switch (keypress()) {
    case KEY_SPACE:
      cont ^= 1;
      continue;
    case KEY_Q:
    case KEY_q: {
      loop = 0;
      continue;
    }
    }
    chess_board(c,WIDTH,HEIGHT);
    c->draw(c);
    usleep(1000 * 1000 / FPS);
    c->clear(c);
  }
  free_canvas(c);
  reset_all();
  return 0;
}
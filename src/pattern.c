#include "pattern.h"
#include <math.h>
#include <ncurses.h>

void init_colors() {
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);    // low frequencies
  init_pair(2, COLOR_YELLOW, COLOR_BLACK); // mid frequencies
  init_pair(3, COLOR_GREEN, COLOR_BLACK);  // high frequencies
}

void visualize(const float *magnitude, int size) {
  clear();
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  // restrict the area to 50% width and 50% height
  int display_width = max_x * 0.5;
  int display_height = max_y * 0.5;

  for (int i = 0; i < size && i < display_width; i++) {
    int bar_height = (int)(magnitude[i] * display_height);
    for (int j = 0; j < bar_height && j < display_height; j++) {
      mvprintw(max_y - j - 1, i, "-");
    }
  }
  refresh();
}

void visualize_wave_pattern(const float *magnitude, int size) {
  clear();
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  // restrict the area to 50% width and 50% height
  int display_width = max_x * 0.5;
  int display_height = max_y * 0.5;

  for (int i = 0; i < size && i < display_width; i++) {
    int bar_height =
        (int)((magnitude[i] * display_height) * (sin(i * 0.1) + 1.0) / 2.0);

    if (i < size / 3) {
      attron(COLOR_PAIR(1));
    } else if (i < 2 * size / 3) {
      attron(COLOR_PAIR(2));
    } else {
      attron(COLOR_PAIR(3));
    }

    for (int j = 0; j < bar_height; j++) {
      mvprintw(max_y - j - 1, i, "-");
    }

    attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
  }
  refresh();
}

void visualize_moving_wave(const float *magnitude, int size, float phase) {
  clear();
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  // restrict the area to 50% width and 50% height
  int display_width = max_x * 0.5;
  int display_height = max_y * 0.5;

  for (int i = 0; i < size && i < display_width; i++) {
    int bar_height = (int)((magnitude[i] * display_height) *
                           (sin(i * 0.1 + phase) + 1.0) / 2.0);

    if (i < size / 3) {
      attron(COLOR_PAIR(1));
    } else if (i < 2 * size / 3) {
      attron(COLOR_PAIR(2));
    } else {
      attron(COLOR_PAIR(3));
    }

    for (int j = 0; j < bar_height; j++) {
      mvprintw(max_y - j - 1, i, "-");
    }

    attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
  }

  refresh();
}

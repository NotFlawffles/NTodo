#include "../include/ui.h"
#include <ncurses.h>
#include <malloc.h>
#include <string.h>

#define NORMAL_PAIR      0
#define ESC_MESSAGE_PAIR 2

Ui *newUi(Point *size) {
    Ui *ui        = malloc(sizeof(Ui));
    ui->exit      = false;
    ui->size      = size;
    ui->cursor    = newPoint(1, 1);
    ui->selection = 1;
    return ui;
}

Point *newPoint(unsigned x, unsigned y) {
    Point *point = malloc(sizeof(Point));
    point->x     = x;
    point->y     = y;
    return point;
}

void setup(void) {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    raw();
    start_color();
    init_pair(NORMAL_PAIR,      COLOR_WHITE, COLOR_BLACK);
    init_pair(ESC_MESSAGE_PAIR, COLOR_RED,   COLOR_BLACK);
}

void drawTodos(Ui *ui, VM *vm) {
    ui->cursor->y = 4;
    for (int i = 0; vm->todos[i]; i++) {
        ui->cursor->x = 4;
        if (ui->selection - 1 == i) {
            mvaddch(ui->cursor->y, ui->cursor->x - 2, '>');
            attron(A_BOLD);
        }
        mvaddstr(ui->cursor->y, ui->cursor->x, vm->todos[i]->name);
        attroff(A_BOLD);
        mvaddstr(ui->cursor->y, ui->cursor->x = (int) (ui->size->x / 2) - strlen(vm->todos[i]->name), vm->todos[i]->description);
        ui->cursor->x = ui->size->x - 5;
        if (vm->todos[i]->checked) mvaddstr(ui->cursor->y++, ui->cursor->x, "[x]");
        else mvaddstr(ui->cursor->y++, ui->cursor->x, "[ ]");
    }
}

void toggleAction(Ui *ui, VM *vm) {
    for (int i = 0; vm->todos[i]; i++) {
        char *argv[] = { "ntodo", "toggle", vm->todos[i]->name };
        if (ui->selection - 1 == i) toggle(vm, 3, argv);
    }
}

void draw(VM *vm) {
    Point *size = newPoint(0, 0);
    getmaxyx(stdscr, size->y, size->x);
    Ui *ui = newUi(size);
    while (!ui->exit) {
        clear();
        attron(COLOR_PAIR(ESC_MESSAGE_PAIR));
        mvaddstr(ui->cursor->y = 1, ui->cursor->x = 1, "ESC to exit");
        attroff(COLOR_PAIR(ESC_MESSAGE_PAIR));
        mvaddstr(ui->cursor->y, ui->cursor->x = ((int) (ui->size->x / 2)) - 3, "NTODO");
        drawTodos(ui, vm);
        unsigned key = getch();
        switch (key) {
            case 27:
                ui->exit = true;
                break;
            case KEY_DOWN: {
                unsigned i = 1;
                for (; vm->todos[i]; i++);
                if (ui->selection >= i) ui->selection = 1;
                else ui->selection += 1;
                break;
            }
            case KEY_UP: {
                unsigned i = 1;
                for (; vm->todos[i]; i++);
                if (ui->selection <= 1) ui->selection = i;
                else ui->selection -= 1;
                break;
            }
            case 10:
                toggleAction(ui, vm);
                break;
        }
    }
}

void runUi(VM *vm) {
    setup();
    draw(vm);
    endwin();
}

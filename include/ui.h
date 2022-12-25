#include "ntodo.h"


typedef struct {
    unsigned x, y;
} Point;

typedef struct {
    bool exit;
    Point   *size, *cursor;
    unsigned selection;
} Ui;

Point *newPoint   (unsigned x, unsigned y);
Ui    *newUi      (Point *size);
void   setup      (void);
void   drawTodos  (Ui *ui, VM *vm);
void   draw       (VM *vm);
void   runUi      (VM *vm);

#include <stdio.h>
#include "container.h"
#include <raylib.h>
#include <string.h>

int main() {
    InitWindow(3000,1800, "basic window");

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Tu projecto sirve!",200,200,200,BLACK);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

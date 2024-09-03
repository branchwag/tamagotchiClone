#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    int hunger;
    int happiness;
    int energy;
} Tamagotchi;

Texture2D sprite;

void UpdateTamagotchi(Tamagotchi *pet) {
    pet->hunger = (pet->hunger + 1) % 100;
    pet->happiness = (pet->happiness - 1 + 100) % 100;
    pet->energy = (pet->energy - 1 + 100) % 100;
}

void FeedPet(Tamagotchi *pet) {
    pet->hunger = (pet->hunger - 10 + 100) % 100;
    pet->energy = (pet->energy + 5) % 100;
}

void PlayWithPet(Tamagotchi *pet) {
    pet->happiness = (pet->happiness + 10) % 100;
    pet->energy = (pet->energy - 5 + 100) % 100;
}

void PutPetToSleep(Tamagotchi *pet) {
    pet->energy = (pet->energy + 20) % 100;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tamagotchi Game");
    sprite = LoadTexture("spritesheet.png");
    SetTargetFPS(60);

    Tamagotchi pet;
    int frameCount = 0;

    while (!WindowShouldClose()) {
        frameCount++;
        if (frameCount % 60 == 0) {
            UpdateTamagotchi(&pet);
        }

        if (IsKeyPressed(KEY_F)) FeedPet(&pet);
        if (IsKeyPressed(KEY_P)) PlayWithPet(&pet);
        if (IsKeyPressed(KEY_S)) PutPetToSleep(&pet);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Rectangle source = (Rectangle){0, 170, 190, 150};
        DrawTextureRec(sprite, source, (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, WHITE);

        Rectangle face = (Rectangle){0, 400, 190, 150};
        DrawTextureRec(sprite, face, (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 20}, WHITE);


        DrawText(TextFormat("Hunger: %d", pet.hunger), 10, 10, 20, BLACK);
        DrawText(TextFormat("Happiness: %d", pet.happiness), 10, 40, 20, BLACK);
        DrawText(TextFormat("Energy: %d", pet.energy), 10, 70, 20, BLACK);
        DrawText("Press F to Feed, P to Play, S to Sleep", 10, SCREEN_HEIGHT - 30, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

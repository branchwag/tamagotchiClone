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

void FeedPet(Tamagotchi *pet, Rectangle *currentFace, int *faceShift) {
    pet->hunger = (pet->hunger - 10 + 100) % 100;
    pet->energy = (pet->energy + 5) % 100;
    *currentFace = (Rectangle){425, 400, 190, 150};
    *faceShift = 35;
}

void PlayWithPet(Tamagotchi *pet, Rectangle *body, Rectangle *currentFace, int *faceShift) {
    pet->happiness = (pet->happiness + 10) % 100;
    pet->energy = (pet->energy - 5 + 100) % 100;
    *body = (Rectangle){195, 170, 190, 150};
    *currentFace = (Rectangle){0, 400, 190, 150};
    *faceShift = 0;
}

void PutPetToSleep(Tamagotchi *pet, Rectangle *currentFace, int *faceShift, Rectangle *body) {
    pet->energy = (pet->energy + 20) % 100;
    *currentFace = (Rectangle){225, 400, 190, 150};
    *faceShift = 30;
    *body = (Rectangle){0, 170, 190, 150};
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tamagotchi Game");
    sprite = LoadTexture("spritesheet.png");
    SetTargetFPS(60);

    Tamagotchi pet;
    Rectangle body = (Rectangle){0, 170, 190, 150};
    Rectangle defaultFace = (Rectangle){0, 400, 190, 150};
    Rectangle currentFace = defaultFace;
    int faceShift = 0;

    int frameCount = 0;

    while (!WindowShouldClose()) {
        frameCount++;
        if (frameCount % 60 == 0) {
            UpdateTamagotchi(&pet);
        }

        if (IsKeyPressed(KEY_F)) FeedPet(&pet, &currentFace, &faceShift);
        if (IsKeyPressed(KEY_P)) PlayWithPet(&pet, &body, &currentFace, &faceShift);
        if (IsKeyPressed(KEY_S)) PutPetToSleep(&pet, &currentFace, &faceShift, &body);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Hunger: %d", pet.hunger), 10, 10, 20, BLACK);
        DrawText(TextFormat("Happiness: %d", pet.happiness), 10, 40, 20, BLACK);
        DrawText(TextFormat("Energy: %d", pet.energy), 10, 70, 20, BLACK);
        DrawText("Press F to Feed, P to Play, S to Sleep", 10, SCREEN_HEIGHT - 30, 20, DARKGRAY);

        if (pet.energy < 80) {
            Rectangle body = (Rectangle){0, 170, 190, 150};
            DrawTextureRec(sprite, body, (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, WHITE);
            DrawTextureRec(sprite, currentFace, (Vector2){SCREEN_WIDTH/2 + faceShift, SCREEN_HEIGHT/2 + 20}, WHITE);
        } else {
          DrawTextureRec(sprite, body, (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, WHITE);
          DrawTextureRec(sprite, currentFace, (Vector2){SCREEN_WIDTH/2 + faceShift, SCREEN_HEIGHT/2 + 20}, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

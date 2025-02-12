#include <stdio.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int width = 1152;
int height = 540;

void reload_image(Image *source, Image *dest, Texture2D *text) {
    *dest = ImageCopy(*source);
    if (dest->width > dest->height) { //wider than high
        int newHeight = source->height * ((float) width / (float) source->width);
        ImageResize(dest, width, newHeight);
    }
    else { //higher than wide
        int newWidth = source->width * ((float) height / (float) source->height);
        ImageResize(dest, newWidth, height);
    }
    *text = LoadTextureFromImage(*dest);
}

void put_image_texture(Texture2D *text, Image *active_image) {
    if (active_image->width > active_image->height) {
        DrawTexture(*text, 0, (height - active_image->height) / 2, WHITE);
    }
    else {
        DrawTexture(*text, (width - active_image->width) / 2, 0, WHITE);
    }
}

int main(void) {
    printf("Hello, World!\n");
    InitWindow(width, height, "imview");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    int monitor = GetCurrentMonitor();
    SetTargetFPS(GetMonitorRefreshRate(monitor));


    // /home/joppo/programming/imview/assets/E3CVLW8VoAMAhzr.jpg
    //Image active_image = LoadImage("/home/joppo/programming/imview/assets/E3CVLW8VoAMAhzr.jpg");

    // /home/joppo/programming/imview/assets/E4zj7T0VcAIhQIQ.jpg
    //Image active_image = LoadImage("/home/joppo/programming/imview/assets/E4zj7T0VcAIhQIQ.jpg");

    // /home/joppo/Pictures/bocchi wallpaper/1293442.jpg
    Image active_image = LoadImage("/home/joppo/Pictures/bocchi wallpaper/1293442.jpg");

    Image active_displayed_image;
    Texture2D active_image_text;
    reload_image(&active_image, &active_displayed_image, &active_image_text);
    float zoom_value = 0;
    int reload = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F)) {
            ToggleBorderlessWindowed();
            SetWindowState(FLAG_WINDOW_UNDECORATED);
            reload = 3;
        }
        width = GetScreenWidth();
        height = GetScreenHeight();
        if (reload) {
            reload--;
            reload_image(&active_image, &active_displayed_image, &active_image_text);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        put_image_texture(&active_image_text, &active_displayed_image);
        EndDrawing();
    }

    return 0;
}

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>
#include <cstdio>
#include <cstdarg>
#include <unistd.h>

// 欺骗编译器，避开 C++ 数学库里的 y1 函数
#define y1 y1_chess_array

inline int getch() { return getchar(); }

#define MAKEINTRESOURCEA(x) "img/botton.png"

typedef uint32_t color_t;
#define BLACK 0xFF000000
#define WHITE 0xFFFFFFFF
#define EGEARGB(a, r, g, b) ((uint32_t)(a) << 24 | (uint32_t)(r) << 16 | (uint32_t)(g) << 8 | (uint32_t)(b))
#define EGEACOLOR(a, color) ((uint32_t)(a) << 24 | ((color) & 0x00FFFFFF))

#define INIT_RENDERMANUAL 0
#define TRANSPARENT 1

struct IMAGE {
    std::string path;
    SDL_Texture* tex = nullptr;
    int w = 0, h = 0;
};
typedef IMAGE* PIMAGE;

struct mouse_msg {
    int x, y;
    bool down, up, left, right;
    bool is_down() const { return down; }
    bool is_up() const { return up; }
    bool is_left() const { return left; }
    bool is_right() const { return right; }
};

class MUSIC {
public:
    Mix_Chunk* chunk = nullptr;
    void OpenFile(const char* path);
    void Play(int loop);
    void Close();
};

void initgraph(int width, int height, int flag = 0);
void closegraph();
void setcaption(const char* caption);
void setbkcolor(color_t color);
void cleardevice();
void delay_fps(int fps);
bool is_run();

void setcolor(color_t color);
void setfillcolor(color_t color);
void setlinewidth(int width);
void ege_enable_aa(bool enable);
void line(int x1, int y1, int x2, int y2);
void rectangle(int x1, int y1, int x2, int y2);
void ege_fillrect(int x, int y, int w, int h);
void ege_fillellipse(int x, int y, int w, int h);

void setfont(int height, int width, const char* fontName);
void setbkmode(int mode);
void xyprintf(int x, int y, const char* fmt, ...);

PIMAGE newimage();
void delimage(PIMAGE img);
void getimage(PIMAGE img, const char* filename);
void getimage(PIMAGE img, const char* type, const char* res_name);
void putimage(int x, int y, PIMAGE img);
void putimage_transparent(void* dst, PIMAGE img, int x, int y, color_t color);

bool mousemsg();
mouse_msg getmouse();

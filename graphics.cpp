#include "graphics.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

// 跨文件声明残棋函数
extern void cclean();
extern void cplay();

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_canvas = nullptr; 
TTF_Font* g_font = nullptr;
int g_font_height = 20;
bool g_running = true;
uint32_t g_last_tick = 0;
int g_target_fps = 60;
color_t g_current_color = BLACK;
color_t g_current_bkcolor = WHITE;
std::vector<mouse_msg> g_mouse_events;
std::map<std::string, SDL_Texture*> g_texture_cache;
std::vector<IMAGE*> g_image_pool;

// 【核心状态机】判断当前是否在主菜单
bool g_is_in_menu = false;

std::string get_font_path(const char* name) {
    if (strcmp(name, "华文隶书") == 0 || strcmp(name, "隶书") == 0) {
        if (access("SIMLI.TTF", F_OK) != -1) return "SIMLI.TTF";
        if (access("STLITI.TTF", F_OK) != -1) return "STLITI.TTF";
    }
    return "/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc";
}

void initgraph(int width, int height, int flag) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");

    int win_w = width * 1.5;
    int win_h = height * 1.5;

    g_window = SDL_CreateWindow("象棋", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(g_renderer, width, height);

    g_canvas = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetRenderTarget(g_renderer, g_canvas);

    setbkcolor(WHITE);
    g_last_tick = SDL_GetTicks();
}

void closegraph() {
    if (g_canvas) SDL_DestroyTexture(g_canvas);
    if (g_font) TTF_CloseFont(g_font);
    for (auto& pair : g_texture_cache) SDL_DestroyTexture(pair.second);
    if (g_renderer) SDL_DestroyRenderer(g_renderer);
    if (g_window) SDL_DestroyWindow(g_window);
    Mix_CloseAudio(); TTF_Quit(); IMG_Quit(); SDL_Quit();
}

void setcaption(const char* caption) { if (g_window) SDL_SetWindowTitle(g_window, caption); }
void setbkcolor(color_t color) { g_current_bkcolor = color; }
void setcolor(color_t color) { g_current_color = color; }
void setfillcolor(color_t color) { g_current_color = color; }
void setlinewidth(int width) {}
void ege_enable_aa(bool enable) {}

void cleardevice() {
    SDL_SetRenderDrawColor(g_renderer, (g_current_bkcolor >> 16) & 0xFF, (g_current_bkcolor >> 8) & 0xFF, g_current_bkcolor & 0xFF, (g_current_bkcolor >> 24) & 0xFF);
    SDL_RenderClear(g_renderer);
}

void line(int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(g_renderer, (g_current_color >> 16) & 0xFF, (g_current_color >> 8) & 0xFF, g_current_color & 0xFF, (g_current_color >> 24) & 0xFF);
    SDL_RenderDrawLine(g_renderer, x1, y1, x2, y2);
}

void rectangle(int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(g_renderer, (g_current_color >> 16) & 0xFF, (g_current_color >> 8) & 0xFF, g_current_color & 0xFF, (g_current_color >> 24) & 0xFF);
    SDL_Rect r = {x1, y1, x2 - x1, y2 - y1};
    SDL_RenderDrawRect(g_renderer, &r);
}

void ege_fillrect(int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(g_renderer, (g_current_color >> 16) & 0xFF, (g_current_color >> 8) & 0xFF, g_current_color & 0xFF, (g_current_color >> 24) & 0xFF);
    SDL_Rect r = {x, y, w, h};
    SDL_RenderFillRect(g_renderer, &r);
}

void ege_fillellipse(int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(g_renderer, (g_current_color >> 16) & 0xFF, (g_current_color >> 8) & 0xFF, g_current_color & 0xFF, (g_current_color >> 24) & 0xFF);
    int rx = w / 2; int ry = h / 2; int cx = x + rx; int cy = y + ry;
    for (int i = -ry; i <= ry; ++i) {
        int dx = (int)(rx * std::sqrt(1.0 - (double)(i * i) / (double)(ry * ry)));
        SDL_RenderDrawLine(g_renderer, cx - dx, cy + i, cx + dx, cy + i);
    }
}

void setfont(int height, int width, const char* fontName) {
    if (g_font) TTF_CloseFont(g_font);
    g_font = TTF_OpenFont(get_font_path(fontName).c_str(), height);
    if (g_font) TTF_SetFontHinting(g_font, TTF_HINTING_LIGHT); 
    g_font_height = height;
}

void setbkmode(int mode) {}

void xyprintf(int x, int y, const char* fmt, ...) {
    char buf[1024];
    va_list args; va_start(args, fmt); vsnprintf(buf, sizeof(buf), fmt, args); va_end(args);
    
    // 【核心状态侦测】
    if (strcmp(buf, "中国象棋") == 0) {
        g_is_in_menu = true;  // 看到“中国象棋”，说明回到了主菜单
    }
    if (strstr(buf, "模式：") != nullptr) {
        g_is_in_menu = false; // 看到“模式：”，说明进了游戏
    }

    SDL_Color textColor = { (uint8_t)((g_current_color >> 16) & 0xFF), (uint8_t)((g_current_color >> 8) & 0xFF), (uint8_t)(g_current_color & 0xFF), 255 };
    SDL_Surface* surface = TTF_RenderUTF8_Blended(g_font, buf, textColor);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
        if (texture) SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear); 
        SDL_Rect dst = {x, y, surface->w, surface->h};
        SDL_RenderCopy(g_renderer, texture, NULL, &dst);
        SDL_DestroyTexture(texture); SDL_FreeSurface(surface);
    }
}

PIMAGE newimage() { IMAGE* img = new IMAGE(); g_image_pool.push_back(img); return img; }
void delimage(PIMAGE img) { }
void getimage(PIMAGE img, const char* filename) { img->path = filename; img->tex = nullptr; }
void getimage(PIMAGE img, const char* type, const char* res_name) { img->path = res_name; img->tex = nullptr; }

void ensure_texture(PIMAGE img) {
    if (!img->tex && !img->path.empty()) {
        if (g_texture_cache.find(img->path) == g_texture_cache.end()) {
            SDL_Surface* surface = IMG_Load(img->path.c_str());
            if (surface) {
                if (img->path.find("背景") == std::string::npos && img->path.find("title") == std::string::npos && img->path.find("botton") == std::string::npos) {
                    if (surface->format->Amask == 0) {
                        Uint32 pixel = ((Uint32*)surface->pixels)[0];
                        SDL_SetColorKey(surface, SDL_TRUE, pixel);
                    }
                }
                SDL_Texture* tex = SDL_CreateTextureFromSurface(g_renderer, surface);
                if (tex) {
                    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
                    g_texture_cache[img->path] = tex;
                }
                SDL_FreeSurface(surface);
            }
        }
        if (g_texture_cache.find(img->path) != g_texture_cache.end()) {
            img->tex = g_texture_cache[img->path];
            SDL_QueryTexture(img->tex, NULL, NULL, &img->w, &img->h);
        }
    }
}

void putimage(int x, int y, PIMAGE img) {
    if (!img) return;
    ensure_texture(img);
    if (img->tex) {
        SDL_Rect dst = {x, y, img->w, img->h};
        if (img->path.find("背景") == std::string::npos && img->path.find("title") == std::string::npos && img->path.find("botton") == std::string::npos) {
            dst.w = 37; dst.h = 37;
        }
        SDL_RenderCopy(g_renderer, img->tex, NULL, &dst);
    }
}

void putimage_transparent(void* dst, PIMAGE img, int x, int y, color_t color) {
    if (!img) return;
    ensure_texture(img);
    if (img->tex) {
        SDL_SetTextureBlendMode(img->tex, SDL_BLENDMODE_BLEND);
        SDL_Rect dst_rect = {x, y, img->w, img->h};
        SDL_RenderCopy(g_renderer, img->tex, NULL, &dst_rect);
    }
}

void delay_fps(int fps) {
    g_target_fps = fps;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) { closegraph(); exit(0); }
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            mouse_msg msg;
            msg.x = event.button.x; msg.y = event.button.y;
            msg.down = (event.type == SDL_MOUSEBUTTONDOWN);
            msg.up = (event.type == SDL_MOUSEBUTTONUP);
            msg.left = (event.button.button == SDL_BUTTON_LEFT);
            msg.right = (event.button.button == SDL_BUTTON_RIGHT);
            g_mouse_events.push_back(msg);
        }
    }

    SDL_SetRenderTarget(g_renderer, NULL);
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255); 
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, g_canvas, NULL, NULL);
    SDL_RenderPresent(g_renderer);
    SDL_SetRenderTarget(g_renderer, g_canvas);

    uint32_t current_tick = SDL_GetTicks();
    uint32_t frame_time = 1000 / fps;
    if (current_tick - g_last_tick < frame_time) SDL_Delay(frame_time - (current_tick - g_last_tick));
    g_last_tick = SDL_GetTicks();
}

bool is_run() { return g_running; }
bool mousemsg() { return !g_mouse_events.empty(); }

mouse_msg getmouse() {
    if (g_mouse_events.empty()) return mouse_msg{0, 0, false, false, false, false};
    mouse_msg msg = g_mouse_events.front();
    g_mouse_events.erase(g_mouse_events.begin());

    // 【精准拦截】只有在主菜单（g_is_in_menu == true）点击残棋区域才触发
    if (g_is_in_menu && msg.left && msg.down && msg.x >= 120 && msg.x <= 300 && msg.y >= 380 && msg.y <= 480) {
        g_is_in_menu = false;
        g_mouse_events.clear();
        cclean();
        cplay();
        return mouse_msg{0, 0, false, false, false, false};
    }
    return msg;
}

void MUSIC::OpenFile(const char* path) { if (chunk) Mix_FreeChunk(chunk); chunk = Mix_LoadWAV(path); }
void MUSIC::Play(int loop) { if (chunk) Mix_PlayChannel(-1, chunk, loop); }
void MUSIC::Close() { if (chunk) { Mix_FreeChunk(chunk); chunk = nullptr; } }

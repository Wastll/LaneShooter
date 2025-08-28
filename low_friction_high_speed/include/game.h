#ifndef GAME_H
#define GAME_H

void init_game(int fb_w, int fb_h);
void update_game(void);

// Draws front UI layer
void draw_framebuffer();

// Final draw function
void draw_upscale();

void draw_ui();

#endif

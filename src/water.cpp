// WATER
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <cstdlib>
#include <cmath>

#include "lib/main.h"

#define MAX_WLEN 25
#define MIN_WLEN 10

int num_waves;

void draw_wave(int cx, int cy, float amp, float wavelength) {
    int x, y;
    for (x = 0; x < bytes->width; x++) {
        for (y = 0; y < bytes->height; y++) {
            float dist = sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            float radius = wavelength * (rand() % 10 + 10);
            float val = amp * (1 - dist / (bytes->width + bytes->height)) * (1 + sin(dist / wavelength)
                                                              * (radius > dist ? 1 : radius / dist));
            bytes->setR(x, y, bytes->getR(x, y) + (20 + val * 70) / num_waves);
            bytes->setG(x, y, bytes->getG(x, y) + (20 + val * 70) / num_waves);
            bytes->setB(x, y, bytes->getB(x, y) + (120 + val * 70) / num_waves);
        }
    }
}

void draw() {
    num_waves = rand() % 5 + 2;
    int i;
    for (i = 0; i < num_waves; i++) {
        int x = rand() % bytes->width;
        int y = rand() % bytes->height;
        float amp = .5 + ((float) (rand() & 0xFF)) / 0x100 / 2;
        float wavelength = rand() % (MAX_WLEN - MIN_WLEN) + MIN_WLEN;
        draw_wave(x, y, amp, wavelength);
    }
}

//Idea stolen from http://pcg.wikidot.com/forum/t-79282/multiplicative-cascades-ish

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>

#include "lib/main.h"

std::vector<char> map;
int width, height;

void init_map() {
    width = 4;
    height = 3;
    map.resize(width * height);
    int i;
    for (i = 0; i < width * height; i++) {
        map[i] = rand();
    }
}

//value is the value of the current pixel, 0 to 255
//n_per_level is how many subdivisions per step
//x is a random value between 0 and 1, straight out of the random number generator
char foo(unsigned char value, int n_per_level, float x) {
    float v = value / 255.;
    if (v > 1. / n_per_level / n_per_level) {
        v = 1 + log(v) / log(4);
        return (unsigned char) (255 * v + .5);
    } else return (unsigned char) (255 * x + .5);
}

void next_iter() {
    std::vector<char> newmap;
    newmap.resize(width * height);
    int i;
    for (i = 0; i < width * height; i++) {
        float rnd = rand() / 10000.;
        rnd = rnd - (int) rnd;
        rnd = rnd < 0 ? -rnd : rnd;
        newmap[i] = foo(map[i], 2, rnd);
    }
    map = newmap;
}

void scale2x_horiz() {
    std::vector<char> newmap;
    newmap.resize(width * 2 * height);
    int i;

    for (i = 0; i < width * height; i++) {
        newmap[i * 2] = map[i];
        newmap[i * 2 + 1] = (map[i] + map[(i + 1) % (width * height)]) / 2;
    }
    map = newmap;
    width *= 2;
}

void scale2x_vert() {
    std::vector<char> newmap;
    newmap.resize(width * 2 * height);
    int x, y;
    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            newmap[y * 2 * width + x] = map[y * width + x];
            newmap[(y * 2 + 1) * width + x] = (map[y * width + x] + map[((y + 1) % height) * width + x]) / 2;
        }
    }
    map = newmap;
    height *= 2;
}

void draw() {
    init_map();
    int i;
    while (width < WID && height < HEI) {
        scale2x_horiz();
        scale2x_vert();
        next_iter();
    }
    int x, y;
    for (x = 0; x < WID; x++) {
        for (y = 0; y < HEI; y++) {
            bytes[(WID * y + x) * 3] = map[width * y + x] / 2 + 127;
            bytes[(WID * y + x) * 3 + 1] = map[width * y + x] / 2 + 127;
            bytes[(WID * y + x) * 3 + 2] = map[width * y + x] / 2 + 127;
        }
    }
}

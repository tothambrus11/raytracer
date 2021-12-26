#define SDL_MAIN_HANDLED

#include "Vector3.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <color.h>
#include <Ray.h>
#include <string>
#include <objects/Sphere.h>
#include <vector>
#include <objects/Octahedron.h>
#include <atomic>
#include "array"
#include "thread"

using namespace std;

//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH * 9.0 / 16.0);

const int SCREEN_WIDTH = 2500;
const int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH / 16.0 * 7.0 / 5.0);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int pxcount = SCREEN_HEIGHT * SCREEN_WIDTH;

int main(int argc, char *args[]) {

    cout << "hello world\n";
    RGB255Color pixels[pxcount];
    array<array<Ray, SCREEN_WIDTH>, SCREEN_HEIGHT> rays;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {

        if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
            SDL_SetWindowTitle(window, "Render2D");
            //SDL_SetWindowFullscreen(window, SDL_TRUE);

            int i = 0, mouseX, mouseY;
            SDL_Event event;

            Uint64 t0 = SDL_GetTicks();

            SDL_Texture *t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
                                               SDL_TEXTUREACCESS_STATIC,
                                               SCREEN_WIDTH, SCREEN_HEIGHT);

            for (int j = 0; j < pxcount; ++j) {
                pixels[j] = {0, 0, 0};
            }


            const double PI = 3.14159265;

            double w = SCREEN_WIDTH;
            double alpha = PI / 2;

            double scale = w / SCREEN_WIDTH;

            double h = scale * SCREEN_HEIGHT;
            double c = w / (2 * sqrt(1 - pow(cos(alpha / 2), 2)));
            double d = cos(alpha / 2) * c;
            cout << "d: " << d;

            for (int y = 0; y < SCREEN_HEIGHT; ++y) {
                for (int x = 0; x < SCREEN_WIDTH; ++x) {
                    rays[y][x].direction = {x * scale - w / 2, y * scale - h / 2, d};
                    rays[y][x].direction._normalize();
                }
            }
            cout << endl << rays[0][0].direction.toString();
            cout << endl << rays[SCREEN_HEIGHT - 1][0].direction.toString();
            cout << endl << rays[SCREEN_HEIGHT / 2][SCREEN_WIDTH / 2].direction.toString();

            vector<HittableObject *> objects = {};

            /*objects.push_back((HittableObject *) new Sphere({0, 40, 500}, 100, {1, 0, 0}, Material(
                    {.0, .1,.0},
                    {.0,.6,0},
                    {.5},
                    {128},
                    {.9}
            )));
            objects.push_back((HittableObject *) new Sphere({-120, 0, 500}, 60, {0, 0, 0}, Material(
                    {0, .0, 0.1},
                    {.05,.05,.6},
                    {.4},
                    {128},
                    {.8}
            )));
            objects.push_back((HittableObject *) new Sphere({0, 60, 500}, 60, {0, 0, 0}, Material(
                    {0, .1, .1},
                    {.05,.6,.6},
                    {.4},
                    {128},
                    {.8}
                    )));
            objects.push_back((HittableObject *) new Sphere({120, 0, 500}, 60, {0, 0, 1}, Material(
                    {.1, .0, .0},
                    {.6,.05,.05},
                    {.4},
                    {128},
                    {.8}
            )));*/

            const array<array<int, 2>, 219> charCoords = {
                    {
                            {0, 0},
                            {4, 0},
                            {0, 1},
                            {1, 1},
                            {3, 1},
                            {4, 1},
                            {0, 2},
                            {2, 2},
                            {4, 2},
                            {0, 3},
                            {4, 3},
                            {0, 4},
                            {4, 4},
                            {0, 5},
                            {4, 5},
                            {0, 6},
                            {4, 6},
                            {6, 0},
                            {7, 0},
                            {8, 0},
                            {9, 0},
                            {10, 0},
                            {6, 1},
                            {6, 2},
                            {6, 3},
                            {7, 3},
                            {8, 3},
                            {9, 3},
                            {10, 3},
                            {6, 4},
                            {6, 5},
                            {6, 6},
                            {7, 6},
                            {8, 6},
                            {9, 6},
                            {10, 6},
                            {12, 0},
                            {13, 0},
                            {14, 0},
                            {15, 0},
                            {12, 1},
                            {16, 1},
                            {12, 2},
                            {16, 2},
                            {12, 3},
                            {13, 3},
                            {14, 3},
                            {15, 3},
                            {12, 4},
                            {16, 4},
                            {12, 5},
                            {16, 5},
                            {12, 6},
                            {16, 6},
                            {18, 0},
                            {19, 0},
                            {20, 0},
                            {21, 0},
                            {18, 1},
                            {22, 1},
                            {18, 2},
                            {22, 2},
                            {18, 3},
                            {19, 3},
                            {20, 3},
                            {21, 3},
                            {18, 4},
                            {22, 4},
                            {18, 5},
                            {22, 5},
                            {18, 6},
                            {22, 6},
                            {24, 0},
                            {28, 0},
                            {24, 1},
                            {28, 1},
                            {25, 2},
                            {27, 2},
                            {26, 3},
                            {26, 4},
                            {26, 5},
                            {26, 6},
                            {37, 0},
                            {38, 0},
                            {39, 0},
                            {36, 1},
                            {40, 1},
                            {36, 2},
                            {36, 3},
                            {36, 4},
                            {36, 5},
                            {40, 5},
                            {37, 6},
                            {38, 6},
                            {39, 6},
                            {42, 0},
                            {46, 0},
                            {42, 1},
                            {46, 1},
                            {42, 2},
                            {46, 2},
                            {42, 3},
                            {43, 3},
                            {44, 3},
                            {45, 3},
                            {46, 3},
                            {42, 4},
                            {46, 4},
                            {42, 5},
                            {46, 5},
                            {42, 6},
                            {46, 6},
                            {48, 0},
                            {49, 0},
                            {50, 0},
                            {51, 0},
                            {48, 1},
                            {52, 1},
                            {48, 2},
                            {52, 2},
                            {48, 3},
                            {49, 3},
                            {50, 3},
                            {51, 3},
                            {48, 4},
                            {52, 4},
                            {48, 5},
                            {52, 5},
                            {48, 6},
                            {52, 6},
                            {56, 0},
                            {56, 1},
                            {56, 2},
                            {56, 3},
                            {56, 4},
                            {56, 5},
                            {56, 6},
                            {61, 0},
                            {62, 0},
                            {63, 0},
                            {60, 1},
                            {64, 1},
                            {60, 2},
                            {61, 3},
                            {62, 3},
                            {63, 3},
                            {64, 4},
                            {60, 5},
                            {64, 5},
                            {61, 6},
                            {62, 6},
                            {63, 6},
                            {66, 0},
                            {67, 0},
                            {68, 0},
                            {69, 0},
                            {70, 0},
                            {68, 1},
                            {68, 2},
                            {68, 3},
                            {68, 4},
                            {68, 5},
                            {68, 6},
                            {72, 0},
                            {76, 0},
                            {72, 1},
                            {73, 1},
                            {75, 1},
                            {76, 1},
                            {72, 2},
                            {74, 2},
                            {76, 2},
                            {72, 3},
                            {76, 3},
                            {72, 4},
                            {76, 4},
                            {72, 5},
                            {76, 5},
                            {72, 6},
                            {76, 6},
                            {79, 0},
                            {80, 0},
                            {81, 0},
                            {78, 1},
                            {82, 1},
                            {78, 2},
                            {82, 2},
                            {78, 3},
                            {79, 3},
                            {80, 3},
                            {81, 3},
                            {82, 3},
                            {78, 4},
                            {82, 4},
                            {78, 5},
                            {82, 5},
                            {78, 6},
                            {82, 6},
                            {85, 0},
                            {86, 0},
                            {87, 0},
                            {84, 1},
                            {88, 1},
                            {84, 2},
                            {85, 3},
                            {86, 3},
                            {87, 3},
                            {88, 4},
                            {84, 5},
                            {88, 5},
                            {85, 6},
                            {86, 6},
                            {87, 6},
                            {92, 0},
                            {92, 1},
                            {92, 2},
                            {92, 3},
                            {92, 4},
                            {92, 6}
                    }
            };

            const double s = 9;
            int asd = 0;
            for (auto el : charCoords) {
                Color c = {(rand() % 200 + 55.0) / 255, (rand() % 200 + 55.0) / 255, (rand() % 200 + 55.0) / 255};
                if (asd++ < 82) {
                    c = (rand() % 2==0) ? Color(1, .1, .1) : Color(1, 1, 1);
                }
                objects.push_back(new Sphere(
                        {(el[0] - 8 * 6) * s, (el[1] - 3) * s, 500},
                        s * 0.8,
                        {0},
                        {
                                c * .1,
                                c * .4,
                                c * .3,
                                {128},
                                {.2}
                        }
                ));
            }

            vector<PointLight *> lights = {};
            lights.push_back(new PointLight({-400, 40, 400}, {1, .1, .1})); // piros
            // lights.push_back(new PointLight({400, 40, 400}, {.1, .1, 1}));    // kék
            lights.push_back(new PointLight({100, -100, 50}, {1, .8, .2}));    // sárga
            // lights.push_back(new PointLight({-300, -200, 350}, {1}));

            /*objects.push_back(new Sphere(lights[0]->origin, 15, {0}, {
                    {.5, 0, 0},
                    {0},
                    {0},
                    {0},
                    {0}
            }));

            objects.push_back(new Sphere(lights[1]->origin, 25, {0}, {
                    {0, 0, .5},
                    {0},
                    {0},
                    {0},
                    {0}
            }));*/

            auto *s1 = (Sphere *) objects[0];
            auto *s2 = (Sphere *) objects[1];

            while (!done) {
                SDL_SetWindowTitle(window, (to_string(i++ / ((SDL_GetTicks() - t0) / 1000.0)) + " fps").c_str());
                SDL_GetMouseState(&mouseX, &mouseY);

                Vector3 s;
                //s = rays[mouseY][mouseX].direction * s1->origin.z / rays[mouseY][mouseX].direction.z;
                //lights[0]->origin.x = 200;//s.x; //mouseX / scale - w / 2;
                //lights[0]->origin.y = 0; //s.y; // mouseY / scale - h / 2;
                //lights[1]->origin.x = s.x; //s.x-200; //mouseX / scale - w / 2;
                //lights[1]->origin.y = s.y; //s.y; // mouseY / scale - h / 2;
                //s1->origin.x = s.x;
                //s1->origin.y = s.y;

                SDL_Delay(10);

                double minDistance; // reset for each pixel
                HittableObject *nearestObject; // reset for each pixel

                Color pixelColor;
                for (int y = 0; y < SCREEN_HEIGHT && i == 1; y += 1) {
                    for (int x = 0; x < SCREEN_WIDTH; x += 1) {
                        Ray &ray = rays[y][x];

                        nearestObject = nullptr;
                        for (auto &object : objects) {
                            double distance = object->intersectsRayAt(ray);
                            if (distance > 0 && (nearestObject == nullptr || distance < minDistance)) {
                                minDistance = distance;
                                nearestObject = object;
                            }
                        }

                        if (nearestObject != nullptr) {
                            pixelColor = nearestObject->calculateEmittedLight(3, ray,
                                                                              ray.origin + ray.direction * minDistance,
                                                                              objects, lights);
                        } else {
                            pixelColor = {0, 0, 0};
                        }

                        pixels[x + y * SCREEN_WIDTH] = RGB255Color::from(pixelColor);

                    }
                }

                SDL_UpdateTexture(t, NULL, &pixels, SCREEN_WIDTH * sizeof(RGB255Color));

                SDL_RenderCopy(renderer, t, NULL, NULL);
                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
            for (const auto &item : objects) {
                //delete item;
            }
            objects.clear();
        }


        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}

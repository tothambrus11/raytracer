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
#include "objects/Cylinder.h"
#include "objects/CylinderInsideOut.h"
#include "MyMatrixFunctions.h"

using namespace std;

//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH * 9.0 / 16.0);

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH / 16.0 * 9);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int pxcount = SCREEN_HEIGHT * SCREEN_WIDTH;

int main(int argc, char *args[]) {
    int n = 6;
    for (int i = 0; i < n; i++) {
        cout << i << endl;
    }
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

            for (auto &pixel: pixels) {
                pixel = {0, 0, 0};
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


            objects.push_back((HittableObject *) new Cylinder({0, 0, 500}, 50, 100, 0, Material(
                    {.0, 0, 0.05},
                    {.05, .05, .6},
                    {.4},
                    {128},
                    {.15}
            )));

            objects.push_back((HittableObject *) new Cylinder({0, 0, 500}, 50, 0, -100, Material(
                    {.05, 0, 0},
                    {.6, .05, .05},
                    {.4},
                    {128},
                    {.15}
            )));


            /*objects.push_back((HittableObject *) new CylinderInsideOut({0, 0, 600}, 99, 300, -150, Material(
                    {.05, 0, 0},
                    {.6, .05, .05},
                    {.4},
                    {128},
                    {.5}
            )));*/

            objects.push_back((HittableObject *) new Sphere({200, 200, 500}, 100, {
                    {.0,  .3, .0},
                    {.05, .3, .05},
                    {.2},
                    {1},
                    {.5}
            }));


            vector<PointLight *> lights = {};
            lights.push_back(new PointLight({0, 0, -0}, {1}));

            auto *c1 = (Cylinder *) objects[0];
            auto *c2 = (Cylinder *) objects[1];

            objects.push_back((HittableObject *) new Sphere({0, 0, 0}, c1->radius, {
                    {.0,  0,   0.05},
                    {.05, .05, .6},
                    {.4},
                    {128},
                    {.15}
            }));

            objects.push_back((HittableObject *) new Sphere({0, 0, 0}, c1->radius, {
                    {.05, 0,   0},
                    {.6,  .05, .05},
                    {.4},
                    {128},
                    {.15}
            }));

            auto *s1 = (Sphere *) objects[3];
            auto *s2 = (Sphere *) objects[4];

            double rot;
            while (!done) {
                SDL_SetWindowTitle(window, (to_string(i++ / ((SDL_GetTicks() - t0) / 1000.0)) + " fps").c_str());
                SDL_GetMouseState(&mouseX, &mouseY);

                Vector3 s;
                double z = 500;
                double r = mouseX;


                s = rays[mouseY][mouseX].direction * z / rays[mouseY][mouseX].direction.z;
                //lights[0]->origin.x = 200;//s.x; //mouseX / scale - w / 2;
                //lights[0]->origin.y = 0; //s.y; // mouseY / scale - h / 2;
                lights[0]->origin.x = -200; //s.x-200; //mouseX / scale - w / 2;
                //lights[1]->origin.x = -s.x*5; //s.x-200; //mouseX / scale - w / 2;
                lights[0]->origin.y = 0; //s.y; // mouseY / scale - h / 2;
                lights[0]->origin.z = -10000;
                //lights[1]->origin.y = -s.y*5; //s.y; // mouseY / scale - h / 2;
                //lamp->origin.x = -s.x*15; //s.x-200; //mouseX / scale - w / 2;
                //lamp->origin.y = -s.y*15; //s.y; // mouseY / scale - h / 2;

                c1->radius = 50;
                c2->radius = c1->radius;
                s1->radius = c1->radius;
                s2->radius = c1->radius;


                double k1 = c1->topZ;
                double k2 = c2->bottomZ;
                double r_g_1 = sqrt(r * r + k1 * k1);
                double r_g_2 = sqrt(r * r + k2 * k2);
                double dAlpha1=acos(r/r_g_1);
                double dAlpha2=-acos(r/r_g_2);

                c1->origin.x = 0 + cos(PI * rot) * r;
                c2->origin.x = 0 + cos(PI * rot) * r;
                c1->origin.z = z + sin(PI * rot) * r;
                c2->origin.z = z + sin(PI * rot) * r;

                c1->origin.y = s.y;
                c2->origin.y = s.y;


                c1->updateRotation(PI * rot);
                c2->updateRotation(PI * rot);

                s1->origin.y = s.y;
                s2->origin.y = s.y;

                s1->origin.x = 0 + cos(PI * rot + dAlpha1) * r_g_1;
                s2->origin.x = 0 + cos(PI * rot + dAlpha2) * r_g_2;

                s1->origin.z = z + sin(PI*rot + dAlpha1)*r_g_1;
                s2->origin.z = z + sin(PI*rot + dAlpha2)*r_g_2;


                //s3->origin.x = s.x;
                //s3->origin.y = s.y;

                rot += .05;

                SDL_Delay(10);

                double minDistance; // reset for each pixel
                HittableObject *nearestObject; // reset for each pixel

                Color pixelColor;
                for (int y = 0; y < SCREEN_HEIGHT; y += 1) {
                    for (int x = 0; x < SCREEN_WIDTH; x += 1) {
                        Ray &ray = rays[y][x];

                        nearestObject = nullptr;
                        for (auto &object: objects) {
                            double distance = object->intersectsRayAt(ray);
                            if (distance > 0 && (nearestObject == nullptr || distance < minDistance)) {
                                minDistance = distance;
                                nearestObject = object;
                            }
                        }

                        if (nearestObject != nullptr) {
                            pixelColor = nearestObject->calculateEmittedLight(10, ray,
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

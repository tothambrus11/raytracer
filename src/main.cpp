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

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH * 9.0 / 16.0);

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

            objects.push_back((HittableObject *) new Sphere({100, 100, 300}, 60, {1, 0, 0}, Material(
                    {0.2, 0, 0},
                    {.6,.2,.2},
                    {.2},
                    {128},
                    {}
            )));
            objects.push_back((HittableObject *) new Sphere({0, 0, 370}, 60, {0, 1, 0}, Material(
                    {0, 0.2, 0},
                    {.2,.6,.2},
                    {.2},
                    {128},
                    {}
            )));

            vector<PointLight *> lights = {};
            lights.push_back(new PointLight({-300, -200, 200}, {1, 1, 1}));
            // cout << "\n\n" << objects[2] << "\t\thll\n";

            auto *s1 = (Sphere *) objects[0];
            auto *s2 = (Sphere *) objects[1];

            while (!done) {
                SDL_SetWindowTitle(window, (to_string(i++ / ((SDL_GetTicks() - t0) / 1000.0)) + " fps").c_str());
                SDL_GetMouseState(&mouseX, &mouseY);

                Vector3 s;
                s = rays[mouseY][mouseX].direction * lights[0]->origin.z / rays[mouseY][mouseX].direction.z;
                lights[0]->origin.x = s.x; //mouseX / scale - w / 2;
                lights[0]->origin.y = s.y; // mouseY / scale - h / 2;

                SDL_UpdateTexture(t, NULL, &pixels, SCREEN_WIDTH * sizeof(RGB255Color));

                SDL_RenderCopy(renderer, t, NULL, NULL);
                SDL_RenderPresent(renderer);

                double minDistance; // reset for each pixel
                HittableObject *nearestObject; // reset for each pixel

                Color pixelColor;
                for (int y = 0; y < SCREEN_HEIGHT; ++y) {
                    for (int x = 0; x < SCREEN_WIDTH; ++x) {
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
                            pixelColor = nearestObject->calculateEmittedLight(5, ray,
                                                                              ray.origin + ray.direction * minDistance,
                                                                              objects, lights);
                        } else {
                            pixelColor = {0, 0, 0};
                        }

                        pixels[x + y * SCREEN_WIDTH] = RGB255Color::from(pixelColor);

                        /*
                        Color bestColor;
                        double bestDistance;
                        bool found;

                        bestColor = {0, 0, 0};
                        bestDistance = 0;
                        found = false;
                        Sphere *bestSphere;
                        for (auto &object : objects) {
                            double distance = object->intersectsRayAt(ray);
                            if (distance >= 0 && (!found || distance < bestDistance)) {
                                bestDistance = distance;
                                bestColor = object->color * 0.2;
                                found = true;
                                bestSphere = (Sphere *) object;
                            }
                        }

                        if (found) {
                            auto &O = bestSphere->origin;
                            auto &D = ray.direction;
                            auto M = D * bestDistance;
                            auto n = (M - O).normalize();
                            auto e = n * ((D * -1) * n);
                            auto D2 = (e * 2) + D;

                            Ray r2(M, D2);

                            Color bestColor2 = {0, 0, 0};
                            bestDistance = 0;
                            found = false;
                            Sphere * bestSphere2;

                            for (auto &object : objects) {
                                double distance = object->intersectsRayAt(r2);
                                if (distance >= 0 && (!found || distance < bestDistance) && object != bestSphere) {
                                    bestDistance = distance;
                                    bestColor2 = object->color;
                                    found = true;
                                    bestSphere2 = (Sphere *) object;
                                }
                            }

                            if(found){
                                bestColor += bestColor2 * 0.5;
                            }

                        }*/

                    }
                }

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }

                // cout << avgDist << endl;
                // avgDist = distSumTimes100 / 100.0 / (double) newCount;
                //SDL_Delay(10);
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

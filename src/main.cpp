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
#include "array"

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = SCREEN_WIDTH * 9.0 / 16.0;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int pxcount = SCREEN_HEIGHT * SCREEN_WIDTH;


int main(int argc, char *args[]) {

    cout << "hello world\n";
    Color pixels[pxcount];
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

            Octahedron octahedron({0, 0, d + 100}, 50);
            for (int y = 0; y < SCREEN_HEIGHT; ++y) {
                for (int x = 0; x < SCREEN_WIDTH; ++x) {
                    rays[y][x].direction = {x * scale - w / 2, y * scale - h / 2, d};
                    rays[y][x].direction._normalize();
                }
            }
            cout << endl << rays[0][0].direction.toString();
            cout << endl << rays[SCREEN_HEIGHT - 1][0].direction.toString();
            cout << endl << rays[SCREEN_HEIGHT / 2][SCREEN_WIDTH / 2].direction.toString();


            vector<Sphere> objects = {
                    {{0, 0, 480}, 20, {255, 0,   0}},
                    {{0, 0, 480}, 20, {0,   255, 0}},
                    {{0, 0, 500}, 40, {0,   0,   255}}
            };
            Sphere &sphere = objects[0];

            double avgDist = 0;
            while (!done) {
                SDL_SetWindowTitle(window, (to_string(i++ / ((SDL_GetTicks() - t0) / 1000.0)) + " fps").c_str());
                SDL_GetMouseState(&mouseX, &mouseY);


                Vector3 s;

                int yy = mouseY + sin(i / 5.0) * SCREEN_HEIGHT / 4.0;
                yy %= SCREEN_HEIGHT;
                yy = abs(yy);

                s = rays[mouseY][mouseX].direction * octahedron.origin.z / rays[mouseY][mouseX].direction.z;
                octahedron.origin.x = s.x;
                octahedron.origin.y = s.y;

                s = rays[yy][mouseX].direction * sphere.origin.z / rays[yy][mouseX].direction.z;
                sphere.origin.x = s.x; //mouseX / scale - w / 2;
                sphere.origin.y = s.y; // mouseY / scale - h / 2;

                s = rays[yy][SCREEN_WIDTH - 1 - mouseX].direction * objects[1].origin.z /
                    rays[yy][SCREEN_WIDTH - 1 - mouseX].direction.z;
                objects[1].origin.x = s.x;
                objects[1].origin.y = s.y;
                //sphere.origin.z = pow(sin(i / 30.0), 2) * 1000 + d;

                //sphere.origin.x = sin(i/10.0)* 300;
                //sphere.origin.z = cos(i/10.0)* 300 + 1000;

                //cout << "origin: " << sphere.origin.toString() << "; radius: " << sphere.radius << endl;
                SDL_UpdateTexture(t, NULL, &pixels, SCREEN_WIDTH * sizeof(Color));

                SDL_RenderCopy(renderer, t, NULL, NULL);
                SDL_RenderPresent(renderer);

                double newAvgDist = 0;
                int newCount = 0;
                for (int y = 0; y < SCREEN_HEIGHT; ++y) {
                    for (int x = 0; x < SCREEN_WIDTH; ++x) {
                        Color bestColor;
                        double bestDistance;
                        bool found;

                        bestColor = {0, 0, 0};
                        bestDistance = 0;
                        found = false;

                        /*for (Sphere &s : objects) {
                            double distance = s.intersectsRayAt(rays[y][x]);
                            if (distance >= 0 && (!found || distance < bestDistance)) {
                                bestDistance = distance;
                                bestColor = s.color;
                                found = true;
                            }
                        }*/
                        auto dist = octahedron.intersectsRayAt(rays[y][x]);
                        if (dist > 0) {
                            newAvgDist += dist;
                            newCount++;

                            Uint8 color = 255 - min(255.0, max(0.0, 127 + (avgDist - dist) * 127.0/50.0));
                            //cout << dist
                            bestColor = {color, 0, 0};
                        }

                        pixels[x + y * SCREEN_WIDTH] = bestColor;

                    }
                }

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }

                cout << avgDist <<endl;
                avgDist = newAvgDist / newCount;
                //SDL_Delay(10);
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

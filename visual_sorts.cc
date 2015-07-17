#include <SDL.h>
#include <cstdio>
#include <ctime>

#include "random.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>

#define W 1900
#define H 1

#define PX(i,j) px[j*W+i]

SDL_Texture *texture;
SDL_Renderer *renderer;
uint32_t px[W*H];

int i = 0;

void disp()
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      exit(1);
    }
  }
  SDL_RenderClear(renderer);
  SDL_UpdateTexture(texture, NULL, px, W);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void heapsort(uint32_t *arr, int len)
{
  uint32_t *first = arr, *last = arr;
  puts("Heapifying");
  while (last - first != len) {
    std::push_heap(first, last++);
    disp();
  }
  puts("Sorting");
  while (first != last) {
    std::pop_heap(first, last--);
    disp();
  }
  puts("Done");
}

void quicksort(uint32_t *arr, int lb, int ub)
{
  if (ub - lb < 1) {
    return;
  }
  int last = lb;
  for (int i = lb+1; i < ub; i++) {
    if (arr[i] < arr[lb]) {
      last++;
      std::swap(arr[i], arr[last]);
      disp();
    }
  }
  std::swap(arr[lb], arr[last]);
  disp();
  quicksort(arr, lb, last);
  quicksort(arr, last+1, ub);
}


void selection_sort(uint32_t *arr, int sz)
{
  for (int i = 0; i < sz; i++) {
    int max = 0;
    for (int j = 0; j < sz-i; j++) {
      if (arr[j] > arr[max]) {
        max = j;
      }
    }
    std::swap(arr[max], arr[sz-1-i]);
    disp();
  }
}

void insertion_sort(uint32_t *arr, int sz)
{
  for (int i = 1; i < sz; i++) {
    for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
      std::swap(arr[j], arr[j-1]);
      disp();
    }
  }
}

void bubble_sort(uint32_t *arr, int sz)
{
  for (int i = 0; i < sz; i++) {
    for (int j = i; j < sz; j++) {
      if (arr[i] > arr[j]) {
        std::swap(arr[i], arr[j]);
        disp();
      }
    }
  }
}

int main(int argc, char **argv)
{
  //The window we'll be rendering to
  SDL_Window* window = NULL;

  Random rng(time(0));

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }
  else
  {
    //Create window
    window = SDL_CreateWindow( "SUM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, 500, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
      texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
      for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
          PX(i,j) = 0x7F000000 | (rng.next<uint32_t>() & 0xFF);
        }
      }
      heapsort(px, W*H);
      char c;
      std::cin >> c;
      for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
          PX(i,j) = 0x7F000000 | (rng.next<uint32_t>() & 0xFF);
        }
      }
      puts("quicksorting...");
      quicksort(px, 0, W*H);
      puts("done quicksorting");
      for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
          PX(i,j) = 0x7F000000 | (rng.next<uint32_t>() & 0xFF);
        }
      }
      std::cin >> c;
      puts("selection sorting");
      selection_sort(px, W*H);
      puts("done selection sorting");
      for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
          PX(i,j) = 0x7F000000 | (rng.next<uint32_t>() & 0xFF);
        }
      }
      std::cin >> c;
      puts("insertion sorting");
      insertion_sort(px, W*H);
      puts("done insertion sorting");
      for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
          PX(i,j) = 0x7F000000 | (rng.next<uint32_t>() & 0xFF);
        }
      }
      std::cin >> c;
      puts("bubble sorting");
      bubble_sort(px, W*H);
      puts("done bubble sorting");

    }
  }
  //Destroy window
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();
  return 0;
}

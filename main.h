// main.h
#include <gtk/gtk.h>
#include <cairo.h>
#ifndef MAIN_H
#define MAIN_H

// MAIN
#define okay(msg, ...) printf("\033[1;32m[ + ]\033[0m " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("\033[1;31m[ - ]\033[0m " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("\033[1;34m[ i ]\033[0m " msg "\n", ##__VA_ARGS__)
int getRandomNumber(int x);

#endif
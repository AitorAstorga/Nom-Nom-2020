#ifndef IMAGEN_H
#define IMAGEN_H

#define MAX_IMG 200

int loadImage(char* fileName, int windowId);
int findImagePosition(int id);
void moveImage(int numImg, int x, int y);
void deleteImage(int id);
void drawImages(int windowId);
int getImageCount();

#endif
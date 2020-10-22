#ifndef TEXTURE
#define TEXTURE

#include "Texture.h"

void InitAllTextures();
void InitRailTexture();
void InitTerrainTexture();
void InitBridgeRoadTexture();
void ReadBitmap(char* fname);
void BindTexture(Texture* texture, GLvoid* pixels);
#endif



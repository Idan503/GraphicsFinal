#ifndef TEXTURE
#define TEXTURE

#include "Texture.h"

void InitAllTextures();
void InitRailTexture();
void InitTerrainTexture();
void InitTrainTubeTexture();
void InitTrainTubeLinesTexture();
void InitTrainNoseTexture();
void InitMetalAccentTexture();
void InitBridgeRoadTexture();
void InitMetalBrightTexture();

void ReadBitmap(char* fname);
void BindTexture(Texture* texture, GLvoid* pixels);
#endif



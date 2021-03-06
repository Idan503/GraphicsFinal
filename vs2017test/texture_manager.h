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
void InitMetalGreyTexture();
void InitTreeLeavesTexture();
void InitTreeLogTexture();
void InitRedMetalTexture();
void InitYellowMetalTexture();
void InitMetalDarkGreyTexture();
void InitTrainHalfTubeTexture();
void InitTrainPatchTubeFrontTexture();
void InitTrainPatchTubeBackTexture();
void InitSkyTexture();
void InitMetalWhiteTexture();
void InitMetalWhiteDarkTexture();
void InitRockTexture();


void ReadBitmap(const char* fname, bool alpha = false);
void BindTexture(Texture* texture, GLvoid* pixels);
#endif



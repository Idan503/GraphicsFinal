#ifndef TEXTURE
#define TEXTURE

void InitAllTextures();
void InitRailTexture();
void InitTerrainTexture();
void InitBridgeRoadTexture();
void ReadBitmap(char* fname);

const vector<int> rail_tex_size;
const vector<int> grass_tex_size;
const vector<int> bridge_road_tex_size;
const vector<int> train_pipe_tex_size;


#endif



#include "SystemParams.h"

// FilePath
string SystemParams::str_Resources						= "../Output/";
string SystemParams::str_Resources_Original				= "../Output/Original/";
string SystemParams::str_Resources_Binarization			= "../Output/Binarization/";
string SystemParams::str_Resources_CFR					= "../Output/Cartoon Filter Region/";
string SystemParams::str_Resources_CFC					= "../Output/Cartoon Filter Color/";
string SystemParams::str_Resources_TextureConfig		= "../Output/TextureConfig/";
string SystemParams::str_Resources_Mesh					= "../Output/Mesh/";
string SystemParams::str_Resources_KLMMesh				= "../Output/KLMesh/";
string SystemParams::str_Resources_Mesh_Parts			= "../Output/Mesh_Parts/";
string SystemParams::str_Resources_OCR					= "../Output/OCR/";

// Otsu + Gaussian
int SystemParams::O_length = 11;
int SystemParams::G_block_size = 511;
int SystemParams::G_params = -17;
int SystemParams::OG_sigma = 0;
int SystemParams::OG_Bsigma = 0;
int SystemParams::OG_Wsigma = 0;

// Texture
double SystemParams::ct_f_sigma = 5.5f;
double SystemParams::ct_v_lim = 20;
double SystemParams::s_min_size_area = 5000;

// Local binary pattern
int SystemParams::lbp_neighbors = 16;
int SystemParams::lbp_radius = 4;

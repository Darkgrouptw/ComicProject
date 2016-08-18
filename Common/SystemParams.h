#include <QString>
using namespace std;

class SystemParams
{
public:

	// FilePath
	static string str_Resources;
	static string str_Resources_Original;
	static string str_Resources_Binarization;
	static string str_Resources_OCR;
	static string str_Resources_CFR;
	static string str_Resources_CFC;
	static string str_Resources_TextureConfig;
	static string str_Resources_Mesh;
	static string str_Resources_KLMMesh;
	static string str_Resources_Mesh_Parts;


	// Otsu + Gaussian
	static int O_length;
	static int G_block_size;
	static int G_params;
	static int OG_sigma;
	static int OG_Bsigma;
	static int OG_Wsigma;

	// Cartoon + Texture Filter
	static double ct_f_sigma;
	static double ct_v_lim;
	static double s_min_size_area;

	// Local binary pattern
	static int lbp_neighbors;
	static int lbp_radius;

};
#include "image_util.h"

float clamp(const float &lo, const float &hi, const float &v)
{ return std::max(lo, std::min(hi, v)); }

void save_image(
  std::vector<std::vector<glm::vec4>> &image, int width, int height
) {
  std::ofstream ofs;
  ofs.open("./out_3.ppm");
  ofs << "P6\n" << width << " " << height << "\n255\n";
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      glm::vec4 point_image = image[i][j];
      char r = (char)(255 * clamp(0, 1, point_image.x));
      char g = (char)(255 * clamp(0, 1, point_image.y));
      char b = (char)(255 * clamp(0, 1, point_image.z));
      ofs << r << g << b;
    }
  }
  ofs.close();
}

std::vector<std::vector<glm::vec4>> read_image(const char * filename) {
  std::vector<std::vector<glm::vec4>> image;
	int i, j, width, height, max_value, r, g, b;
  char r_char, g_char, b_char;
	FILE * fp;
	assert(fp = fopen(filename, "rb")) ;
  fscanf(fp, "%*s") ;
  fscanf(fp, "%d", &width);
  fscanf(fp, "%d", &height);
  fscanf(fp, "%d", &max_value);
	fscanf(fp, "%*d%*c") ;
  image.resize(height);
	for (i = 0 ; i < height ; i++) {
    image[floor(i)].resize(width);
    for (j = 0 ; j < width ; j++) {
      fscanf(fp, "%c", &r_char) ;
      fscanf(fp, "%c", &g_char) ;
      fscanf(fp, "%c", &b_char) ;
      r = (int)r_char;
      g = (int)g_char;
      b = (int)b_char;
      if (r < 0) {
        r = max_value + 1 + r;
      }
      if (g < 0) {
        g = max_value + 1 + g;
      }
      if (b < 0) {
        b = max_value + 1 + b;
      }
      image[floor(i)][floor(j)] = glm::vec4(
        1.0 * r / max_value, 1.0 * g / max_value,
        1.0 * b / max_value, 1);
    }
  }
	fclose(fp);
  return image;
}

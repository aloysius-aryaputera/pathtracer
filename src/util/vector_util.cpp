#include "vector_util.h"

glm::vec3 get_random_unit_vector_hemisphere() {
  double sin_theta = double_rand();
  double cos_theta = pow(1 - pow(sin_theta, 2), 0.5);
  double phi = double_rand() * 2 * M_PI;

  glm::vec3 v3_rand = glm::vec3(
    sin_theta * cos(phi), sin_theta * sin(phi), cos_theta
  );
  return v3_rand;
}

void print_vec3(const glm::vec3 &v) {
  printf("\n");
  printf("| %5.4f |\n", v.x);
  printf("| %5.4f |\n", v.y);
  printf("| %5.4f |\n", v.z);
  printf("\n");
}

glm::vec3 transform_vec3(const glm::mat4 &trans_matrix, const glm::vec3 &v) {
  glm::vec4 v_temp = glm::vec4(v.x, v.y, v.z, 1);
  v_temp = trans_matrix * v_temp;
  return glm::vec3(
    v_temp.x / v_temp.w, v_temp.y / v_temp.w, v_temp.z / v_temp.w);
}

double compute_distance(const glm::vec3 &v1, const glm::vec3 &v2) {
  glm::vec3 temp = v1 - v2;
  return pow(glm::dot(temp, temp), 0.5);
}

glm::mat3 rotate(const float degrees, const glm::vec3& axis) {
  glm::mat3 ret;
  glm::vec3 normaxis = glm::normalize(axis);
  float x = normaxis[0], y = normaxis[1], z = normaxis[2];
	float firstC = cos(degrees * M_PI / 180.0);
	float secondC = 1 - cos(degrees * M_PI / 180.0);
	float thirdC = sin(degrees * M_PI / 180.0);
  glm::mat3 firstMat = glm::mat3(firstC, 0, 0, 0, firstC, 0, 0, 0, firstC);
	glm::mat3 secondMat = glm::mat3(secondC * x * x, secondC * x * y, secondC * x * z,\
		                              secondC * x * y, secondC * y * y, secondC * y * z, \
		                              secondC * x * z, secondC * y * z, secondC * z * z);
	glm::mat3 thirdMat = glm::mat3(0, thirdC * z, thirdC * -y, thirdC * -z, 0, thirdC * x,\
		                             thirdC * y, thirdC * -x, 0);
  ret = firstMat + secondMat + thirdMat;
  return ret;
}

glm::mat4 scale(const double &sx, const double &sy, const double &sz)
{
  glm::mat4 ret;
  ret = glm::mat4(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
  return ret;
}

glm::mat4 translate(const float &tx, const float &ty, const float &tz)
{
  glm::mat4 ret;
  ret = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
  return ret;
}

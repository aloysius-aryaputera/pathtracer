#include "lib_scene.h"

Scene* create_scene_1() {

  Camera* my_camera = new Camera(
    glm::vec3(0, -15, 15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 45, 650, 500
  );

  vector<Primitive*> geom_array, additional_geom_array;
  vector<Light*> light_array;
  glm::mat4 trans_matrix;
  Material* material;
  std::vector<std::vector<glm::vec4>> plain_texture;
  std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array;

  material = new Material(
    glm::vec4(0.1, 0.1, 0.1, 1), glm::vec4(0.0, 0.0, 0.0, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(9.0, 8.0, 6.0, 1),
    glm::vec4(0.0, 0.0, 0.0, 1), 50, plain_texture
  );
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, -3, 11), 2.0, material, glm::mat4(1)
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0.1, 0.1, 0.1, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(.5, .5, .5, 1), 50, plain_texture
  );
  geom_array.push_back(new Triangle());
  trans_matrix = translate(0, 0, 0);
  parameter_array = prepare_triangle_parameters(
      glm::vec3(0, 15, 0), glm::vec3(-10, -9, 0), glm::vec3(10, -9, 0),
      glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0),
      material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  geom_array.push_back(new Triangle());
  trans_matrix = translate(0, 0, 0);
  parameter_array = prepare_triangle_parameters(
      glm::vec3(0, 15, 11), glm::vec3(10, -5, 11), glm::vec3(-10, -5, 11),
      glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0),
      material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0.1, 0.1, 0.1, 1), glm::vec4(1, 0, 0, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(.5, .25, .25, 1), 50, plain_texture
  );
  additional_geom_array = create_rectangle(
    glm::vec3(0, 15, 0), glm::vec3(0, 15, 30), glm::vec3(-10, -9, 30),
    glm::vec3(-10, -9, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0.1, 0.1, 0.1, 1), glm::vec4(0, 0, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(.25, .25, .5, 1), 50, plain_texture
  );
  additional_geom_array = create_rectangle(
    glm::vec3(0, 15, 0), glm::vec3(10, -9, 0), glm::vec3(10, -9, 30),
    glm::vec3(0, 15, 30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0.1, 0.1, 0.1, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    50, plain_texture
  );
  trans_matrix = translate(4, -5, 2);
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 2.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  for (int i = 0; i < 3; i++) {
    trans_matrix = translate(0, 2, .5) * \
      glm::mat4(rotate(120 * i, glm::vec3(0, 0, 1))) * \
      scale(3, 1.5, 1.0);
    material = new Material(
      glm::vec4(0.1, 0.1, 0.1, 1),
      glm::vec4(0, 1, 1, 1),
      glm::vec4(0, 0, 0, 1),
      glm::vec4(0, 0, 0, 1),
      glm::vec4(.25, .5, .5, 1),
      50, plain_texture
    );
    geom_array.push_back(new Sphere());
    parameter_array = prepare_sphere_parameters(
        glm::vec3(0, 0, 0), 1.0, material, trans_matrix
      );
    geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);
  }

  trans_matrix = translate(-3, -4, 5);
  additional_geom_array = create_box(
    glm::vec3(0, 0, 0), 0.5, 0.5, 8, material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);
  for (int i = 0; i < 10; i++) {
    material = new Material(
      glm::vec4(0.1, 0.1, 0.1, 1),
      glm::vec4(0, 0, 0, 0),
      glm::vec4(0, 0, 0, 1),
      glm::vec4((double)i / 10, 1.0 - ((double)i / 10), 0, 1),
      glm::vec4(.25 + .25 * i / 10, .5 - .25 * i / 10, .25, 1),
      50, plain_texture
    );
    trans_matrix = translate(-3, -4, 0.125 + i * 0.7) * \
      glm::mat4(rotate(45 + 9 * i, glm::vec3(0, 0, 1))) * \
      scale(1 - .5 * i / 10, 1 - .5 * i / 10, 1);
    additional_geom_array = create_box(
      glm::vec3(0, 0, 0), 3, 3, .5, material, trans_matrix
    );
    add_to_geom_array(geom_array, additional_geom_array);
  }

  material = new Material(
    glm::vec4(0.1, 0.1, 0.1, 1), glm::vec4(1, 0, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(.5, .25, .5, 1), 50, plain_texture
  );
  trans_matrix = translate(0, -6.5, 0) * \
    glm::mat4(rotate(30, glm::vec3(0, 0, 1))) * scale(2, 3, 6);
  additional_geom_array = create_rect_pyramid(
    glm::vec3(0, 0, 0), 1, 1, 1, material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  Scene* my_scene = new Scene(my_camera, geom_array, light_array);

  return my_scene;
}

Scene* create_scene_2() {

  Camera* my_camera = new Camera(
    glm::vec3(0, -15, 15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 45, 650, 500
  );

  vector<Primitive*> geom_array, additional_geom_array;
  vector<Light*> light_array;
  glm::mat4 trans_matrix;
  Material* material;
  std::vector<std::vector<glm::vec4>> oak_wood_texture = read_image(
    "texture/oak_wood.ppm");
  std::vector<std::vector<glm::vec4>> silver_wood_texture = read_image(
    "texture/silver_wood.ppm");
  std::vector<std::vector<glm::vec4>> brick_texture = read_image(
    "texture/bricks.ppm");
  std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array;

  trans_matrix = translate(0, -3, 16) * scale(3, 3, 1);
  material = new Material(
    glm::vec4(0, 0, 0, 1), glm::vec4(0.0, 0.0, 0.0, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(13.0, 12.0, 8.0, 1),
    glm::vec4(0.0, 0.0, 0.0, 1), 50
  );
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 1.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(.5, .5, .5, 1), 50, oak_wood_texture, 2, 2
  );
  geom_array.push_back(new Triangle());
  trans_matrix = translate(0, 0, 0);
  parameter_array = prepare_triangle_parameters(
      glm::vec3(0, 15, 0), glm::vec3(-13, -16, 0), glm::vec3(13, -16, 0),
      glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0),
      material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  geom_array.push_back(new Triangle());
  trans_matrix = translate(0, 0, 0);
  parameter_array = prepare_triangle_parameters(
      glm::vec3(0, 15, 16), glm::vec3(13, -16, 16), glm::vec3(-13, -16, 16),
      glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0),
      material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(.5, .5, .5, 1), 50, brick_texture, 4, 8
  );
  additional_geom_array = create_rectangle(
    glm::vec3(0, 15, 0), glm::vec3(0, 15, 30), glm::vec3(-13, -16, 30),
    glm::vec3(-13, -16, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0),
    glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  additional_geom_array = create_rectangle(
    glm::vec3(0, 15, 0), glm::vec3(13, -16, 0), glm::vec3(13, -16, 30),
    glm::vec3(0, 15, 30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  additional_geom_array = create_rectangle(
    glm::vec3(13, -16, 0), glm::vec3(-13, -16, 0), glm::vec3(-13, -16, 30),
    glm::vec3(13, -16, 30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    50
  );
  for (int i = 0; i < 3; i++) {
    trans_matrix = translate(0, 2, .5) * \
      glm::mat4(rotate(120 * i, glm::vec3(0, 0, 1))) * \
      scale(3, 1.5, 1.0);
    geom_array.push_back(new Sphere());
    parameter_array = prepare_sphere_parameters(
        glm::vec3(0, 0, 0), 1.0, material, trans_matrix
      );
    geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);
  }

  material = new Material(
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    50
  );
  trans_matrix = translate(-3, -4, 5);
  additional_geom_array = create_box(
    glm::vec3(0, 0, 0), 0.5, 0.5, 8, material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);
  for (int i = 0; i < 10; i++) {
    material = new Material(
      glm::vec4(0, 0, 0, 1),
      glm::vec4((double)i / 10, 1 - (double)i / 10, 0, 1),
      glm::vec4(0, 0, 0, 1),
      glm::vec4((double)i / 3.4, 3.0 - ((double)i / 3.4), 0, 1),
      glm::vec4(.25 + .25 * i / 10, .5 - .25 * i / 10, .25, 1),
      50
    );
    trans_matrix = translate(-3, -4, 0.125 + i * 0.7) * \
      glm::mat4(rotate(45 + 9 * i, glm::vec3(0, 0, 1))) * \
      scale(1 - .5 * i / 10, 1 - .5 * i / 10, 1);
    additional_geom_array = create_box(
      glm::vec3(0, 0, 0), 3, 3, .5, material, trans_matrix
    );
    add_to_geom_array(geom_array, additional_geom_array);
  }

  material = new Material(
    glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(.5, .5, .5, 1), 50, silver_wood_texture
  );
  trans_matrix = translate(0, -6.5, 0) * \
    glm::mat4(rotate(30, glm::vec3(0, 0, 1))) * scale(2, 3, 6);
  additional_geom_array = create_rect_pyramid(
    glm::vec3(0, 0, 0), 1, 1, 1, material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    50
  );
  trans_matrix = translate(4, -5, 2);
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 2.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0.1, 0.1, 3.0, 1),
    glm::vec4(0, 0, 0, 1),
    50
  );
  trans_matrix = translate(-5.5, -6.5, 1);
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 1.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  Scene* my_scene = new Scene(my_camera, geom_array, light_array);

  return my_scene;
}

Scene* create_scene_3() {

  Camera* my_camera = new Camera(
    glm::vec3(0, -13, 5), glm::vec3(0, 0, 3), glm::vec3(0, 1, 0), 45, 600, 600
  );

  std::vector<std::vector<glm::vec4>> blue_wood_texture = read_image(
    "texture/blue_wood.ppm");
  std::vector<std::vector<glm::vec4>> marble_texture = read_image(
    "texture/marble.ppm");
  std::vector<std::vector<glm::vec4>> green_marble_texture = read_image(
    "texture/green_marble.ppm");
  std::vector<std::vector<glm::vec4>> abstract_texture = read_image(
    "texture/abstract.ppm");
  std::vector<std::vector<glm::vec4>> marble_floor_texture = read_image(
    "texture/marble_floor.ppm");
  std::vector<std::vector<glm::vec4>> white_plaster_texture = read_image(
    "texture/white_plaster.ppm");
  std::vector<std::vector<glm::vec4>> red_plaster_texture = read_image(
    "texture/red_plaster.ppm");
  vector<Primitive*> geom_array, additional_geom_array;
  vector<Light*> light_array;
  glm::mat4 trans_matrix;
  Material* material;
  std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array;

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(0.0, 0.0, 0.0, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(20.0, 17.0, 15.0, 1),
    glm::vec4(0.0, 0.0, 0.0, 1), 50
  );
  trans_matrix = translate(0, -3, 8.5) * scale(1.5, 1.5, 1);
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 2.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(0.4, 0.4, 0.4, 1), 50, green_marble_texture, 3, 3
  );
  trans_matrix = translate(2, -2.5, 1.0);
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 1.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(0.4, 0.4, 0.4, 1), 50, marble_texture, 6, 6
  );
  trans_matrix = translate(-3, 3, 3);
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 3.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec4(0, 0, 0, 1),
    50
  );
  trans_matrix = translate(3, 1.5, 1.5) * \
    glm::mat4(rotate(30, glm::vec3(0, 0, 1)));
  additional_geom_array = create_box(
    glm::vec3(0, 0, 0), 3, 3, 3, material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(0.2, 0.2, 0.2, 1), 50, abstract_texture, 3, 3
  );
  trans_matrix = translate(-2, -2, .5) * glm::mat4(
    rotate(45, glm::vec3(0, 0, 1))) * scale(2.5, 1.5, 1);
  geom_array.push_back(new Sphere());
  parameter_array = prepare_sphere_parameters(
      glm::vec3(0, 0, 0), 1.0, material, trans_matrix
    );
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(0.3, 0.3, 0.3, 1), 50, blue_wood_texture, 3, 3
  );
  trans_matrix = translate(3, 1.5, 3.0) * \
    glm::mat4(rotate(30, glm::vec3(0, 0, 1))) * scale(1, 1, 3);
  additional_geom_array = create_rect_pyramid(
    glm::vec3(0, 0, 0), 1, 1, 1, material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(0.4, 0.4, 0.4, 1), 50, marble_floor_texture, 6, 6
  );
  additional_geom_array = create_rectangle(
    glm::vec3(6, 6, 0), glm::vec3(-6, 6, 0), glm::vec3(-6, -6, 0),
    glm::vec3(6, -6, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(0.4, 0.4, 0.4, 1), 50, white_plaster_texture, 3, 3
  );
  additional_geom_array = create_rectangle(
    glm::vec3(-6, -12, 8), glm::vec3(-6, 6, 8), glm::vec3(6, 6, 8),
    glm::vec3(6, -12, 8), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(0.0, 0.0, 0.0, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(10.0, 8.0, 4.0, 1),
    glm::vec4(0.0, 0.0, 0.0, 1), 50
  );
  additional_geom_array = create_box(
    glm::vec3(-6.0, -3, 8), 1, 18, .5, material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  additional_geom_array = create_box(
    glm::vec3(6.0, -3, 8), 1, 18, .5, material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  additional_geom_array = create_box(
    glm::vec3(0, 6.0, 8), 12, 1, .5, material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  material = new Material(
    glm::vec4(0.0, 0.0, 0.0, 1), glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1),
    glm::vec4(0.4, 0.4, 0.4, 1), 50, red_plaster_texture, 3, 3
  );
  additional_geom_array = create_rectangle(
    glm::vec3(6, 6, 0), glm::vec3(6, -12, 0), glm::vec3(6, -12, 8),
    glm::vec3(6, 6, 8), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  additional_geom_array = create_rectangle(
    glm::vec3(-6, -12, 0), glm::vec3(-6, 6, 0), glm::vec3(-6, 6, 8),
    glm::vec3(-6, -12, 8), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  additional_geom_array = create_rectangle(
    glm::vec3(-6, 6, 0), glm::vec3(6, 6, 0), glm::vec3(6, 6, 8),
    glm::vec3(-6, 6, 8), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, glm::mat4(1)
  );
  add_to_geom_array(geom_array, additional_geom_array);

  Scene* my_scene = new Scene(my_camera, geom_array, light_array);

  return my_scene;
}

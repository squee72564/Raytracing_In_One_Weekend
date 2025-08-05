#include <glm/glm.hpp>
#include <iostream>

#include "Ray.hpp"

void write_color(std::ostream& out, const glm::vec3& color)
{
    const auto& r = color.x;
    const auto& g = color.y;
    const auto& b = color.z;

    const int rbyte = static_cast<int>(255.99 * r);
    const int gbyte = static_cast<int>(255.99 * g);
    const int bbyte = static_cast<int>(255.99 * b);

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

bool is_hitting_sphere(const glm::vec3& center, float radius, const Ray& r)
{
    glm::vec3 oc = center - r.origin();

    auto a = glm::dot(r.direction(), r.direction());

    auto b = -2.0f * glm::dot(r.direction(), oc);

    auto c = glm::dot(oc, oc) - radius * radius;

    auto discriminant = b * b - 4.0f * a * c;

    return (discriminant >= 0);
}

glm::vec3 ray_color(const Ray& r)
{
    if (is_hitting_sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r)) {
        return glm::vec3(1.0f, 0.0f, 0.0f);
    }

    const glm::vec3 dir = r.direction();

    const glm::vec3 unit_direction = dir / static_cast<float>(dir.length());

    const auto a = 0.5f * (unit_direction.y + 1.0f);

    return (1.0f - a) * glm::vec3(1.0f, 1.0f, 1.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f); 
}

int main()
{
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    auto camera_center = glm::vec3{0.0f, 0.0f, 0.0f};

    // Calculate vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = glm::vec3(viewport_width, 0.0f, 0.0f);
    auto viewport_v = glm::vec3(0.0f, -viewport_height, 0.0f);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / static_cast<float>(image_width);
    auto pixel_delta_v = viewport_v / static_cast<float>(image_height);

    auto viewport_upper_left =
        camera_center
        - glm::vec3(0.0f, 0.0f, focal_length)
        - viewport_u / 2.0f
        - viewport_v / 2.0f;

    auto pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);


    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_height; ++i) {
        for (int j = 0; j < image_width; ++j) {
            auto pixel_center =
                pixel00_loc
                + (static_cast<float>(j) * pixel_delta_u)
                + (static_cast<float>(i) * pixel_delta_v);

            auto ray_direction = pixel_center - camera_center;

            Ray r{camera_center, ray_direction};

            glm::vec3 color = ray_color(r);

            write_color(std::cout, color);
        }
    }


    return 0;
}

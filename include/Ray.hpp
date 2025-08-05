#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

class Ray {
public:
    Ray() : origin_{}, direction_{} {}

    Ray(const glm::vec3& origin, const glm::vec3& direction)
        : origin_{origin}
        , direction_{direction}
    {}

    const glm::vec3 & origin() const noexcept { return origin_; }
    const glm::vec3 & direction() const noexcept { return direction_; }

    glm::vec3 at(float t) const {
        return origin_ + t * direction_;
    }

private:
    glm::vec3 origin_;
    glm::vec3 direction_;
};

#endif // RAY-HPP

//
// Created by Egor Lentarev on 12.01.2026.
//

#ifndef VECTHAR_MATERIAL_H
#define VECTHAR_MATERIAL_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

namespace vecthar {

struct Material {
    // --- Base color ---
    glm::vec4 baseColor = {1.0f, 1.0f, 1.0f, 1.0f};  // RGBA
    std::string baseColorTexturePath;                // path to texture (if exist)
    unsigned int baseColorTextureID = 0;             // loaded texture (0 = not)

    // --- PBR (optional, for the future) ---
    float metallic = 0.0f;
    float roughness = 1.0f;
    std::string metallicRoughnessTexturePath;
    unsigned int metallicRoughnessTextureID = 0;

    // --- Convenient methods ---
    bool hasBaseColorTexture() const { return baseColorTextureID != 0; }
    bool isUnlit() const { return !hasBaseColorTexture() && baseColor.a == 0.0f; }  // example
};

}  // namespace vecthar

#endif  // VECTHAR_MATERIAL_H
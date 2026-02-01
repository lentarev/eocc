//
// Created by Egor Lentarev on 28.01.2026.
//

#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include <vecthar/assets/model/ModelLoader.h>
#include <vecthar/assets/mesh/structures/MeshData.h>  // убедись, что подключено
#include <stdexcept>
#include <cstring>
#include <glm/vec4.hpp>

namespace vecthar {

Model ModelLoader::loadFromFile(const std::string& filePath) {
    cgltf_options options = {};
    cgltf_data* data = nullptr;
    cgltf_result result = cgltf_parse_file(&options, filePath.c_str(), &data);

    if (result != cgltf_result_success) {
        throw std::runtime_error("ModelLoader: failed to parse glTF file");
    }

    result = cgltf_load_buffers(&options, data, filePath.c_str());
    if (result != cgltf_result_success) {
        cgltf_free(data);
        throw std::runtime_error("ModelLoader: failed to load buffers");
    }

    Model model;

    // Проходим по всем мешам (логическим объектам)
    for (size_t i = 0; i < data->meshes_count; ++i) {
        const cgltf_mesh& mesh = data->meshes[i];

        // Обрабатываем каждый примитив ОТДЕЛЬНО
        for (size_t p = 0; p < mesh.primitives_count; ++p) {
            const cgltf_primitive& prim = mesh.primitives[p];

            if (prim.type != cgltf_primitive_type_triangles) {
                continue;
            }

            // --- Создаём MeshData ДЛЯ ОДНОГО ПРИМИТИВА ---
            MeshData meshData;

            // --- Находим атрибуты ---
            const cgltf_attribute* pos_attr = nullptr;
            const cgltf_attribute* nrm_attr = nullptr;
            const cgltf_attribute* uv_attr = nullptr;

            for (size_t a = 0; a < prim.attributes_count; ++a) {
                const cgltf_attribute& attr = prim.attributes[a];
                if (attr.type == cgltf_attribute_type_position) {
                    pos_attr = &attr;
                } else if (attr.type == cgltf_attribute_type_normal) {
                    nrm_attr = &attr;
                } else if (attr.type == cgltf_attribute_type_texcoord && attr.index == 0) {
                    uv_attr = &attr;
                }
            }

            // --- Загружаем позиции ---
            if (pos_attr) {
                const float* src = (const float*)pos_attr->data->buffer_view->buffer->data;
                size_t count = pos_attr->data->count;
                size_t offset = pos_attr->data->buffer_view->offset + pos_attr->data->offset;
                src = (const float*)((const char*)src + offset);
                meshData.positions.assign(src, src + count * 3);
            }

            // --- Загружаем нормали ---
            if (nrm_attr) {
                const float* src = (const float*)nrm_attr->data->buffer_view->buffer->data;
                size_t count = nrm_attr->data->count;
                size_t offset = nrm_attr->data->buffer_view->offset + nrm_attr->data->offset;
                src = (const float*)((const char*)src + offset);
                meshData.normals.assign(src, src + count * 3);
            }

            // --- Загружаем UV ---
            if (uv_attr) {
                const float* src = (const float*)uv_attr->data->buffer_view->buffer->data;
                size_t count = uv_attr->data->count;
                size_t offset = uv_attr->data->buffer_view->offset + uv_attr->data->offset;
                src = (const float*)((const char*)src + offset);
                meshData.texCoords.assign(src, src + count * 2);
            }

            // --- Загружаем индексы ---
            if (prim.indices) {
                size_t index_count = prim.indices->count;
                meshData.indices.resize(index_count);

                const void* src = prim.indices->buffer_view->buffer->data;
                size_t offset = prim.indices->buffer_view->offset + prim.indices->offset;
                src = (const char*)src + offset;

                if (prim.indices->component_type == cgltf_component_type_r_16u) {
                    const uint16_t* src16 = (const uint16_t*)src;
                    for (size_t i = 0; i < index_count; ++i) {
                        meshData.indices[i] = static_cast<unsigned int>(src16[i]);
                    }
                } else if (prim.indices->component_type == cgltf_component_type_r_32u) {
                    const uint32_t* src32 = (const uint32_t*)src;
                    for (size_t i = 0; i < index_count; ++i) {
                        meshData.indices[i] = src32[i];
                    }
                } else {
                    const uint8_t* src8 = (const uint8_t*)src;
                    for (size_t i = 0; i < index_count; ++i) {
                        meshData.indices[i] = static_cast<unsigned int>(src8[i]);
                    }
                }
            }

            // --- Читаем материал примитива ---
            if (prim.material) {
                const cgltf_material& mat = *prim.material;
                if (mat.has_pbr_metallic_roughness) {
                    const cgltf_pbr_metallic_roughness& pbr = mat.pbr_metallic_roughness;
                    meshData.material.baseColor =
                        glm::vec4(pbr.base_color_factor[0], pbr.base_color_factor[1], pbr.base_color_factor[2], pbr.base_color_factor[3]);
                    // Позже добавишь текстуры
                }
            }
            // Если материала нет — material остаётся белым по умолчанию

            // --- Создаём Mesh и добавляем в модель ---
            model.meshes.push_back(std::make_unique<Mesh>(meshData));
        }
    }

    cgltf_free(data);
    return model;
}

}  // namespace vecthar

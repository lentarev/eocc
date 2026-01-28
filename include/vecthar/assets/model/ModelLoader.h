//
// Created by Egor Lentarev on 28.01.2026.
//

#ifndef VECTHAR_MODEL_LOADER_H
#define VECTHAR_MODEL_LOADER_H

#include <string>
#include <vecthar/assets/model/structures/Model.h>

namespace vecthar {

class ModelLoader {
private:
    ModelLoader() = delete;  //  Disable creation of instances.

public:
    static Model loadFromFile(const std::string& filePath);
};

}  // namespace vecthar

#endif  // VECTHAR_MODEL_LOADER_H
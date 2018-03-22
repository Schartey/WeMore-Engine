#include "VSkybox.h"

#include "../../Utils/Assimp/VAssimpUtils.h"

#include "glm/gtx/transform.hpp"

VSkybox::VSkybox(VScene* Scene, std::string Name) : VSceneObject(Scene, Name)
{
}

VSkybox::~VSkybox()
{
}

#include <Spark/SPARK_Core.h>
#include "SPK_Urho3D_Renderer.h"

namespace SPK {
namespace URHO {

IUrho3DRenderer::IUrho3DRenderer(Urho3D::Context* context, bool NEEDS_DATASET) :
    Renderer(NEEDS_DATASET)
{
    _context = context;
    _camera = nullptr;
    _material = nullptr;
}

void IUrho3DRenderer::setBlendMode(BlendMode blendMode)
{
    switch(blendMode)
    {
    case BLEND_MODE_NONE :
        break;

    case BLEND_MODE_ADD :
        break;

    case BLEND_MODE_ALPHA :
        break;

    default :
        SPK_LOG_WARNING("IUrho3DRenderer::setBlendMode(BlendMode) - Unsupported blending mode. Nothing happens");
        break;
    }
}

void IUrho3DRenderer::updateView(Urho3D::Camera* camera)
{
    _camera = camera;
}

Urho3D::Material* IUrho3DRenderer::getMaterial()
{
    return _material;
}
void IUrho3DRenderer::setMaterial(Urho3D::Material* material)
{
    _material =  material;
}


}}

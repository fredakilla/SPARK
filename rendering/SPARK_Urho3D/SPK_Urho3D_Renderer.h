#ifndef H_SPK_URHO3D_RENDERER
#define H_SPK_URHO3D_RENDERER

#include "SPK_Urho3D_DEF.h"
#include "SPK_Urho3D_Buffer.h"

#include <Spark/Core/SPK_Renderer.h>

#include "../Graphics/Camera.h"
#include "../Graphics/Material.h"

namespace SPK {
namespace URHO {

/// The base renderer for all Urho3D renderers
class SPK_URHO_PREFIX IUrho3DRenderer : public Renderer
{
public :

    /// Destructor of IUrho3DRenderer
    virtual ~IUrho3DRenderer() {}

    virtual void setBlendMode(BlendMode blendMode) override;

    void updateView(Urho3D::Camera* camera);

    Urho3D::Material* getMaterial();
    void setMaterial(Urho3D::Material* material);

protected :

    IUrho3DRenderer(Urho3D::Context *context, bool NEEDS_DATASET = false);
    Urho3D::Context*    _context;
    Urho3D::Camera*     _camera;
    Urho3D::SharedPtr<Urho3D::Material>   _material;
};


}}

#endif

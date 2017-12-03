//#include <SPARK_Core.h>
#include "SPK_Urho3D_Buffer.h"

namespace SPK {
namespace URHO {

IUrho3DBuffer::IUrho3DBuffer(Urho3D::Context* context, size_t nbParticles, size_t nbVerticesPerParticle, size_t nbIndicesPerParticle) :
    RenderBuffer()
  , _context(context)
{
    SPK_ASSERT(nbParticles > 0, "IUrho3DBuffer::IUrho3DBuffer - The number of particles cannot be 0");
    SPK_ASSERT(nbVerticesPerParticle > 0, "IUrho3DBuffer::IUrho3DBuffer - The number of vertices per particle cannot be 0");
    SPK_ASSERT(nbIndicesPerParticle > 0, "IUrho3DBuffer::IUrho3DBuffer - The number of indices per particle cannot be 0");

    _vb = new Urho3D::VertexBuffer(_context);
    _ib = new Urho3D::IndexBuffer(_context);
    _geometry = new Urho3D::Geometry(_context);

    _ib->SetShadowed(true);
    _vb->SetShadowed(true);

    _geometry->SetVertexBuffer(0, _vb);
    _geometry->SetIndexBuffer(_ib);
}

IUrho3DBuffer::~IUrho3DBuffer()
{

}

}}

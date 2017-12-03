#include "SPK_Urho3D_DEF.h"
#include "SPK_Urho3D_QuadRenderer.h"
#include <Spark/Core/IO/SPK_IO_Manager.h>


namespace SPK {
namespace URHO {

    Urho3DContext::Urho3DContext()
    {       
    }

    Urho3DContext& Urho3DContext::get()
    {
        static Urho3DContext instance;
        return instance;
    }    

    void Urho3DContext::registerUrhoContext(Urho3D::Context* context)
    {
        SPK_ASSERT(context, "[registerUrhoContext] : Urho3D context is null.");
        urhoContext = context;       
    }

    Urho3D::Context* Urho3DContext::getUrhoContext()
    {
        SPK_ASSERT(urhoContext, "[getUrhoContext] : Urho3D Context is null, use registerUrhoContext");
        return urhoContext;
    }



    //////////////////////////
    // Conversion functions //
    //////////////////////////


    inline Urho3D::Vector3 spk2urho(const Vector3D& v)
    {
        return Urho3D::Vector3(v.x, v.y, v.z);
    }

    inline SPK::Vector3D urho2spk(const Urho3D::Vector3& v)
    {
        return Vector3D(v.x_, v.y_, v.z_);
    }

    inline Urho3D::Color spk2urho(unsigned char a, unsigned char  r, unsigned char  g, unsigned char  b)
    {
        return Urho3D::Color(r,g,b,a);
    }

    inline const Urho3D::Color spk2urho(SPK::Color c)
    {
        return Urho3D::Color(c.r, c.g, c.g, c.a);
    }

}}

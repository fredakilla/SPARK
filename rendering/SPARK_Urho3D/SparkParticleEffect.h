#pragma once

#include "../Graphics/GraphicsDefs.h"
#include "../Resource/Resource.h"

#include <Spark/SPARK_Core.h>
#include "SPARK_URHO3D.h"

namespace Urho3D
{

//class Material;
class XMLFile;
class XMLElement;

/// %Particle effect definition.
class URHO3D_API SparkParticleEffect : public Resource
{
    URHO3D_OBJECT(SparkParticleEffect, Resource);

public:
    /// Construct.
    SparkParticleEffect(Context* context);
    /// Destruct.
    virtual ~SparkParticleEffect() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad() override;
    /// Save resource. Return true if successful.
    bool Save(const String &filename) const;

    /// Helper function for loading SPK files.
    bool BeginLoadSPK(Deserializer& source);
    /// Get Spark particle system loaded
    const SPK::Ref<SPK::System> GetSystem() const;
    /// Clone the particle system.
    SharedPtr<SparkParticleEffect> Clone(const String& cloneName = String::EMPTY) const;

    /// Manually set spark particle system
    void SetSystem(SPK::Ref<SPK::System> spkSystem);

private:
    /// Search file in resources directories and return file path prefixed with resource dir or return empty string if not exists
    String GetFixedPath();

private:
    /// loaded spark particle system
    SPK::Ref<SPK::System> loadedSystem_;

};

}

#include "UrhoSparkSystem.h"


#include "../Resource/ResourceCache.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"

namespace Urho3D
{


SparkParticleEffect::SparkParticleEffect(Context* context) :
    Resource(context)
{
    loadedSystem_.reset();
}

SparkParticleEffect::~SparkParticleEffect()
{
}

void SparkParticleEffect::RegisterObject(Context* context)
{
    context->RegisterFactory<SparkParticleEffect>();

    // Register Urho3D context inside Spark.
    SPK::URHO::Urho3DContext::get().registerUrhoContext(context);
}

bool SparkParticleEffect::BeginLoad(Deserializer& source)
{
    String extension = GetExtension(source.GetName());

    bool success = false;

    if (extension == ".spk")
    {
        // Check ID
        String fileID = source.ReadFileID();
        if (fileID != "SPK")
        {
            URHO3D_LOGERROR(source.GetName() + " is not a valid spk file");
            return false;
        }
    }

    success = BeginLoadSPK(source);
    if (success)
        return true;

    return false;
}

bool SparkParticleEffect::EndLoad()
{
    if(!loadedSystem_)
    {
       return false;
    }

    return true;
}

bool SparkParticleEffect::BeginLoadSPK(Deserializer& source)
{
    // Get relative file path prefixed wuth resource dir or empty if not exists
    String fixedPath = GetFixedPath();

    // if file exists, load file from spark IO
    if(fixedPath != String::EMPTY)
    {
        loadedSystem_ = SPK::IO::IOManager::get().load(fixedPath.CString());

        if(loadedSystem_)
            return true;
    }

    return false;
}

String SparkParticleEffect::GetFixedPath()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    for(unsigned i=0; i<cache->GetResourceDirs().Size(); ++i)
    {
        String dir = cache->GetResourceDirs()[i];
        String path = dir + GetName();

        if(GetSubsystem<FileSystem>()->FileExists(path))
        {
            return path;
        }
    }

    return String::EMPTY;
}

bool SparkParticleEffect::Save(const String& filename) const
{
    if(loadedSystem_)
    {
        return SPK::IO::IOManager::get().save(filename.CString(), loadedSystem_);
    }

    return false;
}

const SPK::Ref<SPK::System> SparkParticleEffect::GetSystem() const
{
    return loadedSystem_;
}

SharedPtr<SparkParticleEffect> SparkParticleEffect::Clone(const String& cloneName) const
{
    return 0;
}

void SparkParticleEffect::SetSystem(SPK::Ref<SPK::System> spkSystem)
{
    loadedSystem_ = spkSystem; ////SPK::SPKObject::copy(spkSystem);
}



}

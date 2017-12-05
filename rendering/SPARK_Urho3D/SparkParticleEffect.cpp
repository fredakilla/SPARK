//
// Copyright (c) 2008-2017 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Resource/ResourceCache.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"

#include "SparkParticleEffect.h"
#include "SPK_Urho3D_DEF.h"

#include "../DebugNew.h"

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
    // Spark has is own serialisation system, used to load and save .xml or .spk files effects.
    // To use it inside Urho3D resources directories, we need to prefix filenames.

    // Get relative file path prefixed with resource dir or empty if not exists
    String fixedPath = GetFixedPath();

    // if file exists, load file from spark IO
    if(fixedPath != String::EMPTY)
    {
        loadedSystem_ = SPK::IO::IOManager::get().load(fixedPath.CString());

        if(loadedSystem_)
            return true;
    }
    else
    {
        // file not found.
        URHO3D_LOGERROR(source.GetName() + " not found. Path = : " + fixedPath);
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
    loadedSystem_ = spkSystem;
}

}

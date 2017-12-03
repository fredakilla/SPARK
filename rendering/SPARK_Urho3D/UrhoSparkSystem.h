#ifndef H_SPK_URHOSPARKSYSTEM
#define H_SPK_URHOSPARKSYSTEM

#include <Spark/SPARK_Core.h>
#include "SPARK_URHO3D.h"

namespace Urho3D {

#include "../Graphics/Drawable.h"

/// Drawable component that draw a spark particle system.
class URHO3D_API SparkParticle : public Drawable
{
    URHO3D_OBJECT(SparkParticle, Drawable);

public:
    /// Construct.
    SparkParticle(Context* context);
    /// Destruct.
    virtual ~SparkParticle() override;
    /// Register object factory.
    static void RegisterObject(Context* context);
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled() override;
    /// Update before octree reinsertion. Is called from a main thread.
    virtual void Update(const FrameInfo &frame) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame) override;
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame) override;
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType() override;

    /// Mark for bounding box and vertex buffer update. Call after modifying the particles.
    void Commit();
    /// Set whether to update when particles are not visible.
    void SetUpdateInvisible(bool enable);
    /// Return whether to update when particles are not visible.
    bool GetUpdateInvisible() const { return updateInvisible_; }

    /// Set SPARK particle system
    void SetSystem(SPK::Ref<SPK::System> system);
    /// Get SPARK particle system
    const SPK::Ref<SPK::System> GetSystem() const { return _system; }

    /// Set SPARK particle system from SparkEffect ressource
    void SetEffect(SparkParticleEffect *sparkEffect);


    /// Set model attribute.
    void SetEffectAttr(const ResourceRef& value);
    /// Return model attribute.
    ResourceRef GetEffectAttr() const;

protected:
    /// Handle node being assigned.
    virtual void OnSceneSet(Scene* scene) override;
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate() override;
    /// Mark vertex buffer to need an update.
    void MarkPositionsDirty();

    /// Particles sorted flag.
    bool sorted_;
    /// Animation LOD bias.
    float animationLodBias_;
    /// Animation LOD timer.
    float animationLodTimer_;

private:

    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Resize vertex and index buffers.
    void UpdateBufferSize();
    /// Rewrite vertex buffer.
    void UpdateVertexBuffer(const FrameInfo& frame);
    /// Update particles (called by UpdateBatches())
    void UpdateParticles();

    /// Transform matrices for position and orientation.
    Matrix3x4 transform_;
    /// Buffers need resize flag.
    bool bufferSizeDirty_;
    /// Vertex buffer needs rewrite flag.
    bool bufferDirty_;

    /// Last scene timestep.
    float lastTimeStep_;
    /// Rendering framenumber on which was last updated.
    unsigned lastUpdateFrameNumber_;
    /// Need update flag.
    bool needUpdate_;
    /// Previous offset to camera for determining whether sorting is necessary.
    Vector3 previousOffset_;
    /// Force update flag (ignore animation LOD momentarily.)
    bool forceUpdate_;
    /// Update when invisible flag.
    bool updateInvisible_;

    /// Spark particle system
    SPK::Ref<SPK::System>  _system;
    /// Flag used internally to test if it is the first time we render the particles
    bool firstRenderSet_;

    /// spark effect
    SharedPtr<SparkParticleEffect> sparkEffect_;
};


}

#endif




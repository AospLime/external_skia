/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "GrBackendSurface.h"
#include "GrClip.h"
#include "GrContextOptions.h"
#include "GrContextPriv.h"
#include "GrDrawOpAtlas.h"
#include "GrDrawingManager.h"
#include "GrGpu.h"
#include "GrGpuResourceCacheAccess.h"
#include "GrMemoryPool.h"
#include "GrRenderTargetContext.h"
#include "GrRenderTargetContextPriv.h"
#include "GrRenderTargetProxy.h"
#include "GrResourceCache.h"
#include "GrSemaphore.h"
#include "GrSurfaceContextPriv.h"
#include "GrTexture.h"
#include "SkGr.h"
#include "SkImage_Gpu.h"
#include "SkMathPriv.h"
#include "SkString.h"
#include "SkTo.h"
#include "ccpr/GrCoverageCountingPathRenderer.h"
#include "ccpr/GrCCPathCache.h"
#include "ops/GrMeshDrawOp.h"
#include "text/GrStrikeCache.h"
#include "text/GrTextBlobCache.h"

#include <algorithm>

bool GrSurfaceProxy::isWrapped_ForTesting() const {
    return SkToBool(fTarget);
}

bool GrRenderTargetContext::isWrapped_ForTesting() const {
    return fRenderTargetProxy->isWrapped_ForTesting();
}

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

void GrResourceCache::changeTimestamp(uint32_t newTimestamp) { fTimestamp = newTimestamp; }

#ifdef SK_DEBUG
int GrResourceCache::countUniqueKeysWithTag(const char* tag) const {
    int count = 0;
    UniqueHash::ConstIter iter(&fUniqueHash);
    while (!iter.done()) {
        if (0 == strcmp(tag, (*iter).getUniqueKey().tag())) {
            ++count;
        }
        ++iter;
    }
    return count;
}
#endif

///////////////////////////////////////////////////////////////////////////////

#define ASSERT_SINGLE_OWNER \
    SkDEBUGCODE(GrSingleOwner::AutoEnforce debug_SingleOwner(fRenderTargetContext->singleOwner());)


uint32_t GrRenderTargetContextPriv::testingOnly_getOpListID() {
    return fRenderTargetContext->getOpList()->uniqueID();
}

void GrRenderTargetContextPriv::testingOnly_addDrawOp(std::unique_ptr<GrDrawOp> op) {
    this->testingOnly_addDrawOp(GrNoClip(), std::move(op));
}

void GrRenderTargetContextPriv::testingOnly_addDrawOp(
        const GrClip& clip,
        std::unique_ptr<GrDrawOp> op,
        const std::function<GrRenderTargetContext::WillAddOpFn>& willAddFn) {
    ASSERT_SINGLE_OWNER
    if (fRenderTargetContext->drawingManager()->wasAbandoned()) {
        fRenderTargetContext->fContext->priv().opMemoryPool()->release(std::move(op));
        return;
    }
    SkDEBUGCODE(fRenderTargetContext->validate());
    GR_AUDIT_TRAIL_AUTO_FRAME(fRenderTargetContext->fAuditTrail,
                              "GrRenderTargetContext::testingOnly_addDrawOp");
    fRenderTargetContext->addDrawOp(clip, std::move(op), willAddFn);
}

#undef ASSERT_SINGLE_OWNER

///////////////////////////////////////////////////////////////////////////////

GrInternalSurfaceFlags GrSurfaceProxy::testingOnly_getFlags() const {
    return fSurfaceFlags;
}

//////////////////////////////////////////////////////////////////////////////

void GrCoverageCountingPathRenderer::testingOnly_drawPathDirectly(const DrawPathArgs& args) {
    // Call onDrawPath() directly: We want to test paths that might fail onCanDrawPath() simply for
    // performance reasons, and GrPathRenderer::drawPath() assert that this call returns true.
    // The test is responsible to not draw any paths that CCPR is not actually capable of.
    this->onDrawPath(args);
}

const GrCCPerFlushResources*
GrCoverageCountingPathRenderer::testingOnly_getCurrentFlushResources() {
    SkASSERT(fFlushing);
    if (fFlushingPaths.empty()) {
        return nullptr;
    }
    // All pending paths should share the same resources.
    const GrCCPerFlushResources* resources = fFlushingPaths.front()->fFlushResources.get();
#ifdef SK_DEBUG
    for (const auto& flushingPaths : fFlushingPaths) {
        SkASSERT(flushingPaths->fFlushResources.get() == resources);
    }
#endif
    return resources;
}

const GrCCPathCache* GrCoverageCountingPathRenderer::testingOnly_getPathCache() const {
    return fPathCache.get();
}

const GrTexture* GrCCPerFlushResources::testingOnly_frontCopyAtlasTexture() const {
    if (fCopyAtlasStack.empty()) {
        return nullptr;
    }
    const GrTextureProxy* proxy = fCopyAtlasStack.front().textureProxy();
    return (proxy) ? proxy->peekTexture() : nullptr;
}

const GrTexture* GrCCPerFlushResources::testingOnly_frontRenderedAtlasTexture() const {
    if (fRenderedAtlasStack.empty()) {
        return nullptr;
    }
    const GrTextureProxy* proxy = fRenderedAtlasStack.front().textureProxy();
    return (proxy) ? proxy->peekTexture() : nullptr;
}

const SkTHashTable<GrCCPathCache::HashNode, const GrCCPathCache::Key&>&
GrCCPathCache::testingOnly_getHashTable() const {
    return fHashTable;
}

const SkTInternalLList<GrCCPathCacheEntry>& GrCCPathCache::testingOnly_getLRU() const {
    return fLRU;
}

int GrCCPathCacheEntry::testingOnly_peekOnFlushRefCnt() const { return fOnFlushRefCnt; }

int GrCCCachedAtlas::testingOnly_peekOnFlushRefCnt() const { return fOnFlushRefCnt; }

//////////////////////////////////////////////////////////////////////////////

#define DRAW_OP_TEST_EXTERN(Op) \
    extern std::unique_ptr<GrDrawOp> Op##__Test(GrPaint&&, SkRandom*, GrContext*, GrFSAAType)
#define DRAW_OP_TEST_ENTRY(Op) Op##__Test

DRAW_OP_TEST_EXTERN(AAConvexPathOp);
DRAW_OP_TEST_EXTERN(AAFlatteningConvexPathOp);
DRAW_OP_TEST_EXTERN(AAHairlineOp);
DRAW_OP_TEST_EXTERN(AAStrokeRectOp);
DRAW_OP_TEST_EXTERN(CircleOp);
DRAW_OP_TEST_EXTERN(DashOp);
DRAW_OP_TEST_EXTERN(DefaultPathOp);
DRAW_OP_TEST_EXTERN(DIEllipseOp);
DRAW_OP_TEST_EXTERN(EllipseOp);
DRAW_OP_TEST_EXTERN(FillRectOp);
DRAW_OP_TEST_EXTERN(GrAtlasTextOp);
DRAW_OP_TEST_EXTERN(GrDrawAtlasOp);
DRAW_OP_TEST_EXTERN(GrDrawVerticesOp);
DRAW_OP_TEST_EXTERN(NonAALatticeOp);
DRAW_OP_TEST_EXTERN(NonAAStrokeRectOp);
DRAW_OP_TEST_EXTERN(ShadowRRectOp);
DRAW_OP_TEST_EXTERN(SmallPathOp);
DRAW_OP_TEST_EXTERN(RegionOp);
DRAW_OP_TEST_EXTERN(RRectOp);
DRAW_OP_TEST_EXTERN(TesselatingPathOp);
DRAW_OP_TEST_EXTERN(TextureOp);

void GrDrawRandomOp(SkRandom* random, GrRenderTargetContext* renderTargetContext, GrPaint&& paint) {
    GrContext* context = renderTargetContext->surfPriv().getContext();
    using MakeDrawOpFn = std::unique_ptr<GrDrawOp>(GrPaint&&, SkRandom*, GrContext*, GrFSAAType);
    static constexpr MakeDrawOpFn* gFactories[] = {
            DRAW_OP_TEST_ENTRY(AAConvexPathOp),
            DRAW_OP_TEST_ENTRY(AAFlatteningConvexPathOp),
            DRAW_OP_TEST_ENTRY(AAHairlineOp),
            DRAW_OP_TEST_ENTRY(AAStrokeRectOp),
            DRAW_OP_TEST_ENTRY(CircleOp),
            DRAW_OP_TEST_ENTRY(DashOp),
            DRAW_OP_TEST_ENTRY(DefaultPathOp),
            DRAW_OP_TEST_ENTRY(DIEllipseOp),
            DRAW_OP_TEST_ENTRY(EllipseOp),
            DRAW_OP_TEST_ENTRY(FillRectOp),
            DRAW_OP_TEST_ENTRY(GrAtlasTextOp),
            DRAW_OP_TEST_ENTRY(GrDrawAtlasOp),
            DRAW_OP_TEST_ENTRY(GrDrawVerticesOp),
            DRAW_OP_TEST_ENTRY(NonAALatticeOp),
            DRAW_OP_TEST_ENTRY(NonAAStrokeRectOp),
            DRAW_OP_TEST_ENTRY(ShadowRRectOp),
            DRAW_OP_TEST_ENTRY(SmallPathOp),
            DRAW_OP_TEST_ENTRY(RegionOp),
            DRAW_OP_TEST_ENTRY(RRectOp),
            DRAW_OP_TEST_ENTRY(TesselatingPathOp),
            DRAW_OP_TEST_ENTRY(TextureOp),
    };

    static constexpr size_t kTotal = SK_ARRAY_COUNT(gFactories);
    uint32_t index = random->nextULessThan(static_cast<uint32_t>(kTotal));
    auto op = gFactories[index](
            std::move(paint), random, context, renderTargetContext->fsaaType());
    SkASSERT(op);
    renderTargetContext->priv().testingOnly_addDrawOp(std::move(op));
}

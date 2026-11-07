#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>

struct OrthoProjectionSync;

// Address: 0x02A05A9C
// Builds mViewProj at +0x44. Course tile draws negate top and bottom before this call, so element 5 (vertical scale) is negated.
sead::Matrix44f* OrthoProjection_syncViewProj(OrthoProjectionSync* projection);

// Address: 0x02AA56EC
void ModelMtxUpload_calcViewFromModelEx(void* model_ex, s32 view_index);

// Address: 0x02AA56F4
// Writes the shape matrix block. A rigid one-bone draw, such as a player head, uses this block. Shape byte +0x16 is 0.
void ModelMtxUpload_uploadShapeBlockMatrices(void* model_ex, s32 view_index);

// Address: 0x02AAAD18
// Writes the skeleton uniform block from the world matrices at skeleton+0x10, multiplied by the matrix at 0x101B7750.
// The block sits at skeleton+0x18. Its data pointer is the word at +0x18 and its size is the word at +0x1C.
void ModelMtxUpload_calcView(void* model_obj, s32 view_index);

// Address: 0x02AA6FDC
void ModelMtxUpload_writeShapeEntry(void* entry, s32 param_4, void* dst_mtx, s32 view_index);

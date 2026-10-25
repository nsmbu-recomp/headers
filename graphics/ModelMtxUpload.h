#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>

struct OrthoProjectionSync;

// Address: 0x02A05A9C
sead::Matrix44f* OrthoProjection_syncViewProj(OrthoProjectionSync* projection);

// Address: 0x02AA56EC
void ModelMtxUpload_calcViewFromModelEx(void* model_ex, s32 view_index);

// Address: 0x02AA56F4
void ModelMtxUpload_uploadShapeBlockMatrices(void* model_ex, s32 view_index);

// Address: 0x02AAAD18
void ModelMtxUpload_calcView(void* model_obj, s32 view_index);

// Address: 0x02AA6FDC
void ModelMtxUpload_writeShapeEntry(void* entry, s32 param_4, void* dst_mtx, s32 view_index);

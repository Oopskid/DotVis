#define X_THREADS 1
#define Y_THREADS 1
#define Z_THREADS 1

#include "RayCommon.hlsli"

struct RayQType
{
    Ray ray;
};

// Static ray information (in order of initiation, important for query indexing)
RWStructuredBuffer<RayQType> raysRW : register(u0);

RWStructuredBuffer<RayHit> hitOut : register(u1);

RWStructuredBuffer<float4> tex : register(u0);

[numthreads(X_THREADS, Y_THREADS, Z_THREADS)]
void main(uint3 gid : SV_GroupID, uint3 tid : SV_DispatchThreadID)
{
    uint g = tid.x + tid.y * 1000;
    tex[g] = float4(0, 1, 1, 1);
}
#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.f;

    float4 worldPosition = mul(In.Pos, WorldMatrix);
    float4 viewPosition = mul(worldPosition, ViewMatrix);
    float4 projPosition = mul(viewPosition, ProjectionMatrix);

    Out.WorldPos = worldPosition.xyz;
    Out.Pos = projPosition;
    Out.Color = In.Color;
    Out.UV = In.UV;

    return Out;
}
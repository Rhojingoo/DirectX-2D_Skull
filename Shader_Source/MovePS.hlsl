#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

cbuffer Time: register(b3)
{
    int type;
    float3 mTime;
}


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);

    return color;
}
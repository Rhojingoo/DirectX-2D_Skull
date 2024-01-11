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


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    float2 uv = In.UV;

    color = albedoTexture.Sample(anisotropicSampler, uv);

    // HP 백분율 계산
    float hpPercentage = Damage.y / Damage.x;
    if (uv.x > hpPercentage)
    {
        color.a = 0;
    }

    return color;
}
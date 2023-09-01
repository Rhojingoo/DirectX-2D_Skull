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
    // float4 color = (float4) 0.0f;

    //float2 uv = In.UV;
    //color = albedoTexture.Sample(anisotropicSampler, uv);

    //// HP 바의 너비를 조절합니다.
    //// Damage.x는 현재 HP, Damage.y는 피해량입니다.
    //float hpPercentage = (Damage.x - Damage.y) / Damage.x;
    //if (uv.x > hpPercentage)
    //{
    //    color.a = 0;
    //}

    //return color;


    float4 color = (float4) 0.0f;    
     
    float2 uv =In.UV;
    color = albedoTexture.Sample(anisotropicSampler, uv);

    return color;
}
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

#define moveX Time.x
#define moveY Time.y
float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;    
     
    float2 uv =In.UV;
    uv.x += Time.y;

    color = albedoTexture.Sample(anisotropicSampler, uv);

    return color;
}
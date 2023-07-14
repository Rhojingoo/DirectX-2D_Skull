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
    //float4 color = (float4)0.0f;
    ////color.r = 1.0f;
    ////color.b = 1.0f;
    //
    //color = albedoTexture.Sample(anisotropicSampler, In.UV);

    float4 color = (float4)0.0f;
    //color.r = 1.0f;
    //color.b = 1.0f;

    //if (In.UV.y < 0.2f)
    //{
    //    discard;
    //}
    //else
    //{
    //    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    //}
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    if (color.a <= 0.0f)
        discard;

    return color;
}
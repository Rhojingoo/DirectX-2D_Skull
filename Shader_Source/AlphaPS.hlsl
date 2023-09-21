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

#define moveX Alpha.x
#define moveY Alpha.y
#define moveZ Alpha.z
float4 main(VSOut In) : SV_TARGET
{
     float4 color = (float4)0.0f;

    color = albedoTexture.Sample(anisotropicSampler, In.UV);

    if(moveZ == 1)
        color.rgb = lerp(float3(0, 0, 0), color.rgb, moveX);
    if(moveZ == 0)
        color.rgb = lerp(float3(1, 1, 1), color.rgb, moveX);
    color.a = moveY;

    return color;
   
}
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
float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;    

    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
   if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset) + (AtlasSize * In.UV);    
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;        

        color = atlasTexture.Sample(anisotropicSampler, UV);

        if (moveX == 1)
        {
            color.rgb = float3(0, 0, 0);
            //color.rgb = float3(255, 255, 255);
            //color.rgb = float3(192, 192, 192);
            //color.a = 0.08;
        }
    }
    return color;
}
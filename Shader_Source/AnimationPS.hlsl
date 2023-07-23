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


//cbuffer Animator : register(b3)
//{
//    float2 SpriteLeftTop;
//    float2 SpriteSize;
//    float2 SpriteOffset;
//    float2 AtlasSize;
//    uint animationType;
//}


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


       //float2 diff = (AtlasSize - SpriteSize) / 2.0f;
       //// SpriteCenter�� SpriteLeftTop�� SpriteSize�� ����Ͽ� ��������Ʈ�� �߽����� ����մϴ�.
       //float2 SpriteCenter = SpriteLeftTop + (SpriteSize / 2.0f);
       //// Sprite�� �߽��� ���� �߹ؿ� ���߱� ���� ����� UV
       //float2 UV = (SpriteCenter - diff - float2(0, SpriteSize.y / 2.0f) - SpriteOffset) + (AtlasSize * In.UV);
       //// UV�� ���� �˻縦 �߾����� �������� �����մϴ�.
       //if (UV.x < SpriteCenter.x - SpriteSize.x / 2.0f || UV.x > SpriteCenter.x + SpriteSize.x / 2.0f
       //    || UV.y < SpriteCenter.y - SpriteSize.y / 2.0f || UV.y > SpriteCenter.y + SpriteSize.y / 2.0f)
       //    discard;
       //color = atlasTexture.Sample(anisotropicSampler, UV);


        //float2 SpriteCenter = SpriteLeftTop + (SpriteSize * 0.5f);
        //float2 ScaledUV = In.UV * SpriteSize;
        //float2 UV = ScaledUV + SpriteCenter - (SpriteSize * 0.5f) - SpriteOffset;
        //if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        //    || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
        //    discard;
        //color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    
    return color;
}
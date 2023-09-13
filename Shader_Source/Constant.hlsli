


cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
}

cbuffer MaterialData : register(b1)
{
    int cbiData1;
    int cbiData2;
    int cbiData3;
    int cbiData4;

    float cbfData1;
    float cbfData2;
    float cbfData3;
    float cbfData4;

    float2 cbxy1;
    float2 cbxy2;
    float2 cbxy3;
    float2 cbxy4;

    float3 cbxyz1;
    float cbxyzPadding1;
    float3 cbxyz2;
    float cbxyzPadding2;
    float3 cbxyz3;
    float cbxyzPadding3;
    float3 cbxyz4;
    float cbxyzPadding4;

    float4 cbxyzw1;
    float4 cbxyzw2;
    float4 cbxyzw3;
    float4 cbxyzw4;

    matrix cbmat1;
    matrix cbmat2;
    matrix cbmat3;
    matrix cbmat4;


    int     g_int_0;
    int     g_int_1;
    int     g_int_2;
    int     g_int_3;

    float   g_float_0;
    float   g_float_1;
    float   g_float_2;
    float   g_float_3;

    int     g_tex_on_0;
    int     g_tex_on_1;
    int     g_tex_on_2;
    int     g_tex_on_3;

    float2  g_vec2_0;
    float2  g_vec2_1;
    float2  g_vec2_2;
    float2  g_vec2_3;

    float4  g_vec4_0;
    float4  g_vec4_1;
    float4  g_vec4_2;
    float4  g_vec4_3;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
    float meshScale;
    float3 cbGridPadding;
}

cbuffer Animator : register(b3)
{
    float2 SpriteLeftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 AtlasSize;
    uint animationType;
}


cbuffer Move : register(b4)
{
    float4 Time;
}


cbuffer Tile : register(b5)
{
    float4 Index_map;
}


cbuffer ParticleSystem : register(b6)
{
    uint elementCount;
    float elapsedTime;
    float deltaTime;
    int padd2;
}

cbuffer Noise : register(b7)
{
    float4 noiseTextureSize;
}

cbuffer HP_Bar : register(b8)
{
    float4 Damage;
}

cbuffer AlphaBlend : register(b9)
{
    float4 Alpha;
}


struct Particle
{
    float4 position;
    float4 direction;

    float endTime;
    float time;
    float speed;
    uint active;
};

StructuredBuffer<Particle> particles : register(t14);
Texture2D noiseTexture : register(t15);

struct ParticleShared
{
    uint ActiveSharedCount;
};

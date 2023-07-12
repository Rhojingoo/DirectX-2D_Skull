


cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
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
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
    float meshScale;

    float3 cbGridPadding;
}

cbuffer Move : register(b3)
{
    float4 Time;
}

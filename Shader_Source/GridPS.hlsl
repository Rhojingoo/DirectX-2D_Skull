#include "globals.hlsli"


struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    float2 GridPos : POSITION;
};


float4 main(VSOut In) : SV_TARGET
{
    // 선 색상
    float4 Out = ALPHA(GREY, 0.5f);

    // 대각타일 색상
    float4 OutDiagonal = ALPHA(BLUE, 0.1f);
    float4 OutInverseDiagonal = ALPHA(YELLOW, 0.1f);

    // 타일을 포함한 한 칸의 크기를 나타낸다.
    // 33이 100과 매핑된다.  
    const float width = 50.f;//42.6f;
    const float height = 50.f;//42.6f;

    // 연산 문제로 329.9f 설정
    const float widthX10 = 500.f;//426.f;
    const float heightX10 = 500.f;//426.f;

    // 픽셀의 월드 좌표
    int gridX = (int)In.GridPos.x;
    int gridY = (int)In.GridPos.y;

    // 선 두께
    const float thickness = 1.f * cameraScale.x;

    // 한 칸 상의 픽셀의 좌표
    float calcX = abs((float)(gridX) % width);
    float calcY = abs((float)(gridY) % height);

    float calcX10 = abs((float)(gridX) % widthX10);
    float calcY10 = abs((float)(gridY) % heightX10);

    // 원점의 벡터 그리기
    if (calcX <= thickness || calcY <= thickness)
    {
        float4 axisXColor = BLACK;
        float4 axisYColor = BLACK; 

        // 좌표축 그리기
        if (abs(gridX) <= thickness)
            return axisYColor;
        if (abs(gridY) <= thickness)
            return axisXColor;

        if (abs(gridX) <= thickness * 3.f)
            return axisYColor;
        if (abs(gridY) <= thickness * 3.f)
            return axisXColor;

        if (abs(calcX10) <= thickness || abs(calcY10) <= thickness)
            return RED;

        return Out;
    }

    // 타일의 크기
    const int halfWidth = width * 0.5f;
    const int halfHeight = height * 0.5f;

    // 타일 칠하기
    if (calcX < halfWidth && calcY < halfHeight
        || calcX > halfWidth && calcY > halfHeight)
    {
        // 1사분면
        if (gridY > 0.f)
        {
            if (gridX > 0.f)
                return OutDiagonal;
            else if (gridX < 0.f)
                return OutInverseDiagonal;
        }
        // 2사분면
        else if (gridY < 0.f)
        {
            if (gridX > 0.f)
                return OutInverseDiagonal;
            else if (gridX < 0.f)
                return OutDiagonal;
        }
    }

    if (gridY > 0.f)
    {
        // 3사분면
        if (gridX > 0.f)
            return OutInverseDiagonal;
        else if (gridX < 0.f)
            return OutDiagonal;
    }
    else
    {
        // 4사분면
        if (gridX > 0.f)
            return OutDiagonal;
        else if (gridX < 0.f)
            return OutInverseDiagonal;
    }

    return float4(1.f, 0.f, 1.f, 1.f);
}
RWTexture2D<float4> tex : register(u0);

//https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/sv-dispatchthreadid
// SV_GroupID           : �����尡 ���� �׷��� ��ǥ
// SV_GoupThreadID      : �׷� ������, �������� ��ǥ
// SV_GoupIndex         : �׷� ������, �������� �ε��� (1����)
// SV_DispatchThreadID  : ��ü ������(��� �׷� ����) ��������, ȣ��� �������� ��ǥ

[numthreads(32, 32, 1)]// �׷� �� ������ ���� (�ִ� 1024 ���� ���� ����)
void main(uint3 DTid : SV_DispatchThreadID)
{
    if ( DTid.x >= 1024 || DTid.y >= 1024 )
    {
        return;
    }

    tex[DTid.xy] = float4(0.f, 0.f, 1.f, 1.f);
}
#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;

    if (ParticleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].ActiveSharedCount)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;

            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange);

            if (origin == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
        if (ParticleBuffer[DTid.x].active == 1)
        {

            ParticleBuffer[DTid.x].position.xyz; // �÷��̾� ��ġ �޵��� �����ʿ�            
            ParticleBuffer[DTid.x].endTime; // endTime�� ���� (�����Ѱ��� ÷���ʿ� ����� ������)
        }
    }
    else
    {
        ParticleBuffer[DTid.x].position.xyz += ParticleBuffer[DTid.x].direction.xyz * ParticleBuffer[DTid.x].speed * deltaTime;

        // Ȱ��ȭ�� ��ƼŬ�� �ð� ����
        ParticleBuffer[DTid.x].time += deltaTime;

        if (ParticleBuffer[DTid.x].time > ParticleBuffer[DTid.x].endTime)
        {
            ParticleBuffer[DTid.x].active = 0;
            ParticleBuffer[DTid.x].time = 0.0f;  // �ð��� �ٽ� 0���� �ʱ�ȭ
        }
    }
}


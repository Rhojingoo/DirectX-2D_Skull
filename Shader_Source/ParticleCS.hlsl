#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);


[numthreads(1024, 1, 1)]
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

            //1���������
            float2 vUV = float2((float)DTid.x / elementCount, 0.5f);
            vUV.x += elapsedTime;
            vUV.y += sin((vUV.x + elapsedTime) * 3.141592f + 2.f * 10.f) * 0.5f;
            float4 vRandom = float4
                (
                    GaussianBlur(vUV + float2(0.f, 0.f)).x,
                    GaussianBlur(vUV + float2(0.1f, 0.f)).x,
                    GaussianBlur(vUV + float2(0.2f, 0.f)).x,
                    GaussianBlur(vUV + float2(0.3f, 0.f)).x
                 );

            
            //2�� �������
            float x = ((float)DTid.x / (float)elementCount) + elapsedTime;
            float r1 = Rand(float2(x, elapsedTime));
            float r2 = Rand(float2(x * elapsedTime, elapsedTime));
            float r3 = Rand(float2(x * elapsedTime * elapsedTime, elapsedTime * elapsedTime));     
            // [0.5~1] -> [0~1]
            float3 noise =
            {
                2 * r1 - 1,
                2 * r2 - 1,
                2 * r3 - 1
            };


            float3 randomDirection = float3(vRandom.x * -2.0, abs(vRandom.y)*-2.f, vRandom.z * 2.0f - 1.0f);//���̷��� 1������
            float3 dir = (noise - 0.5f) * 2.f;// ���̷��� 2������

            if (ParticleBuffer[DTid.x].direction.z == 0.0f)
            {
                randomDirection;
                ParticleBuffer[DTid.x].endTime = lerp(7.0f, 15.0f, vRandom.w);  //  endTime�� �����ϰ� ���� (��: 7.0�ʿ��� 15.0�� ����)
            }
            else if (ParticleBuffer[DTid.x].direction.z == 1.0f)
            {
                randomDirection = dir;            
                ParticleBuffer[DTid.x].endTime = 3.5f;  //  endTime�� �����ϰ� ���� (��: 7.0�ʿ��� 15.0�� ����)
            }

            ParticleBuffer[DTid.x].position.xyz;// = vRandom.xyz * 100.0f; // ���� ���� ��ġ ����

            ParticleBuffer[DTid.x].direction.xyz = normalize(randomDirection);  // ���⼳��(2������)

            ParticleBuffer[DTid.x].speed = vRandom.w * 100.0f; // ���� �ӵ� ����
          
            
            //if (ParticleBuffer[DTid.x].direction.z == 0.0f)
            //{
            //    ParticleBuffer[DTid.x].endTime = lerp(7.0f, 15.0f, vRandom.w);  //  endTime�� �����ϰ� ���� (��: 7.0�ʿ��� 15.0�� ����)
            //}
            //if (ParticleBuffer[DTid.x].direction.z == 1.0f)
            //{
            //    ParticleBuffer[DTid.x].endTime = 5.0f;  //  endTime�� �����ϰ� ���� (��: 7.0�ʿ��� 15.0�� ����)
            //}
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

            // �ð��� �ٽ� 0���� �ʱ�ȭ
            // ParticleBuffer[DTid.x].time = 0.0f;


            if (ParticleBuffer[DTid.x].direction.z == 0.0f)
            {
               ParticleBuffer[DTid.x].time = 0.0f;
            }
           if (ParticleBuffer[DTid.x].direction.z == 1.0f)
            {
               // ParticleBuffer[DTid.x].time;
            }
             
        }
    }
}


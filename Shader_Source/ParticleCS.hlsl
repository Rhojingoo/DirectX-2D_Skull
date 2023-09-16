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

            // 쓰레드 동기화 Interlock 관련 함수
            InterlockedExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , exchange, exchange);

            if (origin == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
    }
    else
    {
        ParticleBuffer[DTid.x].position
            += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * elapsedTime;
    }

    //ParticleBuffer[DTid.x].position += /*float4(1.0f, 0.0f, 0.0f, 1.0f)*/
    //    ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * elapsedTime;
}


//[numthreads(128, 1, 1)]
//void main(uint3 DTid : SV_DispatchThreadID)
//{
//    if (elementCount <= DTid.x)
//        return;
//
//
//    if (ParticleBuffer[DTid.x].active == 0)
//    {
//        while (0 < ParticleSharedBuffer[0].ActiveSharedCount)
//        {
//            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
//            int exchange = origin - 1;
//
//            // 쓰레드 동기화 Interlock 관련 함수
//            //InterlockedExchange(ParticleSharedBuffer[0].ActiveSharedCount
//            //    , exchange, exchange);
//
//            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
//                , origin, exchange, exchange);
//
//            if (origin == exchange)
//            {
//                ParticleBuffer[DTid.x].active = 1;
//                break;
//            }
//        }
//
//        if (ParticleBuffer[DTid.x].active == 1)
//        {
//            //float4 vRandom = (float4) 0.f;
//
//            //float2 vUV = float2((float)DTid.x / elementCount, 0.5f);
//            //vUV.x += elapsedTime;
//            //vUV.y += sin((vUV.x + elapsedTime) * 3.141592f + 2.f * 10.f) * 0.5f;
//
//            //vRandom = float4
//            //    (
//            //        GaussianBlur(vUV + float2(0.f, 0.f)).x
//            //        , GaussianBlur(vUV + float2(0.1f, 0.f)).x
//            //        , GaussianBlur(vUV + float2(0.2f, 0.f)).x
//            //        , GaussianBlur(vUV + float2(0.3f, 0.f)).x
//            //        );
//
//            //ParticleBuffer[DTid.x].position.xyz = vRandom.xyz * 3.0f;
//            //ParticleBuffer[DTid.x].position.x -= 0.65f;
//            //ParticleBuffer[DTid.x].position.y -= 1.4f;
//            //ParticleBuffer[DTid.x].position.z = 0.0f;
//
//
//
//            // 랜덤값으로 위치와 방향을 설정한다.
//            // 샘플링을 시도할 UV 를 계산한다.
//            //float x = ((float)DTid.x / (float)elementCount) + elapsedTime;
//
//            //float r1 = Rand(float2(x, elapsedTime));
//            //float r2 = Rand(float2(x * elapsedTime, elapsedTime));
//            //float r3 = Rand(float2(x * elapsedTime * elapsedTime, elapsedTime * elapsedTime));
//
//            //// [0.5~1] -> [0~1]
//            //float3 noise =
//            //{
//            //    2 * r1 - 1,
//            //    2 * r2 - 1,
//            //    2 * r3 - 1
//            //};
//
//            //// [0~1] -> [-1~1]
//            //float3 dir = (noise - 0.5f) * 2.f;
//
//
//            //ParticleBuffer[DTid.x].position.xyz = (noise.xyz - 0.5f) * 25;
//            //ParticleBuffer[DTid.x].direction  = float4(normalize(dir), 1.0);
//            //ParticleBuffer[DTid.x].endTime = ((10 - 2) * noise.x) + 2;
//            //ParticleBuffer[DTid.x].time = 0.0f;
//
//
//            //g_particle[threadIndex.x].worldDir = normalize(dir);
//            //g_particle[threadIndex.x].worldPos = (noise.xyz - 0.5f) * 25;
//            //g_particle[threadIndex.x].lifeTime = ((10 - 2) * noise.x) + 2;
//            //g_particle[threadIndex.x].curTime = 0.f;
//
//        }
//    }
//    else
//    {
//        //ParticleBuffer[DTid.x].position 
//        //   += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;
//
//        // 시간을 체크해서 일정 시간(랜덤)이 지나면
//        // active = 0;
//        //ParticleBuffer[DTid.x].time += elapsedTime;
//        //if(ParticleBuffer[DTid.x].endTime< ParticleBuffer[DTid.x].time)
//        //{
//        //    ParticleBuffer[DTid.x].active = 0;
//        //    return;
//        //}
//
//        //float ratio = ParticleBuffer[DTid.x].time / ParticleBuffer[DTid.x].endTime;
//        //float speed = (10 - 3) * ratio + 3;        
//
//        //ParticleBuffer[DTid.x].position += ParticleBuffer[DTid.x].direction * speed * deltaTime;
//    }
//
//}
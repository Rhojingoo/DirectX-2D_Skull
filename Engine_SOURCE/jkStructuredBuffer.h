#pragma once
#include "jkEntity.h"
#include "jkGraphics.h"

namespace jk::graphics
{
	class StructuredBuffer : public GpuBuffer
	{
	public:
		StructuredBuffer();
		~StructuredBuffer();

		bool Create(UINT size, UINT stride, eViewType type, void* data, bool cpuAccess = false);
		bool Create(UINT size, UINT stride, eSRVType type, void* data);
		bool CreateRWBuffer();
		void SetData_Buffer (void* data, UINT stride);
		void SetData(void* data, UINT bufferCount);
		void GetData(void* data, UINT size);
		void Bind(eShaderStage stage, UINT slot);
		void BindSRV(eShaderStage stage, UINT slot);
		void BindUAV(UINT slot);

		void Clear();

		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }
		UINT GetTotalSize() { return mSize * mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mReadBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mWriteBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		eViewType _Type;
		eSRVType mType;

		UINT mSize;
		UINT mStride;

		UINT mSRVSlot;
		UINT mUAVslot;
	};
}

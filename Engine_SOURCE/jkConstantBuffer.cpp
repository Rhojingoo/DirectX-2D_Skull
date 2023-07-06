#include "jkConstantBuffer.h"
#include "jkGraphicDevice_Dx11.h"

namespace jk::graphics
{
	ConstantBuffer::ConstantBuffer(const eCBType type)
		: GpuBuffer()
		, mType(type)
	{

	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	bool ConstantBuffer::Create(size_t size)
	{
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		jk::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return false;
	}

	void ConstantBuffer::SetData(void* data)
	{
		jk::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}

	void ConstantBuffer::Bind(eShaderStage stage)
	{
		jk::graphics::GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
	}

}

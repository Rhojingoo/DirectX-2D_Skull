#include "jkPaintShader.h"
#include "jkTexture.h"

namespace jk::graphics
{
	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessViews(0);

		mGroupX = static_cast<UINT>(mTarget->GetWidth()) / mThreadGroupCountX + 1;
		mGroupY = static_cast<UINT>(mTarget->GetHeight()) / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}
	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessViews(0);
	}
}

//
// SPARK particle engine
//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com
// Copyright (C) 2017 - Frédéric Martin - fredakilla@gmail.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include <SPARK_Core.h>

namespace SPK
{
	ShaderHint Renderer::shaderHint = SHADER_HINT_NONE;
	bool Renderer::vboHint = false;

	void Renderer::useShaderHint(ShaderHint hint)
	{
		SPK_LOG_INFO("Shader hint is not yet considered");
	}

	void Renderer::useVBOHint(bool hint)
	{
		SPK_LOG_INFO("VBO hint is not yet considered");
	}
}

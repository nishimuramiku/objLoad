
#pragma once

#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")


HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
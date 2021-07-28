#pragma once
#define D3DFONT_BOLD    0x0001
#define D3DFONT_ITALIC  0x0002
#define D3DFONT_SIZE_IN_PIXELS 0x1000

#define D3DFONT_FILTERED    0x0004

__declspec(align(16)) class CD3D11Font
{
public:
    CD3D11Font(ID3D11DeviceContext *pContext);
    virtual ~CD3D11Font(void);
    virtual HRESULT RestoreDeviceObjects(ID3D11DeviceContext *pContext);
    virtual HRESULT ReleaseDeviceObjects(ID3D11DeviceContext *pContext);
    
    virtual void    Render(ID3D11DeviceContext *pContext);
    HRESULT CreateFontTexture();

    virtual void DrawAnkText(ID3D11DeviceContext *pContext,TCHAR *pString, DirectX::XMFLOAT4 color ,FLOAT x, FLOAT y);
    virtual void DrawChar(ID3D11DeviceContext *pContext, char ankCode, DirectX::XMFLOAT4 color, FLOAT *px, FLOAT *py);

    HRESULT NoAlfa();
    //  keep 16-byte aligned
    void *operator new(size_t size){
        return _mm_malloc(size,16);
    }
    void operator delete(void *p){
        return _mm_free(p);
    }
protected:
    HRESULT CompileShaderFromMemory(BYTE *code, DWORD dwSize, LPCSTR szEntryPoint,LPCSTR szShaderModel, ID3DBlob **ppBlobOut);

    ID3D11DeviceContext     *m_pDeviceContext;
    ID3D11Device            *m_pDevice;
    ID3D11Texture2D         *m_pTexture;
    ID3D11ShaderResourceView    *m_pTextureShaderResourceView;
    ID3D11SamplerState      *m_pTextureSamplerState;
    ID3D11VertexShader      *m_pVertexShader;
    ID3D11PixelShader       *m_pPixelShader;
    ID3D11InputLayout       *m_pInputLayout;
    ID3D11BlendState        *m_pBlendState;

    ID3D11Buffer        *m_pVertexBuffer;
    ID3D11Buffer        *m_pConstantBuffer;

    DWORD               m_dwFontFlags;
    DWORD               m_dwFontHeight;

    DirectX::XMMATRIX   m_matProj;

    DWORD   m_dwTexWidth;
    DWORD   m_dwTexHeight;
    TCHAR   *m_strFontName;
    BOOL    m_bInitialized;
    FLOAT   m_fTexCoords[128-32][4];
};

//---------------------------------------------
//  class CD3D11Font
//  Author MR.K
//  Desc: Ank Font on Direct3D11
//      Debug purpose
//---------------------------------------------
//#include "stdafx.h"
#include <tchar.h>//2021-03-26
#include <stdio.h>
#include <D3D11.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#include "D3D11Font.h"

#define SAFE_RELEASE(o) if(o){  (o)->Release(); o = NULL; }
//
//extern HRESULT CompileShaderFromFile(
//    WCHAR*      szFileName,
//    LPCSTR      szEntryPoint,
//    LPCSTR      szShaderModel,
//    ID3DBlob    **ppBlobOut
//);
//2021-03-26 Add
using namespace DirectX;

static char shadercode[]="\
//-----------------------------------------------------------------------------------\n\
//  texture sampler\n\
//-----------------------------------------------------------------------------------\n\
SamplerState textureSampler : register(s0);\n\
Texture2D    diffuseTexture : register(t0);\n\
\n\
\n\
//-----------------------------------------------------------------------------------\n\
// Constant buffer\n\
//-----------------------------------------------------------------------------------\n\
cbuffer VSConstantBuffer : register( b0 )\n\
{\n\
    matrix  Proj;   //  projection matrix\n\
    float4  Color;  //  font color\n\
};\n\
\n\
\n\
//-----------------------------------------------------------------------------------\n\
// VSInput structure\n\
//-----------------------------------------------------------------------------------\n\
struct VSInput\n\
{\n\
    float3 Position : POSITION;     //  position\n\
    float2 texCoord : TEXCOORD0;    //  texture coordinates\n\
};\n\
\n\
//-----------------------------------------------------------------------------------\n\
// GSPSInput structure\n\
//-----------------------------------------------------------------------------------\n\
struct GSPSInput\n\
{\n\
    float4 Position : SV_POSITION;  //  position\n\
    float2 texCoord : TEXCOORD0;    //  texture coordinates\n\
    float4 diffuse  : COLOR;        //  font color\n\
};\n\
\n\
//-----------------------------------------------------------------------------------\n\
//  Vertex Shader Entry point\n\
//-----------------------------------------------------------------------------------\n\
GSPSInput VSFunc( VSInput input )\n\
{\n\
    GSPSInput output = (GSPSInput)0;\n\
\n\
    // 入力データをfloat4 へ変換.\n\
    float4 pos = float4( input.Position, 1.0f );\n\
\n\
    // 射影空間に変換.\n\
    float4 projPos  = mul( Proj,  pos );\n\
\n\
    output.Position = projPos;\n\
    output.texCoord = input.texCoord;\n\
    output.diffuse  = Color;\n\
    return output;\n\
}\n\
\n\
//------------------------------------------------------------------------------------\n\
//  Pixel shader entry point\n\
//------------------------------------------------------------------------------------\n\
float4 PSFunc( GSPSInput psin ) : SV_TARGET0\n\
{\n\
    float4 pixel = diffuseTexture.Sample(textureSampler, psin.texCoord);\n\
    pixel = psin.diffuse * pixel;\n\
    return pixel;\n\
}\n\
\n";

struct AnkFontVertex
{
    DirectX::XMFLOAT3 position;     //  position
    DirectX::XMFLOAT2 texture;      //  texture coordinates
};

typedef struct{
    DirectX::XMMATRIX    matProj;
    DirectX::XMFLOAT4    color;
}    AnkFontConstantBuffer;


CD3D11Font::CD3D11Font(ID3D11DeviceContext *pContext)
{
    m_pDeviceContext = NULL;
    m_pDevice = NULL;
    m_pTexture = NULL;
    m_pTextureShaderResourceView = NULL;
    m_pTextureSamplerState = NULL;
    m_pVertexShader = NULL;
    m_pPixelShader = NULL;
    m_pInputLayout = NULL;
    m_pBlendState = NULL;
    m_pVertexBuffer = NULL;
    m_pConstantBuffer = NULL;
    
    m_strFontName =(TCHAR *)_T("ＭＳ ゴシック");
    m_dwFontHeight = 20;
    m_dwFontFlags = 0;

    m_bInitialized = false;

    RestoreDeviceObjects(pContext);
}

CD3D11Font::~CD3D11Font(void)
{
    ReleaseDeviceObjects(NULL);
}

HRESULT CD3D11Font::RestoreDeviceObjects(ID3D11DeviceContext *pContext){
    ID3DBlob    *pShader = NULL;
    HRESULT hr;

    m_bInitialized = false;

    pContext->AddRef();
    ReleaseDeviceObjects(pContext);

    m_pDeviceContext = pContext;
    m_pDeviceContext->GetDevice(&m_pDevice);

    //Vertex　シェーダー生成
    hr = CompileShaderFromMemory((BYTE*)shadercode,sizeof(shadercode),"VSFunc","vs_4_0",&pShader);
    if (FAILED(hr)){
        return    hr;
    }
    hr = m_pDevice->CreateVertexShader(pShader->GetBufferPointer(),pShader->GetBufferSize(),NULL,&m_pVertexShader);
    if (FAILED(hr)){
        return    hr;
    }

    //Inputレイアウトの定義
    D3D11_INPUT_ELEMENT_DESC layout[] = {
    {
       "POSITION", 
       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 
    },
    {
        "TEXCOORD", 
        0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 
    }
    };
    UINT numElements = ARRAYSIZE( layout );
    
    //Inputレイアウト作成
    hr = m_pDevice->CreateInputLayout( 
        layout,
        numElements,
        pShader->GetBufferPointer(),
        pShader->GetBufferSize(),
        &m_pInputLayout
    );
    SAFE_RELEASE(pShader);
    if ( FAILED( hr ) )
    {
        return hr;
    }

    //入力アセンブラにInputレイアウト設定
    m_pDeviceContext->IASetInputLayout( m_pInputLayout );

    //Pixelシェーダー生成
    hr = CompileShaderFromMemory((BYTE*)shadercode,sizeof(shadercode),"PSFunc","ps_4_0",&pShader);
    if (FAILED(hr))
        return hr;
    hr = m_pDevice->CreatePixelShader(pShader->GetBufferPointer(),pShader->GetBufferSize(),NULL,&m_pPixelShader);
    SAFE_RELEASE(pShader);
    if (FAILED(hr))
        return    hr;

    hr = CreateFontTexture();

    if (FAILED(hr))
        return hr;

    //シェーダーリソースビュー作成
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
        D3D11_TEXTURE2D_DESC    texDesc;
        ZeroMemory( &srvd, sizeof( D3D11_SHADER_RESOURCE_VIEW_DESC ) );
        m_pTexture->GetDesc(&texDesc);
        srvd.Format                     = texDesc.Format;
          srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvd.Texture2D.MipLevels = texDesc.MipLevels;
        srvd.Texture2D.MostDetailedMip = 0;
        hr = m_pDevice->CreateShaderResourceView( m_pTexture, &srvd, &m_pTextureShaderResourceView);
        if (FAILED(hr))
            return hr;
    }

    //サンプラーセットアップ
    {
        D3D11_SAMPLER_DESC samplerDesc;
        samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;         // サンプリング時に使用するフィルタ。ここでは異方性フィルターを使用する。
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 ～ 1 の範囲外にある u テクスチャー座標の描画方法
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 ～ 1 の範囲外にある v テクスチャー座標
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 ～ 1 の範囲外にある w テクスチャー座標
        samplerDesc.MipLODBias = 0;                            // 計算されたミップマップ レベルからのバイアス
        samplerDesc.MaxAnisotropy = 16;                        // サンプリングに異方性補間を使用している場合の限界値。有効な値は 1 ～ 16 。
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;  // 比較オプション。
        
        /*memcpy((void*)&samplerDesc.BorderColor,
            (void*)&DirectX::XMFLOAT4(0,0,0,0),4*sizeof(FLOAT));*/

        //2021-03-26 修正
        samplerDesc.BorderColor[0] = 0;
        samplerDesc.BorderColor[1] = 0;
        samplerDesc.BorderColor[2] = 0;
        samplerDesc.BorderColor[3] = 0;
        samplerDesc.MinLOD = 0;                                // アクセス可能なミップマップの下限値
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;                // アクセス可能なミップマップの上限値
        // ID3D11Device::CreateSamplerState
        hr = m_pDevice->CreateSamplerState( &samplerDesc, &m_pTextureSamplerState );
        if( FAILED( hr ) )
            return    hr;

    }
    //頂点バッファ設定
    {
            //頂点定義
            AnkFontVertex vertices[] = {
                {  DirectX::XMFLOAT3( -0.5f,  0.5f, 0.0f ),  DirectX::XMFLOAT2(  0.0f,  0.0f ) },
                {  DirectX::XMFLOAT3(  0.5f,  0.5f, 0.0f ),  DirectX::XMFLOAT2(  1.0f,  0.0f ) },
                {  DirectX::XMFLOAT3( -0.5f, -0.5f, 0.0f ),  DirectX::XMFLOAT2(  0.0f,  1.0f ) },
                {  DirectX::XMFLOAT3(  0.5f, -0.5f, 0.0f ),  DirectX::XMFLOAT2(  1.0f,  1.0f ) },
            };
  
        D3D11_BUFFER_DESC bd;
        ZeroMemory( &bd, sizeof( D3D11_BUFFER_DESC ) );
        bd.Usage          = D3D11_USAGE_DEFAULT;
        bd.ByteWidth      = sizeof( AnkFontVertex ) * 4;
        bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;

        //サブリソース設定
        D3D11_SUBRESOURCE_DATA initData;
        ZeroMemory( &initData, sizeof( D3D11_SUBRESOURCE_DATA ) );
        initData.pSysMem = vertices;

        //頂点バッファ作成
        hr = m_pDevice->CreateBuffer( &bd, &initData, &m_pVertexBuffer );
        if ( FAILED( hr ) )
        {
            return    hr;
        }
    }
    //定数バッファ作成
    {
        
        D3D11_BUFFER_DESC bd;
        ZeroMemory( &bd, sizeof( D3D11_BUFFER_DESC ) );
        bd.ByteWidth        = sizeof( AnkFontConstantBuffer );
        bd.Usage            = D3D11_USAGE_DEFAULT;
        bd.BindFlags        = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags   = 0;

        hr = m_pDevice->CreateBuffer( &bd, NULL, &m_pConstantBuffer );
        if ( FAILED( hr ) )
        {
            return    hr;
        }
    }
    {
        //アルファ抜きブレンドステート設定
        D3D11_BLEND_DESC BlendDesc;
        ZeroMemory( &BlendDesc, sizeof( BlendDesc ) );
        BlendDesc.AlphaToCoverageEnable = FALSE;
        BlendDesc.IndependentBlendEnable = FALSE;
        BlendDesc.RenderTarget[0].BlendEnable = TRUE;
        BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        for (int i = 1 ; i < 8 ; ++i){
            BlendDesc.RenderTarget[i] = BlendDesc.RenderTarget[0];
        }
        hr = m_pDevice->CreateBlendState( &BlendDesc, &m_pBlendState );
        if ( FAILED( hr ) )
        {
            return    hr;
        }
    }
     //行列設定
    {
        //  non scaled ortho matrix (2D)
        m_matProj = DirectX::XMMatrixIdentity();
        m_matProj.r[0].m128_f32[0] = 1.0f;
        m_matProj.r[1].m128_f32[1] = 1.0f;
        m_matProj.r[2].m128_f32[2] = 0.0f;
        m_matProj.r[2].m128_f32[3] = 1.0f;
        m_matProj.r[3].m128_f32[2] = 0.0f;
        m_matProj.r[3].m128_f32[3] = 0.0f;
    }
    m_bInitialized = true;
    return S_OK;
}

HRESULT CD3D11Font::NoAlfa() {


    D3D11_BLEND_DESC BlendDesc;
    ZeroMemory(&BlendDesc, sizeof(BlendDesc));
    BlendDesc.AlphaToCoverageEnable = FALSE;
    BlendDesc.IndependentBlendEnable = FALSE;
    BlendDesc.RenderTarget[0].BlendEnable = FALSE;
    BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    for (int i = 1; i < 8; ++i) {
        BlendDesc.RenderTarget[i] = BlendDesc.RenderTarget[0];
    }
    HRESULT hr = m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState);
    
    if (FAILED(hr))
    {
        return    hr;
    }

    return S_OK;
}
//
//  ANKフォント用テクスチャ生成
//
HRESULT CD3D11Font::CreateFontTexture(){
    HDC        hDC = NULL;
    HBITMAP hbmBitmap = NULL;
    HFONT hFont = NULL;
    hDC        = CreateCompatibleDC( NULL );
    HRESULT hr;
    INT    nHeight;

    DWORD dwBold   = (m_dwFontFlags&D3DFONT_BOLD)   ? FW_BOLD : FW_NORMAL;
    DWORD dwItalic = (m_dwFontFlags&D3DFONT_ITALIC) ? TRUE    : FALSE;


    if (m_dwFontFlags & D3DFONT_SIZE_IN_PIXELS){
        nHeight = (INT)(m_dwFontHeight);
    }else{
        __int64    tmp64 = m_dwFontHeight;
        tmp64 *= (INT)(GetDeviceCaps(hDC, LOGPIXELSY));
        nHeight    = (INT)(tmp64 / 72);    //  フォント高 * dpi * testScale / 72
    }

    // Large fonts need larger textures
    if( nHeight > 64 )
        m_dwTexWidth = m_dwTexHeight = 1024;
    else if( nHeight > 32 )
        m_dwTexWidth = m_dwTexHeight = 512;
    else
        m_dwTexWidth  = m_dwTexHeight = 256;

    D3D11_TEXTURE2D_DESC td;
    ZeroMemory( &td, sizeof( D3D11_TEXTURE2D_DESC ) );
    td.Width                = m_dwTexWidth;
    td.Height               = m_dwTexHeight;
    td.MipLevels            = 1;
    td.ArraySize            = 1;
    td.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count     = 1;    //  MULTI SAMPLE COUNT
    td.SampleDesc.Quality   = 0;    //  MULtI SAMPLE QUALITY
    td.Usage                = D3D11_USAGE_DYNAMIC;    //  Make it writeable
    td.BindFlags            = D3D11_BIND_SHADER_RESOURCE;
    td.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
    td.MiscFlags            = 0;
  
    // 2Dテクスチャの生成
    hr = m_pDevice->CreateTexture2D( &td, NULL, &this->m_pTexture );
    if ( FAILED( hr ) )
        return hr;

    
    DWORD*      pBitmapBits;
    BITMAPINFO bmi;
    ZeroMemory( &bmi.bmiHeader,  sizeof(BITMAPINFOHEADER) );
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       =  (int)m_dwTexWidth;
    bmi.bmiHeader.biHeight      = -(int)m_dwTexHeight;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount    = 32;

    // ビットマップの作成
    hbmBitmap = CreateDIBSection( hDC, &bmi, DIB_RGB_COLORS,
                                        (VOID**)&pBitmapBits, NULL, 0 );
    SetMapMode( hDC, MM_TEXT );

    //  ANTIALIASED_QUALITYを指定してフォントを生成する。
    //  アンチエイリアスを効かせたフォントを得ようとするが、
    //  アンチエイリアスがかかるとは保証されない。
    hFont    = CreateFont( -nHeight, 0, 0, 0, dwBold, dwItalic,
                        FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                        VARIABLE_PITCH, m_strFontName );
    if( NULL==hFont ){
        hr = E_FAIL;
    }else{
        SelectObject( hDC, hbmBitmap );
        SelectObject( hDC, hFont );

        // テキストプロパティーの設定
        SetTextColor( hDC, RGB(255,255,255) );
        SetBkColor(   hDC, 0x00000000 );
        SetTextAlign( hDC, TA_TOP );

        //  texture coordinatesを保存しながら、出力可能な文字をビットマップに
        //  出力してゆく。
        DWORD x = 0;
        DWORD y = 0;
        TCHAR str[2] = _T("x");
        SIZE size;

        for( TCHAR c=32; c<127; c++ )
        {
            str[0] = c;
            GetTextExtentPoint32( hDC, str, 1, &size );

            if( (DWORD)(x+size.cx+1) > m_dwTexWidth )
            {
                x  = 0;
                y += size.cy+1;
            }

            ExtTextOut( hDC, x+0, y+0, ETO_OPAQUE, NULL, str, 1, NULL );

            m_fTexCoords[c-32][0] = ((FLOAT)(x+0))/m_dwTexWidth;
            m_fTexCoords[c-32][1] = ((FLOAT)(y+0))/m_dwTexHeight;
            m_fTexCoords[c-32][2] = ((FLOAT)(x+0+size.cx))/m_dwTexWidth;
            m_fTexCoords[c-32][3] = ((FLOAT)(y+0+size.cy))/m_dwTexHeight;

            x += size.cx+1;
        }

        // Lock the surface and write the alpha values for the set pixels
        D3D11_MAPPED_SUBRESOURCE hMappedResource;
        hr = m_pDeviceContext->Map( 
            m_pTexture,
            0,
            D3D11_MAP_WRITE_DISCARD,
            0,
            &hMappedResource );
        if (SUCCEEDED(hr)){
            // ここで書き込む
            BYTE* pBits = (BYTE*)hMappedResource.pData;

            BYTE bAlpha; // 4-bit measure of pixel intensity

            for( y=0; y < m_dwTexHeight; y++ )
            {
                DWORD* pDst32 = (DWORD*)(pBits+(y*hMappedResource.RowPitch));
                for( x=0; x < m_dwTexWidth; x++ )
                {
                    bAlpha = (BYTE)(pBitmapBits[m_dwTexWidth*y + x] & 0xff);
                    if (bAlpha > 0){
                        *pDst32++ = 0x00ffffff | (bAlpha<<24);
                    }
                    else
                    {
                        *pDst32++ = 0x00000000;
                    }
                }
            }
            m_pDeviceContext->Unmap(m_pTexture,0);
        }
    }

    if (hbmBitmap)
        DeleteObject( hbmBitmap );
    if (hFont)
        DeleteObject( hFont );
    if (hDC)
        DeleteDC( hDC );

    return S_OK;
}

HRESULT CD3D11Font::ReleaseDeviceObjects(ID3D11DeviceContext *pContext){

    SAFE_RELEASE(m_pDeviceContext);
    SAFE_RELEASE(m_pDevice);
    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_pTextureShaderResourceView);
    SAFE_RELEASE(m_pTextureSamplerState);
    SAFE_RELEASE(m_pVertexShader);
    SAFE_RELEASE(m_pPixelShader);
    SAFE_RELEASE(m_pInputLayout);
    SAFE_RELEASE(m_pBlendState);
    SAFE_RELEASE(m_pVertexBuffer);
    SAFE_RELEASE(m_pConstantBuffer);
    return    S_OK;

}


void    CD3D11Font::Render(ID3D11DeviceContext *pContext){

    if (!m_bInitialized)
        return;

    //　シェーダを設定して描画.
    pContext->VSSetShader( m_pVertexShader, NULL, 0 );
    pContext->GSSetShader( NULL,            NULL, 0 );
    pContext->PSSetShader( m_pPixelShader,  NULL, 0 );

    // 定数バッファの設定.
    AnkFontConstantBuffer cb;
    cb.matProj  = m_matProj;
    //memcpy((void*)&cb.matProj,(void*)&m_matProj,sizeof(DirectX::XMMATRIX));
    cb.color = DirectX::XMFLOAT4(1.0,1.0,1.0,1.0);
    // サブリソースを更新.
    pContext->UpdateSubresource( m_pConstantBuffer, 0, NULL, &cb, 0, 0 );

    // ジオメトリシェーダに定数バッファを設定.
    pContext->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

    // 入力アセンブラに頂点バッファを設定.
    UINT stride = sizeof( AnkFontVertex );
    UINT offset = 0;
    pContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

    // プリミティブの種類を設定.
    pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

    ID3D11ShaderResourceView* ppShaderResourceViews[] = { m_pTextureShaderResourceView, 0 };
    ID3D11SamplerState    *ppSamplerStates[] = { m_pTextureSamplerState, 0 };
    pContext->PSSetShaderResources(0, 1, ppShaderResourceViews);
    pContext->PSSetSamplers( 0, 1, ppSamplerStates );

    pContext->Draw(4,0);    //  Draw 4 vertices.

    ppSamplerStates[0] = NULL;
    ppShaderResourceViews[0] = NULL;
    pContext->PSSetSamplers( 0, 1, ppSamplerStates );
    pContext->PSSetShaderResources(0, 1, ppShaderResourceViews);
}

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

HRESULT CD3D11Font::CompileShaderFromMemory(BYTE* pCode, DWORD dwSize, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob **ppBlobOut){
    // リターンコードを初期化.
    HRESULT hr = S_OK;

    // コンパイルフラグ.
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif//defiend(DEBUG) || defined(_DEBUG)

#if defined(NDEBUG) || defined(_NDEBUG)
    //dwShaderFlags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif//defined(NDEBUG) || defined(_NDEBUG)

    ID3DBlob* pErrorBlob = NULL;

    // シェーダをコンパイル.
    hr = D3DCompile(pCode,dwSize,NULL,NULL,D3D_COMPILE_STANDARD_FILE_INCLUDE,
        szEntryPoint,szShaderModel,dwShaderFlags,0,ppBlobOut,&pErrorBlob);

    // エラーチェック.
    if ( FAILED( hr ) )
    {
        // エラーメッセージを出力.
        if ( pErrorBlob != NULL )
        { OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() ); }
    }

    // 解放処理.
    if ( pErrorBlob )
    {
        pErrorBlob->Release();
        pErrorBlob = NULL;
    }

    // リターンコードを返却.
    return hr;
}

void CD3D11Font::DrawChar(ID3D11DeviceContext *pContext,  char ankCode, DirectX::XMFLOAT4 color, FLOAT *px, FLOAT *py){
    
    if (!m_bInitialized)
        return;

    if (m_pDeviceContext != pContext)
        return;


    char c = ankCode;
    if (c < ' ')
        return;
    FLOAT fTexWidth = (FLOAT)m_dwTexWidth;
    FLOAT fTexHeight = (FLOAT)m_dwTexHeight;
    FLOAT fTexWidthInv = 1.0f / fTexWidth;
    FLOAT fTexHeightInv = 1.0f / fTexHeight;

    FLOAT tx1 = m_fTexCoords[c-32][0];
    FLOAT ty1 = m_fTexCoords[c-32][1];
    FLOAT tx2 = m_fTexCoords[c-32][2];
    FLOAT ty2 = m_fTexCoords[c-32][3];
    FLOAT w = (tx2-tx1) * fTexWidth;
    FLOAT h = (ty2-ty1) * fTexHeight;


    D3D11_VIEWPORT  vp;
    UINT            uiNumViewport = 1;
    m_pDeviceContext->RSGetViewports(&uiNumViewport,&vp);
    if (uiNumViewport != 1)
        return;

    //  transform 2D -> clipping space
    FLOAT l = *px;
    FLOAT t = *py;
    FLOAT r = l + w;
    FLOAT b = t + h;
    FLOAT z = 1.0f;
    l /= vp.Width*0.5f;
    t /= vp.Height*0.5f;
    r /= vp.Width*0.5f;
    b /= vp.Height*0.5f;
    l -= 1.0f;
    r -= 1.0f;
    t = 1.0f - t;
    b = 1.0f - b;
    
    *px += w;

    // 頂点バッファの設定.
    {
        // 頂点の定義.
        AnkFontVertex vertices[] = {
            {  DirectX::XMFLOAT3( l, t, z ),  DirectX::XMFLOAT2(  tx1,  ty1 ) },
            {  DirectX::XMFLOAT3( r, t, z ),  DirectX::XMFLOAT2(  tx2,  ty1 ) },
            {  DirectX::XMFLOAT3( l, b, z ),  DirectX::XMFLOAT2(  tx1,  ty2 ) },
            {  DirectX::XMFLOAT3( r, b, z ),  DirectX::XMFLOAT2(  tx2,  ty2 ) },
        };
  
        pContext->UpdateSubresource( m_pVertexBuffer, 0, NULL, vertices, 0, 0 );
        
    }

    //　シェーダを設定
    pContext->VSSetShader( m_pVertexShader,   NULL, 0 );
    pContext->GSSetShader( NULL, NULL, 0 );
    pContext->PSSetShader( m_pPixelShader,    NULL, 0 );

    // 定数バッファの設定.
    AnkFontConstantBuffer cb;
    cb.matProj  = m_matProj;
    //memcpy((void*)&cb.matProj,(void*)&m_matProj,sizeof(DirectX::XMMATRIX));
    cb.color = DirectX::XMFLOAT4(color.x,color.y,color.z,color.w);
    DirectX::XMMatrixTranspose(cb.matProj);
    // サブリソースを更新.
    pContext->UpdateSubresource( m_pConstantBuffer, 0, NULL, &cb, 0, 0 );

    // ジオメトリシェーダに定数バッファを設定.
    pContext->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

    // 入力アセンブラに頂点バッファを設定.
    UINT stride = sizeof( AnkFontVertex );
    UINT offset = 0;
    pContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

    // 入力アセンブラに入力レイアウトを設定.
    pContext->IASetInputLayout( m_pInputLayout );

    // プリミティブの種類を設定.
    pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

    ID3D11ShaderResourceView* ppShaderResourceViews[] = { m_pTextureShaderResourceView, 0 };
    ID3D11SamplerState    *ppSamplerStates[] = { m_pTextureSamplerState, 0 };
    pContext->PSSetShaderResources(0, 1, ppShaderResourceViews);
    pContext->PSSetSamplers( 0, 1, ppSamplerStates );

    pContext->Draw(4,0);    //  Draw 4 vertices.

    ppSamplerStates[0] = NULL;
    ppShaderResourceViews[0] = NULL;
    pContext->PSSetSamplers( 0, 1, ppSamplerStates );
    pContext->PSSetShaderResources(0, 1, ppShaderResourceViews);

}

void CD3D11Font::DrawAnkText(ID3D11DeviceContext* pContext, TCHAR* pString, 
    DirectX::XMFLOAT4 color, FLOAT x, FLOAT y) {
    FLOAT tmpx = x;
    FLOAT tmpy = y;

    float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    pContext->OMSetBlendState(m_pBlendState, blendFactor, 0xffffffff);

    TCHAR* p = pString;
    while (*p != (TCHAR)0) {
        DrawChar(pContext, (char)(*p & 0x7f), color, &tmpx, &tmpy);
        p++;
    }

    pContext->OMSetBlendState( NULL, blendFactor, 0xffffffff );
}
 
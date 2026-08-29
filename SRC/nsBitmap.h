//---------------------------------------------------------------------------
#ifndef nsBitmapH
#define nsBitmapH
//---------------------------------------------------------------------------

class nsBitmap
{
private:
	TBitmap *pBmp = nullptr;
public:
	//コンストラクタ
	nsBitmap();
	//コピーコンストラクタ
	nsBitmap(const nsBitmap& h);
	//デストラクタ
	virtual ~nsBitmap();
public:
	//代入
	nsBitmap& operator = (const nsBitmap& h);
	//->演算子
	TBitmap* operator -> ();
public:
	//ビットマップ再構築
	bool reset();
	//ビットマップ取得
	TBitmap *get() const;
};

#endif

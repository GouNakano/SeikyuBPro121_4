//---------------------------------------------------------------------------
#ifndef TReopenH
#define TReopenH
//---------------------------------------------------------------------------
//再開処理情報
class TReopen
{
public:
	String  sdoPath;  //ファイル(.sdo)パス
	String  histID;   //履歴ID
public:
	//コンストラクタ
	TReopen() = default;
	//コピーコンストラクタ
	TReopen(const TReopen& him) = default;
public:
	//代入
	TReopen& operator = (const TReopen& him) = default;
public:
	//再開処理情報を得る
	static bool LoadReopenSet(TReopen& ReopenInf);
	//再開処理情報をセット
	static bool SaveReopenSet(bool IsReopen,const TReopen& reopenInf);
};
#endif

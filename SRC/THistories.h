//---------------------------------------------------------------------------
#ifndef THistoriesH
#define THistoriesH
//---------------------------------------------------------------------------
#include <System.Win.ComObj.hpp>
#include <vector>

//履歴データ
class THistory
{
private:
	String   ID    = L""; //ID(レジストリキー)
	int      Year  = 0;   //年
	int      Month = 0;   //月
	int      Day   = 0;   //日
	String   NameStr;     //名前
	String   ItemStr;     //件名
	String   FilePath;    //ファイルパス
public:
	//コンストラクタ
	THistory() = default;
	//コピーコンストラクタ
	THistory(const THistory& h) = default;
public:
	//代入
	THistory& operator = (const THistory& h) = default;
public:
	//同じキーかチェック
	bool operator == (const String& h)
	{
		return (ID == h);
	}
	//同じ相手か
	bool operator == (const THistory& h)
	{
		return (FilePath.CompareIC(h.FilePath) == 0);
	}
public:
	//全てのメンバーをセット
	bool setAll(const String& sid,int y,int m,int d,const String& nm,const String& itm,const String& fn)
	{
		setID(sid);
		setYear(y);
		setMonth(m);
		setDay(d);
		setName(nm);
		setItem(itm);
		setFilePath(fn);

        return true;
	}

	//IDを得る
	String getID() const
	{
		return ID;
	}
	//IDをセット
	bool setID(const String& sid)
	{
		ID = sid;

		return true;
	}
	//IDが有効か？
	bool isValidID() const
	{
		return (ID != L"");
	}
	//Yearを得る
	int getYear() const
	{
		return Year;
	}
	//IDをセット
	bool setYear(int y)
	{
		Year = y;

		return true;
	}
	//Monthを得る
	int getMonth() const
	{
		return Month;
	}
	//IDをセット
	bool setMonth(int m)
	{
		Month = m;

		return true;
	}
	//Dayを得る
	int getDay() const
	{
		return Day;
	}
	//IDをセット
	bool setDay(int d)
	{
		Day = d;

		return true;
	}
	//名前を得る
	String getName() const
	{
		return NameStr;
	}
	//名前をセット
	bool setName(const String& nm)
	{
		NameStr = nm;

		return true;
	}
	//件名を得る
	String getItem() const
	{
		return ItemStr;
	}
	//件名をセット
	bool setItem(const String& itm)
	{
		ItemStr = itm;

		return true;
	}
	//件名を得る
	String getFilePath() const
	{
		return FilePath;
	}
	//ファイルパスをセット
	bool setFilePath(const String& fn)
	{
		FilePath = fn;

		return true;
	}
public:
	//ID振り直し
	bool renumberID()
	{
		//ID(レジストリキー)
		ID = CreateClassID();

		return true;
	}
	//初期化(IDは空白)
	bool init_hist()
	{
		//データ消去
		*this = THistory();

		return true;
	}
};

//履歴データリスト
class THistories
{
private:
	std::vector<THistory> Histories;
private:
	//IDで検索
	int getIndexFromID(const String& id);
	//履歴をレジストリに記載
	bool write_histreg(const THistory& hist);
	//履歴の上書きか追加を判断する(trueの場合追加) hist_idxは上書きの場合の対象のインデックスを返却
	bool judgeOverwriteOrAdd(const THistory& hist,int& hist_idx);
public:
	//コンストラクタ
	THistories() = default;
public:
	//数を得る
	int size();
	//リストの消去
	bool clear();
	//更新
	bool update(THistory& hist);
	//IDから履歴情報取得
	bool get(const String& id,THistory& hist);
	//インデックスから履歴情報取得
	bool get(int idx,THistory& hist);
	//レジストリから履歴の一覧をセット
	bool load();
	//履歴情報をレジストリに保存
	bool save(const THistory& hist);
	//履歴情報をレジストリから削除
	bool deleteHistReg(THistory& hist);
};

//現在使用中の履歴情報
extern THistory NowHistory;
//履歴データリスト
extern THistories Histories;


#endif

//---------------------------------------------------------------------------
#ifndef THistoriesH
#define THistoriesH
//---------------------------------------------------------------------------
#include <System.IOUtils.hpp>
#include <System.SysUtils.hpp>
#include <System.Win.ComObj.hpp>
#include <vector>

//履歴データ
class THistory
{
private:
	std::wstring ID    = L""; //ID(レジストリキー)
	int          Year  = 0;   //年
	int          Month = 0;   //月
	int          Day   = 0;   //日
	std::wstring NameStr;     //名前
	std::wstring ItemStr;     //件名
	std::wstring FilePath;    //ファイルパス
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
	bool operator == (const std::wstring& h)
	{
		return (ID == h);
	}
	//同じ相手か
	bool operator == (const THistory& h)
	{
		String compStr = FilePath.c_str();

		return (compStr.CompareIC(h.FilePath.c_str()) == 0);
	}
public:
	//全てのメンバーをセット
	bool setAll(const std::wstring& sid,int y,int m,int d,const std::wstring& nm,const std::wstring& itm,const std::wstring& fn)
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
	std::wstring getID() const
	{
		return ID;
	}
	//IDをセット
	bool setID(const std::wstring& sid)
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
	std::wstring getName() const
	{
		return NameStr;
	}
	//名前をセット
	bool setName(const std::wstring& nm)
	{
		NameStr = nm;

		return true;
	}
	//件名を得る
	std::wstring getItem() const
	{
		return ItemStr;
	}
	//件名をセット
	bool setItem(const std::wstring& itm)
	{
		ItemStr = itm;

		return true;
	}
	//ファイルパスを得る
	std::wstring getFilePath() const
	{
		return FilePath;
	}
	//ファイルパスをセット
	bool setFilePath(const std::wstring& fn)
	{
		FilePath = fn;

		return true;
	}
	//拡張子無しのファイル名を得る
	std::wstring getFileNameOnly() const
	{
		return TPath::GetFileNameWithoutExtension(FilePath.c_str()).c_str();
	}
	//格納フォルダパスを得る
	std::wstring getDirectoryName() const
	{
		return TPath::GetDirectoryName(FilePath.c_str()).c_str();
	}
	//日付文字列を得る
	std::wstring getDayString() const
	{
		std::wstring dayStr = std::to_wstring(getYear()) + L"/" + std::to_wstring(getMonth()) + L"/" + std::to_wstring(getDay());

		return dayStr.c_str();
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
	int getIndexFromID(const std::wstring& id);
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
	bool get(const std::wstring& id,THistory& hist);
	//インデックスから履歴情報取得
	bool get(int idx,THistory& hist);
	//レジストリから履歴の一覧をセット
	bool load();
	//履歴情報をレジストリに保存
	bool save(const THistory& hist);
	//履歴情報をレジストリから削除
	bool deleteHistReg(THistory& hist);
	//指定したファイルパスと同じデータがある場合はIDを返す(ない場合はfalse)
	bool getSameFilePathID(const std::wstring& chkFilePath,std::wstring& id);
};

//現在使用中の履歴情報
extern THistory NowHistory;
//履歴データリスト
extern THistories Histories;


#endif

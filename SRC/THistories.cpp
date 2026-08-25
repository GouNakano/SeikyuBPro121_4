//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SeikyuBConst.h"
#include "SBRegIni.h"
#include "THistories.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---- 現在使用中の履歴情報 ----
THistory NowHistory;
//---- 履歴データリスト ----
THistories Histories;

//---------------------------------------------------------------------------
//数を得る
//---------------------------------------------------------------------------
int THistories::size()
{
	return Histories.size();
}
//---------------------------------------------------------------------------
//リストの消去
//---------------------------------------------------------------------------
bool THistories::clear()
{
	Histories.clear();

	return true;
}
//---------------------------------------------------------------------------
//IDで検索
//---------------------------------------------------------------------------
int THistories::getIndexFromID(const String& id)
{
	//検索
	decltype(Histories)::iterator it = std::find(Histories.begin(),Histories.end(),id);
	//チェック
	if(it == Histories.end())
	{
		return -1;
	}
	//値のセット
	int idx = std::distance(Histories.begin(),it);

	return idx;
}
//---------------------------------------------------------------------------
//履歴の上書きか追加を判断する(trueの場合追加) hist_idxは上書きの場合の対象のインデックスを返却
//---------------------------------------------------------------------------
bool THistories::judgeOverwriteOrAdd(const THistory& hist,int& hist_idx)
{
	bool isSame = false;
	//IDで検索
	hist_idx = getIndexFromID(hist.getID());
	//同じもので上書き出来るかチェック
	if(hist_idx >= 0)
	{
		isSame = (Histories[hist_idx] == hist);
	}
	//追加の場合はtrue 上書きの場合は false
	bool isAdd = (isSame == false);

	return isAdd;
}
//---------------------------------------------------------------------------
//履歴をレジストリに記載
//---------------------------------------------------------------------------
bool THistories::write_histreg(const THistory& hist)
{
	// レジストリ
	std::unique_ptr<SBHistRegIni> pReg(new SBHistRegIni);

	// キー名の作成
	String KeyName = NowHistory.getID();
	// 履歴データ保存
	pReg->WriteString (KeyName,INI_REG_FILE_PATH ,hist.getFilePath()); //ファイルパス
	pReg->WriteString (KeyName,INI_REG_NAME      ,hist.getName());     //名前
	pReg->WriteString (KeyName,INI_REG_ITEM_NAME ,hist.getItem());     //件名
	pReg->WriteInteger(KeyName,INI_REG_YEAR      ,hist.getYear());     //年
	pReg->WriteInteger(KeyName,INI_REG_MONTH     ,hist.getMonth());    //月
	pReg->WriteInteger(KeyName,INI_REG_DAY       ,hist.getDay());      //日

	return true;
}
//---------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------
bool THistories::update(THistory& new_hist)
{
	int hist_idx;
	//履歴の上書きか追加を判断する(trueの場合追加)
	bool isAdd = judgeOverwriteOrAdd(new_hist,hist_idx);

	//上書きor新規作成
	if(isAdd == true)
	{
		//IDがない場合追加のためにIDを振り直す
		if(new_hist.isValidID() == false)
		{
			//IDを振り直す
			new_hist.renumberID();
		}
		//追加
		Histories.push_back(new_hist);
	}
	else
	{
		//上書き
		Histories[hist_idx] = new_hist;
	}
	return true;
}
//---------------------------------------------------------------------------
//IDから履歴情報取得
//---------------------------------------------------------------------------
bool THistories::get(const String& id,THistory& hist)
{
	//IDで検索
	int hist_idx = getIndexFromID(id);
	//チェック
	if(hist_idx < 0)
	{
		//IDから履歴情報を取得出来ない
		return false;
	}
	//履歴情報セット
	hist = Histories[hist_idx];

	return true;
}
//---------------------------------------------------------------------------
//インデックスから履歴情報取得
//---------------------------------------------------------------------------
bool THistories::get(int idx,THistory& hist)
{
	//範囲チェック
	if(idx < 0 || idx >= Histories.size())
	{
		//範囲外
		return false;
	}
	//履歴情報セット
	hist = Histories[idx];

	return true;
}
//---------------------------------------------------------------------------
//レジストリから履歴の一覧をセット
//---------------------------------------------------------------------------
bool THistories::load()
{
	// 履歴消去
	clear();
	// 文字列リスト
	std::unique_ptr<TStringList> pSections(new TStringList);
	// レジストリ
	std::unique_ptr<SBHistRegIni> pReg(new SBHistRegIni);
	// セクション一覧を得る
	pReg->ReadSections(pSections.get());
	// セクションの件数
	int SecNum = pSections->Count;
	// リストをセット
	for (int Cnt = 0; Cnt < SecNum; Cnt++)
	{
		// セクション名
		String SectionStr = pSections->Strings[Cnt];

		// データを得る
		int Year        = pReg->ReadInteger(SectionStr,INI_REG_YEAR ,2000);     // 年
		int Month       = pReg->ReadInteger(SectionStr,INI_REG_MONTH,1);        // 月
		int Day         = pReg->ReadInteger(SectionStr,INI_REG_DAY  ,1);        // 日
		String NameStr  = pReg->ReadString(SectionStr ,INI_REG_NAME ,L"");      // 名前
		String ItemStr  = pReg->ReadString(SectionStr ,INI_REG_ITEM_NAME ,L""); // 件名
		String FilePath = pReg->ReadString(SectionStr,INI_REG_FILE_PATH,L"");   // 請求書番頭ファイルのパス
		String FileID   = SectionStr;                                           // 請求書番頭ファイルのID

		// 関連データ
		THistory  pData;
		pData.setAll(FileID,Year,Month,Day,NameStr,ItemStr,FilePath);

		//履歴データリスト更新
		update(pData);
	}
	return true;
}
//---------------------------------------------------------------------------
//履歴情報をレジストリに保存
//---------------------------------------------------------------------------
bool THistories::save(const THistory& hist)
{
	// レジストリ
	std::unique_ptr<SBHistRegIni> pReg(new SBHistRegIni);
	// レジストリをセット
	String SectionStr = hist.getID();

	// データをレジストリに保存
	pReg->WriteInteger(SectionStr,INI_REG_YEAR      ,hist.getYear());     // 年
	pReg->WriteInteger(SectionStr,INI_REG_MONTH     ,hist.getMonth());    // 月
	pReg->WriteInteger(SectionStr,INI_REG_DAY       ,hist.getDay());      // 日
	pReg->WriteString (SectionStr,INI_REG_NAME      ,hist.getName());     // 名前
	pReg->WriteString (SectionStr,INI_REG_ITEM_NAME ,hist.getItem());     // 件名
	pReg->WriteString (SectionStr,INI_REG_FILE_PATH ,hist.getFilePath()); // 請求書番頭ファイルのパス

	return true;
}
//---------------------------------------------------------------------------
//履歴情報をレジストリから削除
//---------------------------------------------------------------------------
bool THistories::deleteHistReg(THistory& hist)
{
	//指定履歴情報を削除
	try
	{
		//IDを得る
		String id = hist.getID();
		//履歴のレジストリオブジェクト作成
		std::unique_ptr<SBHistRegIni> pReg(new SBHistRegIni);
		//削除を試みる
		pReg->EraseSection(hist.getID());
		//リストから削除
		decltype(Histories)::iterator it = std::find_if(Histories.begin(), Histories.end(), [id](const THistory& e)
		{
			return e.getID() == id;
		});
		if(it != Histories.end())
		{
            Histories.erase(it);
        }
	}
	catch (...)
	{
		return false;
	}
	return true;
}


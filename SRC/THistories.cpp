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
int THistories::getIndexFromID(const std::wstring& id)
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
	std::wstring KeyName = NowHistory.getID();
	// 履歴データ保存
	pReg->WriteString (KeyName.c_str(),INI_REG_FILE_PATH ,hist.getFilePath().c_str()); //ファイルパス
	pReg->WriteString (KeyName.c_str(),INI_REG_NAME      ,hist.getName().c_str());     //名前
	pReg->WriteString (KeyName.c_str(),INI_REG_ITEM_NAME ,hist.getItem().c_str());     //件名
	pReg->WriteInteger(KeyName.c_str(),INI_REG_YEAR      ,hist.getYear());             //年
	pReg->WriteInteger(KeyName.c_str(),INI_REG_MONTH     ,hist.getMonth());            //月
	pReg->WriteInteger(KeyName.c_str(),INI_REG_DAY       ,hist.getDay());              //日

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
		//IDを振り直す
		new_hist.renumberID();
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
bool THistories::get(const std::wstring& id,THistory& hist)
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
		int Year              = pReg->ReadInteger(SectionStr,INI_REG_YEAR ,2000);              // 年
		int Month             = pReg->ReadInteger(SectionStr,INI_REG_MONTH,1);                 // 月
		int Day               = pReg->ReadInteger(SectionStr,INI_REG_DAY  ,1);                 // 日
		std::wstring NameStr  = pReg->ReadString(SectionStr ,INI_REG_NAME ,L"").c_str();       // 名前
		std::wstring ItemStr  = pReg->ReadString(SectionStr ,INI_REG_ITEM_NAME ,L"").c_str();  // 件名
		std::wstring filePath = pReg->ReadString(SectionStr,INI_REG_FILE_PATH,L"").c_str();    // 請求書番頭ファイルのパス
		std::wstring FileID   = SectionStr.c_str();                                            // 請求書番頭ファイルのID

		// 関連データ
		THistory  pData;
		pData.setAll(FileID,Year,Month,Day,NameStr,ItemStr,filePath);

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
	std::wstring SectionStr = hist.getID();

	// データをレジストリに保存
	pReg->WriteInteger(SectionStr.c_str(),INI_REG_YEAR      ,hist.getYear());             // 年
	pReg->WriteInteger(SectionStr.c_str(),INI_REG_MONTH     ,hist.getMonth());            // 月
	pReg->WriteInteger(SectionStr.c_str(),INI_REG_DAY       ,hist.getDay());              // 日
	pReg->WriteString (SectionStr.c_str(),INI_REG_NAME      ,hist.getName().c_str());     // 名前
	pReg->WriteString (SectionStr.c_str(),INI_REG_ITEM_NAME ,hist.getItem().c_str());     // 件名
	pReg->WriteString (SectionStr.c_str(),INI_REG_FILE_PATH ,hist.getFilePath().c_str()); // 請求書番頭ファイルのパス

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
		std::wstring id = hist.getID();
		//履歴のレジストリオブジェクト作成
		std::unique_ptr<SBHistRegIni> pReg(new SBHistRegIni);
		//削除を試みる
		pReg->EraseSection(hist.getID().c_str());
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
//---------------------------------------------------------------------------
//指定したファイルパスと同じデータがある場合はIDを返す(ない場合はfalse)
//---------------------------------------------------------------------------
bool THistories::getSameFilePathID(const std::wstring& chkFilePath,std::wstring& id)
{
	std::wstring findID = L"";

	try
	{
		//指定したファイルパスを正規化
		std::wstring cmpPath1 = TPath::GetFullPath(chkFilePath.c_str()).c_str();
		//履歴ループ
		for(int idx = 0;idx < size();idx++)
		{
			//インデックスに対応する履歴情報
			THistory& histInf = Histories[idx];
			// 1. 相対パスや「.」「..」を含む表記を、きれいな絶対パス（フルパス）に補完・正規化
			std::wstring cmpPath2 = TPath::GetFullPath(histInf.getFilePath().c_str()).c_str();
			// 2. Windowsの仕様（大文字小文字を区別しない）に合わせてパスを比較
			if(SameFileName(cmpPath1.c_str(), cmpPath2.c_str()) == true)
			{
				//IDセット
				id = histInf.getID();

				return true;
			}
		}
	}
	catch (...)
	{
		// 無効な文字が含まれているなど、パスとして解析できない場合はIDは返さない
		return L"";
	}
	//見つからないで最後まで来た
	return L"";
}


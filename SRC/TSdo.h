//---------------------------------------------------------------------------
#ifndef TSdoH
#define TSdoH
//---------------------------------------------------------------------------
#include "typDocument.h"

//.sdoファイルのためのクラス
class TSdo
{
private:
	//Iniにフォント設定の情報をセット
	void SetColInfToIni(TMemIniFile *Ini,String Sec,String Val,typFontDef& ECol);
	//フォルダーを削除する
	bool deleteDir(const String folder_path);
	//sdoファイルを展開する
	bool expandSDO(const String sdo_file,std::unique_ptr<TMemIniFile>& pIni,String& TmpIniPath);
	//基礎情報のセット
	bool setBasicInfo(std::unique_ptr<TMemIniFile>& pIni,const String& sdo_file,const String& fileID,typDocument& DocInfo);
	//部品情報の読み出し
	bool readComponents(std::unique_ptr<TMemIniFile>& pIni,typDocument& DocInfo);
	//Iniからフォント設定の情報を読む
	typFontDef GetColInfFromIni(TMemIniFile *Ini,String Sec,String Val);
	//書類ファイルのデータ読み込み
	bool loadDocumentData(std::unique_ptr<TMemIniFile>& pIni,typDocument& DocInfo);
	//グリッドのデータ読み込み
	bool loadGridData(std::unique_ptr<TMemIniFile>& pIni,typDocument& DocInfo);
	//書類情報のバージョン更新
	bool updateDocumentVersion(typDocument& DocInfo);
	//グリッド情報を保存
	bool writeGridInfo(const String& SecName,typDocData& DocData,std::unique_ptr<TMemIniFile>& pIni);
	//書類データの保存
	bool writeDocInfo(const String& SecName,typDocData& DocData,std::unique_ptr<TMemIniFile>& pIni);
	//ラベル内容保存
	bool writeLableInfo(const String& SecName,typDocData& DocData,std::unique_ptr<TMemIniFile>& pIni);
	//イメージ(印影、ロゴ)の保存
	bool writeImageInfo(const String& SecName,const String& TmpDirStr,int KindCnt,typDocData& DocData,std::unique_ptr<TStringList>& pFiles,std::unique_ptr<TMemIniFile>& pIni);
	//基礎情報の保存
	bool writeBasicInfo(typDocument& DocInfo,std::unique_ptr<TMemIniFile>& pIni);
	//部品情報の保存
	bool writeCompoInfo(const String& SecName,typDocument& DocInfo,std::unique_ptr<TMemIniFile>& pIni);
	//現在のファイルのバックアップを取る
	bool makeBackup(typDocument& DocInfo);
	//sdoファイルを作成する
	bool makeSDO(const String& TmpDirStr,std::unique_ptr<TStringList>& pFiles,const String& FilePath);
	//作成されるファイルのリスト(圧縮対象)の原本作成
	bool makeCompression(std::unique_ptr<TStringList>& pFiles,std::unique_ptr<TMemIniFile>& pIni,String& TmpDirStr);
public:
	//デフォルトコンストラクタ
	TSdo() = default;
	//デストラクタ
	virtual ~TSdo() = default;
public:
	//.sdoファイルの読み込み
	bool readSDO(const String& fileID,typDocument& DocInfo);
	//テンプレート.sdoファイルの読み込み
	bool readTemplateSDO(const String& filePath,typDocument& DocInfo);
	//空読み込み
	bool readVoid(typDocument& DocInfo);
	//.sdoファイルの保存
	bool writeSDO(typDocument& DocInfo,const String& FilePath);
};

#endif

//---------------------------------------------------------------------------
#ifndef TLicenseH
#define TLicenseH
//---------------------------------------------------------------------------

//ライセンス関連クラス
class TLicense
{
private:
	//ディスクシリアル文字列を得る
	String GetDiskSerialString();
	//バイナリ配列を文字列化する
	String SetBinToString(unsigned char bin[],int len);
	//ライセンス設定文字列の作成
	String CreateLicenceSettingString(String LicenceApplicationString);
	//ライセンス申請のための文字列を作成する
	String GetLicenceApplicationString();
public:
	//ライセンス設定文字列を得る
	String getLicenceSettingString();
	//現在レジストリに設定されているライセンス文字列を得る
	String getLicenceStringFromReg();
	//正解のライセンス文字列を得る
	String getCorrectLicenceString();

};

#endif

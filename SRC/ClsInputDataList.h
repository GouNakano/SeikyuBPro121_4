//---------------------------------------------------------------------------
#ifndef ClsInputDataListH
#define ClsInputDataListH
//---------------------------------------------------------------------------

//繰り返し入力用ﾘｽﾄｸﾗｽ
class ClsInputDataList
{
public:
	//一件分ﾃﾞｰﾀ定義
	struct InputData
	{
	public:
		String CtrlName; //ｺﾝﾄﾛｰﾙ名
		String Str;      //内容
		String Rank;     //順位(実際には日付＆時刻が入る)
	public:
		//コンストラクタ
		InputData() = default;
		//コピーコンストラクタ
		InputData(const InputData& him) = default;
		//移譲コンストラクタ
		InputData(InputData&& him) = default;
	public:
		//代入
		InputData& operator = (const InputData& him) = default;
		//移譲代入
		InputData& operator = (InputData&& him) = default;
	public:
		bool operator == (const InputData& Him)const
		{
			return (CtrlName == Him.CtrlName && Str == Him.Str);
		}
		bool operator  > (const InputData& Him)const
		{
			if(CtrlName  >  Him.CtrlName)
			{
				return true;
			}
			if(CtrlName  == Him.CtrlName)
			{
				if(Str >  Him.Str)
				{
					return true;
				}
			}
			return false;
		}
		bool operator  < (const InputData& Him)const
		{
			return  ((operator > (Him)) == false);
        }
	};
	//一件分ﾃﾞｰﾀ定義(Rankで並び替え版)
	struct InputDataRank : public InputData
	{
	public:
		bool operator == (const InputData& Him)const
		{
			return (Rank == Him.Rank);
		}
		bool operator  > (const InputData& Him)const
		{
			return (Rank < Him.Rank);
		}
		bool operator  < (const InputData& Him)const
		{
			return (Rank > Him.Rank);
		}
	};
private:
	std::vector<InputData> StrList;
public:
	//ﾌｧｲﾙから読込む
	bool Load();
	//ﾌｧｲﾙへ保存
	bool Save();
public:
	//追加
	void AddInputData(String ctrlname,String str);
	//削除
	void DeleteInputData(String ctrlname,String str);
	//取得
	void GetInputDataList(String ctrlname,TStrings *List);
};

#endif

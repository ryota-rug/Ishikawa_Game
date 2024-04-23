#include "SaveLoad.h"

#define StageNum (16)

using namespace std;

SaveData StageSave[StageNum];
SaveFile Savefile[StageNum];

//string fileName = "Assets/SaveData.csv";

//====================================================================
//用途　：ファイルの読み込み(ロード)
//戻り値：なし
//使い方：ファイルの読み込み用なのでゲーム内では最初だけ呼び出します
//注意点：基本的に呼び出すのは一回のみにしてください(※基本的に使わないでください)
//=====================================================================
void FileLoad()
{
	ifstream ifs("Assets/SaveData.csv");        //ifstream型はファイル読み込みを行う型


	// 読み込み
	vector<string> lines;	// データ格納用
	string line;	        // 一時データ保持用
	// 行取り出し
	while (getline(ifs, line))  //左の引数(文字列)を右の引数に格納
	{
		lines.push_back(line);  //読み込んだファイルの中の文字列を格納しているline変数をvector型のlines変数に格納
	}
	//列取り出し
	SaveFile temp;
	string str;
	char delimiter = ',';  //区切り文字(コンマ)


	for (int i = 0; i < (int)lines.size(); i++)
	{
		string check = lines[i];                //vector型のlines変数の中を1つずつcheck関数の中に格納して確認する
		istringstream issSave(check);         //check変数をistringstream型に変換してissSaveに格納(「,」区切りで読み込めるようになる)
		//初めてのステージか否か
		getline(issSave, str, delimiter);     //stringstream型の入力文字列をコンマで分割しstr変数に格納
		temp.AgainStage = stoi(str);                   //文字列から数値への変換
		if (temp.AgainStage == 0) StageSave[i].AgainStage = false;
		else StageSave[i].AgainStage = true;
		//クリアしているステージか否か
		getline(issSave, str, delimiter);
		temp.ClearStage = stoi(str);
		if (temp.ClearStage == 0) StageSave[i].ClearStage = false;
		else StageSave[i].ClearStage = true;
		//最小打ち付け回数(ベスト)
		getline(issSave, str, delimiter);
		temp.MinHitnum = stoi(str);
		StageSave[i].MinHitnum = temp.MinHitnum;
		//杭の総打ち付け回数
		getline(issSave, str, delimiter);
		temp.AllHitnum = stoi(str);
		StageSave[i].AllHitnum = temp.AllHitnum;
		//ブロックの総破壊数
		getline(issSave, str, delimiter);
		temp.AllBlocknum = stoi(str);
		StageSave[i].AllBlocknum = temp.AllBlocknum;

		//格納
		//m_StageSave.push_back(temp);        //アイテム用のvector変数の中に格納
		//後片付け
		issSave.clear(stringstream::goodbit);  //clear()はメモリの中をすべて消去、しかしキャパシティは0にならない(stringstream::goodbitで0にしてる?)

	}

	ifs.close();     //ファイルを閉じる
}

//====================================================================
//用途　：ファイルの書き込み(セーブ)
//戻り値：なし
//使い方：ファイルの書き込み用なのでゲーム内では最後だけ呼び出します
//注意点：基本的に呼び出すのは一回のみにしてください(※基本的に使わないでください)
//=====================================================================
void FileSave()
{
	char delimiter = ',';  //区切り文字(コンマ)

	for (int i = 0; i < StageNum; i++)
	{
		if (StageSave[i].AgainStage == false) Savefile[i].AgainStage = 0;
		else Savefile[i].AgainStage = 1;
		if (StageSave[i].ClearStage == false) Savefile[i].ClearStage = 0;
		else Savefile[i].ClearStage = 1;
		Savefile[i].MinHitnum = StageSave[i].MinHitnum;
		Savefile[i].AllHitnum = StageSave[i].AllHitnum;
		Savefile[i].AllBlocknum = StageSave[i].AllBlocknum;
	}

	ofstream ofs("Assets/SaveData.csv");

	for (int i = 0; i < StageNum; i++)
	{
		ofs << Savefile[i].AgainStage << delimiter;
		ofs << Savefile[i].ClearStage << delimiter;
		ofs << Savefile[i].MinHitnum << delimiter;
		ofs << Savefile[i].AllHitnum << delimiter;
		ofs << Savefile[i].AllBlocknum << delimiter;
		ofs << endl;
	}

	ofs.close();    //ファイルを閉じる
}

//====================================================================
//用途　：ステージを指定して欲しいステージのセーブ情報を得る
//戻り値：SaveData型
//使い方：引数にセーブデータの欲しいステージを指定して返す
//注意点：なし
//=====================================================================
SaveData GetLoadStage(SaveElea stage)
{
	if (stage < 0 || stage >= StageNum)    //配列外アクセス判定
	{//例外処理
		SaveData error = {
			-1, -1, -1, -1
		};
		return error;              //配列外アクセスの場合にerorrの値を返す
	}

	return StageSave[stage];         //指定された番号に格納されているアイテム情報を返す
}

//====================================================================
//用途　：セーブしたい情報をゲーム内で保持しているセーブ構造体に保存(セーブ)
//戻り値：なし
//使い方：引数に(訪れたことがあるか、クリアしたことがあるか、
//　　　　何回打ち付けたか、何個ブロックを破壊したか)を指定
//注意点：ゲーム内で使うセーブはこれを使ってください
//=====================================================================
void SetSave(SaveElea stage, bool again, bool clear, int hit, int bloak)
{
	StageSave[stage].AgainStage = again;
	StageSave[stage].ClearStage = clear;
	if (StageSave[stage].MinHitnum > hit)
		StageSave[stage].MinHitnum = hit;
	StageSave[stage].AllHitnum += hit;
	StageSave[stage].AllBlocknum += bloak;
}

void SetAgain(SaveElea stage, bool again)
{
	StageSave[stage].AgainStage = again;
}

//====================================================================
//用途　：ゲーム内のセーブデータをリセット
//戻り値：なし
//使い方：新しい人がゲームを始める時に使ってください(ファイルにセーブロードする意味ってある?)
//注意点：なし
//=====================================================================
void ResetData()
{
	for (int i = 0; i < StageNum; i++)
	{
		StageSave[i].AgainStage = false;
		StageSave[i].ClearStage = false;
		StageSave[i].MinHitnum = 999;
		StageSave[i].AllHitnum = 0;
		StageSave[i].AllBlocknum = 0;
	}
}

void CheatData()
{
	for (int i = 0; i < StageNum; i++)
	{
		StageSave[i].AgainStage = true;
		StageSave[i].ClearStage = true;
		StageSave[i].MinHitnum = 1;
		StageSave[i].AllHitnum = 999;
		StageSave[i].AllBlocknum = 999;
	}
}
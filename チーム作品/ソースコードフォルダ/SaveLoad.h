
#pragma once
#ifndef __SAVELOAD_H__
#define __SAVELOAD_H__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

enum SaveElea
{
	Stage11,
	Stage12,
	Stage13,
	Stage14,
	Stage15,
	Stage21,
	Stage22,
	Stage23,
	Stage24,
	Stage25,
	Stage31,
	Stage32,
	Stage33,
	Stage34,
	Stage35,

};

//ゲーム内で扱うセーブデータ(何かするときは基本的にこの構造体を扱ってください)
//ゲーム内にセーブデータを保持している構造体
struct SaveData
{
	bool AgainStage;      //訪れたことがあるステージ(true:1 false:0)
	bool ClearStage;      //クリアしたステージ(true:1 false:0)
	int MinHitnum;        //杭の最小打ち付け回数(ベスト)
	int AllHitnum;        //杭の総打ち付け回数
	int AllBlocknum;      //ブロックの総破壊数
};

//ファイルアクセス用の構造体(ファイルの読み込み書き込み用なので扱わないでください)
//ゲーム内で扱うセーブデータに変換するための構造体
struct SaveFile
{
	int AgainStage;      //訪れたことがあるステージ(true:1 false:0)
	int ClearStage;      //クリアしたステージ(true:1 false:0)
	int MinHitnum;       //杭の最小打ち付け回数(ベスト)
	int AllHitnum;       //杭の総打ち付け回数
	int AllBlocknum;     //ブロックの総破壊数
};


void FileLoad();            //ファイルの読み込み&ゲーム内セーブ情報に格納(ロード)(ゲーム開始時のみ？)
void FileSave();            //ファイルに書き込む(セーブ)(ゲーム終了時のみ？)
SaveData GetLoadStage(SaveElea stage);		//指定された番号のステージ情報を取得
void SetSave(SaveElea stage, bool again, bool clear, int hit, int bloak);   //ゲーム内セーブ情報に格納
void SetAgain(SaveElea stage, bool again);	//入場したか情報だけ保存する
void ResetData();                           //ゲーム内のセーブデータをリセット
void CheatData();	//全ステージ解放


#endif


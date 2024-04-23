#include "XboxKeyboard.h"

#define RightStickDeadZone (5000)

DWORD dwResult;
XINPUT_STATE state;     //XINPUT_STATE型の構造体宣言(コントローラーの変更があったか、現在の状態)
XINPUT_STATE oldstate;

XINPUT_VIBRATION vibration;
int Vibtime = 0;
bool Stop = false;

//====================================================================
//用途　：コントローラーの状態を取得(更新)
//戻り値：なし
//使い方：main.cppかGame.cppのUpdate関数の初めのほうに書いてください
//注意点：現在コントローラーは一台のみの設定にしてあります
//=====================================================================
void UpdateGamePad()
{
	ZeroMemory(&oldstate, sizeof(XINPUT_STATE));
	oldstate = state;
	static int Count = 0;

	for (DWORD i = 0; i < 1; i++)
	{		                      
		ZeroMemory(&state, sizeof(XINPUT_STATE));      //XINPUT_STATE型のメモリ初期化

	    //XInputからコントローラの情報を取得(絶対消さないで)
		dwResult = XInputGetState(i, &state);    //引数(コントローラーのインデックス、 XINPUT_STATE構造体へのポインタ)		

		//バイブレーションの設定
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = 0;                       //バイブレーションの強さ設定(とりあえず適当な値で初期化しています)
		vibration.wRightMotorSpeed = 0;
	}

	if (Stop != false)
	{
		Count++;
		if (Count > Vibtime)
		{
			SetPowerVibration(0, 0);
			XInputSetState(0, &vibration);
			Count = 0;
			Stop = false;
		}
	}
}

//====================================================================
//用途　：押されているキーの判定
//戻り値：特に考慮しなくてよい
//使い方：if文で囲ってあげるとよろしいかと
//注意点：なし
//=====================================================================
int InputPressKey(Key key)
{
	switch (key)
	{
	case A_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
		break;
	case B_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
		break;
	case X_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
		break;
	case Y_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
		break;
	case START_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
		break;
	case BACK_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
		break;
	case LEFT_SHOULDER:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
		break;
	case RIGHT_SHOULDER:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
		break;
	case UP_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
		break;
	case DOWN_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
		break;
	case LEFT_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	case RIGHT_BUTTON:
		return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
		break;
	case LEFT_TRIGGER:
		return (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		break;
	case RIGHT_TRIGGER:
		return (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		break;
	case LEFT_STICK:
		return (((state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) || (state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			|| ((state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) || (state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)));
		break;
	case RIGHT_STICK:
		return (((state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) || (state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			|| ((state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) || (state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)));
		break;
	default:
		return 0;
		break;
	}
}

//====================================================================
//用途　：押した瞬間のキーの判定
//戻り値：特に考慮しなくてよい
//使い方：if文で囲ってあげるとよろしいかと
//注意点：なし
//=====================================================================
int InputTriggerKey(Key key)
{
	switch (key)
	{
	case A_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_A;  //ビット演算^(排他的OR演算) &(AND演算)
		break;
	case B_BUTTON:				
		return TRIGGER & XINPUT_GAMEPAD_B;
		break;
	case X_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_X;
		break;
	case Y_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_Y;
		break;
	case START_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_START;
		break;
	case BACK_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_BACK;
		break;
	case LEFT_SHOULDER:
		return TRIGGER & XINPUT_GAMEPAD_LEFT_SHOULDER;
		break;
	case RIGHT_SHOULDER:
		return TRIGGER & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		break;
	case UP_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_UP;
		break;
	case DOWN_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_DOWN;
		break;
	case LEFT_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_LEFT;
		break;
	case RIGHT_BUTTON:
		return TRIGGER & XINPUT_GAMEPAD_DPAD_RIGHT;
		break;
	case LEFT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButton(state.Gamepad.bLeftTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return (TRIGGER & state.Gamepad.wButtons && InputPressKey(LEFT_TRIGGER));
		break;
	case RIGHT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButton(state.Gamepad.bRightTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return (TRIGGER & state.Gamepad.wButtons) && InputPressKey(RIGHT_TRIGGER);
		break;
	case LEFT_STICK:
		state.Gamepad.wButtons |= StickChangeButton(
			state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		return (TRIGGER & state.Gamepad.wButtons && InputPressKey(LEFT_STICK));
		break;
	case RIGHT_STICK:
		state.Gamepad.wButtons |= StickChangeButton(
			state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		return (TRIGGER & state.Gamepad.wButtons && InputPressKey(RIGHT_STICK));
		break;	
	default:
		return 0;
		break;
	}
}

//====================================================================
//用途　：キーを離した瞬間の判定
//戻り値：特に考慮しなくてよい
//使い方：if文で囲ってあげるとよろしいかと
//注意点：スティックは対応しておりません(どうしても必要なら実装します)
//        トリガーはすぐに離したりすると反応しないことがあります
//=====================================================================
int InputReleaseKey(Key key)
{
	switch (key)
	{
	case A_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_A;
		break;
	case B_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_B;
		break;
	case X_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_X;
		break;
	case Y_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_Y;
		break;
	case START_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_START;
		break;
	case BACK_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_BACK;
		break;
	case LEFT_SHOULDER:
		return RELEASE & XINPUT_GAMEPAD_LEFT_SHOULDER;
		break;
	case RIGHT_SHOULDER:
		return RELEASE & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		break;
	case UP_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_UP;
		break;
	case DOWN_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_DOWN;
		break;
	case LEFT_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_LEFT;
		break;
	case RIGHT_BUTTON:
		return RELEASE & XINPUT_GAMEPAD_DPAD_RIGHT;
		break;
	case LEFT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButtonReleaseVer(
			state.Gamepad.bLeftTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return TRIGGER & state.Gamepad.wButtons && state.Gamepad.bLeftTrigger > 0.0f;
		break;
	case RIGHT_TRIGGER:
		state.Gamepad.wButtons |= TriggerChangeButtonReleaseVer(
			state.Gamepad.bRightTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		return TRIGGER & state.Gamepad.wButtons && state.Gamepad.bRightTrigger > 0.0f;
		break;
	default:
		return 0;
		break;
	}
}

//====================================================================
//用途　：スティックを傾けた時の値を返す(Press)
//戻り値：XMFLOAT2型
//使い方：プレイヤーの座標更新などにおすすめです
//注意点：-1.0～1.0の値で返します
//=====================================================================
DirectX::XMFLOAT2 GetPressStick()
{
	DirectX::XMFLOAT2 normalized(0, 0);
	float normalizedMagnitude = 0;              //0.0～1.0に補正した大きさベクトルを格納する変数

	if(InputPressKey(LEFT_STICK))
	{
		float LX = state.Gamepad.sThumbLX;    //左スティックのX軸
		float LY = state.Gamepad.sThumbLY;    //左スティックのY軸

		float magnitudeL = sqrt(LX * LX + LY * LY);  //スティックを傾けた方向のベクトルの大きさ

		normalized.x = LX / magnitudeL;        //スティックを傾けた方向のベクトル方向(X軸)
		normalized.y = LY / magnitudeL;        //スティックを傾けた方向のベクトル方向(Y軸)

		//スティックが円形のデッドゾーンの外側にあるか(スティックを傾けたときの最大値)
		if (magnitudeL > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)     //スティックのあそび(実際に反応するまでの余白みたいなもの)を超えたら
		{
			if (magnitudeL > 32767) magnitudeL = 32767;           //スティックのベクトルの大きさが最大値を超えたとき最大値に補正

			magnitudeL -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;    //実際に使われる分のベクトルの大きさを計算

			normalizedMagnitude = magnitudeL / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);     //使われているベクトルの大きさを0.0～1.0の値に補正
		}
		else
		{
			magnitudeL = 0.0f;
			normalizedMagnitude = 0.0f;
		}
	}
	else if(InputPressKey(RIGHT_STICK))
	{
		 float RX = state.Gamepad.sThumbRX;
		float RY = state.Gamepad.sThumbRY;

		float magnitudeR = sqrt(RX * RX + RY * RY);

		normalized.x = RX / magnitudeR;
		normalized.y = RY / magnitudeR;

		//スティックが円形のデッドゾーンの外側にあるか(スティックを傾けたときの最大値)
		if (magnitudeR > RightStickDeadZone)
		{
			if (magnitudeR > 32767) magnitudeR = 32767;

			magnitudeR -= RightStickDeadZone;

			normalizedMagnitude = magnitudeR / (32767 - RightStickDeadZone);
		}
		else
		{
			magnitudeR = 0.0f;
			normalizedMagnitude = 0.0f;
		}
	}

	normalized.x *= normalizedMagnitude;
	normalized.y *= normalizedMagnitude;
	return normalized;
}

//====================================================================
//用途　：トリガーをどれくらい押しているか値を返す(Press)
//戻り値：float型
//使い方：溜めの動作などにおすすめです
//注意点：0～255の値で返します
//=====================================================================
float GetPressTrigger()
{
	float normalized = 0;
	float normalizedMagnitude = 0;

	if (InputPressKey(LEFT_TRIGGER))
	{
		float LT = state.Gamepad.bLeftTrigger;
		if (LT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			if (LT > 255) LT = 255;
			LT -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			normalizedMagnitude = LT / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else if(LT < 30)
		{
			LT = 0.0f;
			normalizedMagnitude = 0.0f;
		}
		normalized = LT;
	}
	else if (InputPressKey(RIGHT_TRIGGER))
	{
		float RT = state.Gamepad.bRightTrigger;
		if (RT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			if (RT > 255) RT = 255;
			RT -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			normalizedMagnitude = RT / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else if(RT < 30)
		{
			RT = 0.0f;
			normalizedMagnitude = 0.0f;
		}
		normalized = RT;
	}
	normalized *= normalizedMagnitude;
	return normalized;
}

//====================================================================
//用途　：スティックを傾けた瞬間の値を返す(Trigger)
//戻り値：XMFLOAT2型
//使い方：特になし
//注意点：使うとスティックの入力が変な感じになります
//        (現在原因究明中！※出来るだけGetPressStick()で代用しましょう)
//=====================================================================
DirectX::XMFLOAT2 GetTriggerStick()
{
	DirectX::XMFLOAT2 Clone(0.0f, 0.0f);

	if (InputTriggerKey(LEFT_STICK))
	{
		Clone = GetPressStick();
	}
	else if (InputTriggerKey(RIGHT_STICK))
	{
		Clone = GetPressStick();
	}

	return Clone;
}

//====================================================================
//用途　：トリガーを押した瞬間の値を返す(Trigger)
//戻り値：float型
//使い方：特になし
//注意点：基本的にこの関数は使い道ないです(しかも押した瞬間だから返る値も小さすぎる)
//=====================================================================
float GetTriggerTrigger()
{
	float Clone = 0.0f;
	if (InputTriggerKey(LEFT_TRIGGER))
	{
		Clone = GetPressTrigger();
	}
	if (InputTriggerKey(RIGHT_TRIGGER))
	{
		Clone = GetPressTrigger();
	}
	return Clone;
}

//====================================================================
//用途　：何かボタンを押したとき反応する(トリガー)
//戻り値：int型
//使い方：if文で囲ってあげればよいかと
//注意点：なし
//=====================================================================
int AllKeyTrigger()
{
	if (InputTriggerKey(A_BUTTON) || InputTriggerKey(B_BUTTON) || InputTriggerKey(X_BUTTON) || InputTriggerKey(Y_BUTTON)
		|| InputTriggerKey(START_BUTTON) || InputTriggerKey(BACK_BUTTON) || InputTriggerKey(LEFT_SHOULDER)
		|| InputTriggerKey(RIGHT_SHOULDER) || InputTriggerKey(UP_BUTTON) || InputTriggerKey(DOWN_BUTTON)
		|| InputTriggerKey(LEFT_BUTTON) || InputTriggerKey(RIGHT_BUTTON) || InputTriggerKey(LEFT_TRIGGER)
		|| InputTriggerKey(RIGHT_TRIGGER) || InputTriggerKey(LEFT_STICK) || InputTriggerKey(RIGHT_STICK))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//====================================================================
//用途　：ABXYのボタンのみ使う
//戻り値：int型
//使い方：if文で囲ってあげればよいかと(決定の操作で使えるかもしれない)
//注意点：なし
//=====================================================================
int AlfaKeyTrigger()
{
	if (InputTriggerKey(A_BUTTON) || InputTriggerKey(B_BUTTON)
		|| InputTriggerKey(X_BUTTON) || InputTriggerKey(Y_BUTTON))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//====================================================================
//用途　：ABXYのボタンのみ使う(Press)
//戻り値：int型
//使い方：if文で囲ってあげればよいかと(決定の操作で使えるかもしれない)
//注意点：なし
//=====================================================================
int AlfaKeyPress()
{
	if (InputPressKey(A_BUTTON) || InputPressKey(B_BUTTON)
		|| InputPressKey(X_BUTTON) || InputPressKey(Y_BUTTON))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//====================================================================
//用途　：スティック入力をキー入力に変換
//戻り値：WORD型
//使い方：キー入力にしてTriggerなどの判定に使う
//注意点：基本的に別の関数内で使う用です(使わないでください)
//=====================================================================
WORD StickChangeButton(SHORT StickX, SHORT StickY, SHORT DeadZone)
{
	WORD wButton = 0;
	if (StickY >= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if(StickY <= -DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_DOWN;
	}
	if (StickX <= -DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (StickX >= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButton;
}

//====================================================================
//用途　：トリガー入力をキー入力に変換
//戻り値：WORD型
//使い方：キー入力にしてTriggerなどの判定に使う
//注意点：基本的に別の関数内で使う用です(使わないでください)
//=====================================================================
WORD TriggerChangeButton(BYTE Trigger, BYTE DeadZone)
{
	WORD wButton = 0;

	if (Trigger >= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_UP;
	}	

	return wButton;
}

//====================================================================
//用途　：トリガー入力をキー入力に変換(ReleaseVer)
//戻り値：WORD型
//使い方：キー入力にしてReleaseなどの判定に使う
//注意点：基本的に別の関数内で使う用です(使わないでください)
//=====================================================================
WORD TriggerChangeButtonReleaseVer(BYTE Trigger, BYTE DeadZone)
{
	WORD wButton = 0;

	if (Trigger <= DeadZone)
	{
		wButton |= XINPUT_GAMEPAD_DPAD_UP;
		wButton |= XINPUT_GAMEPAD_DPAD_DOWN;
		wButton |= XINPUT_GAMEPAD_DPAD_LEFT;
		wButton |= XINPUT_GAMEPAD_DPAD_RIGHT;
		wButton |= XINPUT_GAMEPAD_START;
		wButton |= XINPUT_GAMEPAD_BACK;
		wButton |= XINPUT_GAMEPAD_LEFT_SHOULDER;
		wButton |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
		wButton |= XINPUT_GAMEPAD_A;
		wButton |= XINPUT_GAMEPAD_B;
		wButton |= XINPUT_GAMEPAD_X;
		wButton |= XINPUT_GAMEPAD_Y;
	}

	return wButton;
}

//====================================================================
//用途　：バイブレーションの強度を変更
//戻り値：なし
//使い方：引数に左のモーターと右のモーターの強度を設定
//注意点：強度は0～65535の間で設定してください(左右の強度は違っても大丈夫です)
//        デフォルトは左(0),右(0)に設定してあります。
//=====================================================================
void SetPowerVibration(WORD LEFT, WORD RIGHT)  //強度0～65535
{
	vibration.wLeftMotorSpeed = LEFT;
	vibration.wRightMotorSpeed = RIGHT;
}

//====================================================================
//用途　：バイブレーションさせる
//戻り値：なし
//使い方：バイブレーションさせたいところで呼ぶ
//注意点：SetPowerVibration(引数)で強度を設定してからでないと揺れない
//　　　　引数に振動させたいフレーム数を入力
//=====================================================================
void SetVibration(int num)
{
	XInputSetState(0, &vibration);
	Vibtime = num;
	Stop = true;
}

//====================================================================
//用途　：バイブレーションを強制的に発動(止める関数を呼ぶまで)
//戻り値：なし
//使い方：バイブレーションさせたいところで呼ぶ
//注意点：SetPowerVibration(引数)で強度を設定してからでないと揺れない
//=====================================================================
void MoveVibration()
{
	XInputSetState(0, &vibration);
}

//====================================================================
//用途　：バイブレーションを強制的止める
//戻り値：なし
//使い方：バイブレーション強制終了させたいところで呼ぶ
//注意点：なし
//=====================================================================
void StopVibration()
{
	SetPowerVibration(0, 0);
	XInputSetState(0, &vibration);
}

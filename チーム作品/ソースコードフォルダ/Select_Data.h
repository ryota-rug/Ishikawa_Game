#ifndef ___SELECT_DATA_H___
#define ___SELECT_DATA_H___

#define SELECT1_POS_X (140)// (240)
#define SELECT2_POS_X (390)// (440)
#define SELECT3_POS_X (640)// (640)
#define SELECT4_POS_X (890)// (840)
#define SELECT5_POS_X (1140)//(1040)

namespace SelectState
{
	enum SELECT
	{
		SELECT_1 = 1,
		SELECT_2 = 2,
		SELECT_3 = 3,
		SELECT_4 = 4,
		SELECT_5 = 5,
	};

	enum STAGE
	{
		STAGE_1 = 1,
		STAGE_2 = 2,
		STAGE_3 = 3,
		STAGE_4 = 4,
		STAGE_5 = 5,
	};

	SELECT GetSelect();
	void SetSelect(SelectState::SELECT);

	STAGE GetStage();
	void SetStage(SelectState::STAGE);
}




#endif // !___SELECT_DATA_H___

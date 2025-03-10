#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Base.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Mode
{
	class Regular
		: public Base
	{
	public:
		// コンストラクタ
		Regular( PScene pScene, const Conf::Regular &conf );

		// 次のステージを取得する
		virtual PStage GetNextStage();
		// 乱数生成器の取得
		virtual PRandom GetRandom() const;
		// シーンの再起動
		virtual void Restart() const;

	private:
		PRandom mpRandom;

		// 更新時の処理
		virtual void OnUpdate();
		// 描画時の処理
		virtual void OnDraw() const;
	};
}
}
}
}
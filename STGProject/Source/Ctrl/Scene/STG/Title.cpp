#include "PCH.h"
#include "Title.h"

using namespace Game;
using namespace Ctrl::Scene::STG;
namespace py = boost::python;


// 1�t���[�����̏�ԍX�V
void Title::UpdateState()
{
	currentView.attr( "update" )();

	currentView.attr( "draw" )();
}


// �R���X�g���N�^
Title::Title()
: currentView()
{
	py::object pyConf = py::import( "STG.Title.Conf" );
	currentView = pyConf.attr( "getTitleInstance" )();
}
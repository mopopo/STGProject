#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/iostreams/stream.hpp>
#include "Util/File/Detail/SourceOfFile.h"
#include "Util/File/Detail/DeviceOfDynamicFile.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace File
{
	// �R���X�g���N�^��PFile��n�����ƂŃX�g���[�����쐬�ł���
	typedef boost::iostreams::stream<Detail::SourceOfFile> FileStream;
	// �R���X�g���N�^��IDynamicFile::SharedPtr��n�����ƂŃX�g���[�����쐬�ł���
	typedef boost::iostreams::stream<Detail::DeviceOfDynamicFile> DynamicFileStream;
}
}
}
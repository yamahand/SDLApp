#include "Core/File.h"
#include "Core/FileLoader.h"

namespace lib {

File::File(const FileLoader& loader) {
	m_buffer = loader.GetBuffer();
	m_size = loader.GetSize();
}

}  // namespace lib

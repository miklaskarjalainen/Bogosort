#pragma once

namespace Sorting {

	template<typename ArrayType>
	class Sort {
	public:
		Sort(ArrayType& array)
			: m_Array(array) {}
        
	protected:
		ArrayType& m_Array;
	};

}
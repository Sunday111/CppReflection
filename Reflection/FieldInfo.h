#pragma once

namespace edt::reflection
{
	class TypeInfo;

	class FieldInfo
	{
	public:
		/* Field type
		 */
		virtual const TypeInfo* GetType() const = 0;

		/* Offset in bytes from beginning of object to this field
		 */
		virtual size_t GetByteOffset() const = 0;

		virtual const char* GetName() const = 0;

		// 
		virtual ~ClassFieldInfo() = default;
	};
}

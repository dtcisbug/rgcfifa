#ifndef SERIALIZE_INC
#define SERIALIZE_INC

//数据协议包序列化支持，目前只支持基本数据类型， 以后会对STL容器类型支持进行扩展

template <typename Type, size_t Size>
struct Array
{
	typedef Type elem_type;
	static const size_t elem_size = Size;
};

namespace std
{
template <class Type, class AllocatorType > class vector;	//for std::vector serialize
}


template <bool Boolean, class Type = void>
struct EnableIf { typedef Type type; };
template <class Type> struct EnableIf<false, Type > {};

template <class Type> struct IsShortInteger { static const bool s_Value = false; };
template <> struct IsShortInteger<Int16> { static const bool s_Value = true; };
template <> struct IsShortInteger<UInt16> { static const bool s_Value = true; };

template <class Type> struct IsInteger { static const bool s_Value = false; };
template <> struct IsInteger<bool> { static const bool s_Value = true; };
template <> struct IsInteger<wchar_t> { static const bool s_Value = true; };
template <> struct IsInteger<Int8> { static const bool s_Value = true; };
template <> struct IsInteger<Int16> { static const bool s_Value = true; };
template <> struct IsInteger<Int32> { static const bool s_Value = true; };
template <> struct IsInteger<Int64> { static const bool s_Value = true; };
template <> struct IsInteger<UInt8> { static const bool s_Value = true; };
template <> struct IsInteger<UInt16> { static const bool s_Value = true; };
template <> struct IsInteger<UInt32> { static const bool s_Value = true; };
template <> struct IsInteger<UInt64> { static const bool s_Value = true; };

template <class Type> struct IsFloat { static const bool s_Value = false; };
template <> struct IsFloat<float> { static const bool s_Value = true; };

template <class Type> struct IsDouble { static const bool s_Value = false; };
template <> struct IsDouble<double> { static const bool s_Value = true; };

template <class Type> struct IsArray { static const bool s_Value = false; };
template <class Type, size_t Size> struct IsArray<Array<Type, Size> > { static const bool s_Value = true; };	//能traits出来，就是数组

template <class Type>
struct IsStdVector { static const bool s_Value = false; };
template <class ValueType, class AllocatorType>
struct IsStdVector<std::vector<ValueType, AllocatorType > >  { static const bool s_Value = true; };

//////////////////////////////////////////////////////////////////////////
template <typename Type, typename Enable = void>
struct S11NTraits
{
	static UInt32 Size(const Type&)
	{
		return 0;
	}

	static UInt32 Serialize(Type& instance, std::vector<UInt8>& buffer)
	{
		return 0;
	}

	static UInt32 Unserialize(Type& instance, void* buffer, UInt32 size)
	{
		return 0;
	}
};

//指针
template <>
struct S11NTraits<void *>
{
	static UInt32 Size(const void *&)
	{
		return sizeof(void *);
	}

	static UInt32 Serialize(const void *& instance, std::vector<UInt8>& buffer)
	{
		const UInt8* data = reinterpret_cast<const UInt8 *>(&instance);
		buffer.insert(buffer.end(), data, data + sizeof(void *));
		return sizeof(void *);
	}

	static UInt32 Unserialize(void *& instance, void* buffer, UInt32 size)
	{
		if(sizeof(void *) > size)
			return static_cast<UInt32>(-1);
		memcpy(&instance, buffer, sizeof(void *));
		return sizeof(void *);
	}
};

//整数
template <class Type>
struct S11NTraits<Type, typename EnableIf<IsInteger<Type >::s_Value>::type>
{
	static UInt32 Size(const Type&)
	{
		return sizeof(Type);
	}

	static UInt32 Serialize(const Type& instance, std::vector<UInt8>& buffer)
	{
		const UInt8* data = reinterpret_cast<const UInt8 *>(&instance);
		buffer.insert(buffer.end(), data, data + sizeof(Type));
		return sizeof(Type);
	}

	static UInt32 Unserialize(Type& instance, void* buffer, UInt32 size)
	{
		if(sizeof(Type) > size)
			return static_cast<UInt32>(-1);
		memcpy(&instance, buffer, sizeof(Type));
		return sizeof(Type);
	}
};

//float
template <class Type>
struct S11NTraits<Type, typename EnableIf<IsFloat<Type >::s_Value>::type>
{
	static UInt32 Size(const Type&)
	{
		return sizeof(Type);
	}

	static UInt32 Serialize(const Type& instance, std::vector<UInt8>& buffer)
	{
		const UInt8* data = reinterpret_cast<const UInt8 *>(&instance);
		buffer.insert(buffer.end(), data, data + sizeof(Type));
		return sizeof(Type);
	}

	static UInt32 Unserialize(Type& instance, void* buffer, UInt32 size)
	{
		if(sizeof(Type) > size)
			return static_cast<UInt32>(-1);
		memcpy(&instance, buffer, sizeof(Type));
		return sizeof(Type);
	}
};

//double
template <class Type>
struct S11NTraits<Type, typename EnableIf<IsDouble<Type >::s_Value>::type>
{
	static UInt32 Size(const Type&)
	{
		return sizeof(Type);
	}

	static UInt32 Serialize(const Type& instance, std::vector<UInt8>& buffer)
	{
		const UInt8* data = reinterpret_cast<const UInt8 *>(&instance);
		buffer.insert(buffer.end(), data, data + sizeof(Type));
		return sizeof(Type);
	}

	static UInt32 Unserialize(Type& instance, void* buffer, UInt32 size)
	{
		if(sizeof(Type) > size)
			return static_cast<UInt32>(-1);
		memcpy(&instance, buffer, sizeof(Type));
		return sizeof(Type);
	}
};

//Array
template <class Type>
struct S11NTraits<Type, typename EnableIf<IsArray<Type >::s_Value>::type>
{
	typedef typename Type::elem_type elem_type;
	static const size_t elem_size = Type::elem_size;

	static UInt32 Size(const elem_type*)
	{
		return sizeof(elem_type) * elem_size;
	}

	static UInt32 Serialize(elem_type* instance, std::vector<UInt8>& buffer)
	{
		const UInt8* data = reinterpret_cast<const UInt8 *>(instance);
		buffer.insert(buffer.end(), data, data + sizeof(elem_type) * elem_size);
		return sizeof(elem_type) * elem_size;
	}

	static UInt32 Unserialize(elem_type* instance, void* buffer, UInt32 size)
	{
		if(elem_size > size)
			return static_cast<UInt32>(-1);
		memcpy( instance, buffer, sizeof(elem_type) * elem_size );
		return sizeof(elem_type) * elem_size;
	}
};

//String
template <>
struct S11NTraits<std::string >
{
	static UInt32 Size(const std::string& s)
	{
		return s.length() + 2;
	}

	static UInt32 Serialize(const std::string& str, std::vector<UInt8>& buffer)
	{
		UInt16 l = static_cast<UInt16>(str.length());
		const UInt8* data = reinterpret_cast<const UInt8 *>(&l);
		buffer.insert(buffer.end(), data, data + 2);
		if(l > 0)
		{
			buffer.insert(buffer.end(), str.begin(), str.end());
		}
		return l + 2;
	}

	static UInt32 Unserialize(std::string& str, void* buffer, UInt32 size)
	{
		if(size < 2)
			return static_cast<UInt32>(-1);
		UInt16 l;
		memcpy(&l, buffer, 2);
		if(size < static_cast<UInt32>(l) + 2)
			return static_cast<UInt32>(-1);
		str.resize(l);
		if(l > 0)
			memcpy( &str[0], static_cast<char *>(buffer) + 2, l );
		return 2 + l;
	}
};

template <class Type>
struct S11NTraits<Type, typename EnableIf<IsStdVector<Type >::s_Value>::type>
{
	typedef typename Type::value_type ElemType;
	typedef typename Type::const_iterator IteratorType;

	static UInt32 Size(const Type& instance)
	{
		UInt32 size = sizeof(UInt16);	//表示长度
		for (IteratorType it = instance.begin(); it != instance.end(); ++it)
			size += S11NTraits<ElemType >::Size(*it);
		return size;
	}

	static UInt32 Serialize(const Type& instance, std::vector<UInt8>& buffer)
	{
		UInt16 l = static_cast<UInt16>(instance.size());
		const UInt8* data = reinterpret_cast<const UInt8 *>(&l);
		buffer.insert(buffer.end(), data, data + 2);
		l = 2;
		for (IteratorType it = instance.begin(); it != instance.end(); ++it)
			l += S11NTraits<ElemType >::Serialize((ElemType&)*it, buffer);
		return static_cast<UInt32>(l);
	}

	//FIXME
	static UInt32 Unserialize(Type& instance, void* buffer, UInt32 size)
	{
		if(size < 2)
			return static_cast<UInt32>(-1);
		UInt16 l;
		memcpy(&l, buffer, 2);
		if (l > 1024)	//元素个数太多？
			return static_cast<UInt32>(-1);
		UInt32 consumeSize = 2;
		instance.resize(l);
		for (UInt16 i = 0; i < l; ++ i)
		{
			ElemType& elem = instance[i];
			UInt32 elemSize = S11NTraits<ElemType >::Unserialize(elem, static_cast<UInt8 *>(buffer) + consumeSize, size - consumeSize);	//返回实际序列化此元素的buffer长度
			if (elemSize == static_cast<UInt32>(-1))
			{
				instance.clear();
				return static_cast<UInt32>(-1);
			}
			consumeSize += elemSize;
		}
		return consumeSize;
	}
};


#define SllN_TRAITS_MEMBER(memtype, memname)	\
	r = S11NTraits<memtype >::Unserialize(instance.memname, (char *)buffer + len, size - len);	\
	if(r == static_cast<UInt32>(-1)) \
	return r; \
	len += r; \

#define S11N_TRAITS_1(classname, member1type, member1name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			return S11NTraits<member1type >::Size(instance.member1name);	\
		};	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			return S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
		};	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			return S11NTraits<member1type >::Unserialize(instance.member1name, buffer, size);	\
		};	\
	}

#define S11N_TRAITS_2(classname, member1type, member1name, member2type, member2name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			return len;	\
		};	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			return len;	\
		};	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			return len;	\
		}	\
	}


#define S11N_TRAITS_3(classname, member1type, member1name, member2type, member2name, member3type, member3name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			len += S11NTraits<member3type >::Size(instance.member3name);	\
			return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
			return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			SllN_TRAITS_MEMBER(member3type, member3name);	\
			return len;	\
		}	\
	}


#define S11N_TRAITS_4(classname, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			len += S11NTraits<member3type >::Size(instance.member3name);	\
			len += S11NTraits<member4type >::Size(instance.member4name);	\
			return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
			len	+= S11NTraits<member4type >::Serialize(instance.member4name, buffer);	\
			return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			SllN_TRAITS_MEMBER(member3type, member3name);	\
			SllN_TRAITS_MEMBER(member4type, member4name);	\
			return len;	\
		}	\
	}


#define S11N_TRAITS_5(classname, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			len += S11NTraits<member3type >::Size(instance.member3name);	\
			len += S11NTraits<member4type >::Size(instance.member4name);	\
			len += S11NTraits<member5type >::Size(instance.member5name);	\
			return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
			len	+= S11NTraits<member4type >::Serialize(instance.member4name, buffer);	\
			len	+= S11NTraits<member5type >::Serialize(instance.member5name, buffer);	\
			return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			SllN_TRAITS_MEMBER(member3type, member3name);	\
			SllN_TRAITS_MEMBER(member4type, member4name);	\
			SllN_TRAITS_MEMBER(member5type, member5name);	\
			return len;	\
		}	\
	}


#define S11N_TRAITS_6(classname, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			len += S11NTraits<member3type >::Size(instance.member3name);	\
			len += S11NTraits<member4type >::Size(instance.member4name);	\
			len += S11NTraits<member5type >::Size(instance.member5name);	\
			len += S11NTraits<member6type >::Size(instance.member6name);	\
			return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
			len	+= S11NTraits<member4type >::Serialize(instance.member4name, buffer);	\
			len	+= S11NTraits<member5type >::Serialize(instance.member5name, buffer);	\
			len	+= S11NTraits<member6type >::Serialize(instance.member6name, buffer);	\
			return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			SllN_TRAITS_MEMBER(member3type, member3name);	\
			SllN_TRAITS_MEMBER(member4type, member4name);	\
			SllN_TRAITS_MEMBER(member5type, member5name);	\
			SllN_TRAITS_MEMBER(member6type, member6name);	\
			return len;	\
		}	\
	}

#define S11N_TRAITS_6(classname, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name)	\
	template <>	\
struct S11NTraits<classname >	\
	{	\
	static UInt32 Size(const classname& instance)	\
		{	\
		UInt32 len = 0;	\
		len += S11NTraits<member1type >::Size(instance.member1name);	\
		len	+= S11NTraits<member2type >::Size(instance.member2name);	\
		len += S11NTraits<member3type >::Size(instance.member3name);	\
		len += S11NTraits<member4type >::Size(instance.member4name);	\
		len += S11NTraits<member5type >::Size(instance.member5name);	\
		len += S11NTraits<member6type >::Size(instance.member6name);	\
		return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
		UInt32 len = 0;	\
		len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
		len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
		len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
		len	+= S11NTraits<member4type >::Serialize(instance.member4name, buffer);	\
		len	+= S11NTraits<member5type >::Serialize(instance.member5name, buffer);	\
		len	+= S11NTraits<member6type >::Serialize(instance.member6name, buffer);	\
		return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
		UInt32 len = 0;	\
		UInt32 r; \
		SllN_TRAITS_MEMBER(member1type, member1name);	\
		SllN_TRAITS_MEMBER(member2type, member2name);	\
		SllN_TRAITS_MEMBER(member3type, member3name);	\
		SllN_TRAITS_MEMBER(member4type, member4name);	\
		SllN_TRAITS_MEMBER(member5type, member5name);	\
		SllN_TRAITS_MEMBER(member6type, member6name);	\
		return len;	\
		}	\
	}

#define S11N_TRAITS_7(classname, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			len += S11NTraits<member3type >::Size(instance.member3name);	\
			len += S11NTraits<member4type >::Size(instance.member4name);	\
			len += S11NTraits<member5type >::Size(instance.member5name);	\
			len += S11NTraits<member6type >::Size(instance.member6name);	\
			len += S11NTraits<member7type >::Size(instance.member7name);	\
			return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
			len	+= S11NTraits<member4type >::Serialize(instance.member4name, buffer);	\
			len	+= S11NTraits<member5type >::Serialize(instance.member5name, buffer);	\
			len	+= S11NTraits<member6type >::Serialize(instance.member6name, buffer);	\
			len	+= S11NTraits<member7type >::Serialize(instance.member7name, buffer);	\
			return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			SllN_TRAITS_MEMBER(member3type, member3name);	\
			SllN_TRAITS_MEMBER(member4type, member4name);	\
			SllN_TRAITS_MEMBER(member5type, member5name);	\
			SllN_TRAITS_MEMBER(member6type, member6name);	\
			SllN_TRAITS_MEMBER(member7type, member7name);	\
			return len;	\
		}	\
	}



#define S11N_TRAITS_8(classname, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name, member8type, member8name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			len += S11NTraits<member3type >::Size(instance.member3name);	\
			len += S11NTraits<member4type >::Size(instance.member4name);	\
			len += S11NTraits<member5type >::Size(instance.member5name);	\
			len += S11NTraits<member6type >::Size(instance.member6name);	\
			len += S11NTraits<member7type >::Size(instance.member7name);	\
			len += S11NTraits<member8type >::Size(instance.member8name);	\
			return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
			len	+= S11NTraits<member4type >::Serialize(instance.member4name, buffer);	\
			len	+= S11NTraits<member5type >::Serialize(instance.member5name, buffer);	\
			len	+= S11NTraits<member6type >::Serialize(instance.member6name, buffer);	\
			len	+= S11NTraits<member7type >::Serialize(instance.member7name, buffer);	\
			len	+= S11NTraits<member8type >::Serialize(instance.member8name, buffer);	\
			return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			SllN_TRAITS_MEMBER(member3type, member3name);	\
			SllN_TRAITS_MEMBER(member4type, member4name);	\
			SllN_TRAITS_MEMBER(member5type, member5name);	\
			SllN_TRAITS_MEMBER(member6type, member6name);	\
			SllN_TRAITS_MEMBER(member7type, member7name);	\
			SllN_TRAITS_MEMBER(member8type, member8name);	\
			return len;	\
		}	\
	}




#define S11N_TRAITS_9(classname, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name, member8type, member8name, member9type, member9name)	\
	template <>	\
	struct S11NTraits<classname >	\
	{	\
		static UInt32 Size(const classname& instance)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Size(instance.member1name);	\
			len	+= S11NTraits<member2type >::Size(instance.member2name);	\
			len += S11NTraits<member3type >::Size(instance.member3name);	\
			len += S11NTraits<member4type >::Size(instance.member4name);	\
			len += S11NTraits<member5type >::Size(instance.member5name);	\
			len += S11NTraits<member6type >::Size(instance.member6name);	\
			len += S11NTraits<member7type >::Size(instance.member7name);	\
			len += S11NTraits<member8type >::Size(instance.member8name);	\
			len += S11NTraits<member9type >::Size(instance.member9name);	\
			return len;	\
		}	\
		static UInt32 Serialize(const classname& instance, std::vector<UInt8>& buffer)	\
		{	\
			UInt32 len = 0;	\
			len += S11NTraits<member1type >::Serialize(instance.member1name, buffer);	\
			len	+= S11NTraits<member2type >::Serialize(instance.member2name, buffer);	\
			len	+= S11NTraits<member3type >::Serialize(instance.member3name, buffer);	\
			len	+= S11NTraits<member4type >::Serialize(instance.member4name, buffer);	\
			len	+= S11NTraits<member5type >::Serialize(instance.member5name, buffer);	\
			len	+= S11NTraits<member6type >::Serialize(instance.member6name, buffer);	\
			len	+= S11NTraits<member7type >::Serialize(instance.member7name, buffer);	\
			len	+= S11NTraits<member8type >::Serialize(instance.member8name, buffer);	\
			len	+= S11NTraits<member9type >::Serialize(instance.member9name, buffer);	\
			return len;	\
		}	\
		static UInt32 Unserialize(classname& instance, void* buffer, UInt32 size)	\
		{	\
			UInt32 len = 0;	\
			UInt32 r; \
			SllN_TRAITS_MEMBER(member1type, member1name);	\
			SllN_TRAITS_MEMBER(member2type, member2name);	\
			SllN_TRAITS_MEMBER(member3type, member3name);	\
			SllN_TRAITS_MEMBER(member4type, member4name);	\
			SllN_TRAITS_MEMBER(member5type, member5name);	\
			SllN_TRAITS_MEMBER(member6type, member6name);	\
			SllN_TRAITS_MEMBER(member7type, member7name);	\
			SllN_TRAITS_MEMBER(member8type, member8name);	\
			SllN_TRAITS_MEMBER(member9type, member9name);	\
			return len;	\
		}	\
	}
//////////////////////////////////////////////////////////////////////////
//需要对长度进行限定！！！ TODO----------
#define MSG_SllN_0()	\
UInt32 Size() { return 0; }	\
UInt32 Serialize(std::vector<UInt8>& buffer) { return 0; }	\
UInt32 Unserialize(void * buffer, UInt32 size) { return 0;}

#define MSG_SllN_MEMBER(memtype, memname) \
	r = S11NTraits<memtype >::Unserialize(this->memname, (char *)buffer + len, size - len);	\
	if(r == static_cast<UInt32>(-1)) \
	return r; \
	len += r; \

#define MSG_SllN_1(member1type, member1name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	return S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	return S11NTraits<member1type >::Unserialize(this->member1name, buffer, size);	\
}


#define MSG_SllN_2(member1type, member1name, member2type, member2name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) + S11NTraits<member2type >::Size(this->member2name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	return len;	\
}

#define MSG_SllN_3(member1type, member1name, member2type, member2name, member3type, member3name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
		S11NTraits<member2type >::Size(this->member2name) +	\
		S11NTraits<member3type >::Size(this->member3name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	return len;	\
}

#define MSG_SllN_4(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	return len;	\
}


#define MSG_SllN_5(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	return len;	\
}

#define MSG_SllN_6(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name) +	\
	S11NTraits<member6type >::Size(this->member6name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	len += S11NTraits<member6type >::Serialize(this->member6name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	MSG_SllN_MEMBER(member6type, member6name); \
	return len;	\
}


#define MSG_SllN_7(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name) +	\
	S11NTraits<member6type >::Size(this->member6name) +	\
	S11NTraits<member7type >::Size(this->member7name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	len += S11NTraits<member6type >::Serialize(this->member6name, buffer);	\
	len += S11NTraits<member7type >::Serialize(this->member7name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	MSG_SllN_MEMBER(member6type, member6name); \
	MSG_SllN_MEMBER(member7type, member7name); \
	return len;	\
}



#define MSG_SllN_8(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name, member8type, member8name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name) +	\
	S11NTraits<member6type >::Size(this->member6name) +	\
	S11NTraits<member7type >::Size(this->member7name) +	\
	S11NTraits<member8type >::Size(this->member8name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	len += S11NTraits<member6type >::Serialize(this->member6name, buffer);	\
	len += S11NTraits<member7type >::Serialize(this->member7name, buffer);	\
	len += S11NTraits<member8type >::Serialize(this->member8name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	MSG_SllN_MEMBER(member6type, member6name); \
	MSG_SllN_MEMBER(member7type, member7name); \
	MSG_SllN_MEMBER(member8type, member8name); \
	return len;	\
}

#define MSG_SllN_9(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name, member8type, member8name, member9type,member9name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name) +	\
	S11NTraits<member6type >::Size(this->member6name) +	\
	S11NTraits<member7type >::Size(this->member7name) +	\
	S11NTraits<member8type >::Size(this->member8name) +	\
	S11NTraits<member9type >::Size(this->member9name);	\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	len += S11NTraits<member6type >::Serialize(this->member6name, buffer);	\
	len += S11NTraits<member7type >::Serialize(this->member7name, buffer);	\
	len += S11NTraits<member8type >::Serialize(this->member8name, buffer);	\
	len += S11NTraits<member9type >::Serialize(this->member9name, buffer);	\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	MSG_SllN_MEMBER(member6type, member6name); \
	MSG_SllN_MEMBER(member7type, member7name); \
	MSG_SllN_MEMBER(member8type, member8name); \
	MSG_SllN_MEMBER(member9type, member9name); \
	return len;	\
}

#define MSG_SllN_10(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name, member8type, member8name, member9type,member9name, member10type,member10name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name) +	\
	S11NTraits<member6type >::Size(this->member6name) +	\
	S11NTraits<member7type >::Size(this->member7name) +	\
	S11NTraits<member8type >::Size(this->member8name) +	\
	S11NTraits<member9type >::Size(this->member9name) + \
	S11NTraits<member10type >::Size(this->member10name);\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	len += S11NTraits<member6type >::Serialize(this->member6name, buffer);	\
	len += S11NTraits<member7type >::Serialize(this->member7name, buffer);	\
	len += S11NTraits<member8type >::Serialize(this->member8name, buffer);	\
	len += S11NTraits<member9type >::Serialize(this->member9name, buffer);	\
	len += S11NTraits<member10type >::Serialize(this->member10name, buffer);\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	MSG_SllN_MEMBER(member6type, member6name); \
	MSG_SllN_MEMBER(member7type, member7name); \
	MSG_SllN_MEMBER(member8type, member8name); \
	MSG_SllN_MEMBER(member9type, member9name); \
	MSG_SllN_MEMBER(member10type, member10name); \
	return len;	\
}

#define MSG_SllN_11(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name, member8type, member8name, member9type,member9name, member10type,member10name, member11type,member11name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name) +	\
	S11NTraits<member6type >::Size(this->member6name) +	\
	S11NTraits<member7type >::Size(this->member7name) +	\
	S11NTraits<member8type >::Size(this->member8name) +	\
	S11NTraits<member9type >::Size(this->member9name) + \
	S11NTraits<member10type >::Size(this->member10name) + \
	S11NTraits<member11type >::Size(this->member11name);\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	len += S11NTraits<member6type >::Serialize(this->member6name, buffer);	\
	len += S11NTraits<member7type >::Serialize(this->member7name, buffer);	\
	len += S11NTraits<member8type >::Serialize(this->member8name, buffer);	\
	len += S11NTraits<member9type >::Serialize(this->member9name, buffer);	\
	len += S11NTraits<member10type >::Serialize(this->member10name, buffer);\
	len += S11NTraits<member11type >::Serialize(this->member11name, buffer);\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	MSG_SllN_MEMBER(member6type, member6name); \
	MSG_SllN_MEMBER(member7type, member7name); \
	MSG_SllN_MEMBER(member8type, member8name); \
	MSG_SllN_MEMBER(member9type, member9name); \
	MSG_SllN_MEMBER(member10type, member10name); \
	MSG_SllN_MEMBER(member11type, member11name); \
	return len;	\
}

#define MSG_SllN_12(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name, member6type, member6name, member7type, member7name, member8type, member8name, member9type,member9name, member10type,member10name, member11type,member11name, member12type,member12name)	\
UInt32 Size()	\
{	\
	return S11NTraits<member1type >::Size(this->member1name) +	\
	S11NTraits<member2type >::Size(this->member2name) +	\
	S11NTraits<member3type >::Size(this->member3name) + \
	S11NTraits<member4type >::Size(this->member4name) + \
	S11NTraits<member5type >::Size(this->member5name) +	\
	S11NTraits<member6type >::Size(this->member6name) +	\
	S11NTraits<member7type >::Size(this->member7name) +	\
	S11NTraits<member8type >::Size(this->member8name) +	\
	S11NTraits<member9type >::Size(this->member9name) + \
	S11NTraits<member10type >::Size(this->member10name) + \
	S11NTraits<member11type >::Size(this->member11name);\
	S11NTraits<member12type >::Size(this->member12name);\
}	\
UInt32 Serialize(std::vector<UInt8>& buffer)	\
{	\
	UInt32 len = 0;	\
	len += S11NTraits<member1type >::Serialize(this->member1name, buffer);	\
	len += S11NTraits<member2type >::Serialize(this->member2name, buffer);	\
	len += S11NTraits<member3type >::Serialize(this->member3name, buffer);	\
	len += S11NTraits<member4type >::Serialize(this->member4name, buffer);	\
	len += S11NTraits<member5type >::Serialize(this->member5name, buffer);	\
	len += S11NTraits<member6type >::Serialize(this->member6name, buffer);	\
	len += S11NTraits<member7type >::Serialize(this->member7name, buffer);	\
	len += S11NTraits<member8type >::Serialize(this->member8name, buffer);	\
	len += S11NTraits<member9type >::Serialize(this->member9name, buffer);	\
	len += S11NTraits<member10type >::Serialize(this->member10name, buffer);\
	len += S11NTraits<member11type >::Serialize(this->member11name, buffer);\
	len += S11NTraits<member12type >::Serialize(this->member12name, buffer);\
	return len;	\
}	\
UInt32 Unserialize(void * buffer, UInt32 size)	\
{	\
	UInt32 len = 0;	\
	UInt32 r; \
	MSG_SllN_MEMBER(member1type, member1name); \
	MSG_SllN_MEMBER(member2type, member2name); \
	MSG_SllN_MEMBER(member3type, member3name); \
	MSG_SllN_MEMBER(member4type, member4name); \
	MSG_SllN_MEMBER(member5type, member5name); \
	MSG_SllN_MEMBER(member6type, member6name); \
	MSG_SllN_MEMBER(member7type, member7name); \
	MSG_SllN_MEMBER(member8type, member8name); \
	MSG_SllN_MEMBER(member9type, member9name); \
	MSG_SllN_MEMBER(member10type, member10name); \
	MSG_SllN_MEMBER(member11type, member11name); \
	MSG_SllN_MEMBER(member12type, member12name); \
	return len;	\
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define MESSAGE_HEAD_DEF(msgid) \
	void BuildHeader(std::vector<UInt8>& buffer) \
	{ \
		UInt8 hdr[4] = {0, 0, 0xFF, msgid}; \
		buffer.assign(hdr, hdr + 4); \
		buffer.reserve(4 + Size()); \
	} \
	static void FixHeader(std::vector<UInt8>& buffer) \
	{ \
		if(buffer.size() < 4) \
			return; \
		*(UInt16 *)&buffer[0] = buffer.size() - 4; \
	} \
	static const UInt32 s_MsgId = msgid


#define MESSAGE_DEF(msgid)	MSG_SllN_0() \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF1(msgid, member1type, member1name) \
	MSG_SllN_1(member1type, member1name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF2(msgid, member1type, member1name, member2type, member2name) \
	MSG_SllN_2(member1type, member1name, member2type, member2name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF3(msgid, member1type, member1name, member2type, member2name, member3type, member3name) \
	MSG_SllN_3(member1type, member1name, member2type, member2name, member3type, member3name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF4(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name) \
	MSG_SllN_4(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF5(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name) \
	MSG_SllN_5(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF6(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name,member6type, member6name) \
	MSG_SllN_6(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name,member6type, member6name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF7(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name,member6type, member6name,member7type, member7name) \
	MSG_SllN_7(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name,member6type, member6name,member7type, member7name) \
	MESSAGE_HEAD_DEF(msgid)


#define MESSAGE_DEF8(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name) \
	MSG_SllN_8(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF9(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name) \
	MSG_SllN_9(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF10(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name, member10type,member10name) \
	MSG_SllN_10(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name, member10type,member10name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF11(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name, member10type,member10name, member11type,member11name) \
	MSG_SllN_11(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name, member10type,member10name, member11type,member11name) \
	MESSAGE_HEAD_DEF(msgid)

#define MESSAGE_DEF12(msgid, member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name,member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name, member10type,member10name, member11type,member11name, member12type,member12name) \
	MSG_SllN_12(member1type, member1name, member2type, member2name, member3type, member3name, member4type, member4name, member5type, member5name,member6type, member6name,member7type, member7name,member8type, member8name, member9type,member9name, member10type,member10name, member11type,member11name, member12type,member12name) \
	MESSAGE_HEAD_DEF(msgid)

#endif

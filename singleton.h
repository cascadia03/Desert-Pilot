#pragma once

template <typename T>
class singleton
{
private:
	static T* inst;
public:
	singleton() {}
	~singleton() {}

	static T* GetInst()
	{
		if (!inst) inst = new T();
		return inst;
	}

	static void ReleaseInst()
	{
		if (inst) delete inst;
		inst = nullptr;
	}
};

template <typename T>
T* singleton<T>::inst = nullptr;
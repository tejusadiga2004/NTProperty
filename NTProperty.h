
#ifndef NTProperty
#define NTProperty

#define NTPropertyStrong(typevar, variable) \
	private: typevar* _##variable = nullptr; \
	public: void Set##variable(typevar* inVar) { NTRelease(_##variable); _##variable = inVar; NTRetain(_##variable) } \
	typevar* variable() { return _##variable; }

#define NTPropertyStrongAtomic(typevar, variable) \
	private: typevar* _##variable; std::mutex mutex; \
	public: void Set##variable(typevar* inVar) { std::lock_guard<std::mutex> lock(mutex); NTRelease(_##variable); _##variable = inVar; NTRetain(_##variable) } \
	typevar* variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

#define NTPropertyWeak(typevar, variable) \
	private: typevar* _##variable = nullptr; \
	public: void Set##variable(typevar* inVar) { _##variable = inVar; } \
	typevar* variable() { return _##variable; }

#define NTPropertyWeakAtomic(typevar, variable) \
	private: typevar* _##variable = nullptr; std::mutex mutex; \
	public: void Set##variable(typevar* inVar) { std::lock_guard<std::mutex> lock(mutex); _##variable = inVar; } \
	typevar* variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

#define NTPropertyAssign(typevar, variable) \
	private: typevar _##variable; \
	public: void Set##variable(typevar inVar) { _##variable = inVar; } \
	typevar variable() { return _##variable; }

#define NTPropertyAssignAtomic(typevar, variable) \
	private: typevar _##variable; std::mutex mutex; \
	public: void Set##variable(typevar inVar) { std::lock_guard<std::mutex> lock(mutex); _##variable = inVar; } \
	typevar variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

#define NTPropertyAssignReadOnly(typevar,variable) \
	private: typevar _##variable; \
	public: typevar variable() { return _##variable; }

#define NTPropertyReadOnly(typevar,variable) \
	private: typevar* _##variable = nullptr; \
	public: typevar* variable() { return _##variable; }

#define NTPropertyReadOnlyAtomic(typevar, variable) \
	private: typevar* _##variable = nullptr; std::mutex mutex; \
	public: typevar* variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

#define NTPropertyAssignReadOnlyAtomic(typevar, variable) \
	private: typevar _##variable; std::mutex mutex; \
	public: typevar variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

#endif
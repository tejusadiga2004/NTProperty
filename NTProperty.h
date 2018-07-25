/*!
 @file      NTProperty.h
 
 @abstract NTProperties are set of macros to declare the property in C++ header file. Do not declare the property within public private or protected scope. This macro itself declares the scope specifier. Declare a property as shown bellow. Each of the macros declare a private variable with given identifier name and define setter and getter for that property.
 
 class MyClass {
 
     // Declare a property of type NTArray* of name deviceList.
     NSPropertyStrong(NTArray, DeviceList)
     
     NTPropertyAssign(int, StudentId)
     
     public:
     ...
 }
 
 To access the variable directly use _StudentId. To set the property use MyCassInstance->SetStudentId(344). To get the student id use MyCassInstance->StudentId().
 
 @author    Tejus Adiga M
            President and Director,
            Entropy R&D India.
 
 @copyright Copyright (c) Entropy R&D India 2016.
 
 */

#ifndef NTAudioHardware_NTProperty
#define NTAudioHardware_NTProperty

/*!
 @field     NTPropertyValueDeclare
 @abstract  Property declaration for objects and types other than NTFoundation types. This ust declares the Getters and Setters. YOu need to implement the definition of getters and setters in your code. THis is useful in implementing Computed property.
 
 Example:
 NTPropertyValueDeclare(float, Temparature)
 Variable name: _Temparature
 Getter:        Temparature()
 Setter:        SetTemparature(inTemp)
 
 In ypur .cpp file you need to implement the following methods.
 float YOUR_CLASS_NAME::Temparature ()
 {
    // You can return any value here of type float. YOu can even compute the temparature at the time some one asks for temparature.
    return _Temparature;
 }
 
 void YOUR_CLASS_NAME::SetTemparature (float inTemp)
 {
    _Temparature = inTemp;
 }
 
 Uses:
 1. Implementation of Computed properties.
 2. Override the default Setter/Getter.
 
 @field     typevar, datatype of the property. This can be of any type except NTFoundation. There is no Retain cycle for this.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyValueDeclare(typevar, variable) \
    protected: typevar _##variable; \
    public: void Set##variable(typevar inVar); \
    typevar variable();

/*!
 @field     NTPropertyObjectDeclare
 @abstract  Property declaration for NTFoundation object types whcih can be overrided. You have to implement the getter/setter for this.
 
 Example:
 NTPropertyValueDeclare(NTArray, NameList)
 Variable name: _NameList
 Getter:        NameList()
 Setter:        SetNameList(inList)
 
 In ypur .cpp file you need to implement the following methods.
 NTArray* YOUR_CLASS_NAME::NameList ()
 {
    // You can return any value here of type NSArray*. YOu can even compute the temparature at the time some one asks for temparature.

    if (_NameList == nullptr) {
        _NameList = NTArray();
    }
    return _NameList;
 }
 
 void YOUR_CLASS_NAME::SetTemparature (NTArray* inList)
 {
    _NameList = inList;
 }
 
 Uses:
 1. Implementation of Computed properties.
 2. Override the default Setter/Getter.
 
 @field     typevar, datatype of the property. This should be of type extended from NTObject. Any NTFoundation object honor this property.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyObjectDeclare(typevar, variable) \
    protected: typevar* _##variable = nullptr; \
    public: void Set##variable(typevar* inVar); \
    typevar* variable();

/*!
 @field     NTPropertyStrong
 @abstract  Property declaration for NTFoundation object types with strong reference. When the property is set it first releases the reference count of the previous object if any, assigns the new object to the member variable and increments the reference count of the member variable. Both getter and setter is defined.
 
 Example:
 NTPropertyStrong(NTArray, StudentList)
 Variable name: _StudentList
 Getter:        StudentList()
 Setter:        SetStudentList(inList)
 
 @field     typevar, datatype of the property. This should be of type extended from NTObject. Any NTFoundation object honor this property.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyStrong(typevar, variable) \
	protected: typevar* _##variable = nullptr; \
	public: void Set##variable(typevar* inVar) { NTRelease(_##variable); _##variable = inVar; NTRetain(_##variable) } \
	typevar* variable() { return _##variable; }

/*!
 @field     NTPropertyStrongAtomic
 @abstract  Property declaration for NTFoundation object types with strong reference. When the property is set it first releases the reference count of the previous object if any, assigns the new object to the member variable and increments the reference count of the member variable. Both getter and setter is defined. In addition this is thread safe.
 
 Example:
 NTPropertyStrongAtomic(NTArray, StudentList)
 Variable name: _StudentList
 Getter:        StudentList()
 Setter:        SetStudentList(inList)
 
 @field     typevar, datatype of the property. This should be of type extended from NTObject. Any NTFoundation object honor this property.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyStrongAtomic(typevar, variable) \
	protected: typevar* _##variable; std::mutex mutex; \
	public: void Set##variable(typevar* inVar) { std::lock_guard<std::mutex> lock(mutex); NTRelease(_##variable); _##variable = inVar; NTRetain(_##variable) } \
	typevar* variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

/*!
 @field     NTPropertyWeak
 @abstract  Property declaration for NTFoundation object types with weak reference. When the property is set it assigns the new property to the property. Reference count is not altered.
 Both getter and setter is defined. This is not thead safe.
 
 Example:
 NTPropertyWeak(NTArray, StudentList)
 Variable name: _StudentList
 Getter:        StudentList()
 Setter:        SetStudentList(inList)
 
 @field     typevar, datatype of the property. This should be of type extended from NTObject. Any NTFoundation object honor this property.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyWeak(typevar, variable) \
	protected: typevar* _##variable = nullptr; \
	public: void Set##variable(typevar* inVar) { _##variable = inVar; } \
	typevar* variable() { return _##variable; }

/*!
 @field     NTPropertyWeakAtomic
 @abstract  Property declaration for NTFoundation object types with weak reference. When the property is set it assigns the new property to the property. Reference count is not altered.
 Both getter and setter is defined. In addition this is thread safe.
 
 Example:
 NTPropertyWeakAtomic(NTArray, StudentList)
 Variable name: _StudentList
 Getter:        StudentList()
 Setter:        SetStudentList(inList)
 
 @field     typevar, datatype of the property. This should be of type extended from NTObject. Any NTFoundation object honor this property.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyWeakAtomic(typevar, variable) \
	protected: typevar* _##variable = nullptr; std::mutex mutex; \
	public: void Set##variable(typevar* inVar) { std::lock_guard<std::mutex> lock(mutex); _##variable = inVar; } \
	typevar* variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

/*!
 @field     NTPropertyAssign
 @abstract  Property declaration for any type. When the property is set it assigns the new property to the property. This could be any data type.
 Both getter and setter is defined.
 
 Example:
 NTPropertyAssign(int, StudentId)
 Variable name: _StudentId
 Getter:        StudentId()
 Setter:        SetStudentId(inId)
 
 @field     typevar, datatype of the property. Can be any datatype.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyAssign(typevar, variable) \
	protected: typevar _##variable; \
	public: void Set##variable(typevar inVar) { _##variable = inVar; } \
	typevar variable() { return _##variable; }

/*!
 @field     NTPropertyAssignAtomic
 @abstract  Property declaration for any type. When the property is set it assigns the new property to the property. This could be any data type.
 Both getter and setter is defined. In addition this is thread safe.
 
 Example:
 NTPropertyAssignAtomic(int, StudentId)
 Variable name: _StudentId
 Getter:        StudentId()
 Setter:        SetStudentId(inId)
 
 @field     typevar, datatype of the property. Can be any datatype.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyAssignAtomic(typevar, variable) \
	protected: typevar _##variable; std::mutex mutex; \
	public: void Set##variable(typevar inVar) { std::lock_guard<std::mutex> lock(mutex); _##variable = inVar; } \
	typevar variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

/*!
 @field     NTPropertyAssignReadOnly
 @abstract  Property declaration for any type. When the property is set it assigns the new property to the property. This could be any data type.
 Only getter is defined.
 
 Example:
 NTPropertyAssignReadOnly(int, StudentId)
 Variable name: _StudentId
 Getter:        StudentId()
 
 @field     typevar, datatype of the property. Can be any datatype.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyAssignReadOnly(typevar,variable) \
	protected: typevar _##variable; \
	public: typevar variable() { return _##variable; }

/*!
 @field     NTPropertyReadOnly
 @abstract  Property declaration for NTFoundation object types with strong reference. Only getter is defined.
 
 Example:
 NTPropertyReadOnly(NTString, StudentId)
 Variable name: _StudentId
 Getter:        StudentId()
 
 @field     typevar, datatype of the property. Can be any datatype.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyReadOnly(typevar,variable) \
	protected: typevar* _##variable = nullptr; \
	public: typevar* variable() { return _##variable; }

/*!
 @field     NTPropertyReadOnlyAtomic
 @abstract  Property declaration for NTFoundation object types with strong reference. Only getter is defined. In addition this is thread safe.
 
 Example:
 NTPropertyReadOnlyAtomic(NTString, StudentId)
 Variable name: _StudentId
 Getter:        StudentId()
 
 @field     typevar, datatype of the property. Can be any datatype.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyReadOnlyAtomic(typevar, variable) \
	protected: typevar* _##variable = nullptr; std::mutex mutex; \
	public: typevar* variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

/*!
 @field     NTPropertyAssignReadOnlyAtomic
 @abstract  Property declaration for any type. When the property is set it assigns the new property to the property. 
 This could be any data type. In addition this is thread safe. Only getter is defined.
 
 Example:
 NTPropertyAssignReadOnlyAtomic(int, StudentId)
 Variable name: _StudentId
 Getter:        StudentId()
 
 @field     typevar, datatype of the property. Can be any datatype.
 @field     variable, property Name. First letter should be in Capital.
 */
#define NTPropertyAssignReadOnlyAtomic(typevar, variable) \
	protected: typevar _##variable; std::mutex mutex; \
	public: typevar variable() { std::lock_guard<std::mutex> lock(mutex); return _##variable; }

#endif

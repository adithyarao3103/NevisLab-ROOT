// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME ExampleEventDictionary
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "ExampleEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_ExampleParticle(void *p = nullptr);
   static void *newArray_ExampleParticle(Long_t size, void *p);
   static void delete_ExampleParticle(void *p);
   static void deleteArray_ExampleParticle(void *p);
   static void destruct_ExampleParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ExampleParticle*)
   {
      ::ExampleParticle *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ExampleParticle >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("ExampleParticle", ::ExampleParticle::Class_Version(), "ExampleEvent.h", 20,
                  typeid(::ExampleParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ExampleParticle::Dictionary, isa_proxy, 4,
                  sizeof(::ExampleParticle) );
      instance.SetNew(&new_ExampleParticle);
      instance.SetNewArray(&newArray_ExampleParticle);
      instance.SetDelete(&delete_ExampleParticle);
      instance.SetDeleteArray(&deleteArray_ExampleParticle);
      instance.SetDestructor(&destruct_ExampleParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ExampleParticle*)
   {
      return GenerateInitInstanceLocal(static_cast<::ExampleParticle*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::ExampleParticle*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ExampleEvent(void *p = nullptr);
   static void *newArray_ExampleEvent(Long_t size, void *p);
   static void delete_ExampleEvent(void *p);
   static void deleteArray_ExampleEvent(void *p);
   static void destruct_ExampleEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ExampleEvent*)
   {
      ::ExampleEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ExampleEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("ExampleEvent", ::ExampleEvent::Class_Version(), "ExampleEvent.h", 35,
                  typeid(::ExampleEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ExampleEvent::Dictionary, isa_proxy, 4,
                  sizeof(::ExampleEvent) );
      instance.SetNew(&new_ExampleEvent);
      instance.SetNewArray(&newArray_ExampleEvent);
      instance.SetDelete(&delete_ExampleEvent);
      instance.SetDeleteArray(&deleteArray_ExampleEvent);
      instance.SetDestructor(&destruct_ExampleEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ExampleEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::ExampleEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::ExampleEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ExampleParticle::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *ExampleParticle::Class_Name()
{
   return "ExampleParticle";
}

//______________________________________________________________________________
const char *ExampleParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExampleParticle*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int ExampleParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExampleParticle*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ExampleParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExampleParticle*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ExampleParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExampleParticle*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ExampleEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *ExampleEvent::Class_Name()
{
   return "ExampleEvent";
}

//______________________________________________________________________________
const char *ExampleEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExampleEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int ExampleEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExampleEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ExampleEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExampleEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ExampleEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExampleEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ExampleParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class ExampleParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ExampleParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(ExampleParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ExampleParticle(void *p) {
      return  p ? new(p) ::ExampleParticle : new ::ExampleParticle;
   }
   static void *newArray_ExampleParticle(Long_t nElements, void *p) {
      return p ? new(p) ::ExampleParticle[nElements] : new ::ExampleParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_ExampleParticle(void *p) {
      delete (static_cast<::ExampleParticle*>(p));
   }
   static void deleteArray_ExampleParticle(void *p) {
      delete [] (static_cast<::ExampleParticle*>(p));
   }
   static void destruct_ExampleParticle(void *p) {
      typedef ::ExampleParticle current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::ExampleParticle

//______________________________________________________________________________
void ExampleEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class ExampleEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ExampleEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(ExampleEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ExampleEvent(void *p) {
      return  p ? new(p) ::ExampleEvent : new ::ExampleEvent;
   }
   static void *newArray_ExampleEvent(Long_t nElements, void *p) {
      return p ? new(p) ::ExampleEvent[nElements] : new ::ExampleEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_ExampleEvent(void *p) {
      delete (static_cast<::ExampleEvent*>(p));
   }
   static void deleteArray_ExampleEvent(void *p) {
      delete [] (static_cast<::ExampleEvent*>(p));
   }
   static void destruct_ExampleEvent(void *p) {
      typedef ::ExampleEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::ExampleEvent

namespace ROOT {
   static TClass *vectorlEExampleParticlegR_Dictionary();
   static void vectorlEExampleParticlegR_TClassManip(TClass*);
   static void *new_vectorlEExampleParticlegR(void *p = nullptr);
   static void *newArray_vectorlEExampleParticlegR(Long_t size, void *p);
   static void delete_vectorlEExampleParticlegR(void *p);
   static void deleteArray_vectorlEExampleParticlegR(void *p);
   static void destruct_vectorlEExampleParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ExampleParticle>*)
   {
      vector<ExampleParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ExampleParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ExampleParticle>", -2, "vector", 389,
                  typeid(vector<ExampleParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEExampleParticlegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<ExampleParticle>) );
      instance.SetNew(&new_vectorlEExampleParticlegR);
      instance.SetNewArray(&newArray_vectorlEExampleParticlegR);
      instance.SetDelete(&delete_vectorlEExampleParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEExampleParticlegR);
      instance.SetDestructor(&destruct_vectorlEExampleParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ExampleParticle> >()));

      ::ROOT::AddClassAlternate("vector<ExampleParticle>","std::vector<ExampleParticle, std::allocator<ExampleParticle> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<ExampleParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEExampleParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<ExampleParticle>*>(nullptr))->GetClass();
      vectorlEExampleParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEExampleParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEExampleParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ExampleParticle> : new vector<ExampleParticle>;
   }
   static void *newArray_vectorlEExampleParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ExampleParticle>[nElements] : new vector<ExampleParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEExampleParticlegR(void *p) {
      delete (static_cast<vector<ExampleParticle>*>(p));
   }
   static void deleteArray_vectorlEExampleParticlegR(void *p) {
      delete [] (static_cast<vector<ExampleParticle>*>(p));
   }
   static void destruct_vectorlEExampleParticlegR(void *p) {
      typedef vector<ExampleParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<ExampleParticle>

namespace {
  void TriggerDictionaryInitialization_ExampleEventDictionary_Impl() {
    static const char* headers[] = {
"ExampleEvent.h",
nullptr
    };
    static const char* includePaths[] = {
"/usr/include/root",
"/nevis/tanya/home/seligman/root-class/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ExampleEventDictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$ExampleEvent.h")))  ExampleParticle;
class __attribute__((annotate("$clingAutoload$ExampleEvent.h")))  ExampleEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ExampleEventDictionary dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "ExampleEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"ExampleEvent", payloadCode, "@",
"ExampleParticle", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ExampleEventDictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_ExampleEventDictionary_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_ExampleEventDictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_ExampleEventDictionary() {
  TriggerDictionaryInitialization_ExampleEventDictionary_Impl();
}

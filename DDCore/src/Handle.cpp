// $Id$
//====================================================================
//  AIDA Detector description implementation for LCD
//--------------------------------------------------------------------
//
//  Author     : M.Frank
//
//====================================================================

#include "DD4hep/InstanceCount.h"
#include "DD4hep/Handle.inl"
#include "XML/Evaluator.h"
#include <iostream>
#include <cstring>
#include <cstdio>

#if !defined(WIN32) && !defined(__ICC)
#include "cxxabi.h"
#endif

namespace DD4hep {
  XmlTools::Evaluator& evaluator();
}

namespace {
  XmlTools::Evaluator& eval(DD4hep::evaluator());
}

using namespace std;
using namespace DD4hep;
using namespace DD4hep::Geometry;

int DD4hep::Geometry::_toInt(const string& value) {
  string s(value);
  size_t idx = s.find("(int)");
  if (idx != string::npos)
    s.erase(idx, 5);
  while (s[0] == ' ')
    s.erase(0, 1);
  double result = eval.evaluate(s.c_str());
  if (eval.status() != XmlTools::Evaluator::OK) {
    cerr << value << ": ";
    eval.print_error();
    throw runtime_error("DD4hep: Severe error during expression evaluation of " + value);
  }
  return (int) result;
}

long DD4hep::Geometry::_toLong(const string& value) {
  string s(value);
  size_t idx = s.find("(int)");
  if (idx != string::npos)
    s.erase(idx, 5);
  while (s[0] == ' ')
    s.erase(0, 1);
  double result = eval.evaluate(s.c_str());
  if (eval.status() != XmlTools::Evaluator::OK) {
    cerr << value << ": ";
    eval.print_error();
    throw runtime_error("DD4hep: Severe error during expression evaluation of " + value);
  }
  return (long) result;
}

bool DD4hep::Geometry::_toBool(const string& value) {
  return value == "true";
}

float DD4hep::Geometry::_toFloat(const string& value) {
  double result = eval.evaluate(value.c_str());
  if (eval.status() != XmlTools::Evaluator::OK) {
    cerr << value << ": ";
    eval.print_error();
    throw runtime_error("DD4hep: Severe error during expression evaluation of " + value);
  }
  return (float) result;
}

double DD4hep::Geometry::_toDouble(const string& value) {
  double result = eval.evaluate(value.c_str());
  if (eval.status() != XmlTools::Evaluator::OK) {
    cerr << value << ": ";
    eval.print_error();
    throw runtime_error("DD4hep: Severe error during expression evaluation of " + value);
  }
  return result;
}

template <> int DD4hep::Geometry::_multiply<int>(const string& left, const string& right) {
  return (int) _toDouble(left + "*" + right);
}

template <> long DD4hep::Geometry::_multiply<long>(const string& left, const string& right) {
  return (long) _toDouble(left + "*" + right);
}

template <> float DD4hep::Geometry::_multiply<float>(const string& left, const string& right) {
  return _toFloat(left + "*" + right);
}

template <> double DD4hep::Geometry::_multiply<double>(const string& left, const string& right) {
  return _toDouble(left + "*" + right);
}

void DD4hep::Geometry::_toDictionary(const string& name, const string& value) {
  string n = name, v = value;
  size_t idx = v.find("(int)");
  if (idx != string::npos)
    v.erase(idx, 5);
  idx = v.find("(float)");
  if (idx != string::npos)
    v.erase(idx, 7);
  while (v[0] == ' ')
    v.erase(0, 1);
  double result = eval.evaluate(v.c_str());
  if (eval.status() != XmlTools::Evaluator::OK) {
    cerr << value << ": ";
    eval.print_error();
    throw runtime_error("DD4hep: Severe error during expression evaluation " + name + "=" + value);
  }
  eval.setVariable(n.c_str(), result);
}

string DD4hep::Geometry::_toString(bool value) {
  char text[32];
  ::snprintf(text, sizeof(text), "%s", value ? "true" : "false");
  return text;
}

string DD4hep::Geometry::_toString(int value) {
  char text[32];
  ::snprintf(text, sizeof(text), "%d", value);
  return text;
}

string DD4hep::Geometry::_toString(float value) {
  char text[32];
  ::snprintf(text, sizeof(text), "%f", value);
  return text;
}

string DD4hep::Geometry::_toString(double value) {
  char text[32];
  ::snprintf(text, sizeof(text), "%f", value);
  return text;
}
namespace DD4hep {
  namespace Geometry {
    static long s_numVerifies = 0;

    long num_object_validations() {
      return s_numVerifies;
    }
    void increment_object_validations() {
      ++s_numVerifies;
    }
  }
}

#include "DDSegmentation/Segmentation.h"
typedef DDSegmentation::Segmentation _Segmentation;
//INSTANTIATE_UNNAMED(_Segmentation);
namespace DD4hep {
  namespace Geometry {
    template <> void Handle<_Segmentation>::assign(_Segmentation* s, const std::string& n, const std::string&) {
      this->m_element = s;
      s->setName(n);
    }
    template <> const char* Handle<_Segmentation>::name() const {
      return this->m_element ? this->m_element->name().c_str() : "";
    }
    template struct DD4hep::Geometry::Handle<_Segmentation>;
  }
}

#include "DD4hep/LCDD.h"
#include "TMap.h"
#include "TColor.h"

DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TObject);
DD4HEP_INSTANTIATE_HANDLE(TNamed);

#include "TGeoMedium.h"
#include "TGeoMaterial.h"
#include "TGeoElement.h"
DD4HEP_INSTANTIATE_HANDLE(TGeoElement);
DD4HEP_INSTANTIATE_HANDLE(TGeoMaterial);
DD4HEP_INSTANTIATE_HANDLE(TGeoMedium);

#include "TGeoMatrix.h"
DD4HEP_INSTANTIATE_HANDLE(TGeoMatrix);
DD4HEP_INSTANTIATE_HANDLE(TGeoRotation);
DD4HEP_INSTANTIATE_HANDLE(TGeoTranslation);
DD4HEP_INSTANTIATE_HANDLE(TGeoIdentity);
DD4HEP_INSTANTIATE_HANDLE(TGeoCombiTrans);
DD4HEP_INSTANTIATE_HANDLE(TGeoGenTrans);

#include "TGeoNode.h"
DD4HEP_INSTANTIATE_HANDLE(TGeoNode);
DD4HEP_INSTANTIATE_HANDLE(TGeoNodeMatrix);
DD4HEP_INSTANTIATE_HANDLE(TGeoNodeOffset);

// Shapes (needed by "Shapes.cpp")
#include "TGeoBBox.h"
#include "TGeoPcon.h"
#include "TGeoPgon.h"
#include "TGeoTube.h"
#include "TGeoCone.h"
#include "TGeoArb8.h"
#include "TGeoTrd1.h"
#include "TGeoTrd2.h"
#include "TGeoParaboloid.h"
#include "TGeoSphere.h"
#include "TGeoTorus.h"
#include "TGeoBoolNode.h"
#include "TGeoVolume.h"
#include "TGeoCompositeShape.h"
#include "TGeoShapeAssembly.h"
DD4HEP_INSTANTIATE_HANDLE(TGeoVolume);
DD4HEP_INSTANTIATE_HANDLE(TGeoBBox);
DD4HEP_INSTANTIATE_HANDLE(TGeoCone);
DD4HEP_INSTANTIATE_HANDLE(TGeoArb8);
DD4HEP_INSTANTIATE_HANDLE(TGeoConeSeg);
DD4HEP_INSTANTIATE_HANDLE(MyConeSeg);
DD4HEP_INSTANTIATE_HANDLE(TGeoParaboloid);
DD4HEP_INSTANTIATE_HANDLE(TGeoPcon);
DD4HEP_INSTANTIATE_HANDLE(TGeoPgon);
DD4HEP_INSTANTIATE_HANDLE(TGeoTube);
DD4HEP_INSTANTIATE_HANDLE(TGeoTubeSeg);
DD4HEP_INSTANTIATE_HANDLE(TGeoTrap);
DD4HEP_INSTANTIATE_HANDLE(TGeoTrd1);
DD4HEP_INSTANTIATE_HANDLE(TGeoTrd2);
DD4HEP_INSTANTIATE_HANDLE(TGeoSphere);
DD4HEP_INSTANTIATE_HANDLE(TGeoTorus);
DD4HEP_INSTANTIATE_HANDLE(TGeoShape);
DD4HEP_INSTANTIATE_HANDLE(TGeoShapeAssembly);
DD4HEP_INSTANTIATE_HANDLE(TGeoCompositeShape);

// Volume Placements (needed by "Volumes.cpp")
#include "TGeoPhysicalNode.h"
DD4HEP_INSTANTIATE_HANDLE(TGeoPhysicalNode);

#include "TGeoBoolNode.h"
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoUnion);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoIntersection);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoSubtraction);

// Replicated Volumes (needed by "Volumes.cpp")
#include "TGeoPatternFinder.h"
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternFinder);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternX);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternY);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternZ);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternParaX);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternParaY);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternParaZ);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternTrapZ);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternCylR);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternCylPhi);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternSphR);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternSphTheta);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternSphPhi);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(TGeoPatternHoneycomb);

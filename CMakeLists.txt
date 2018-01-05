cmake_minimum_required(VERSION 2.8)

project(libSkinMeshGL)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(libSkinMeshGL STATIC
  src/SmgAnimationKey.cpp
  src/SmgCoords.cpp
  src/SmgFace.cpp
  src/SmgFrame.cpp
  src/SmgImg.cpp
  src/SmgMat.cpp
  src/SmgMaterial.cpp
  src/SmgMesh.cpp
  src/SmgModel.cpp
  src/SmgQuaternion.cpp
  src/SmgSkinInfo.cpp
  src/SmgSkinWeight.cpp
  src/SmgUtil.cpp
  src/SmgVertex.cpp
  src/XFileLoad.cpp
  src/XLex.cpp
  src/main.cpp
)

xof 0303txt 0032

template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}


template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}


Frame Frame_SCENE_ROOT {

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame Frame1_cube_Layer1 {

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh Mesh_cube {
   24;
   -1.100000;0.000000;-0.900000;,
   -1.100000;0.000000;-0.900000;,
   -1.100000;0.000000;-0.900000;,
   1.050000;0.000000;-0.900000;,
   1.050000;0.000000;-0.900000;,
   1.050000;0.000000;-0.900000;,
   1.050000;0.000000;0.850000;,
   1.050000;0.000000;0.850000;,
   1.050000;0.000000;0.850000;,
   -1.100000;0.000000;0.850000;,
   -1.100000;0.000000;0.850000;,
   -1.100000;0.000000;0.850000;,
   -1.100000;1.700000;-0.900000;,
   -1.100000;1.700000;-0.900000;,
   -1.100000;1.700000;-0.900000;,
   1.050000;1.700000;-0.900000;,
   1.050000;1.700000;-0.900000;,
   1.050000;1.700000;-0.900000;,
   1.050000;1.700000;0.850000;,
   1.050000;1.700000;0.850000;,
   1.050000;1.700000;0.850000;,
   -1.100000;1.700000;0.850000;,
   -1.100000;1.700000;0.850000;,
   -1.100000;1.700000;0.850000;;
   6;
   4;0,12,15,3;,
   4;4,16,18,6;,
   4;9,7,19,21;,
   4;1,10,22,13;,
   4;14,23,20,17;,
   4;2,5,8,11;;

   MeshNormals {
    24;
    0.000000;0.000000;-1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;;
    6;
    4;0,12,15,3;,
    4;4,16,18,6;,
    4;9,7,19,21;,
    4;1,10,22,13;,
    4;14,23,20,17;,
    4;2,5,8,11;;
   }

   VertexDuplicationIndices {
    24;
    22;
    0,
    0,
    0,
    3,
    3,
    3,
    6,
    6,
    6,
    9,
    9,
    9,
    12,
    12,
    12,
    15,
    15,
    15,
    18,
    18,
    18,
    21,
    21,
    21;
   }

   MeshMaterialList {
    1;
    6;
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     0.784314;0.784314;0.784314;1.000000;;
     51.200001;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }
}

AnimationSet AnimationSet_cube_rot2 {

 Animation Animation0 {
  { Frame1_cube_Layer1 }
  AnimationKey {
   4;
   61;
   0;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   1;16;0.993280,0.000000,0.115736,0.000000,0.000000,1.000000,0.000000,0.000000,-0.115736,0.000000,0.993280,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   2;16;0.974162,0.000000,0.225849,0.000000,0.000000,1.000000,0.000000,0.000000,-0.225849,0.000000,0.974162,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   3;16;0.943670,0.000000,0.330888,0.000000,0.000000,1.000000,0.000000,0.000000,-0.330888,0.000000,0.943670,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   4;16;0.902146,0.000000,0.431431,0.000000,0.000000,1.000000,0.000000,0.000000,-0.431431,0.000000,0.902146,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   5;16;0.849317,0.000000,0.527883,0.000000,0.000000,1.000000,0.000000,0.000000,-0.527883,0.000000,0.849317,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   6;16;0.784369,0.000000,0.620294,0.000000,0.000000,1.000000,0.000000,0.000000,-0.620294,0.000000,0.784369,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   7;16;0.706041,0.000000,0.708171,0.000000,0.000000,1.000000,0.000000,0.000000,-0.708171,0.000000,0.706041,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   8;16;0.612752,0.000000,0.790275,0.000000,0.000000,1.000000,0.000000,0.000000,-0.790275,0.000000,0.612752,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   9;16;0.502795,0.000000,0.864406,0.000000,0.000000,1.000000,0.000000,0.000000,-0.864406,0.000000,0.502795,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   10;16;0.374606,0.000000,0.927184,0.000000,0.000000,1.000000,0.000000,0.000000,-0.927184,0.000000,0.374606,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   11;16;0.227627,0.000000,0.973748,0.000000,0.000000,1.000000,0.000000,0.000000,-0.973748,0.000000,0.227627,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   12;16;0.064908,0.000000,0.997891,0.000000,0.000000,1.000000,0.000000,0.000000,-0.997891,0.000000,0.064908,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   13;16;-0.107997,0.000000,0.994151,0.000000,0.000000,1.000000,0.000000,0.000000,-0.994151,0.000000,-0.107997,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   14;16;-0.284002,0.000000,0.958824,0.000000,0.000000,1.000000,0.000000,0.000000,-0.958824,0.000000,-0.284002,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   15;16;-0.455060,0.000000,0.890461,0.000000,0.000000,1.000000,0.000000,0.000000,-0.890461,0.000000,-0.455060,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   16;16;-0.612918,0.000000,0.790146,0.000000,0.000000,1.000000,0.000000,0.000000,-0.790146,0.000000,-0.612918,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   17;16;-0.749969,0.000000,0.661474,0.000000,0.000000,1.000000,0.000000,0.000000,-0.661474,0.000000,-0.749969,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   18;16;-0.860045,0.000000,0.510219,0.000000,0.000000,1.000000,0.000000,0.000000,-0.510219,0.000000,-0.860045,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   19;16;-0.939064,0.000000,0.343743,0.000000,0.000000,1.000000,0.000000,0.000000,-0.343743,0.000000,-0.939064,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   20;16;-0.985408,0.000000,0.170210,0.000000,0.000000,1.000000,0.000000,0.000000,-0.170210,0.000000,-0.985408,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   21;16;-0.999954,0.000000,-0.009609,0.000000,0.000000,1.000000,0.000000,0.000000,0.009609,0.000000,-0.999954,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   22;16;-0.980844,0.000000,-0.194795,0.000000,0.000000,1.000000,0.000000,0.000000,0.194795,0.000000,-0.980844,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   23;16;-0.926547,0.000000,-0.376178,0.000000,0.000000,1.000000,0.000000,0.000000,0.376178,0.000000,-0.926547,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   24;16;-0.838724,0.000000,-0.544556,0.000000,0.000000,1.000000,0.000000,0.000000,0.544556,0.000000,-0.838724,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   25;16;-0.722063,0.000000,-0.691827,0.000000,0.000000,1.000000,0.000000,0.000000,0.691827,0.000000,-0.722063,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   26;16;-0.583690,0.000000,-0.811977,0.000000,0.000000,1.000000,0.000000,0.000000,0.811977,0.000000,-0.583690,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   27;16;-0.432264,0.000000,-0.901747,0.000000,0.000000,1.000000,0.000000,0.000000,0.901747,0.000000,-0.432264,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   28;16;-0.276928,0.000000,-0.960891,0.000000,0.000000,1.000000,0.000000,0.000000,0.960891,0.000000,-0.276928,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   29;16;-0.126316,0.000000,-0.991990,0.000000,0.000000,1.000000,0.000000,0.000000,0.991990,0.000000,-0.126316,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   30;16;0.012214,0.000000,-0.999925,0.000000,0.000000,1.000000,0.000000,0.000000,0.999925,0.000000,0.012214,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   31;16;0.135371,0.000000,-0.990795,0.000000,0.000000,1.000000,0.000000,0.000000,0.990795,0.000000,0.135371,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   32;16;0.244154,0.000000,-0.969736,0.000000,0.000000,1.000000,0.000000,0.000000,0.969736,0.000000,0.244154,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   33;16;0.339503,0.000000,-0.940605,0.000000,0.000000,1.000000,0.000000,0.000000,0.940605,0.000000,0.339503,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   34;16;0.422869,0.000000,-0.906191,0.000000,0.000000,1.000000,0.000000,0.000000,0.906191,0.000000,0.422869,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   35;16;0.495930,0.000000,-0.868363,0.000000,0.000000,1.000000,0.000000,0.000000,0.868363,0.000000,0.495930,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   36;16;0.560405,0.000000,-0.828218,0.000000,0.000000,1.000000,0.000000,0.000000,0.828218,0.000000,0.560405,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   37;16;0.617936,0.000000,-0.786228,0.000000,0.000000,1.000000,0.000000,0.000000,0.786228,0.000000,0.617936,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   38;16;0.670010,0.000000,-0.742352,0.000000,0.000000,1.000000,0.000000,0.000000,0.742352,0.000000,0.670010,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   39;16;0.717909,0.000000,-0.696137,0.000000,0.000000,1.000000,0.000000,0.000000,0.696137,0.000000,0.717909,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   40;16;0.762667,0.000000,-0.646792,0.000000,0.000000,1.000000,0.000000,0.000000,0.646792,0.000000,0.762667,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   41;16;0.803041,0.000000,-0.595924,0.000000,0.000000,1.000000,0.000000,0.000000,0.595924,0.000000,0.803041,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   42;16;0.837687,0.000000,-0.546151,0.000000,0.000000,1.000000,0.000000,0.000000,0.546151,0.000000,0.837687,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   43;16;0.867254,0.000000,-0.497867,0.000000,0.000000,1.000000,0.000000,0.000000,0.497867,0.000000,0.867254,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   44;16;0.892351,0.000000,-0.451341,0.000000,0.000000,1.000000,0.000000,0.000000,0.451341,0.000000,0.892351,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   45;16;0.913544,0.000000,-0.406739,0.000000,0.000000,1.000000,0.000000,0.000000,0.406739,0.000000,0.913544,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   46;16;0.931345,0.000000,-0.364139,0.000000,0.000000,1.000000,0.000000,0.000000,0.364139,0.000000,0.931345,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   47;16;0.946213,0.000000,-0.323544,0.000000,0.000000,1.000000,0.000000,0.000000,0.323544,0.000000,0.946213,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   48;16;0.958557,0.000000,-0.284902,0.000000,0.000000,1.000000,0.000000,0.000000,0.284902,0.000000,0.958557,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   49;16;0.968731,0.000000,-0.248112,0.000000,0.000000,1.000000,0.000000,0.000000,0.248112,0.000000,0.968731,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   50;16;0.977045,0.000000,-0.213034,0.000000,0.000000,1.000000,0.000000,0.000000,0.213034,0.000000,0.977045,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   51;16;0.983444,0.000000,-0.181211,0.000000,0.000000,1.000000,0.000000,0.000000,0.181211,0.000000,0.983444,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   52;16;0.988097,0.000000,-0.153831,0.000000,0.000000,1.000000,0.000000,0.000000,0.153831,0.000000,0.988097,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   53;16;0.991493,0.000000,-0.130161,0.000000,0.000000,1.000000,0.000000,0.000000,0.130161,0.000000,0.991493,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   54;16;0.993994,0.000000,-0.109433,0.000000,0.000000,1.000000,0.000000,0.000000,0.109433,0.000000,0.993994,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   55;16;0.995864,0.000000,-0.090854,0.000000,0.000000,1.000000,0.000000,0.000000,0.090854,0.000000,0.995864,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   56;16;0.997286,0.000000,-0.073618,0.000000,0.000000,1.000000,0.000000,0.000000,0.073618,0.000000,0.997286,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   57;16;0.998379,0.000000,-0.056911,0.000000,0.000000,1.000000,0.000000,0.000000,0.056911,0.000000,0.998379,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   58;16;0.999203,0.000000,-0.039913,0.000000,0.000000,1.000000,0.000000,0.000000,0.039913,0.000000,0.999203,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   59;16;0.999762,0.000000,-0.021800,0.000000,0.000000,1.000000,0.000000,0.000000,0.021800,0.000000,0.999762,0.000000,0.000000,0.000000,0.000000,1.000000;;,
   60;16;0.999998,0.000000,-0.001750,0.000000,0.000000,1.000000,0.000000,0.000000,0.001750,0.000000,0.999998,0.000000,0.000000,0.000000,0.000000,1.000000;;;
  }
 }
}
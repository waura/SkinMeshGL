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

AnimationSet AnimationSet_cube_move {

 Animation Animation0 {
  { Frame1_cube_Layer1 }
  AnimationKey {
   0;
   61;
   0;4;1.000000,0.000000,0.000000,0.000000;;,
   1;4;1.000000,0.000000,0.000000,0.000000;;,
   2;4;1.000000,0.000000,0.000000,0.000000;;,
   3;4;1.000000,0.000000,0.000000,0.000000;;,
   4;4;1.000000,0.000000,0.000000,0.000000;;,
   5;4;1.000000,0.000000,0.000000,0.000000;;,
   6;4;1.000000,0.000000,0.000000,0.000000;;,
   7;4;1.000000,0.000000,0.000000,0.000000;;,
   8;4;1.000000,0.000000,0.000000,0.000000;;,
   9;4;1.000000,0.000000,0.000000,0.000000;;,
   10;4;1.000000,0.000000,0.000000,0.000000;;,
   11;4;1.000000,0.000000,0.000000,0.000000;;,
   12;4;1.000000,0.000000,0.000000,0.000000;;,
   13;4;1.000000,0.000000,0.000000,0.000000;;,
   14;4;1.000000,0.000000,0.000000,0.000000;;,
   15;4;1.000000,0.000000,0.000000,0.000000;;,
   16;4;1.000000,0.000000,0.000000,0.000000;;,
   17;4;1.000000,0.000000,0.000000,0.000000;;,
   18;4;1.000000,0.000000,0.000000,0.000000;;,
   19;4;1.000000,0.000000,0.000000,0.000000;;,
   20;4;1.000000,0.000000,0.000000,0.000000;;,
   21;4;1.000000,0.000000,0.000000,0.000000;;,
   22;4;1.000000,0.000000,0.000000,0.000000;;,
   23;4;1.000000,0.000000,0.000000,0.000000;;,
   24;4;1.000000,0.000000,0.000000,0.000000;;,
   25;4;1.000000,0.000000,0.000000,0.000000;;,
   26;4;1.000000,0.000000,0.000000,0.000000;;,
   27;4;1.000000,0.000000,0.000000,0.000000;;,
   28;4;1.000000,0.000000,0.000000,0.000000;;,
   29;4;1.000000,0.000000,0.000000,0.000000;;,
   30;4;1.000000,0.000000,0.000000,0.000000;;,
   31;4;1.000000,0.000000,0.000000,0.000000;;,
   32;4;1.000000,0.000000,0.000000,0.000000;;,
   33;4;1.000000,0.000000,0.000000,0.000000;;,
   34;4;1.000000,0.000000,0.000000,0.000000;;,
   35;4;1.000000,0.000000,0.000000,0.000000;;,
   36;4;1.000000,0.000000,0.000000,0.000000;;,
   37;4;1.000000,0.000000,0.000000,0.000000;;,
   38;4;1.000000,0.000000,0.000000,0.000000;;,
   39;4;1.000000,0.000000,0.000000,0.000000;;,
   40;4;1.000000,0.000000,0.000000,0.000000;;,
   41;4;1.000000,0.000000,0.000000,0.000000;;,
   42;4;1.000000,0.000000,0.000000,0.000000;;,
   43;4;1.000000,0.000000,0.000000,0.000000;;,
   44;4;1.000000,0.000000,0.000000,0.000000;;,
   45;4;1.000000,0.000000,0.000000,0.000000;;,
   46;4;1.000000,0.000000,0.000000,0.000000;;,
   47;4;1.000000,0.000000,0.000000,0.000000;;,
   48;4;1.000000,0.000000,0.000000,0.000000;;,
   49;4;1.000000,0.000000,0.000000,0.000000;;,
   50;4;1.000000,0.000000,0.000000,0.000000;;,
   51;4;1.000000,0.000000,0.000000,0.000000;;,
   52;4;1.000000,0.000000,0.000000,0.000000;;,
   53;4;1.000000,0.000000,0.000000,0.000000;;,
   54;4;1.000000,0.000000,0.000000,0.000000;;,
   55;4;1.000000,0.000000,0.000000,0.000000;;,
   56;4;1.000000,0.000000,0.000000,0.000000;;,
   57;4;1.000000,0.000000,0.000000,0.000000;;,
   58;4;1.000000,0.000000,0.000000,0.000000;;,
   59;4;1.000000,0.000000,0.000000,0.000000;;,
   60;4;1.000000,0.000000,0.000000,0.000000;;;
  }
  AnimationKey {
   1;
   61;
   0;3;1.000000,1.000000,1.000000;;,
   1;3;1.000000,1.000000,1.000000;;,
   2;3;1.000000,1.000000,1.000000;;,
   3;3;1.000000,1.000000,1.000000;;,
   4;3;1.000000,1.000000,1.000000;;,
   5;3;1.000000,1.000000,1.000000;;,
   6;3;1.000000,1.000000,1.000000;;,
   7;3;1.000000,1.000000,1.000000;;,
   8;3;1.000000,1.000000,1.000000;;,
   9;3;1.000000,1.000000,1.000000;;,
   10;3;1.000000,1.000000,1.000000;;,
   11;3;1.000000,1.000000,1.000000;;,
   12;3;1.000000,1.000000,1.000000;;,
   13;3;1.000000,1.000000,1.000000;;,
   14;3;1.000000,1.000000,1.000000;;,
   15;3;1.000000,1.000000,1.000000;;,
   16;3;1.000000,1.000000,1.000000;;,
   17;3;1.000000,1.000000,1.000000;;,
   18;3;1.000000,1.000000,1.000000;;,
   19;3;1.000000,1.000000,1.000000;;,
   20;3;1.000000,1.000000,1.000000;;,
   21;3;1.000000,1.000000,1.000000;;,
   22;3;1.000000,1.000000,1.000000;;,
   23;3;1.000000,1.000000,1.000000;;,
   24;3;1.000000,1.000000,1.000000;;,
   25;3;1.000000,1.000000,1.000000;;,
   26;3;1.000000,1.000000,1.000000;;,
   27;3;1.000000,1.000000,1.000000;;,
   28;3;1.000000,1.000000,1.000000;;,
   29;3;1.000000,1.000000,1.000000;;,
   30;3;1.000000,1.000000,1.000000;;,
   31;3;1.000000,1.000000,1.000000;;,
   32;3;1.000000,1.000000,1.000000;;,
   33;3;1.000000,1.000000,1.000000;;,
   34;3;1.000000,1.000000,1.000000;;,
   35;3;1.000000,1.000000,1.000000;;,
   36;3;1.000000,1.000000,1.000000;;,
   37;3;1.000000,1.000000,1.000000;;,
   38;3;1.000000,1.000000,1.000000;;,
   39;3;1.000000,1.000000,1.000000;;,
   40;3;1.000000,1.000000,1.000000;;,
   41;3;1.000000,1.000000,1.000000;;,
   42;3;1.000000,1.000000,1.000000;;,
   43;3;1.000000,1.000000,1.000000;;,
   44;3;1.000000,1.000000,1.000000;;,
   45;3;1.000000,1.000000,1.000000;;,
   46;3;1.000000,1.000000,1.000000;;,
   47;3;1.000000,1.000000,1.000000;;,
   48;3;1.000000,1.000000,1.000000;;,
   49;3;1.000000,1.000000,1.000000;;,
   50;3;1.000000,1.000000,1.000000;;,
   51;3;1.000000,1.000000,1.000000;;,
   52;3;1.000000,1.000000,1.000000;;,
   53;3;1.000000,1.000000,1.000000;;,
   54;3;1.000000,1.000000,1.000000;;,
   55;3;1.000000,1.000000,1.000000;;,
   56;3;1.000000,1.000000,1.000000;;,
   57;3;1.000000,1.000000,1.000000;;,
   58;3;1.000000,1.000000,1.000000;;,
   59;3;1.000000,1.000000,1.000000;;,
   60;3;1.000000,1.000000,1.000000;;;
  }
  AnimationKey {
   2;
   61;
   0;3;0.000000,0.000000,0.000000;;,
   1;3;0.271831,0.000000,0.193623;;,
   2;3;0.594478,0.000000,0.391892;;,
   3;3;0.946163,0.000000,0.592815;;,
   4;3;1.305107,0.000000,0.794402;;,
   5;3;1.649533,0.000000,0.994661;;,
   6;3;1.957661,0.000000,1.191603;;,
   7;3;2.207714,0.000000,1.383235;;,
   8;3;2.377913,0.000000,1.567568;;,
   9;3;2.446479,0.000000,1.742611;;,
   10;3;2.391634,0.000000,1.906372;;,
   11;3;2.179401,0.000000,2.080274;;,
   12;3;1.813487,0.000000,2.278283;;,
   13;3;1.328644,0.000000,2.487224;;,
   14;3;0.759622,0.000000,2.693920;;,
   15;3;0.141174,0.000000,2.885197;;,
   16;3;-0.491951,0.000000,3.047878;;,
   17;3;-1.105000,0.000000,3.168788;;,
   18;3;-1.663223,0.000000,3.234751;;,
   19;3;-2.131869,0.000000,3.232591;;,
   20;3;-2.476185,0.000000,3.149133;;,
   21;3;-2.721708,0.000000,2.952464;;,
   22;3;-2.918661,0.000000,2.638516;;,
   23;3;-3.069328,0.000000,2.235885;;,
   24;3;-3.175991,0.000000,1.773168;;,
   25;3;-3.240933,0.000000,1.278959;;,
   26;3;-3.266438,0.000000,0.781855;;,
   27;3;-3.254788,0.000000,0.310450;;,
   28;3;-3.208265,0.000000,-0.106659;;,
   29;3;-3.129154,0.000000,-0.440877;;,
   30;3;-3.019737,0.000000,-0.663609;;,
   31;3;-2.864413,0.000000,-0.774413;;,
   32;3;-2.652150,0.000000,-0.802701;;,
   33;3;-2.392078,0.000000,-0.764652;;,
   34;3;-2.093329,0.000000,-0.676447;;,
   35;3;-1.765035,0.000000,-0.554264;;,
   36;3;-1.416328,0.000000,-0.414284;;,
   37;3;-1.056339,0.000000,-0.272688;;,
   38;3;-0.694200,0.000000,-0.145655;;,
   39;3;-0.339042,0.000000,-0.049365;;,
   40;3;0.000002,0.000000,0.000001;;,
   41;3;0.337304,0.000000,0.024223;;,
   42;3;0.690316,0.000000,0.052177;;,
   43;3;1.054533,0.000000,0.078334;;,
   44;3;1.425446,0.000000,0.097165;;,
   45;3;1.798548,0.000000,0.103139;;,
   46;3;2.169332,0.000000,0.090728;;,
   47;3;2.533290,0.000000,0.054400;;,
   48;3;2.885915,0.000000,-0.011374;;,
   49;3;3.222700,0.000000,-0.112123;;,
   50;3;3.539138,0.000000,-0.253377;;,
   51;3;3.871877,0.000000,-0.816200;;,
   52;3;4.095389,0.000000,-1.685716;;,
   53;3;3.961902,0.000000,-2.123551;;,
   54;3;3.485510,0.000000,-2.000493;;,
   55;3;2.875243,0.000000,-1.715554;;,
   56;3;2.175726,0.000000,-1.322695;;,
   57;3;1.431584,0.000000,-0.875875;;,
   58;3;0.687442,0.000000,-0.429055;;,
   59;3;-0.012074,0.000000,-0.036196;;,
   60;3;-0.012074,0.000000,-0.036196;;;
  }
 }
}
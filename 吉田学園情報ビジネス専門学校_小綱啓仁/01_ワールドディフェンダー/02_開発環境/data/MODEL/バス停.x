xof 0302txt 0064
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

Header{
1;
0;
1;
}

Mesh {
 120;
 -11.98445;18.41978;-11.98445;,
 11.98445;18.41978;-11.98445;,
 15.00000;-0.65525;-15.00000;,
 -15.00000;-0.65525;-15.00000;,
 11.98445;18.41978;-11.98445;,
 11.98445;18.41978;11.98445;,
 15.00000;-0.65525;15.00000;,
 15.00000;-0.65525;-15.00000;,
 11.98445;18.41978;11.98445;,
 -11.98445;18.41978;11.98445;,
 -15.00000;-0.65525;15.00000;,
 15.00000;-0.65525;15.00000;,
 -11.98445;18.41978;11.98445;,
 -11.98445;18.41978;-11.98445;,
 -15.00000;-0.65525;-15.00000;,
 -15.00000;-0.65525;15.00000;,
 11.98445;18.41978;-11.98445;,
 -11.98445;18.41978;-11.98445;,
 -15.00000;-0.65525;-15.00000;,
 15.00000;-0.65525;-15.00000;,
 0.00000;57.62300;-3.33000;,
 2.35467;57.62300;-2.35467;,
 2.35467;11.46800;-2.35467;,
 0.00000;11.46800;-3.33000;,
 3.33000;57.62300;0.00000;,
 3.33000;11.46800;0.00000;,
 2.35467;57.62300;2.35467;,
 2.35467;11.46800;2.35467;,
 0.00000;57.62300;3.33000;,
 0.00000;11.46800;3.33000;,
 -2.35467;57.62300;2.35467;,
 -2.35467;11.46800;2.35467;,
 -3.33000;57.62300;0.00000;,
 -3.33000;11.46800;0.00000;,
 -2.35467;57.62300;-2.35467;,
 -2.35467;11.46800;-2.35467;,
 0.00000;57.62300;-3.33000;,
 0.00000;11.46800;-3.33000;,
 0.00000;57.62300;0.00000;,
 0.00000;57.62300;0.00000;,
 0.00000;57.62300;0.00000;,
 0.00000;57.62300;0.00000;,
 0.00000;57.62300;0.00000;,
 0.00000;57.62300;0.00000;,
 0.00000;57.62300;0.00000;,
 0.00000;57.62300;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;11.46800;0.00000;,
 0.00000;135.56660;5.65266;,
 7.13306;133.93853;5.65266;,
 7.13306;133.93853;-4.92234;,
 0.00000;135.56660;-4.92234;,
 12.85331;129.37677;5.65266;,
 12.85331;129.37677;-4.92234;,
 16.02782;122.78485;5.65266;,
 16.02782;122.78485;-4.92234;,
 16.02782;66.38283;5.65266;,
 16.02782;66.38283;-4.92234;,
 12.85331;59.79090;5.65265;,
 12.85331;59.79090;-4.92236;,
 7.13304;55.22915;5.65265;,
 7.13304;55.22915;-4.92236;,
 0.00000;53.60108;5.65265;,
 0.00000;53.60108;-4.92236;,
 -7.13306;55.22915;5.65265;,
 -7.13306;55.22915;-4.92236;,
 -12.85331;59.79090;5.65265;,
 -12.85331;59.79090;-4.92236;,
 -16.02782;66.38283;5.65266;,
 -16.02782;66.38283;-4.92234;,
 -16.02782;122.78486;5.65266;,
 -16.02782;122.78486;-4.92234;,
 -12.85331;129.37679;5.65266;,
 -12.85331;129.37679;-4.92234;,
 -7.13304;133.93854;5.65266;,
 -7.13304;133.93854;-4.92234;,
 0.00000;135.56660;5.65266;,
 0.00000;135.56660;-4.92234;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;5.65266;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 0.00000;70.04108;-4.92234;,
 -13.98000;121.45598;-5.69250;,
 13.98000;121.45598;-5.69250;,
 13.98000;78.72098;-5.69250;,
 -13.98000;78.72098;-5.69250;,
 13.98000;121.45598;5.69250;,
 -13.98000;121.45598;5.69250;,
 -13.98000;78.72098;5.69250;,
 13.98000;78.72098;5.69250;;
 
 74;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 3;38,21,20;,
 3;39,24,21;,
 3;40,26,24;,
 3;41,28,26;,
 3;42,30,28;,
 3;43,32,30;,
 3;44,34,32;,
 3;45,36,34;,
 3;46,23,22;,
 3;47,22,25;,
 3;48,25,27;,
 3;49,27,29;,
 3;50,29,31;,
 3;51,31,33;,
 3;52,33,35;,
 3;53,35,37;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 3;84,55,54;,
 3;85,58,55;,
 3;86,60,58;,
 3;87,62,60;,
 3;88,64,62;,
 3;89,66,64;,
 3;90,68,66;,
 3;91,70,68;,
 3;92,72,70;,
 3;93,74,72;,
 3;94,76,74;,
 3;95,78,76;,
 3;96,80,78;,
 3;97,82,80;,
 3;98,57,56;,
 3;99,56,59;,
 3;100,59,61;,
 3;101,61,63;,
 3;102,63,65;,
 3;103,65,67;,
 3;104,67,69;,
 3;105,69,71;,
 3;106,71,73;,
 3;107,73,75;,
 3;108,75,77;,
 3;109,77,79;,
 3;110,79,81;,
 3;111,81,83;,
 4;112,113,114,115;,
 4;116,117,118,119;;
 
 MeshMaterialList {
  3;
  74;
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2;;
  Material {
   0.426400;0.426400;0.426400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.633600;0.232000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  48;
  0.000000;0.156150;-0.987733;,
  0.987733;0.156150;0.000000;,
  0.000000;0.156150;0.987733;,
  -0.987733;0.156150;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-0.000001;1.000000;,
  0.000000;1.000000;0.000000;,
  0.433884;0.900969;0.000000;,
  0.781832;0.623489;0.000000;,
  0.974928;0.222521;0.000000;,
  0.974928;-0.222521;-0.000000;,
  0.781831;-0.623490;-0.000000;,
  0.433883;-0.900969;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.433884;-0.900969;0.000000;,
  -0.781832;-0.623490;0.000000;,
  -0.974928;-0.222521;0.000000;,
  -0.974928;0.222521;0.000000;,
  -0.781831;0.623490;0.000000;,
  -0.433883;0.900970;0.000000;,
  0.000000;0.000001;-1.000000;,
  -0.000000;-0.000001;1.000000;,
  0.000000;-0.000001;1.000000;,
  0.000000;-0.000001;1.000000;,
  0.000000;-0.000001;1.000000;,
  -0.000000;-0.000001;1.000000;,
  -0.000000;-0.000001;1.000000;,
  0.000000;-0.000001;1.000000;,
  0.000000;0.000001;-1.000000;,
  -0.000000;0.000001;-1.000000;,
  -0.000000;0.000001;-1.000000;,
  -0.000000;0.000001;-1.000000;,
  0.000000;0.000001;-1.000000;,
  0.000000;0.000001;-1.000000;,
  -0.000000;0.000001;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;;
  74;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,7,7,14;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,17,17,30;,
  3;16,11,11;,
  3;16,11,11;,
  3;16,11,11;,
  3;16,32,11;,
  3;16,33,32;,
  3;16,34,33;,
  3;16,35,34;,
  3;16,36,35;,
  3;16,37,36;,
  3;16,38,37;,
  3;16,11,38;,
  3;16,11,11;,
  3;16,11,11;,
  3;16,11,11;,
  3;31,7,7;,
  3;31,7,7;,
  3;31,7,7;,
  3;31,7,39;,
  3;31,39,40;,
  3;31,40,41;,
  3;31,41,42;,
  3;31,42,43;,
  3;31,43,44;,
  3;31,44,45;,
  3;31,45,7;,
  3;31,7,7;,
  3;31,7,7;,
  3;31,7,7;,
  4;46,46,46,46;,
  4;47,47,47,47;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.071430;0.000000;,
  0.071430;1.000000;,
  0.000000;1.000000;,
  0.142860;0.000000;,
  0.142860;1.000000;,
  0.214290;0.000000;,
  0.214290;1.000000;,
  0.285710;0.000000;,
  0.285710;1.000000;,
  0.357140;0.000000;,
  0.357140;1.000000;,
  0.428570;0.000000;,
  0.428570;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.571430;0.000000;,
  0.571430;1.000000;,
  0.642860;0.000000;,
  0.642860;1.000000;,
  0.714290;0.000000;,
  0.714290;1.000000;,
  0.785710;0.000000;,
  0.785710;1.000000;,
  0.857140;0.000000;,
  0.857140;1.000000;,
  0.928570;0.000000;,
  0.928570;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.035710;0.000000;,
  0.107140;0.000000;,
  0.178570;0.000000;,
  0.250000;0.000000;,
  0.321430;0.000000;,
  0.392860;0.000000;,
  0.464290;0.000000;,
  0.535710;0.000000;,
  0.607140;0.000000;,
  0.678570;0.000000;,
  0.750000;0.000000;,
  0.821430;0.000000;,
  0.892860;0.000000;,
  0.964290;0.000000;,
  0.035710;1.000000;,
  0.107140;1.000000;,
  0.178570;1.000000;,
  0.250000;1.000000;,
  0.321430;1.000000;,
  0.392860;1.000000;,
  0.464290;1.000000;,
  0.535710;1.000000;,
  0.607140;1.000000;,
  0.678570;1.000000;,
  0.750000;1.000000;,
  0.821430;1.000000;,
  0.892860;1.000000;,
  0.964290;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}

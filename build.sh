rm -r ./build
mkdir build
cd build
g++ -c ../*.cpp -DDX_GCC_COMPILE -I"../dxlib"


g++ *.o -o game.exe \
../dxlib/libDxLib.a \
../dxlib/libDxUseCLib.a \
../dxlib/libDxDrawFunc.a \
../dxlib/libjpeg.a \
../dxlib/libpng.a \
../dxlib/libzlib.a \
../dxlib/libtiff.a \
../dxlib/libtheora_static.a \
../dxlib/libvorbis_static.a \
../dxlib/libvorbisfile_static.a \
../dxlib/libogg_static.a \
../dxlib/libbulletdynamics.a \
../dxlib/libbulletcollision.a \
../dxlib/libbulletmath.a \
../dxlib/libopusfile.a \
../dxlib/libopus.a \
../dxlib/libsilk_common.a \
../dxlib/libcelt.a

rm *.o
cd ../

echo "build sucsess!!"
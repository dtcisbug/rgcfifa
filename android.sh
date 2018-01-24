#export ANDROID_STANDALONE_TOOLCHAIN=/home/dtc/package/android-ndk-r14b/android-toolchain
#export SYSROOT=$ANDROID_STANDALONE_TOOLCHAIN/sysroot
#export CXXFLAGS="-I$SYSROOT/usr/include -lstdc++ --sysroot=$SYSROOT -march=armv7-a -mfloat-abi=softfp -mfpu=neon"
export PATH=$ANDROID_STANDALONE_TOOLCHAIN:$ANDROID_STANDALONE_TOOLCHAIN/bin:/home/dtc/package/android-ndk-r14b/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin:$PATH
#export LD_LIBRARY_PATH=$SYSROOT/usr/lib:$LD_LIBRARY_PATH
#export LDFLAGS="-L$SYSROOT/usr/lib"
#export ASAN_OPTIONS=symbolize=1 
#export ASAN_SYMBOLIZER_PATH=/home/dtc/package/android-ndk-r14b/toolchains/llvm/prebuilt/linux-x86_64/bin/llvm-symbolizer

ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk

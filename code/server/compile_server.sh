echo "configuring Server.."

rm -r build/

mkdir build
cd build
cmake ..

echo "making Server.."

make

echo "done!"

echo "configuring Client.."

rm -r build/

mkdir build
cd build
cmake ..

echo "making Client.."

make

echo "done!"

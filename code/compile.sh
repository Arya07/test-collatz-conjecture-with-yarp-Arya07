echo "configuring.."

rm -r build/

mkdir build
cd build
cmake ..

echo "making.."

make

echo "done!"

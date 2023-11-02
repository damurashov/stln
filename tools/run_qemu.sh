_HERE=${BASH_SOURCE[0]}
_HERE=`dirname $_HERE`
_HERE=`realpath $_HERE`
IMAGE_PATH=$_HERE/../build/src/common/application.bin

qemu-system-gnuarmeclipse -board NUCLEO-F411RE -image $IMAGE_PATH -gdb tcp::3333 -S -nographic -verbose


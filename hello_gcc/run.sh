# Get Julia installation paths
JULIA_DIR=`julia -e 'print(dirname(Sys.BINDIR))'`
gcc -o ./main -fPIC -I$JULIA_DIR/include/julia -L$JULIA_DIR/lib -Wl,-rpath,$JULIA_DIR/lib main.c -ljulia
./main

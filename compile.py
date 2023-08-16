import os

sys = lambda x: os.system(x)

name = input("name without extension: ")

sys("cls")
sys(f"g++ -c {name}.cpp -I src/include")
sys(f"g++ -o {name} {name}.o -L src/lib -l sfml-graphics-d  -l sfml-window-d   -l sfml-system-d  -l winmm -l glu32 -l gdi32 -Wall")
sys(f"{name}")
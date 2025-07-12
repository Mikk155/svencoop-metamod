# Compiling

```
git clone https://github.com/Mikk155/svencoop-metamod.git
cd svencoop-metamod
git submodule update --init --recursive
mkdir build
```

Full path to your sven coop folder
```
cmake -S . -B build -DDLL_OUTPUT="C:\Program Files (x86)\Steam\steamapps\common\Sven Co-op\svencoop\addons\metamod\dlls"
```

Finally compile either in ``Release`` or in ``Debug``
```
cmake --build build --config Release
```
